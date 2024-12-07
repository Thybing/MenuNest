#include "menu_nest/item.h"
#include "stdlib.h"

MN_item * MN_item_create(void * const p_memory){
    MN_item * new_item = (MN_item *)malloc(sizeof(MN_item));
    if (new_item) {
        new_item->mp_memory = p_memory;

        new_item->mp_interaction = MN_interaction_create(new_item); // 初始化交互模块,其可操作内存为当前申请出的物体对象
        new_item->mp_render = MN_render_create(new_item);// 初始化显示模块
    }
    return new_item;
}

void MN_item_destroy(MN_item * const self){
    MN_interaction_destroy(self->mp_interaction); // 释放交互模块
    self->mp_interaction = NULL;
    free(self);
}
