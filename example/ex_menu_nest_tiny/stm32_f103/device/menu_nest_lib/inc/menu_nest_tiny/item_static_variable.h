#ifndef ITEM_STATIC_VARIABLE_H
#define ITEM_STATIC_VARIABLE_H

#include "menu_nest/menu.h"

typedef enum basic_type {
    TYPE_I8 = 0,
    TYPE_I16,
    TYPE_I32,
    TYPE_I64,
    TYPE_U8,
    TYPE_U16,
    TYPE_U32,
    TYPE_U64,
    TYPE_F32,
    TYPE_F64,
    TYPE_BOOL,
    TYPE_CSTR
} basic_type;

// 创建一个静态变量item，传入的参数是静态变量(广义的静态变量，核心是生命周期一定要比菜单本身长。一般用全局变量比较多。)的地址及其类型。
MN_item* create_item_static_variable(const char* const item_name, void* p_var, enum basic_type var_type);

// 通过页面标题和item名字获取item的静态变量指针
void* get_item_static_variable_ptr(const char* const page_title, const char* const item_name);

// 扩展功能：通过有格式的指令字符串直接对值进行修改(可以用来实现远程串口调参/控制等功能)

// 格式为：
// MN:<page title>:<item name>:<value>;
// 不可省略冒号和结尾的分号(尖括号删去)
// 例如：页面标题为"Main"，item名字为"item"，将值修改为为"123"，则指令为"MN:Main:item:123;"
// 请不要在title和name中出现冒号或分号

// 返回值为错误码，0为成功，其他为失败
typedef enum static_var_command_ctrl_errno {
    static_var_command_no_err = 0,      // 通过
    static_var_command_fmt_err,         // 格式错误
    static_var_command_page_not_found,  // 页面未找到
    static_var_command_item_not_found,  // item未找到
    static_var_command_unknown_type,    // 未知/不支持类型
    static_var_command_var_fmt_err,     // 变量格式错误
} static_var_command_ctrl_errno;

// 通过指令字符串对静态变量进行修改
// 注意，这里为了节省资源，不会对指令字符串进行拷贝。会将原指令字符串进行修改。
static_var_command_ctrl_errno item_static_var_command_ctrl(char* command, const uint32_t len);

#endif
