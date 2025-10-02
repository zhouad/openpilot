#!/usr/bin/env bash
set -e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null && pwd)"
cd $DIR

# 配置
BUILD_DIR=/data/openpilot_build
SOURCE_DIR="$(git rev-parse --show-toplevel)"
SOURCE_BRANCH="cp-v9-1"
RELEASE_BRANCH="cp-v9-prebuilt"

echo "=========================================="
echo "构建 cp-v9-prebuilt"
echo "=========================================="
echo "源分支: $SOURCE_BRANCH"
echo "目标分支: $RELEASE_BRANCH"
echo "构建目录: $BUILD_DIR"
echo ""

# 设置 git 身份
git config user.name "Prebuilt Builder"
git config user.email "builder@local"

# 清理并设置构建目录
echo "[-] 设置构建目录 T=$SECONDS"
rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR
cd $BUILD_DIR

# 初始化 git
git init
git remote add origin $(cd $SOURCE_DIR && git remote get-url origin)

# 检出源分支
echo "[-] 检出源分支 $SOURCE_BRANCH T=$SECONDS"
cd $SOURCE_DIR
git fetch origin $SOURCE_BRANCH
git checkout $SOURCE_BRANCH
git pull origin $SOURCE_BRANCH

# 创建孤立分支
cd $BUILD_DIR
git checkout --orphan $RELEASE_BRANCH

# 复制文件 - 使用 rsync 而不是 cp
echo "[-] 复制源文件 T=$SECONDS"
cd $SOURCE_DIR

# 直接使用 rsync 复制所有文件
rsync -av \
    --exclude='.git' \
    --exclude='.github' \
    --exclude='*.pyc' \
    --exclude='__pycache__' \
    --exclude='.sconsign.dblite' \
    ./ $BUILD_DIR/

cd $BUILD_DIR

# 获取版本信息
if [ -f "common/version.h" ]; then
    VERSION=$(cat common/version.h | awk -F[\"-] '{print $2}')
else
    VERSION="custom-$(date +%Y%m%d)"
fi

echo "[-] 提交版本 $VERSION T=$SECONDS"
git add -f .
git commit -a -m "cp-v9 v$VERSION initial commit" || echo "No changes to commit"

# 构建
echo "[-] 开始构建 T=$SECONDS"
export PYTHONPATH="$BUILD_DIR"

# 编译主要组件
echo "编译主程序..."
scons -j$(nproc) --minimal

# 编译 panda 固件
echo "编译 panda 固件..."
scons -j$(nproc) panda/

echo "[-] 构建完成 T=$SECONDS"

# 清理编译中间文件
echo "[-] 清理中间文件 T=$SECONDS"
find . -name '*.a' -delete
find . -name '*.o' -delete
find . -name '*.os' -delete
find . -name '*.pyc' -delete
find . -name 'moc_*' -delete
find . -name '__pycache__' -delete
rm -rf .sconsign.dblite Jenkinsfile 2>/dev/null || true
rm -rf release/ 2>/dev/null || true

# 删除大型 ONNX 模型（如果存在）
echo "[-] 清理大型文件 T=$SECONDS"
rm -f selfdrive/modeld/models/driving_vision.onnx 2>/dev/null || true
rm -f selfdrive/modeld/models/driving_policy.onnx 2>/dev/null || true

# 删除非 ARM64 的二进制文件
find third_party/ -name '*x86*' -exec rm -rf {} + 2>/dev/null || true
find third_party/ -name '*Darwin*' -exec rm -rf {} + 2>/dev/null || true
find . -type d -name 'x86_64' -exec rm -rf {} + 2>/dev/null || true
find . -type d -name 'Darwin' -exec rm -rf {} + 2>/dev/null || true

# 删除测试文件
find . -type d -name "tests" -exec rm -rf {} + 2>/dev/null || true

# 删除其他大文件
rm -f tinygrad_repo/docs/*.pdf 2>/dev/null || true
rm -f cereal/gen/cpp/log.capnp.h 2>/dev/null || true
rm -f tinygrad_repo/extra/hip_gpu_driver/*.h 2>/dev/null || true
rm -f tinygrad_repo/extra/accel/tpu/logs/*.gz 2>/dev/null || true

# 创建 prebuilt 标记
echo "[-] 创建 prebuilt 标记 T=$SECONDS"
cat > prebuilt << MARKER
Prebuilt for Comma 3 (aarch64)
Built: $(date -u)
Source: $SOURCE_BRANCH
Commit: $(cd $SOURCE_DIR && git rev-parse HEAD | cut -c1-8)
Version: $VERSION
MARKER

# 提交所有更改
echo "[-] 提交 prebuilt 版本 T=$SECONDS"
git add -f .
git commit --amend -m "cp-v9-prebuilt v$VERSION built $(date +%Y%m%d_%H%M%S)"

# 验证关键文件
echo "[-] 验证编译产物 T=$SECONDS"
CRITICAL_FILES=(
    "selfdrive/controls/lib/longitudinal_mpc_lib/c_generated_code/libacados_ocp_solver_long.so"
    "selfdrive/controls/lib/lateral_mpc_lib/c_generated_code/libacados_ocp_solver_lat.so"
    "cereal/messaging/messaging_pyx.so"
)

MISSING=0
echo ""
for file in "${CRITICAL_FILES[@]}"; do
    if [ -f "$file" ]; then
        SIZE=$(du -h "$file" | cut -f1)
        echo "  ✓ $file ($SIZE)"
    else
        echo "  ✗ $file (缺失)"
        MISSING=$((MISSING + 1))
    fi
done
echo ""

if [ $MISSING -gt 0 ]; then
    echo "⚠️  警告：缺少 $MISSING 个关键文件"
    echo "构建可能不完整，但会继续..."
fi

# 显示构建统计
echo "[-] 构建统计 T=$SECONDS"
echo "  动态库 (.so): $(find . -name "*.so" ! -path "./.git/*" | wc -l)"
echo "  总大小: $(du -sh . | cut -f1)"

# 推送到远程（可选）
echo ""
read -p "是否推送到 GitHub？(y/n) " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
    echo "[-] 推送到 GitHub T=$SECONDS"
    git branch -M $RELEASE_BRANCH
    git push -f origin $RELEASE_BRANCH
    
    echo ""
    echo "=========================================="
    echo "✅ 构建并推送完成！T=$SECONDS"
    echo "=========================================="
else
    echo ""
    echo "=========================================="
    echo "✅ 构建完成（未推送）！T=$SECONDS"
    echo "=========================================="
    echo "手动推送:"
    echo "  cd $BUILD_DIR"
    echo "  git push -f origin $RELEASE_BRANCH"
fi

echo ""
echo "版本: $VERSION"
echo "分支: $RELEASE_BRANCH"
echo ""
echo "在其他 C3 上安装:"
echo "  cd /data"
echo "  mv openpilot openpilot.backup"
echo "  git clone -b $RELEASE_BRANCH https://github.com/$(cd $SOURCE_DIR && git remote get-url origin | sed 's/.*github.com[:/]\(.*\)\.git/\1/')"
echo "  reboot"
echo "=========================================="
