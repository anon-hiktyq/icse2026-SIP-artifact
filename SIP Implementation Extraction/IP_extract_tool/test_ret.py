import tree_sitter_c as tspython
from tree_sitter import Language, Parser
from main_class import MacroExprInfo, SubFunctionInfo
from utils import find_function_cursor, get_type_name, read_file_content
C_LANGUAGE = Language(tspython.language())
parser = Parser(C_LANGUAGE)


def extract_macro_def_code(file_code):
    """
    使用 Tree-sitter 提取宏定义中的宏名称和宏体。
    """

    # 解析代码
    tree = parser.parse(bytes(file_code, 'utf8'))
    root_node = tree.root_node

    macro_defs = []

    def traverse(node):
        if node.type == 'preproc_def':
            # 获取宏定义节点的所有子节点
            identifier = None
            body = None

            for child in node.children:
                if child.type == 'identifier':
                    identifier = child.text.decode('utf8')
                elif child.type == 'preproc_arg':
                    body = child.text.decode('utf8').strip()

            if identifier and body:
                macro_defs.append((identifier, body))

        # 递归遍历所有子节点
        for child in node.children:
            traverse(child)

    traverse(root_node)

    return macro_defs

if __name__ == "__main__":
    file_path = '../Input/SAMCode_V1.01/g4ecma.h'
    root_dir = '../Input/SAMCode_V1.01'
    file_cache = {}
    code = read_file_content(file_path, file_cache)
    macro_defs = extract_macro_def_code(code)
    for macro_def in macro_defs:
        print(macro_def)