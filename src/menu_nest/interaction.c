#include "menu_nest/interaction.h"
#include "menu_nest/common.h"

MN_interaction * MN_interaction_create(void * const p_memory){
    MN_interaction * new_moudle = (MN_interaction *)MN_malloc(sizeof(MN_interaction));
    if(new_moudle){
        new_moudle->m_handle_callback = NULL;
        new_moudle->mp_memory = p_memory;
    }
    return new_moudle;
}

void MN_interaction_destroy(MN_interaction * const self){
    MN_assert(self);
    MN_free(self);
}

void MN_interaction_set_handle_callback(MN_interaction * const self,const interaction_callback_t callback){
    MN_assert(self);
    self->m_handle_callback = callback;
}

bool MN_interaction_handle_input(MN_interaction * const self,const input_t input){
    MN_assert(self);
    return self->m_handle_callback(self,input);
}