#include "menu_nest_tiny/item_static_variable.h"

#include "inttypes.h"
#include "math.h"
#include "menu_nest/common.h"
#include "menu_nest_tiny/display.h"
#include "menu_nest_tiny/input_def.h"
#include "stdio.h"
#include "string.h"

// 定义输入操作
static const input_t VAR_UP = BUTTON_0_CLICK;          // 用于变量增加
static const input_t VAR_DOWN = BUTTON_1_CLICK;        // 用于变量减少
static const input_t STEP_UP = BUTTON_0_LONG_PRESS;    // 用于步长增加
static const input_t STEP_DOWN = BUTTON_1_LONG_PRESS;  // 用于步长减少

// 前向声明
struct item_static_variable_t;

typedef enum direction_t {
    DOWN = 0,
    UP,
} direction_t;

// 以下的几个回调函数的类型
typedef void (*var_to_string_callback_t)(struct item_static_variable_t* p_static_variable);
typedef void (*var_change_callback_t)(struct item_static_variable_t* p_static_variable, direction_t dir);
typedef void (*step_change_callback_t)(struct item_static_variable_t* p_static_variable, direction_t dir);

// item所指向的类型
typedef struct item_static_variable_t {
    const char* m_name;  // 变量的名字
    basic_type m_type;   // 变量的类型
    void* mp_var_obj;    // 变量的指针
    void* mp_step;       // 变量的步长
} item_static_variable_t;

// item的render的属性结构体。这里是两个字符串
typedef struct item_static_variable_render_attr_t {
    char* mp_fmt_buffer;       // 格式化后的字符串
    char* mp_step_fmt_buffer;  // 格式化后的步长字符串
} item_static_variable_render_attr_t;

// 变量名的长度和浮点数的精度，可以通过宏定义修改
#define VAR_NAME_LEN 8
#define FLOAT_PRECISION 3

// 定义格式化字符串的宏
#define TO_STRING(x) #x
#define VAR_NAME_LEN_FMT(len) "-" TO_STRING(len) "." TO_STRING(len) "s"
#define PRI_VAR_NAME VAR_NAME_LEN_FMT(VAR_NAME_LEN)

#define FLOAT_PRECISION_FMT(len) TO_STRING(len)
#define PRI_FLOAT_PRECISION FLOAT_PRECISION_FMT(FLOAT_PRECISION)

// 将静态变量类转化为渲染字符串
static void static_var_to_render_str(MN_item* const p_item) {
    item_static_variable_t* p_static_var = p_item->mp_memory;
    item_static_variable_render_attr_t* p_render_attr = p_item->mp_render->mp_attribute;

    const char* var_name = p_static_var->m_name;
    switch (p_static_var->m_type) {
        case TYPE_I8: {
            int8_t* p_i8 = (int8_t*)p_static_var->mp_var_obj;
            snprintf(p_render_attr->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIi8, var_name, *p_i8);
            snprintf(p_render_attr->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIi8,
                     *(int8_t*)(p_static_var->mp_step));
            break;
        }
        case TYPE_I16: {
            int16_t* p_i16 = (int16_t*)p_static_var->mp_var_obj;
            snprintf(p_render_attr->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIi16, var_name,
                     *p_i16);
            snprintf(p_render_attr->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIi16,
                     *(int16_t*)(p_static_var->mp_step));
            break;
        }
        case TYPE_I32: {
            int32_t* p_i32 = (int32_t*)p_static_var->mp_var_obj;
            snprintf(p_render_attr->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIi32, var_name,
                     *p_i32);
            snprintf(p_render_attr->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIi32,
                     *(int32_t*)(p_static_var->mp_step));
            break;
        }
        case TYPE_I64: {
            int64_t* p_i64 = (int64_t*)p_static_var->mp_var_obj;
            snprintf(p_render_attr->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIi64, var_name,
                     *p_i64);
            snprintf(p_render_attr->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIi64,
                     *(int64_t*)(p_static_var->mp_step));
            break;
        }
        case TYPE_U8: {
            uint8_t* p_u8 = (uint8_t*)p_static_var->mp_var_obj;
            snprintf(p_render_attr->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIu8, var_name, *p_u8);
            snprintf(p_render_attr->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIu8,
                     *(uint8_t*)(p_static_var->mp_step));
            break;
        }
        case TYPE_U16: {
            uint16_t* p_u16 = (uint16_t*)p_static_var->mp_var_obj;
            snprintf(p_render_attr->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIu16, var_name,
                     *p_u16);
            snprintf(p_render_attr->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIu16,
                     *(uint16_t*)(p_static_var->mp_step));
            break;
        }
        case TYPE_U32: {
            uint32_t* p_u32 = (uint32_t*)p_static_var->mp_var_obj;
            snprintf(p_render_attr->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIu32, var_name,
                     *p_u32);
            snprintf(p_render_attr->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIu32,
                     *(uint32_t*)(p_static_var->mp_step));
            break;
        }
        case TYPE_U64: {
            uint64_t* p_u64 = (uint64_t*)p_static_var->mp_var_obj;
            snprintf(p_render_attr->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIu64, var_name,
                     *p_u64);
            snprintf(p_render_attr->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIu64,
                     *(uint64_t*)(p_static_var->mp_step));
            break;
        }
        case TYPE_F32: {
            float* p_f32 = (float*)p_static_var->mp_var_obj;
            snprintf(p_render_attr->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1,
                     "%" PRI_VAR_NAME ":%." PRI_FLOAT_PRECISION "f", var_name, *p_f32);
            snprintf(p_render_attr->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step: 10e %d",
                     *(int*)(p_static_var->mp_step));
            break;
        }
        case TYPE_F64: {
            double* p_f64 = (double*)p_static_var->mp_var_obj;
            snprintf(p_render_attr->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1,
                     "%" PRI_VAR_NAME ":%." PRI_FLOAT_PRECISION "lf", var_name, *p_f64);
            snprintf(p_render_attr->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step: 10e %d",
                     *(int*)(p_static_var->mp_step));
            break;
        }
        case TYPE_BOOL: {
            bool* p_bool = (bool*)p_static_var->mp_var_obj;
            snprintf(p_render_attr->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%s", var_name,
                     (*p_bool) ? "true" : "false");
            break;
        }
        case TYPE_CSTR: {
            const char* cstr = (const char*)p_static_var->mp_var_obj;
            size_t len = strlen(cstr);
            size_t line_num = 0;
            if (len == 0) {
                snprintf(p_render_attr->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%s", var_name, cstr);
            } else {
                line_num = ((len - 1) / (LINE_MAX_CHAR_NUM - VAR_NAME_LEN - 1)) + 1;
                size_t cur_line = (*(size_t*)(p_static_var->mp_step));
                if (cur_line > line_num) {
                    cur_line = line_num;
                }
                MN_assert(cur_line > 0);
                size_t str_offset = (cur_line - 1) * (LINE_MAX_CHAR_NUM - VAR_NAME_LEN - 1);
                snprintf(p_render_attr->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%s", var_name,
                         cstr + str_offset);
            }
            snprintf(p_render_attr->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "line:%u/%u",
                     (*(size_t*)(p_static_var->mp_step)), line_num);
            break;
        }
        default: {
            // Handle unknown type
            snprintf(p_render_attr->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "Unknown type");
            break;
        }
    }
}

// 各种类型的变量改变的函数
static void var_change(MN_item const* p_item, direction_t dir) {
    item_static_variable_t* p_static_variable = p_item->mp_memory;
    switch (p_static_variable->m_type) {
        case TYPE_I8: {
            int8_t* p_var = (int8_t*)p_static_variable->mp_var_obj;
            int8_t step = *(int8_t*)p_static_variable->mp_step;
            *p_var = dir ? (*p_var + step) : (*p_var - step);
            break;
        }
        case TYPE_I16: {
            int16_t* p_var = (int16_t*)p_static_variable->mp_var_obj;
            int16_t step = *(int16_t*)p_static_variable->mp_step;
            *p_var = dir ? (*p_var + step) : (*p_var - step);
            break;
        }
        case TYPE_I32: {
            int32_t* p_var = (int32_t*)p_static_variable->mp_var_obj;
            int32_t step = *(int32_t*)p_static_variable->mp_step;
            *p_var = dir ? (*p_var + step) : (*p_var - step);
            break;
        }
        case TYPE_I64: {
            int64_t* p_var = (int64_t*)p_static_variable->mp_var_obj;
            int64_t step = *(int64_t*)p_static_variable->mp_step;
            *p_var = dir ? (*p_var + step) : (*p_var - step);
            break;
        }
        case TYPE_U8: {
            uint8_t* p_var = (uint8_t*)p_static_variable->mp_var_obj;
            uint8_t step = *(uint8_t*)p_static_variable->mp_step;
            *p_var = dir ? (*p_var + step) : (*p_var - step);
            break;
        }
        case TYPE_U16: {
            uint16_t* p_var = (uint16_t*)p_static_variable->mp_var_obj;
            uint16_t step = *(uint16_t*)p_static_variable->mp_step;
            *p_var = dir ? (*p_var + step) : (*p_var - step);
            break;
        }
        case TYPE_U32: {
            uint32_t* p_var = (uint32_t*)p_static_variable->mp_var_obj;
            uint32_t step = *(uint32_t*)p_static_variable->mp_step;
            *p_var = dir ? (*p_var + step) : (*p_var - step);
            break;
        }
        case TYPE_U64: {
            uint64_t* p_var = (uint64_t*)p_static_variable->mp_var_obj;
            uint64_t step = *(uint64_t*)p_static_variable->mp_step;
            *p_var = dir ? (*p_var + step) : (*p_var - step);
            break;
        }
        case TYPE_F32: {
            float* p_var = (float*)p_static_variable->mp_var_obj;
            int step = *(int*)p_static_variable->mp_step;
            *p_var = dir ? (*p_var + pow(10, step)) : (*p_var - pow(10, step));
            break;
        }
        case TYPE_F64: {
            double* p_var = (double*)p_static_variable->mp_var_obj;
            int step = *(int*)p_static_variable->mp_step;
            *p_var = dir ? (*p_var + pow(10, step)) : (*p_var - pow(10, step));
            break;
        }
        case TYPE_CSTR: {
            size_t* p_step = (size_t*)p_static_variable->mp_step;
            *p_step = dir ? (*p_step + 1) : (*p_step > 1 ? *p_step - 1 : 1);
            break;
        }
        case TYPE_BOOL: {
            break;
        }
        default: {
            break;
        }
    }
}

// 步长改变的函数
static void step_change(MN_item* p_item, direction_t dir) {
    item_static_variable_t* p_static_variable = p_item->mp_memory;
    switch (p_static_variable->m_type) {
        case TYPE_I8: {
            int8_t* p_step = (int8_t*)p_static_variable->mp_step;
            if (dir) {
                if (*p_step <= INT8_MAX / 10) {
                    *p_step *= 10;
                }
            } else {
                if (*p_step != 1) {
                    *p_step /= 10;
                }
            }
            break;
        }
        case TYPE_I16: {
            int16_t* p_step = (int16_t*)p_static_variable->mp_step;
            if (dir) {
                if (*p_step <= INT16_MAX / 10) {
                    *p_step *= 10;
                }
            } else {
                if (*p_step != 1) {
                    *p_step /= 10;
                }
            }
            break;
        }
        case TYPE_I32: {
            int32_t* p_step = (int32_t*)p_static_variable->mp_step;
            if (dir) {
                if (*p_step <= INT32_MAX / 10) {
                    *p_step *= 10;
                }
            } else {
                if (*p_step != 1) {
                    *p_step /= 10;
                }
            }
            break;
        }
        case TYPE_I64: {
            int64_t* p_step = (int64_t*)p_static_variable->mp_step;
            if (dir) {
                if (*p_step <= INT64_MAX / 10) {
                    *p_step *= 10;
                }
            } else {
                if (*p_step != 1) {
                    *p_step /= 10;
                }
            }
            break;
        }
        case TYPE_U8: {
            uint8_t* p_step = (uint8_t*)p_static_variable->mp_step;
            if (dir) {
                if (*p_step <= UINT8_MAX / 10) {
                    *p_step *= 10;
                }
            } else {
                if (*p_step != 1) {
                    *p_step /= 10;
                }
            }
            break;
        }
        case TYPE_U16: {
            uint16_t* p_step = (uint16_t*)p_static_variable->mp_step;
            if (dir) {
                if (*p_step <= UINT16_MAX / 10) {
                    *p_step *= 10;
                }
            } else {
                if (*p_step != 1) {
                    *p_step /= 10;
                }
            }
            break;
        }
        case TYPE_U32: {
            uint32_t* p_step = (uint32_t*)p_static_variable->mp_step;
            if (dir) {
                if (*p_step <= UINT32_MAX / 10) {
                    *p_step *= 10;
                }
            } else {
                if (*p_step != 1) {
                    *p_step /= 10;
                }
            }
            break;
        }
        case TYPE_U64: {
            uint64_t* p_step = (uint64_t*)p_static_variable->mp_step;
            if (dir) {
                if (*p_step <= UINT64_MAX / 10) {
                    *p_step *= 10;
                }
            } else {
                if (*p_step != 1) {
                    *p_step /= 10;
                }
            }
            break;
        }
        case TYPE_F32:
        case TYPE_F64: {
            int* p_step = (int*)p_static_variable->mp_step;
            if (dir) {
                *p_step += 1;
            } else {
                *p_step -= 1;
            }
            break;
        }
        case TYPE_BOOL: {
            break;
        }
        case TYPE_CSTR: {
            break;
        }
        default: {
            break;
        }
    }
}

// 用于本item的交互回调函数
static bool item_static_variable_interaction_callback(struct MN_interaction* const p_item_interaction,
                                                      const input_t input) {
    MN_item* p_item = p_item_interaction->mp_memory;
    item_static_variable_t* p_static_var = p_item->mp_memory;
    if (input == VAR_UP) {
        var_change(p_item, UP);
        return true;
    } else if (input == VAR_DOWN) {
        var_change(p_item, DOWN);
        return true;
    } else if (input == STEP_UP) {
        step_change(p_item, UP);
        return true;
    } else if (input == STEP_DOWN) {
        step_change(p_item, DOWN);
        return true;
    } else {
        return false;
    }
}

// 用于本item的渲染回调函数
static void item_static_variable_rendering_callback(MN_render* const p_item_render, void* p_y_offset) {
    MN_item* const p_item = p_item_render->mp_memory;
    uint16_t* const p_used_line = p_y_offset;

    static_var_to_render_str(p_item);
    item_static_variable_render_attr_t* p_render_attr = p_item->mp_render->mp_attribute;
    display_line_text(*p_used_line, p_render_attr->mp_fmt_buffer);

    if (p_item->m_select_flag) {
        display_line_text(0, p_render_attr->mp_step_fmt_buffer);
    }
}

// 用于本item被选择时的回调函数，是对于BOOL类型的特殊处理
static void* item_static_var_on_select_callback(struct MN_item* const p_item) {
    item_static_variable_t* p_variable = p_item->mp_memory;
    if (p_variable->m_type == TYPE_BOOL) {
        *(bool*)(p_variable->mp_var_obj) = !*(bool*)(p_variable->mp_var_obj);
        MN_page_unselect_item(MN_get_cur_page());
    }
    return NULL;
}

/**
 ****************************************************************
 * extern function
 */

MN_item* create_item_static_variable(const char* const item_name, void* p_var, enum basic_type var_type) {
    // item内部参数的结构体
    item_static_variable_t* p_variable = MN_malloc(sizeof(item_static_variable_t));
    p_variable->m_name = item_name;
    p_variable->m_type = var_type;
    p_variable->mp_var_obj = p_var;

    switch (var_type) {
        case TYPE_I8: {
            int8_t* p_step = MN_malloc(sizeof(int8_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_I16: {
            int16_t* p_step = MN_malloc(sizeof(int16_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_I32: {
            int32_t* p_step = MN_malloc(sizeof(int32_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_I64: {
            int64_t* p_step = MN_malloc(sizeof(int64_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_U8: {
            uint8_t* p_step = MN_malloc(sizeof(uint8_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_U16: {
            uint16_t* p_step = MN_malloc(sizeof(uint16_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_U32: {
            uint32_t* p_step = MN_malloc(sizeof(uint32_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_U64: {
            uint64_t* p_step = MN_malloc(sizeof(uint64_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_F32: {
            int* p_step = MN_malloc(sizeof(int));
            *p_step = 0;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_F64: {
            int* p_step = MN_malloc(sizeof(int));
            *p_step = 0;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_BOOL: {
            p_variable->mp_step = NULL;
            break;
        }
        case TYPE_CSTR: {
            size_t* p_step = MN_malloc(sizeof(size_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        default: {
            MN_assert(0);
            break;
        }
    }

    // 创建item并设置回调函数
    MN_item* p_item_static_var = MN_item_create(item_name, p_variable);
    p_item_static_var->mp_on_select = item_static_var_on_select_callback;

    p_item_static_var->mp_render->mp_attribute = MN_malloc(sizeof(struct item_static_variable_render_attr_t));
    ((item_static_variable_render_attr_t*)p_item_static_var->mp_render->mp_attribute)->mp_fmt_buffer =
        MN_malloc(LINE_MAX_CHAR_NUM +
                  1)((item_static_variable_render_attr_t*)p_item_static_var->mp_render->mp_attribute)
            ->mp_step_fmt_buffer = MN_malloc(LINE_MAX_CHAR_NUM + 1)
            MN_render_set_rendering_callback(p_item_static_var->mp_render, item_static_variable_rendering_callback);
    MN_interaction_set_handle_callback(p_item_static_var->mp_interaction, item_static_variable_interaction_callback);
    return p_item_static_var;
}

// 通过页面标题和item名字获取item的静态变量指针
void* get_item_static_variable_ptr(const char* const page_title, const char* const item_name) {
    MN_page* p_page = MN_find_page(page_title);
    if (!p_page) {
        return NULL;
    }
    MN_item* p_item = MN_page_find_item(p_page, item_name);
    if (!p_item) {
        return NULL;
    }
    return ((item_static_variable_t*)(p_item->mp_memory))->mp_var_obj;
}

static_var_command_ctrl_errno item_static_var_command_ctrl(char* command, const uint32_t len) {
    char* p_cur = command;
    if (!(len >= 3 && command[0] == 'M' && command[1] == 'N' && command[2] == ':')) {
        return static_var_command_fmt_err;
    }
    p_cur += 3;
    char* page_title = NULL;
    uint32_t title_len = 0;
    char* item_name = NULL;
    uint32_t item_name_len = 0;
    char* ctrl_command = NULL;
    uint32_t command_len = 0;

    for (; p_cur < command + len; p_cur++) {
        if (*p_cur == ':') {
            if (page_title == NULL) {
                page_title = command + 3;
                title_len = p_cur - page_title;
            } else if (item_name == NULL) {
                item_name = page_title + title_len + 1;
                item_name_len = p_cur - item_name;
            }
        } else if (*p_cur == ';') {
            ctrl_command = item_name + item_name_len + 1;
            command_len = p_cur - ctrl_command;
            break;
        }
    }

    if (title_len == 0 || item_name_len == 0 || command_len == 0) {
        return static_var_command_fmt_err;
    }

    // command parser
    *(page_title + title_len) = '\0';
    *(item_name + item_name_len) = '\0';
    *(ctrl_command + command_len) = '\0';

    MN_page* p_page = MN_find_page(page_title);
    if (!p_page) {
        return static_var_command_page_not_found;
    }
    MN_item* p_item = MN_page_find_item(p_page, item_name);
    if (!p_item) {
        return static_var_command_item_not_found;
    }

    void* p_var = (((item_static_variable_t*)(p_item->mp_memory))->mp_var_obj);
    switch (((item_static_variable_t*)(p_item->mp_memory))->m_type) {
        case TYPE_I8:
            if (sscanf(ctrl_command, "%" SCNi8, (int8_t*)p_var) != 1) {
                return static_var_command_var_fmt_err;
            }
            break;
        case TYPE_I16:
            if (sscanf(ctrl_command, "%" SCNi16, (int16_t*)p_var) != 1) {
                return static_var_command_var_fmt_err;
            }
            break;
        case TYPE_I32:
            if (sscanf(ctrl_command, "%" SCNi32, (int32_t*)p_var) != 1) {
                return static_var_command_var_fmt_err;
            }
            break;
        case TYPE_I64:
            if (sscanf(ctrl_command, "%" SCNi64, (int64_t*)p_var) != 1) {
                return static_var_command_var_fmt_err;
            }
            break;

        case TYPE_U8:
            if (sscanf(ctrl_command, "%" SCNu8, (uint8_t*)p_var) != 1) {
                return static_var_command_var_fmt_err;
            }
            break;
        case TYPE_U16:
            if (sscanf(ctrl_command, "%" SCNu16, (uint16_t*)p_var) != 1) {
                return static_var_command_var_fmt_err;
            }
            break;
        case TYPE_U32:
            if (sscanf(ctrl_command, "%" SCNu32, (uint32_t*)p_var) != 1) {
                return static_var_command_var_fmt_err;
            }
            break;
        case TYPE_U64:
            if (sscanf(ctrl_command, "%" SCNu64, (uint64_t*)p_var) != 1) {
                return static_var_command_var_fmt_err;
            }
            break;

        case TYPE_F32:
            if (sscanf(ctrl_command, "%f", (float*)p_var) != 1) {
                return static_var_command_var_fmt_err;
            }
            break;
        case TYPE_F64:
            if (sscanf(ctrl_command, "%lf", (double*)p_var) != 1) {
                return static_var_command_var_fmt_err;
            }
            break;

        case TYPE_BOOL:
            if (*ctrl_command != '0' && *ctrl_command != '1') {
                return static_var_command_var_fmt_err;
            }
            *(bool*)p_var = (*ctrl_command == '1');
            break;

        default:
            return static_var_command_unknown_type;  // 未知类型
    }
    return static_var_command_no_err;
}
