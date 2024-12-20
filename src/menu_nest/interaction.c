#include "menu_nest/interaction.h"
#include "menu_nest/common.h"

// 默认的交互处理回调函数，不做任何处理，不捕获任何输入
static bool MN_interaction_empty_callback(struct MN_interaction * const self,const input_t input){
    return false;
}

// 构造一个交互模块对象并返回
MN_interaction * MN_interaction_create(void * const p_memory){
    MN_interaction * new_moudle = (MN_interaction *)MN_malloc(sizeof(MN_interaction));
    if(new_moudle){
        new_moudle->m_handle_callback = MN_interaction_empty_callback;
        new_moudle->mp_memory = p_memory;
    }
    return new_moudle;
}

// 析构交互模块
void MN_interaction_destroy(MN_interaction * const self){
    MN_assert(self);
    MN_free(self);
}

// 设置交互回调函数，交互模块捕获输入后，调用此回调函数处理输入
void MN_interaction_set_handle_callback(MN_interaction * const self,const interaction_callback_t callback){
    MN_assert(self);
    self->m_handle_callback = callback;
}

// 处理输入
bool MN_interaction_handle_input(MN_interaction * const self,const input_t input){
    MN_assert(self);
    return self->m_handle_callback(self,input);
}