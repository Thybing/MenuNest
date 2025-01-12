#include "menu_nest_tiny/item_page_entrance.h"
#include "menu_nest/common.h"
#include "menu_nest_tiny/display.h"

typedef struct {
    const char * m_show_str;
    MN_page * mp_target_page;
}item_page_entrance_t;

// 选中物体的回调函数
void * item_page_entrance_on_select_callback(struct MN_item * const p_page_entrance){
    MN_page * p_target_page = ((item_page_entrance_t*)(p_page_entrance->mp_memory))->mp_target_page;
    MN_page_unselect_item(MN_get_cur_page());
    //页面入口类似于一个按键，按下选中之后不会进入选中操作，会进行跳转，当前页面选中后触发自动取消选中
    MN_menu_page_forward(p_target_page);
    return NULL;
}

// 渲染的回调函数，适配于page_base页面
void item_page_entrance_rendering_callback(MN_render * const p_item_render, void * p_y_offset){
    MN_item * const p_item = p_item_render->mp_memory;
    uint16_t * const p_used_line = p_y_offset;

    item_page_entrance_t * p_page_entrance = p_item->mp_memory;

    display_line_text(*p_used_line,p_page_entrance->m_show_str);
}

// 创建一个页面入口，此item的渲染函数适配于page_base类型的页面，内部的渲染回调函数适配page_base页面
MN_item * create_item_page_entrance(const char * const item_name, MN_page * p_target_page){
    //创建item内部的数据结构
    item_page_entrance_t * p_new_page_entrance = MN_malloc(sizeof(item_page_entrance_t));
    p_new_page_entrance->m_show_str = item_name;
    p_new_page_entrance->mp_target_page = p_target_page;

    //创建item
    MN_item * p_page_entrance = MN_item_create(item_name, p_new_page_entrance);
    p_page_entrance->mp_on_select = item_page_entrance_on_select_callback;
    MN_render_set_rendering_callback(p_page_entrance->mp_render,item_page_entrance_rendering_callback);
    return p_page_entrance;
}