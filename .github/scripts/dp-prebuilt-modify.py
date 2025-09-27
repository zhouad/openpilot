import os
import sys
import fileinput
import re  # 用于正则匹配修改soundd的enabled参数

# --- 文件路径 (仅保留需要修改的两个文件) ---
repo_root = os.environ.get('GITHUB_WORKSPACE', '.')  # 默认为当前目录
launch_env_sh = os.path.join(repo_root, "launch_env.sh")  # 新增的launch_env.sh路径
process_config = os.path.join(repo_root, "system/manager/process_config.py")  # 已存在的process_config.py路径


# --- Helper for status printing (复用原有辅助函数) ---
def print_status(filename, modified, message_if_modified, message_if_not_modified="already in desired state"):
    if modified:
        print(f"  {message_if_modified}")
    else:
        print(f"  {os.path.basename(filename)} {message_if_not_modified}.")


# --- 1. 修改 launch_env.sh：添加 export LITE=1 和 export DISABLE_DRIVER=1 ---
def modify_launch_env_sh(filename):
    print(f"Modifying {filename}...")
    if not os.path.exists(filename):
        print(f"File not found: {filename}", file=sys.stderr)
        return False
    
    # 定义要添加的两行环境变量（确保换行符正确）
    lines_to_add = [
        "export LITE=1\n",
        "export DISABLE_DRIVER=1\n"
    ]
    
    try:
        # 读取文件所有内容
        with open(filename, 'r', encoding="utf-8") as f:
            lines = f.readlines()
        
        # 幂等性检查：判断两行是否已存在
        lines_content = ''.join(lines)
        if all(line.strip() in lines_content for line in lines_to_add):
            print_status(filename, False, "")
            return True
        
        # 确定插入位置：优先在开头的export行后插入，无则在shebang后，再无则在文件开头
        insert_index = 0
        # 情况1：找到shebang（#!/bin/bash），在其后插入
        for i, line in enumerate(lines):
            if line.startswith("#!"):
                insert_index = i + 1
                break
        # 情况2：如果没找到shebang，找第一个export行，在其后插入
        if insert_index == 0:
            for i, line in enumerate(lines):
                if line.strip().startswith("export "):
                    insert_index = i + 1
                    break
        
        # 插入新行
        lines = lines[:insert_index] + lines_to_add + lines[insert_index:]
        
        # 写回文件
        with open(filename, 'w', encoding="utf-8") as f:
            f.writelines(lines)
        
        print_status(filename, True, "Added 'export LITE=1' and 'export DISABLE_DRIVER=1' successfully.")
        return True
    
    except Exception as e:
        print(f"  Error modifying {filename}: {e}", file=sys.stderr)
        return False


# --- 2. 修改 process_config.py：soundd启用改为True + beepd行注释 ---
def modify_process_config(filename):
    print(f"Modifying {filename}...")
    if not os.path.exists(filename):
        print(f"File not found: {filename}", file=sys.stderr)
        return False
    
    modified = False
    # 正则表达式：匹配enabled=任意内容（直到逗号或行尾），用于替换soundd的enabled参数
    soundd_enabled_pattern = re.compile(r'(enabled=).*?(?=,|$)')
    
    for line in fileinput.input(filename, inplace=True, encoding="utf-8"):
        stripped_line = line.strip()
        original_line = line  # 保存原始行用于判断
        
        # 处理1：soundd行 - 将enabled改为True（忽略原有值）
        if "PythonProcess(\"soundd\"" in stripped_line and not stripped_line.startswith("#"):
            # 用正则替换enabled参数（匹配"enabled=xxx"并替换为"enabled=True"）
            modified_line = soundd_enabled_pattern.sub(r'enabled=True', line)
            if modified_line != original_line:
                print(modified_line, end='')
                modified = True
                continue
        
        # 处理2：beepd行 - 未注释则添加#注释
        if "PythonProcess(\"beepd\"" in stripped_line and not stripped_line.startswith("#"):
            print(f"# {line}", end='')  # 开头加#注释
            modified = True
            continue
        
        # 未匹配的行保持不变
        print(line, end='')
    
    # 输出修改状态
    if modified:
        print_status(filename, True, "Modified soundd (enabled=True) and commented beepd successfully.")
    else:
        print_status(filename, False, "")
    return True


# --- 主入口 (仅执行两个修改任务) ---
if __name__ == "__main__":
    print("Running targeted modifications for new repository...")

    # 仅保留需要的两个修改任务
    modifications = {
        "launch_env": (modify_launch_env_sh, launch_env_sh),
        "process_config": (modify_process_config, process_config),
    }

    results = {}
    for name, (func, path) in modifications.items():
        # 检查文件是否存在（不存在则标记失败）
        if not os.path.exists(path):
            print(f"  File not found: {path}", file=sys.stderr)
            results[name] = False
            continue
        # 执行修改函数
        results[name] = func(path)

    # 输出最终结果
    if all(results.values()):
        print("\n✅ All targeted modifications applied successfully or files were already in desired state.")
        sys.exit(0)
    else:
        print("\n❌ Some modifications failed:", file=sys.stderr)
        failed = [name for name, ok in results.items() if not ok]
        print(f"  Failed tasks: {', '.join(failed)}", file=sys.stderr)
        sys.exit(1)
