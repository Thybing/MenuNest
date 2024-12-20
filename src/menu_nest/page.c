#include "menu_nest/page.h"
#include "menu_nest/common.h"
#include "string.h"


static MN_page * (page_pool[MN_PAGE_MAX_NUM]) = {0};
static uint32_t page_pool_used = 0;

//page进入和离开的默认函数
static void * ((MN_page_action_empty_callback)(MN_page * const self,void * param)){
    MN_assert(self);
    return NULL;
}

MN_page * MN_page_create(const char * const title, const uint32_t item_max){
    MN_assert(title);

    MN_page * find_page = MN_find_page(title);
    if(find_page) {
        return find_page;
    }

    MN_page * new_page = (MN_page *)MN_malloc(sizeof(MN_page));
    if(new_page){
        page_pool[page_pool_used++] = new_page;

        new_page->m_title = title;
        new_page->mpp_items = (MN_item **)MN_malloc(sizeof(MN_item *) * item_max);
        new_page->m_cur_item_index = -1;
        new_page->m_item_num = 0;
        new_page->m_item_max_num = item_max;
        new_page->mp_interaction = MN_interaction_create(new_page);
        new_page->mp_render = MN_render_create(new_page);
        new_page->mp_on_forward = MN_page_action_empty_callback;
        new_page->mp_on_retreat = MN_page_action_empty_callback;
        new_page->mp_on_retreat_from_other_page = MN_page_action_empty_callback;
        new_page->mp_on_select_item = MN_page_action_empty_callback;
        new_page->mp_on_unselect_item = MN_page_action_empty_callback;
        new_page->mp_memory = NULL;
    }
    return new_page;
}

void MN_page_destroy(MN_page * const self){
    MN_assert(self);

    MN_interaction_destroy(self->mp_interaction);
    MN_render_destroy(self->mp_render);
    MN_free(self->mpp_items);
    MN_free(self);
}

void MN_page_add_item(MN_page * const self, MN_item * const p_item){
    MN_assert(self);
    MN_assert(p_item);

    for(int i = 0;i < self->m_item_num;i++) {
        if(strcmp((self->mpp_items)[i]->m_name,p_item->m_name) == 0) {
            return;
        }
    }
    if(self->m_item_num < self->m_item_max_num){
        (self->mpp_items)[(self->m_item_num)++] = p_item;
    }
}

MN_item * MN_page_find_item(MN_page * const self, const char * const item_name){
    MN_assert(self);
    MN_assert(item_name);

    for(int i = 0;i < self->m_item_num;i++) {
        if(strcmp((self->mpp_items)[i]->m_name,item_name) == 0) {
            return (self->mpp_items)[i];
        }
    }
    return NULL;
}

void * MN_page_select_item(MN_page * const self,const int32_t index){
    MN_assert(self);

    //输入的index不在有效范围内
    if(!(index >= 0 && index < self->m_item_num)){
        return NULL;
    }
    //当前选中的物体和输入的index相同
    if(self->m_cur_item_index == index){
        return NULL;
    }

    //如果有选中物体，取消当前选中的物体
    if(self->m_cur_item_index != -1) {
        MN_page_unselect_item(self);
    }

    self->m_cur_item_index = index;
    MN_item * p_target_item = (self->mpp_items)[index];
    void * p_item_select_ret = MN_item_select(p_target_item);
    return self->mp_on_select_item(self,p_item_select_ret);
}

void * MN_page_select_item_by_name(MN_page * const self, const char * item_name){
    for(int i = 0;i < self->m_item_num;i++) {
        if(strcmp((self->mpp_items)[i]->m_name,item_name) == 0) {
            return MN_page_select_item(self,i);
        }
    }
    return NULL;
}

void * MN_page_unselect_item(MN_page * const self){
    MN_assert(self);

    if(self->m_cur_item_index != -1) {
        MN_item * p_cur_item = (self->mpp_items)[self->m_cur_item_index];
        void * p_item_unselect_ret = MN_item_unselect(p_cur_item);

        void * p_page_unselect_item_ret = self->mp_on_unselect_item(self,p_item_unselect_ret);
        self->m_cur_item_index = -1;
        return p_page_unselect_item_ret;
    }
    return NULL;
}

MN_page * MN_find_page(const char * const title){
    MN_assert(title);

    for(int i = 0;i < page_pool_used;i++){
        if(strcmp(page_pool[i]->m_title,title) == 0){
            return page_pool[i];
        }
    }
    return NULL;
}
