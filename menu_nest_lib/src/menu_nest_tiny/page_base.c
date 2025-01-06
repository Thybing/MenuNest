#include "menu_nest_tiny/page_base.h"

#include "menu_nest/common.h"

#include "menu_nest_tiny/input_def.h"
static const input_t BASE_PAGE_UP = BUTTON_0_CLICK;
static const input_t BASE_PAGE_DOWN = BUTTON_1_CLICK;
static const input_t BASE_PAGE_SELECT = BUTTON_2_CLICK;
static const input_t BASE_PAGE_BACK = BUTTON_3_CLICK;

// 该页面的内部参数
typedef struct {
    uint16_t candidate_index;
} page_base_params_t;

// 显示标题，然后依次向下显示item，每个item的render回调函数中第二个参数会传入屏幕中已经使用的行数
static void base_page_rendering_callback(MN_render *const p_page_render, void *p_none) {
    // 获取参数
    MN_page *p_page = (MN_page *)(p_page_render->mp_memory);
    page_base_params_t *p_page_params = p_page->mp_memory;
    uint16_t candidate_index = p_page_params->candidate_index;

    uint16_t used_y_pixel = 0;  // 已经使用的像素行数

    if (p_page->m_cur_item_index == -1) {
        display_line_text(0, p_page->m_title);
    }
    used_y_pixel += CHAR_HEIGHT;

    uint16_t line_num_max = (DISPLAY_HEIGHT / CHAR_HEIGHT) - 1;  // 可显示item的行数
    uint16_t start_index = 0;

    int underline_y;

    // 页面的item数量大于可显示的行数时
    if (p_page->m_item_num > line_num_max) {
        // 先确定起始显示的item的下标
        if (candidate_index <= line_num_max - 2 || candidate_index == (uint16_t)-1) {
            start_index = 0;
        } else if (candidate_index != p_page->m_item_num - 1) {
            start_index = candidate_index - line_num_max + 2;
        } else {
            start_index = candidate_index - line_num_max + 1;
        }

        // 计算下划线的位置
        if (candidate_index != (uint16_t)-1) {
            // 第一个加1是偏移量 + 1，第二个 + 1是空出标题行
            underline_y = (candidate_index - start_index + 1 + 1) * CHAR_HEIGHT - 1;
        }

        for (int i = start_index; i < start_index + line_num_max; i++) {
            MN_render_rendering(p_page->mpp_items[i]->mp_render, &used_y_pixel);
            used_y_pixel += CHAR_HEIGHT;

            if (underline_y < used_y_pixel && candidate_index != (uint16_t)-1) {
                display_draw_waterline(underline_y, 1);
            }
        }
    } else {
        if (candidate_index != (uint16_t)-1) {
            underline_y = (candidate_index - start_index + 1 + 1) * CHAR_HEIGHT - 1;
        }

        for (int i = 0; i < p_page->m_item_num; i++) {
            MN_render_rendering(p_page->mpp_items[i]->mp_render, &used_y_pixel);
            used_y_pixel += CHAR_HEIGHT;

            if (underline_y < used_y_pixel && candidate_index != (uint16_t)-1) {
                display_draw_waterline(underline_y, 1);
            }
        }
    }
#if DISPLAY_NEED_UPDATE
    display_update();
#endif
}

// 处理页面输入的回调函数
// 四个按键分别对应 上/下，选择，返回
static bool base_page_interaction_callback(struct MN_interaction *const p_page_interaction, const input_t input) {
    MN_page *p_page = (MN_page *)(p_page_interaction->mp_memory);
    page_base_params_t *p_page_params = p_page->mp_memory;
    if (input == BASE_PAGE_UP) {
        if (p_page_params->candidate_index != (uint16_t)-1) {
            p_page_params->candidate_index--;
        }
        return true;
    } else if (input == BASE_PAGE_DOWN) {
        if ((uint16_t)(p_page_params->candidate_index + 1) < p_page->m_item_num) {
            p_page_params->candidate_index++;
        }
        return true;
    } else if (input == BASE_PAGE_SELECT) {
        if (p_page_params->candidate_index != (uint16_t)-1) {
            MN_page_select_item(p_page, p_page_params->candidate_index);
        }
        return true;
    } else if (input == BASE_PAGE_BACK) {
        if (p_page->m_cur_item_index != -1) {
            MN_page_unselect_item(p_page);
        } else {
            MN_menu_page_retreat();
        }
        return true;
    } else {
        return false;
    }
}

// 清屏的回调函数，用于进入页面时清屏
static void *page_clear_action_callback(struct MN_page *const p_page, void *p_none) {
    display_clear();
#if DISPLAY_NEED_UPDATE
    display_update();
#endif
    return NULL;
}

// 是否启动小动画
#if PAGE_BASE_USING_TINY_ANIMATION
// 用于页面切换时的小动画

static void *page_on_forward_callback(struct MN_page *const p_page, void *p_none) {
    // 获取参数
    page_base_params_t *p_page_params = p_page->mp_memory;
    uint16_t candidate_index = p_page_params->candidate_index;

    display_clear();
#if DISPLAY_NEED_UPDATE
    display_update();
#endif

    uint16_t start_index = 0;
    uint16_t line_num_max = (DISPLAY_HEIGHT / CHAR_HEIGHT) - 1;  // 可显示item的行数

    for (int diff_y = 0; diff_y <= CHAR_HEIGHT; diff_y++) {
        uint16_t used_y_pixel = 0;  // 已经使用的像素行数

        if (p_page->m_cur_item_index == -1) {
            display_line_text(0, p_page->m_title);
        }
        used_y_pixel += diff_y;

        // 页面的item数量大于可显示的行数时
        if (p_page->m_item_num > line_num_max) {
            if (candidate_index <= line_num_max - 2 || candidate_index == (uint16_t)-1) {
                start_index = 0;
            } else if (candidate_index != p_page->m_item_num - 1) {
                start_index = candidate_index - line_num_max + 2;
            } else {
                start_index = candidate_index - line_num_max + 1;
            }
            for (int i = start_index; i < start_index + line_num_max; i++) {
                MN_render_rendering(p_page->mpp_items[i]->mp_render, &used_y_pixel);
                used_y_pixel += diff_y;
            }
        } else {
            for (int i = 0; i < p_page->m_item_num; i++) {
                MN_render_rendering(p_page->mpp_items[i]->mp_render, &used_y_pixel);
                used_y_pixel += diff_y;
            }
        }
#if DISPLAY_NEED_UPDATE
        display_update();
#endif
    }

    // 绘制下划线
    if (candidate_index != (uint16_t)-1) {
        // 第一个加1是偏移量 + 1，第二个 + 1是空出标题行
        int underline_y = (candidate_index - start_index + 1 + 1) * CHAR_HEIGHT - 1;
        display_draw_waterline(underline_y, 1);
    }
#if DISPLAY_NEED_UPDATE
    display_update();
#endif
    return NULL;
}

static void *page_on_retreat_callback(struct MN_page *const p_page, void *p_none) {
    // 竖向百叶窗消除的效果
    int block_num = 6;                                                // 百叶窗的块数
    int block_width = (DISPLAY_WIDTH + (block_num - 1)) / block_num;  // 每个块的宽度，(向上取整)
    for (int block_col = 0; block_col < block_width; block_col++) {
        for (int each_block = 0; each_block < block_num; each_block++) {
            int col = each_block * block_width + block_col;
            if (col < DISPLAY_WIDTH) {
                display_draw_verticalline(col, 0);
            }
        }
#if DISPLAY_NEED_UPDATE
        display_update();
#endif
    }
    return NULL;
}

#endif  // USING_TINY_ANIMATION

// 对外接口，创建一个page_base页面
MN_page *create_base_page(const char *const page_title) {
    // 创建页面
    MN_page *p_new_page = MN_page_create(page_title, 16);

// 设置页面中用于的回调函数
#if PAGE_BASE_USING_TINY_ANIMATION
    p_new_page->mp_on_forward = page_on_forward_callback;
    p_new_page->mp_on_retreat_from_other_page = page_on_forward_callback;
    p_new_page->mp_on_retreat = page_on_retreat_callback;
    p_new_page->mp_on_forward_to_other_page = page_on_retreat_callback;
#else   // PAGE_BASE_USING_TINY_ANIMATION
    p_new_page->mp_on_forward = page_clear_action_callback;
    p_new_page->mp_on_retreat_from_other_page = page_clear_action_callback;
    p_new_page->mp_on_retreat = page_clear_action_callback;
    p_new_page->mp_on_forward_to_other_page = page_clear_action_callback;
#endif  // PAGE_BASE_USING_TINY_ANIMATION

    // 设置页面的内部参数
    page_base_params_t *p_param = MN_malloc(sizeof(page_base_params_t));
    p_param->candidate_index = (uint16_t)-1;
    p_new_page->mp_memory = p_param;

    // 设置页面的渲染和输入处理回调函数
    MN_render_set_rendering_callback(p_new_page->mp_render, base_page_rendering_callback);
    MN_interaction_set_handle_callback(p_new_page->mp_interaction, base_page_interaction_callback);
    return p_new_page;
}