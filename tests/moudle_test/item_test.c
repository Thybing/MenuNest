#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu_nest/item.h"

void handle_callback(MN_interaction * const obj,const input_t input){
    MN_item * p_MN_item = (MN_item *)(obj->mp_memory);
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

void render_callback(MN_render * obj){ 
    MN_item * p_MN_item = (MN_item *)(obj->mp_memory);
    int * p_count = (int *)(obj->mp_attribute);
    for(int i = 0;i < *p_count;i++){
        printf("%s\n",(char *)(p_MN_item->mp_memory));
    }
}

int item_test_main(void){
    char * test_memory = (char *)malloc(sizeof(char) * 32);
    MN_item * o_MN_item = MN_item_create(test_memory);
    MN_item_set_handle_callback(o_MN_item,handle_callback);

    int * test_render_attr = (int *)malloc(sizeof(int));
    *test_render_attr = 3;
    MN_render_set_rendering_callback(o_MN_item->mp_render,render_callback);
    MN_render_set_attribute(o_MN_item->mp_render,test_render_attr);

    for(input_t input = 0;input < 7;input++){
        MN_interaction_handle_input(o_MN_item->mp_interaction,input);
        *((int *)MN_render_get_attribute(o_MN_item->mp_render)) = input + 1;
        MN_render_rendering(o_MN_item->mp_render);
    }

    MN_item_destroy(o_MN_item);
    free(test_memory);
    test_memory = NULL;
    return 0;
}
