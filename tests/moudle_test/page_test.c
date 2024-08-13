#include "menu_nest/page.h"
#include "stdlib.h"
#include "string.h"
#include "windows.h"
#include "unistd.h"

void page_handle_callback(MN_interaction * inter, input_t input){
    MN_page * p_page = (MN_page *)(inter->mp_op_memory);
    MN_page_select_item(p_page,input);
}

void page_rendering_callback(MN_render * render){
    MN_page * p_page = (MN_page *)(render->mp_memory);
    for(int i = 0;i < p_page->m_item_count;i++){
        MN_render_rendering((p_page->mpp_items)[i]->mp_render);
    }
    printf("-------Current item--------\n");
    if(p_page->m_current_index != -1){
        MN_render_rendering((p_page->mpp_items)[p_page->m_current_index]->mp_render);
    }else{
        printf("None\n");
    }
}

void str_item_rendering_callback(MN_render * render){
    MN_item * p_item = (MN_item *)(render->mp_memory);
    printf("%s\n",(char *)(p_item->mp_memory));
}

void int_item_rendering_callback(MN_render * render){
    MN_item * p_item = (MN_item *)(render->mp_memory);
    printf("%d\n",*(int *)(p_item->mp_memory));
}

int page_test_main(){
    MN_page * obj = MN_page_create(4);
    MN_page_set_handle_callback(obj,page_handle_callback);
    MN_render_set_rendering_callback(obj->mp_render,page_rendering_callback);
    MN_render_set_attribute(obj->mp_render,NULL);

    char * item_1_str = (char *)malloc(sizeof(char) * 16);
    strcpy(item_1_str,"item 1 str.");
    MN_item * p_item_1 = MN_item_create(item_1_str);
    MN_render_set_rendering_callback(p_item_1->mp_render,str_item_rendering_callback);

    char * item_2_str = (char *)malloc(sizeof(char) * 16);
    strcpy(item_2_str,"item 2 str.");
    MN_item * p_item_2 = MN_item_create(item_2_str);
    MN_render_set_rendering_callback(p_item_2->mp_render,str_item_rendering_callback);

    int * p_item_3_int = (int *)malloc(sizeof(int));
    *p_item_3_int = 9;
    MN_item * p_item_3 = MN_item_create(p_item_3_int);
    MN_render_set_rendering_callback(p_item_3->mp_render,int_item_rendering_callback);

    int * p_item_4_int = (int *)malloc(sizeof(int));
    *p_item_4_int = 666;
    MN_item * p_item_4 = MN_item_create(p_item_4_int);
    MN_render_set_rendering_callback(p_item_4->mp_render,int_item_rendering_callback);

    MN_page_add_item(obj,p_item_1);
    MN_page_add_item(obj,p_item_2);
    MN_page_add_item(obj,p_item_3);
    MN_page_add_item(obj,p_item_4);

    {
        int count;
        while(1){
            system("cls");
            MN_render_rendering(obj->mp_render);
            count++;
            if(count == 10){
                MN_interaction_handle_input(obj->mp_interaction,0);
            }
            if(count == 20){
                MN_interaction_handle_input(obj->mp_interaction,1);
            }
            if(count == 30){
                MN_interaction_handle_input(obj->mp_interaction,2);
            }
            if(count == 40){
                MN_interaction_handle_input(obj->mp_interaction,3);
            }
            if(count == 50){
                MN_interaction_handle_input(obj->mp_interaction,4);
            }
            if(count == 60){
                break;
            }
            Sleep(100);
        }
    }

    MN_page_destroy(obj);
    MN_item_destroy(p_item_1);
    free(item_1_str);
    item_1_str = NULL;
    MN_item_destroy(p_item_2);
    free(item_2_str);
    item_2_str = NULL;
    MN_item_destroy(p_item_3);
    free(p_item_3_int);
    p_item_3_int = NULL;
    MN_item_destroy(p_item_4);
    free(p_item_4_int);
    p_item_4_int = NULL;

    printf("end of exe.\n");
    return 0;
}