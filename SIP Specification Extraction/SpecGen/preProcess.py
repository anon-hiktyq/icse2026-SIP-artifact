import os
import re
import shutil

def copy_files(source_dir, target_dir):
    # 确保目标文件夹存在
    if not os.path.exists(target_dir):
        os.makedirs(target_dir)
        print(f"创建目标文件夹: {target_dir}")

    # 遍历源文件夹
    for filename in os.listdir(source_dir):
        if filename.endswith(".h") or filename.endswith(".c"):
            source_path = os.path.join(source_dir, filename)
            target_path = os.path.join(target_dir, filename)

            # 复制文件
            shutil.copy2(source_path, target_path)


def append_includes(lines):
   
    includes = set()
    include_pattern = re.compile(r'IPCREATE\((\w+),')
    for line in lines:
        match = include_pattern.search(line)
        if match:
            name = match.group(1)
            includes.add(f'#include "{name}.h"\n')

    if includes:
        # 将新的 include 语句插入到文件顶部
        append_lines = list(includes) + lines
        # 确保输出目录存在
    else:
        append_lines = lines

    return append_lines


def modify_funcname(lines,file_name):

    modified_lines = []
    
    # 遍历每一行
    for line in lines:
        # 检查是否包含 void *p
        if re.search(r'void\s*\*\s*p', line):
            # 替换 void *p 为 {file_name} *pIp
            new_line = re.sub(r'void\s*\*\s*p', f'{file_name} *pIp', line)
            modified_lines.append(new_line)
        else:
            # 检查是否匹配 {file_name} *pIp = ({file_name}*)p;
            pattern = re.compile(r'\w+\s*\*\s*pIp\s*=\s*\(\w+\s*\*\)\s*p\s*;')
            if not pattern.search(line):
                # 不修改其他行
                modified_lines.append(line)

    return modified_lines


def process_c_file(input_path, output_dir):

    with open(input_path, 'r', encoding='utf-8') as file:
        lines = file.readlines()

     # 获取文件名（不带扩展名）
    file_name = os.path.splitext(os.path.basename(input_path))[0]

    lines = modify_funcname(lines,file_name)
    
    # lines = append_includes(lines)
    
    output_path = os.path.join(output_dir, os.path.basename(input_path))
    with open(output_path, 'w', encoding='utf-8') as file:
        file.writelines(lines)

    return 



def process_h_file(input_path, output_dir):

    with open(input_path, 'r', encoding='utf-8') as file:
        content = file.read()

    # 获取文件名（不带扩展名）
    file_name = os.path.splitext(os.path.basename(input_path))[0]

    # 使用正则表达式替换 Fun fun; 为 void (*fun)(file_name *);
    modified_content = re.sub(
        r'\bFun\s+(\w+)\s*;',
        rf'void (*\1)( struct __{file_name} *);',
        content
    )

    # 将修改后的内容按行分割
    lines = modified_content.splitlines()
    new_line = None
    
    # 查找第一个以 'void' 开头的行
    void_line_index = None
    for i, line in enumerate(lines):
        if line.strip().startswith('void'):
             # 查找行中的所有 'void' 关键字的位置
            matches = list(re.finditer(r'\bvoid\b', line))
            
            if len(matches) > 1:
                # 如果有超过一个 'void'，则替换第二个 'void'
                second_void_start = matches[1].start()
                second_void_end = matches[1].end()
                
                new_line = line[:second_void_start] + file_name + line[second_void_end:]
        
                void_line_index = i
                break

    # 如果没有找到 'void' 开头的行或者文件少于两行，则直接复制文件
    if void_line_index is not None and len(lines) >= 2:
        # 提取需要移动的行
        lines.pop(void_line_index)

        # 将该行插入到倒数第二行
        lines.insert(-1, new_line)

    # 确保输出目录存在
    os.makedirs(output_dir, exist_ok=True)
    output_path = os.path.join(output_dir, os.path.basename(input_path))

    # 写入修改后的内容到新的文件
    with open(output_path, 'w', encoding='utf-8') as file:
        file.write('\n'.join(lines))


def process_directory(input_dir, output_dir):

    for root, _, files in os.walk(input_dir):
        for file in files:

            if file.endswith('.c'):
                input_path = os.path.join(root, file)
                process_c_file(input_path, output_dir)

            if file.endswith('.h'):
                input_path = os.path.join(root, file)
                process_h_file(input_path, output_dir)

def main():
    # IP 程序做预处理便于 frama-c 的分析
    # original_directory = "Input"  # 输入目录路径
    input_directory = "Input"  # 输出目录路径
    output_directory = "Output"
    
    # process_directory(original_directory, input_directory)  
    copy_files(input_directory,output_directory)



if __name__ == "__main__":
    main()