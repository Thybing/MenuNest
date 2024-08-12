#include <stdio.h>
#include "menu_nest/interaction.h"

void handle_callback(MN_interaction * const o_MN_interaction,const input_t input){
    char * p_op_memory = (char *)(o_MN_interaction->mp_op_memory);
    printf("%u\n",input);
    p_op_memory[input] = input + '0';
}

int interaction_test_main(void){
    char memory[128] = {0};
    MN_interaction * o_MN_interaction = MN_interaction_create(memory);
    MN_interaction_set_handle_callback(o_MN_interaction,&handle_callback);
    for(input_t input = 0;input < 10;input++){
        MN_interaction_handle_input(o_MN_interaction,input);
    }
    MN_interaction_destroy(o_MN_interaction);
    printf("%s\n",memory);
    printf("end of exe\n");
    return 0;
}