#include "menu_nest/interaction.h"
#include "stdlib.h"

MN_interaction * MN_create_interaction(void * const p_op_buffer){
    MN_interaction * new_moudle = (MN_interaction *)malloc(sizeof(MN_interaction));
    if(new_moudle){
        new_moudle->m_handle_callback = NULL;
        new_moudle->mp_op_buffer = p_op_buffer;
    }
    return new_moudle;
}

void MN_destroy_interaction(MN_interaction * const self){
    free(self);
}

void MN_set_handle_callback(MN_interaction * const self,void (* const handle_callback)(struct MN_interaction * const ,const input_t)){
    self->m_handle_callback = handle_callback;
}

void MN_handle_input(MN_interaction * const self,const input_t input){
    self->m_handle_callback(self,input);
}