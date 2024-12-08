#include "menu_nest/item.h"
#include "menu_nest/common.h"

MN_item * MN_item_create(const char * const name, void * const p_memory){
    MN_assert(name);
    MN_assert(p_memory);

    MN_item * new_item = (MN_item *)MN_malloc(sizeof(MN_item));
    if (new_item) {
        new_item->m_name = name;
        new_item->mp_memory = p_memory;

        new_item->mp_interaction = MN_interaction_create(new_item); // 初始化交互模块,其可操作内存为当前申请出的物体对象
        new_item->mp_render = MN_render_create(new_item);// 初始化显示模块

        new_item->mp_on_select = &MN_item_action_empty_callback;
        new_item->mp_on_unselect = &MN_item_action_empty_callback;
    }
    return new_item;
}

void MN_item_destroy(MN_item * const self){
    MN_assert(self);

    MN_interaction_destroy(self->mp_interaction); // 释放交互模块
    self->mp_interaction = NULL;
    MN_free(self);
}

//item选择和取消选择的默认函数
static void * ((MN_item_action_empty_callback)(MN_item * const self,void * param)){
    MN_assert(self);
    return NULL;
}