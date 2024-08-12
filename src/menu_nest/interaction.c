#include "menu_nest/interaction.h"
#include "stdlib.h"

MN_interaction * MN_interaction_create(void * const p_op_memory){
    MN_interaction * new_moudle = (MN_interaction *)malloc(sizeof(MN_interaction));
    if(new_moudle){
        new_moudle->m_handle_callback = NULL;
        new_moudle->mp_op_memory = p_op_memory;
    }
    return new_moudle;
}

void MN_interaction_destroy(MN_interaction * const self){
    free(self);
}

void MN_interaction_set_handle_callback(MN_interaction * const self,const handle_callback_t callback){
    self->m_handle_callback = callback;
}

void MN_interaction_handle_input(MN_interaction * const self,const input_t input){
    self->m_handle_callback(self,input);
}