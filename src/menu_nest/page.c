#include "menu_nest/page.h"
#include "stdlib.h"

MN_page * MN_page_create(const uint32_t item_max){
    MN_page * new_page = (MN_page *)malloc(sizeof(MN_page));
    if(new_page){
        new_page->mpp_items = (MN_item **)malloc(sizeof(MN_item *) * item_max);
        new_page->m_current_index = -1;
        new_page->m_item_count = 0;
        new_page->m_item_max = item_max;
        new_page->mp_interaction = MN_interaction_create(new_page);
        new_page->mp_render = MN_render_create(new_page);
    }
    return new_page;
}

void MN_page_destroy(MN_page * const self){
    MN_interaction_destroy(self->mp_interaction);
    MN_render_destroy(self->mp_render);
    free(self->mpp_items);
    free(self);
}

void MN_page_add_item(MN_page * const self, MN_item * const item){
    if(self->m_item_count < self->m_item_max){
        (self->mpp_items)[(self->m_item_count)++] = item;
    }
}

MN_item * MN_page_select_item(MN_page * const self,const int32_t index){
    if(index >= 0 && index < self->m_item_count){
        self->m_current_index = index;
        return (self->mpp_items)[index];
    }else{
        self->m_current_index = -1;
        return NULL;
    }
}