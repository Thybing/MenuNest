#include "menu_nest/item.h"
#include "menu_nest/common.h"

//item选择和取消选择行为的默认函数
static void * (MN_item_on_select_empty_callback)(MN_item * const self){
    MN_assert(self);
    return NULL;
}

static void * (MN_item_on_unselect_empty_callback)(MN_item * const self){
    MN_assert(self);
    return NULL;
}

MN_item * MN_item_create(const char * const name, void * const p_memory){
    MN_assert(name);
    MN_assert(p_memory);

    MN_item * new_item = (MN_item *)MN_malloc(sizeof(MN_item));
    if (new_item) {
        new_item->m_name = name;
        new_item->m_select_flag = false;
        new_item->mp_memory = p_memory;

        new_item->mp_interaction = MN_interaction_create(new_item); // 初始化交互模块,其可操作内存为当前申请出的物体对象
        new_item->mp_render = MN_render_create(new_item);// 初始化显示模块

        // 默认的选择和取消选择行为
        new_item->mp_on_select = MN_item_on_select_empty_callback;
        new_item->mp_on_unselect = MN_item_on_unselect_empty_callback;
    }
    return new_item;
}

void MN_item_destroy(MN_item * const self){
    MN_assert(self);

    MN_interaction_destroy(self->mp_interaction); // 释放交互模块
    self->mp_interaction = NULL;
    MN_free(self);
}

void * MN_item_select(MN_item * const self) {
    MN_assert(self);

    // 如果已经被选中,则不再执行
    if(self->m_select_flag) {
        return NULL;
    }
    self->m_select_flag = true;
    return self->mp_on_select(self);
}

void * MN_item_unselect(MN_item * const self) {
    MN_assert(self);

    // 如果没有被选中,则不再执行
    if(!self->m_select_flag) {
        return NULL;
    }
    self->m_select_flag = false;
    return self->mp_on_unselect(self);
}

