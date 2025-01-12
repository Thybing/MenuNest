#include "menu_nest_tiny/page_hibernate.h"

#include "menu_nest/common.h"
#include "menu_nest_tiny/display.h"
#include "menu_nest_tiny/input_def.h"
static const input_t EXIT_HIBERNATE = BUTTON_3_CLICK;  // 用于退出休眠

static MN_page* p_default_hibernate_page = NULL;

// 休眠页面的交互函数，仅有退出休眠的功能。
static bool hibernate_page_interaction_callback(struct MN_interaction* const interaction, const input_t input) {
    if (input == EXIT_HIBERNATE) {
        MN_menu_page_retreat();
    }
    return true;
}

// 休眠页面的渲染函数，空函数。
static void hibernate_page_rendering_callback(struct MN_render* const render, void* data) {}

// 默认休眠页面的进入回调函数，清屏并显示休眠字样。
static void* default_hibernate_page_entry_callback(struct MN_page* const p_page, void* p_none) {
    display_clear();
    display_line_text(0, "Hibernate");
#if DISPLAY_NEED_UPDATE
    display_update();
#endif
    return NULL;
}

static void init_default_hibernate_page() {
    p_default_hibernate_page = MN_page_create(
        "dONt@usE^ThIS&tItlE", 0);  // 这个title不会被显示，而且无需查找，另外还要保证不会被其他页面使用。
    p_default_hibernate_page->mp_on_forward = default_hibernate_page_entry_callback;
    p_default_hibernate_page->mp_interaction->m_handle_callback = hibernate_page_interaction_callback;
    p_default_hibernate_page->mp_render->m_rendering_callback = hibernate_page_rendering_callback;
}

MN_page* create_page_hibernate(const char* const title, MN_page_action_callback_t on_forward_callback) {
    MN_page* p_page = MN_page_create(title, 0);
    p_page->mp_on_forward = on_forward_callback;
    p_page->mp_interaction->m_handle_callback = hibernate_page_interaction_callback;
    p_page->mp_render->m_rendering_callback = hibernate_page_rendering_callback;
    return p_page;
}

void into_hibernate_page(MN_page* p_page) {
    if (p_page == NULL) {
        if (p_default_hibernate_page == NULL) {
            init_default_hibernate_page();
        }
        MN_menu_page_forward(p_default_hibernate_page);
    } else {
        MN_menu_page_forward(p_page);
    }
}
