#!/usr/bin/env bash

export OMP_NUM_THREADS=1
export MKL_NUM_THREADS=1
export NUMEXPR_NUM_THREADS=1
export OPENBLAS_NUM_THREADS=1
export VECLIB_MAXIMUM_THREADS=1
if [ -s /data/params/d/dp_device_model_selected ]; then
  export FINGERPRINT="$(cat /data/params/d/dp_device_model_selected)"
fi

if [ -z "$AGNOS_VERSION" ]; then
  export AGNOS_VERSION="11.13"
fi

export STAGING_ROOT="/data/safe_staging"

# 设置DISABLE_DRIVER=1环境变量有两个作用：
# 1. 禁用驾驶员监控功能，系统将以"Lite"模式运行
# 2. 避免nvme固态硬盘未装载的警告，因为系统会跳过相关检查
# 这对于没有安装nvme固态硬盘的设备特别有用
export DISABLE_DRIVER=1
