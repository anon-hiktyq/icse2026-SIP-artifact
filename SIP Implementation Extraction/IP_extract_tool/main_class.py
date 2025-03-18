class CalleeInfo:
    def __init__(self, name=None, file_path=None, content_range=None, expr_cursor=None, def_cursor=None, var_mapping=None, sub_function_info_list=None):
        self.name: str = name
        self.file_path = file_path
        self.content_range: list = content_range
        self.expr_cursor = expr_cursor
        self.def_cursor = def_cursor
        self.var_mapping: dict = var_mapping if var_mapping else {}
        self.sub_function_info_list: list = sub_function_info_list if sub_function_info_list else []


class SubFunctionInfo: #记录作为函数实参的子函数 
    def __init__(self, name=None, body=None, content_range=None, var_mapping=None, sub_function_info_list=None):
        self.name: str = name
        self.body: str = body
        self.content_range: list = content_range
        self.var_mapping: dict = var_mapping if var_mapping else {}
        self.sub_function_info_list: list = sub_function_info_list if sub_function_info_list else []

class FunMacroExprInfo: #记录函数中出现的带参宏的信息
    def __init__(self, name=None, body=None, content_range=None, sub_function_info_list=None):
        self.name: str = name
        self.body: str = body
        self.content_range: list = content_range
        self.sub_function_info_list: list = sub_function_info_list if sub_function_info_list else []

class FunctionInfo:
    def __init__(self, path, code, fun_item_dict, macro_expr_info_list, callee_info_list, fun_var_dict,
                 IP_var_dict, function_cursor, func_type, ret_range_list, callee_item_set = None):
        self.path:str = path
        self.code:str = code
        self.fun_item_dict:dict = fun_item_dict
        self.macro_expr_info_list:list = macro_expr_info_list
        self.callee_info_list:list = callee_info_list
        self.fun_var_dict:dict = fun_var_dict
        self.IP_var_dict:dict = IP_var_dict
        self.function_cursor = function_cursor
        self.func_type = func_type
        self.ret_range_list:list = ret_range_list
        self.callee_item_set:set = callee_item_set if callee_item_set else set()


class MacroInfo:  #使用@进行唯一标识符标记
    def __init__(self, file_path=None, def_code=None, macro_cursor=None, include_type_set=None, 
                 include_macro_set=None, include_global_set=None, macro_expr_info_list=None):
        self.file_path = file_path
        self.def_code: list = def_code
        self.macro_cursor = macro_cursor
        self.include_type_set: set = include_type_set if include_type_set else set()
        self.include_macro_set: set = include_macro_set if include_macro_set else set()
        self.include_global_set: set = include_global_set if include_global_set else set()
        self.macro_expr_info_list: list = macro_expr_info_list if macro_expr_info_list is not None else [] #记录宏中函数(一级函数)信息


class MacroExprInfo:
    def __init__(self, name=None, body=None, origin_content_range=None, var_mapping=None, sub_function_info_list=None):
        self.name: str = name
        self.body: str = body
        self.origin_content_range: list = origin_content_range
        self.var_mapping: dict = var_mapping if var_mapping else {}
        self.sub_function_info_list: list = sub_function_info_list if sub_function_info_list else []

class TypeInfo: #使用@进行唯一标识符标记
    def __init__(self, file_path=None, content_range=None, def_code = None, type_cursor=None, include_type_set=None):
        self.file_path = file_path
        self.content_range: list = content_range
        self.def_code = def_code
        self.type_cursor = type_cursor
        self.include_type_set: set = include_type_set if include_type_set is not None else set()



