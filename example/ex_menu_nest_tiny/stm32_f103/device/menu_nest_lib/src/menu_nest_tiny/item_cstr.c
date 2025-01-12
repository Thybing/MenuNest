#include "menu_nest_tiny/item_cstr.h"
#include "menu_nest_tiny/display.h"

// 字符串的渲染回调函数
void item_str_rendering_callback(MN_render * const p_item_render, void * p_y_offset){
    MN_item * const p_item = p_item_render->mp_memory;
    uint16_t * const p_used_line = p_y_offset;

    const char * str = p_item->mp_memory;

    display_line_text(*p_used_line,str);
}

MN_item * create_cstr_item(const char * const item_name,char * cstr){
    MN_item * p_item_cstr = MN_item_create(item_name,cstr);
    MN_render_set_rendering_callback(p_item_cstr->mp_render,item_str_rendering_callback);
    return p_item_cstr;
}