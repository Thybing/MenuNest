#include "menu_nest_tiny/item_auto_variable.h"
#include "menu_nest_tiny/item_static_variable.h"
#include "menu_nest/common.h"
#include "menu_nest_tiny/display.h"

// 本质上是静态变量的封装，用于调试，无需将变量声明成全局的变量，查看自动变量的值。必要时可以修改自动变量的值。类似一个探针。
MN_item * create_item_auto_variable(const char * const item_name, void * p_auto_var, enum basic_type var_type) {
    void * p_static_var = NULL;

    switch (var_type) {
        case TYPE_I8:
            p_static_var = MN_malloc(sizeof(int8_t));
            *(int8_t*)p_static_var = *(int8_t*)p_auto_var;
            break;
        case TYPE_I16:
            p_static_var = MN_malloc(sizeof(int16_t));
            *(int16_t*)p_static_var = *(int16_t*)p_auto_var;
            break;
        case TYPE_I32:
            p_static_var = MN_malloc(sizeof(int32_t));
            *(int32_t*)p_static_var = *(int32_t*)p_auto_var;
            break;
        case TYPE_I64:
            p_static_var = MN_malloc(sizeof(int64_t));
            *(int64_t*)p_static_var = *(int64_t*)p_auto_var;
            break;
        case TYPE_U8:
            p_static_var = MN_malloc(sizeof(uint8_t));
            *(uint8_t*)p_static_var = *(uint8_t*)p_auto_var;
            break;
        case TYPE_U16:
            p_static_var = MN_malloc(sizeof(uint16_t));
            *(uint16_t*)p_static_var = *(uint16_t*)p_auto_var;
            break;
        case TYPE_U32:
            p_static_var = MN_malloc(sizeof(uint32_t));
            *(uint32_t*)p_static_var = *(uint32_t*)p_auto_var;
            break;
        case TYPE_U64:
            p_static_var = MN_malloc(sizeof(uint64_t));
            *(uint64_t*)p_static_var = *(uint64_t*)p_auto_var;
            break;
        case TYPE_F32:
            p_static_var = MN_malloc(sizeof(float));
            *(float*)p_static_var = *(float*)p_auto_var;
            break;
        case TYPE_F64:
            p_static_var = MN_malloc(sizeof(double));
            *(double*)p_static_var = *(double*)p_auto_var;
            break;
        case TYPE_BOOL:
            p_static_var = MN_malloc(sizeof(bool));
            *(bool*)p_static_var = *(bool*)p_auto_var;
            break;
        case TYPE_CSTR:
            break;
        default:
            MN_assert(0);
            break;
    }

    MN_item * p_item = create_item_static_variable(item_name, p_static_var, var_type);
    return p_item;
}

// 通过页面标题和item名字获取item的自动变量的拷贝的指针，获取的是菜单中的拷贝值如果需要使用则要将返回值拷贝回原变量。
const void * get_item_auto_variable_ptr(const char * const page_title, const char * const item_name) {
    return get_item_static_variable_ptr(page_title, item_name);
}

// 更新自动变量的值到菜单中，传入的参数是页面标题，item名字，自动变量的地址及其类型。
void refresh_item_auto_variable(const char * const page_title, const char * const item_name, const void * const p_var , enum basic_type var_type) {
    void * p_static_var = get_item_static_variable_ptr(page_title, item_name);
    if(p_static_var == NULL) {
        return;
    }

    if(var_type == TYPE_I8) {
        *(int8_t*)p_static_var = *(int8_t*)p_var;
    } else if(var_type == TYPE_I16) {
        *(int16_t*)p_static_var = *(int16_t*)p_var;
    } else if(var_type == TYPE_I32) {
        *(int32_t*)p_static_var = *(int32_t*)p_var;
    } else if(var_type == TYPE_I64) {
        *(int64_t*)p_static_var = *(int64_t*)p_var;
    } else if(var_type == TYPE_U8) {
        *(uint8_t*)p_static_var = *(uint8_t*)p_var;
    } else if(var_type == TYPE_U16) {
        *(uint16_t*)p_static_var = *(uint16_t*)p_var;
    } else if(var_type == TYPE_U32) {
        *(uint32_t*)p_static_var = *(uint32_t*)p_var;
    } else if(var_type == TYPE_U64) {
        *(uint64_t*)p_static_var = *(uint64_t*)p_var;
    } else if(var_type == TYPE_F32) {
        *(float*)p_static_var = *(float*)p_var;
    } else if(var_type == TYPE_F64) {
        *(double*)p_static_var = *(double*)p_var;
    } else if(var_type == TYPE_BOOL) {
        *(bool*)p_static_var = *(bool*)p_var;
    } else if(var_type == TYPE_CSTR) {
        ;
    } else {
        MN_assert(0);
    }
}