#include "menu_nest/menu.h"
#include "stdbool.h"

static const uint32_t MN_main_page_item_max = 8;
static const uint32_t MN_history_page_max = 16;

struct MN_menu{
    MN_page * mp_main_page;
    MN_page ** mpp_history_page_stack;
    uint32_t m_history_top_index;
    MN_interaction * mp_interaction;
};

static MN_menu o_MN_menu;

static bool is_menu_init = false;

static void MN_menu_init(){
    o_MN_menu.mp_main_page = MN_page_create(MN_main_page_item_max);
    o_MN_menu.mpp_history_page_stack = (MN_page **)(sizeof(MN_page *) * MN_history_page_max);
    (o_MN_menu.mpp_history_page_stack)[0] = o_MN_menu.mp_main_page;
    o_MN_menu.m_history_top_index = 0;

    o_MN_menu.mp_interaction = MN_interaction_create(&o_MN_menu);

    is_menu_init = true;
}

MN_menu * MN_get_menu(){
    if(!is_menu_init){
        MN_menu_init();
    }
    return &o_MN_menu;
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

void MN_menu_set_handle_callback(const handle_callback_t callback){
    MN_interaction_set_handle_callback(MN_get_menu()->mp_interaction,callback);
}
