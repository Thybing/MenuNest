#include "menu_nest/menu.h"
#include "menu_nest/common.h"
#include "stdbool.h"

#include "menu_nest/internal_func.h"

/**
 * ************************************************************************
 * @brief 菜单模块
 * 
 * @warning  请在使用前进行初始化，禁止私自创建，请采用get函数获取唯一对象
 * ************************************************************************
 */
typedef struct MN_menu{
    /// @brief 菜单主页面指针
    MN_page * mp_main_page;

    /// @brief 菜单历史页面栈
    MN_page ** mpp_history_page_stack;
    /// @brief 菜单历史页面栈顶下标(仅有主页面时为0)
    uint32_t m_history_top_index;
    /// @brief 菜单交互模块
    MN_interaction * mp_interaction;

    /// @brief 菜单输入队列
    input_t * mp_input_queue;
    /// @brief 菜单输入队列头
    uint32_t input_queue_head;
    /// @brief 菜单输入队列尾
    uint32_t input_queue_tail;

}MN_menu;


MN_menu o_MN_menu;
static MN_page * history_page_stack[MN_HISTORY_PAGE_MAX] = {0};
static input_t input_queue[MN_INPUT_QUEUE_MAX] = {0};

void MN_menu_init(MN_page * p_main_page){
    MN_assert(p_main_page);

    o_MN_menu.mp_main_page = p_main_page;
    o_MN_menu.mpp_history_page_stack = history_page_stack;
    (o_MN_menu.mpp_history_page_stack)[0] = o_MN_menu.mp_main_page;
    o_MN_menu.m_history_top_index = 0;

    o_MN_menu.mp_input_queue = input_queue;
    o_MN_menu.input_queue_head = 0;
    o_MN_menu.input_queue_tail = 0;

    o_MN_menu.mp_interaction = MN_interaction_create(&o_MN_menu);
}

static bool MN_is_input_queue_empty(){
    return o_MN_menu.input_queue_head == o_MN_menu.input_queue_tail;
}

static bool MN_is_input_queue_full(){
    return (o_MN_menu.input_queue_tail + 1) % MN_INPUT_QUEUE_MAX
        == o_MN_menu.input_queue_head;
}

static void MN_input_enqueue(const input_t input){
    if(!MN_is_input_queue_full()){
        o_MN_menu.mp_input_queue[o_MN_menu.input_queue_tail] = input;
        o_MN_menu.input_queue_tail++;
        o_MN_menu.input_queue_tail %= MN_INPUT_QUEUE_MAX;
    }
}

static input_t MN_input_dequeue(){
    if(!MN_is_input_queue_empty()){
        input_t ret = o_MN_menu.mp_input_queue[o_MN_menu.input_queue_head];
        o_MN_menu.input_queue_head++;
        o_MN_menu.input_queue_head %= MN_INPUT_QUEUE_MAX;
        return ret;
    }
    return 0;
}

MN_page * MN_get_main_page(){
    return o_MN_menu.mp_main_page;
}

MN_page * MN_get_cur_page(){
    return (o_MN_menu.mpp_history_page_stack)[o_MN_menu.m_history_top_index];
}

void MN_menu_page_forward(MN_page * const p_target_page){
    MN_assert(p_target_page);

    if(o_MN_menu.m_history_top_index < MN_HISTORY_PAGE_MAX - 1){
        // 调用当前页面的on_forward_to_other_page回调
        MN_page * p_cur_page = o_MN_menu.mpp_history_page_stack[o_MN_menu.m_history_top_index];
        p_cur_page->mp_on_forward_to_other_page(p_cur_page,NULL);

        (o_MN_menu.m_history_top_index)++;
        (o_MN_menu.mpp_history_page_stack)[o_MN_menu.m_history_top_index] = p_target_page;

        // 调用目标页面的on_forward回调
        p_target_page->mp_on_forward(p_target_page,NULL);
    }
}

void MN_menu_page_title_forward(const char * const title){
    MN_page * find_ret = MN_find_page(title);
    if(!find_ret) {
        return;
    }
    MN_menu_page_forward(find_ret);
}

void MN_menu_page_retreat(){
    if(o_MN_menu.m_history_top_index > 0){
        MN_page * p_top_page = o_MN_menu.mpp_history_page_stack[o_MN_menu.m_history_top_index];
        p_top_page->mp_on_retreat(p_top_page,NULL);
        (o_MN_menu.m_history_top_index)--;

        p_top_page = o_MN_menu.mpp_history_page_stack[o_MN_menu.m_history_top_index];
        p_top_page->mp_on_retreat_from_other_page(p_top_page,NULL);
    }
}

void MN_menu_rendering(){
    MN_render_rendering(MN_get_cur_page()->mp_render,NULL);
}

MN_interaction * MN_menu_get_interaction(){
    return o_MN_menu.mp_interaction;
}


void MN_menu_input(const input_t input){
    MN_input_enqueue(input);
}

void MN_menu_handle_input_queue(){
    while(!MN_is_input_queue_empty()){
        input_t input = MN_input_dequeue();
        if((MN_get_cur_page()->m_cur_item_index) != -1){
            if(MN_interaction_handle_input((MN_get_cur_page()->mpp_items)[MN_get_cur_page()->m_cur_item_index]->mp_interaction,input)) continue;
        }
        if(MN_interaction_handle_input(MN_get_cur_page()->mp_interaction,input)) continue;
        if(MN_interaction_handle_input(o_MN_menu.mp_interaction,input)) continue;
    }
}
