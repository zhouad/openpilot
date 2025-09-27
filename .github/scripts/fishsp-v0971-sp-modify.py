import os
import sys

# --- 文件路径 (仅修改system/manager/manager.py) ---
repo_root = os.environ.get('GITHUB_WORKSPACE', '.')  # 默认为当前目录
manager_py = os.path.join(repo_root, "system/manager/manager.py")  # 目标文件路径


# --- 辅助函数：打印修改状态 ---
def print_status(filename, modified, message_if_modified, message_if_not_modified="already in desired state"):
    if modified:
        print(f"  {message_if_modified}")
    else:
        print(f"  {os.path.basename(filename)} {message_if_not_modified}.")


# --- 修改manager.py：在default_params中添加("DriverCameraHardwareMissing", "1") ---
def modify_manager_py(filename):
    print(f"Modifying {filename}...")
    if not os.path.exists(filename):
        print(f"File not found: {filename}", file=sys.stderr)
        return False
    
    # 修正元组格式，确保包含完整的括号和结尾逗号
    target_tuple = ('"DriverCameraHardwareMissing"', '"1"')  # 目标元组的字符串部分
    # 正确的目标行格式：带缩进、完整括号和结尾逗号
    target_line = f"    ({target_tuple[0]}, {target_tuple[1]}),"
    
    try:
        # 读取文件内容
        with open(filename, 'r', encoding="utf-8") as f:
            lines = f.readlines()
        
        # 幂等性检查：判断目标行是否已存在
        exists = any(target_line.strip() in line.strip() for line in lines)
        if exists:
            print_status(filename, False, "")
            return True
        
        # 查找default_params列表并插入目标行
        new_lines = []
        modified = False
        in_default_params = False  # 是否在目标列表中
        indentation = ""  # 记录列表内的缩进格式
        
        for line in lines:
            # 检测default_params列表的开始
            if "default_params: list[tuple[str, str | bytes]] = [" in line:
                new_lines.append(line)
                in_default_params = True
                continue
            
            # 当在default_params列表中时
            if in_default_params:
                # 记录缩进格式（取第一个元组的缩进）
                if not indentation and line.strip().startswith("(") and "," in line:
                    indentation = line[:len(line) - len(line.lstrip())]
                
                # 检测列表结束（遇到"]"时）
                if line.strip().startswith("]"):
                    # 插入正确格式的目标行（带括号和逗号）
                    if indentation:
                        # 使用正确的元组格式：(key, value),
                        new_lines.append(f"{indentation}({target_tuple[0]}, {target_tuple[1]}),\n")
                    else:
                        # 默认缩进格式
                        new_lines.append(f"    ({target_tuple[0]}, {target_tuple[1]}),\n")
                    modified = True
                    in_default_params = False  # 退出列表标记
            
            new_lines.append(line)
        
        # 写回修改后的内容
        if modified:
            with open(filename, 'w', encoding="utf-8") as f:
                f.writelines(new_lines)
            print_status(filename, True, "Added ('DriverCameraHardwareMissing', '1') to default_params successfully.")
        else:
            print(f"  Could not find default_params list in {filename}", file=sys.stderr)
            return False
        
        return True
    
    except Exception as e:
        print(f"  Error modifying {filename}: {e}", file=sys.stderr)
        return False


# --- 主入口 ---
if __name__ == "__main__":
    print("Running modification for system/manager/manager.py...")

    modifications = {
        "manager_py": (modify_manager_py, manager_py),
    }

    results = {}
    for name, (func, path) in modifications.items():
        if not os.path.exists(path):
            print(f"  File not found: {path}", file=sys.stderr)
            results[name] = False
            continue
        results[name] = func(path)

    if all(results.values()):
        print("\n✅ Modification applied successfully or file was already in desired state.")
        sys.exit(0)
    else:
        print("\n❌ Modification failed.", file=sys.stderr)
        failed = [name for name, ok in results.items() if not ok]
        print(f"  Failed tasks: {', '.join(failed)}", file=sys.stderr)
        sys.exit(1)
