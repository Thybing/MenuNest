#include "menu_nest/menu.h"
#include "stdbool.h"
#include "stdlib.h"

#include "stdio.h"

static const uint32_t MN_main_page_item_max = 8;
static const uint32_t MN_history_page_max = 16;
static const uint32_t MN_input_queue_max = 16;

static MN_menu o_MN_menu;

static bool is_menu_init = false;

static void MN_menu_init(){
    o_MN_menu.mp_main_page = MN_page_create(MN_main_page_item_max);
    o_MN_menu.mpp_history_page_stack = (MN_page **)malloc(sizeof(MN_page *) * MN_history_page_max);
    (o_MN_menu.mpp_history_page_stack)[0] = o_MN_menu.mp_main_page;
    o_MN_menu.m_history_top_index = 0;

    o_MN_menu.mp_input_queue = (input_t *)malloc(sizeof(input_t) * MN_input_queue_max);
    o_MN_menu.input_queue_head = 0;
    o_MN_menu.input_queue_tail = 0;

    o_MN_menu.mp_interaction = MN_interaction_create(&o_MN_menu);
    is_menu_init = true;
}

MN_menu * MN_get_menu(){
    if(!is_menu_init){
        MN_menu_init();
    }
    return &o_MN_menu;
}

static bool MN_is_input_queue_empty(){
    return MN_get_menu()->input_queue_head == MN_get_menu()->input_queue_tail;
}

static bool MN_is_input_queue_full(){
    return (MN_get_menu()->input_queue_tail + 1) % MN_input_queue_max
        == MN_get_menu()->input_queue_head;
}

static void MN_input_enqueue(const input_t input){
    if(!MN_is_input_queue_full()){
        MN_get_menu()->mp_input_queue[MN_get_menu()->input_queue_tail] = input;
        MN_get_menu()->input_queue_tail++;
        MN_get_menu()->input_queue_tail %= MN_input_queue_max;
    }
}

static input_t MN_input_dequeue(){
    if(!MN_is_input_queue_empty()){
        input_t ret = MN_get_menu()->mp_input_queue[MN_get_menu()->input_queue_head];
        MN_get_menu()->input_queue_head++;
        MN_get_menu()->input_queue_head %= MN_input_queue_max;
        return ret;
    }
    return 0;
}

MN_page * MN_get_main_page(){
    return MN_get_menu()->mp_main_page;
}

MN_page * MN_get_cur_page(){
    return (MN_get_menu()->mpp_history_page_stack)[MN_get_menu()->m_history_top_index];
}

void MN_menu_page_forward(MN_page * const p_target_page){
    if(MN_get_menu()->m_history_top_index < MN_history_page_max - 1){
        (MN_get_menu()->m_history_top_index)++;
        (MN_get_menu()->mpp_history_page_stack)[(MN_get_menu()->m_history_top_index)] = p_target_page;
    }
}

void MN_menu_page_retreat(){
    if(MN_get_menu()->m_history_top_index > 0){
        (MN_get_menu()->m_history_top_index)--;
    }
}

void MN_menu_set_handle_callback(const interaction_callback_t callback){
    MN_interaction_set_handle_callback(MN_get_menu()->mp_interaction,callback);
}

void MN_menu_rendering(){
    MN_render_rendering(MN_get_cur_page()->mp_render);
}

void MN_menu_input(const input_t input){
    MN_input_enqueue(input);
}

void MN_menu_handle_input_queue(){
    while(!MN_is_input_queue_empty()){
        do{
            input_t input = MN_input_dequeue();
            if((MN_get_cur_page()->m_current_index) != -1){
                if(MN_interaction_handle_input((MN_get_cur_page()->mpp_items)[MN_get_cur_page()->m_current_index]->mp_interaction,input)) break;
            }
            if(MN_interaction_handle_input(MN_get_cur_page()->mp_interaction,input)) break;
            if(MN_interaction_handle_input(MN_get_menu()->mp_interaction,input)) break;
        }while(0);
    }
}
