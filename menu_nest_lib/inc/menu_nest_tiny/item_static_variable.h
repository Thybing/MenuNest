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

#endif
