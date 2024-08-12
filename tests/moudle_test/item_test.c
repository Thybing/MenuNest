#include <stdio.h>
#include <string.h>
#include "menu_nest/item.h"

void handle_callback(MN_interaction * const obj,const input_t input){
    MN_item * p_MN_item = (MN_item *)(obj->mp_op_memory);
    char * test_memory = (char *)(p_MN_item->mp_memory);
    if(input == 0){
        strcpy(test_memory,"zero");
    }else if(input == 1){
        strcpy(test_memory,"one");
    }else if(input == 2){
        strcpy(test_memory,"two");
    }else if(input == 3){
        strcpy(test_memory,"three");
    }else if(input == 4){
        strcpy(test_memory,"four");
    }else if(input == 5){
        strcpy(test_memory,"five");
    }else{
        strcpy(test_memory,"other num");
    }
}

void display_callback(MN_item * const obj){
    printf("%s\n",(char *)(obj->mp_memory));
}

int item_test_main(void){
    char * test_memory[128] = {0};
    MN_item * o_MN_item = MN_item_create(test_memory);
    MN_item_set_handle_callback(o_MN_item,handle_callback);
    MN_item_set_display_callback(o_MN_item,display_callback);

    for(input_t input = 0;input < 7;input++){
        MN_interaction_handle_input(o_MN_item->mp_interaction,input);
        MN_item_refresh_display(o_MN_item);
    }

    MN_item_destroy(o_MN_item);
    return 0;
}
