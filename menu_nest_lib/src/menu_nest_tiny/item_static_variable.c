#include "menu_nest_tiny/item_static_variable.h"

#include "inttypes.h"
#include "math.h"
#include "string.h"
#include "stdio.h"

#include "menu_nest_tiny/display.h"
#include "menu_nest/common.h"

#include "menu_nest_tiny/input_def.h"

// 定义输入操作
static const input_t VAR_UP = BUTTON_0_CLICK;
static const input_t VAR_DOWN = BUTTON_1_CLICK;
static const input_t STEP_UP = BUTTON_0_LONG_PRESS;
static const input_t STEP_DOWN = BUTTON_1_LONG_PRESS;

// 前向声明
struct item_static_variable_t;

// 以下的几个回调函数的类型
typedef void (*var_to_string_callback_t)(struct item_static_variable_t* p_static_variable);
typedef void (*var_change_callback_t)(struct item_static_variable_t* p_static_variable, bool dir);
typedef void (*step_change_callback_t)(struct item_static_variable_t* p_static_variable, bool dir);

typedef struct item_static_variable_t {
    const char* m_name;                             // 变量的名字
    basic_type m_type;                              // 变量的类型
    void* mp_var_obj;                               // 变量的指针
    void* mp_step;                                  // 变量的步长
    char* mp_fmt_buffer;                            // 格式化后的字符串
    char* mp_step_fmt_buffer;                       // 格式化后的步长字符串
    var_to_string_callback_t m_to_string_callback;  // 将变量转换为字符串和步长转换为字符串的回调函数
    var_change_callback_t m_var_change_callback;    // 变量改变的回调函数
    step_change_callback_t m_step_change_callback;  // 步长改变的回调函数
} item_static_variable_t;

// 变量名的长度和浮点数的精度，可以通过宏定义修改
#define VAR_NAME_LEN 8
#define FLOAT_PRECISION 3

// 定义格式化字符串的宏
#define TO_STRING(x) #x
#define VAR_NAME_LEN_FMT(len) "-" TO_STRING(len) "." TO_STRING(len) "s"
#define PRI_VAR_NAME VAR_NAME_LEN_FMT(VAR_NAME_LEN)

#define FLOAT_PRECISION_FMT(len) TO_STRING(len)
#define PRI_FLOAT_PRECISION FLOAT_PRECISION_FMT(FLOAT_PRECISION)

// 以下是各种类型的格式化回调函数

static void static_i8_to_string_callback(item_static_variable_t* p_static_i8_var) {
    const char* var_name = p_static_i8_var->m_name;
    int8_t* p_i8 = (p_static_i8_var->mp_var_obj);
    snprintf(p_static_i8_var->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIi8, var_name, *p_i8);
    snprintf(p_static_i8_var->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIi8,
             *(int8_t*)(p_static_i8_var->mp_step));
}

static void static_i16_to_string_callback(item_static_variable_t* p_static_i16_var) {
    const char* var_name = p_static_i16_var->m_name;
    int16_t* p_i16 = (p_static_i16_var->mp_var_obj);
    snprintf(p_static_i16_var->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIi16, var_name, *p_i16);
    snprintf(p_static_i16_var->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIi16,
             *(int16_t*)(p_static_i16_var->mp_step));
}

static void static_i32_to_string_callback(item_static_variable_t* p_static_i32_var) {
    const char* var_name = p_static_i32_var->m_name;
    int32_t* p_i32 = (p_static_i32_var->mp_var_obj);
    snprintf(p_static_i32_var->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIi32, var_name, *p_i32);
    snprintf(p_static_i32_var->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIi32,
             *(int32_t*)(p_static_i32_var->mp_step));
}

static void static_i64_to_string_callback(item_static_variable_t* p_static_i64_var) {
    const char* var_name = p_static_i64_var->m_name;
    int64_t* p_i64 = (p_static_i64_var->mp_var_obj);
    snprintf(p_static_i64_var->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIi64, var_name, *p_i64);
    snprintf(p_static_i64_var->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIi64,
             *(int64_t*)(p_static_i64_var->mp_step));
}

static void static_u8_to_string_callback(item_static_variable_t* p_static_u8_var) {
    const char* var_name = p_static_u8_var->m_name;
    uint8_t* p_u8 = (p_static_u8_var->mp_var_obj);
    snprintf(p_static_u8_var->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIu8, var_name, *p_u8);
    snprintf(p_static_u8_var->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIu8,
             *(uint8_t*)(p_static_u8_var->mp_step));
}

static void static_u16_to_string_callback(item_static_variable_t* p_static_u16_var) {
    const char* var_name = p_static_u16_var->m_name;
    uint16_t* p_u16 = (p_static_u16_var->mp_var_obj);
    snprintf(p_static_u16_var->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIu16, var_name, *p_u16);
    snprintf(p_static_u16_var->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIu16,
             *(uint16_t*)(p_static_u16_var->mp_step));
}

static void static_u32_to_string_callback(item_static_variable_t* p_static_u32_var) {
    const char* var_name = p_static_u32_var->m_name;
    uint32_t* p_u32 = (p_static_u32_var->mp_var_obj);
    snprintf(p_static_u32_var->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIu32, var_name, *p_u32);
    snprintf(p_static_u32_var->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIu32,
             *(uint32_t*)(p_static_u32_var->mp_step));
}

static void static_u64_to_string_callback(item_static_variable_t* p_static_u64_var) {
    const char* var_name = p_static_u64_var->m_name;
    uint64_t* p_u64 = (p_static_u64_var->mp_var_obj);
    snprintf(p_static_u64_var->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%" PRIu64, var_name, *p_u64);
    snprintf(p_static_u64_var->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step:%" PRIu64,
             *(uint64_t*)(p_static_u64_var->mp_step));
}

static void static_f32_to_string_callback(item_static_variable_t* p_static_f32_var) {
    const char* var_name = p_static_f32_var->m_name;
    float* p_f32 = p_static_f32_var->mp_var_obj;
    snprintf(p_static_f32_var->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%." PRI_FLOAT_PRECISION "f",
             var_name, *p_f32);
    snprintf(p_static_f32_var->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step: 10e%d",
             *(int*)(p_static_f32_var->mp_step));
}

static void static_f64_to_string_callback(item_static_variable_t* p_static_f64_var) {
    const char* var_name = p_static_f64_var->m_name;
    double* p_f64 = p_static_f64_var->mp_var_obj;
    snprintf(p_static_f64_var->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%." PRI_FLOAT_PRECISION "f",
             var_name, *p_f64);
    snprintf(p_static_f64_var->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "step: 10e%d",
             *(int*)(p_static_f64_var->mp_step));
}

static void static_bool_to_string_callback(item_static_variable_t* p_static_bool_var) {
    const char* var_name = p_static_bool_var->m_name;
    bool* p_bool = p_static_bool_var->mp_var_obj;
    snprintf(p_static_bool_var->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%s", var_name,
             (*p_bool) ? "true" : "false");
}

static void static_cstr_to_string_callback(item_static_variable_t* p_static_cstr_var) {
    const char* var_name = p_static_cstr_var->m_name;
    const char* cstr = p_static_cstr_var->mp_var_obj;

    size_t len = strlen(cstr);
    size_t line_num = 0;
    if (len == 0) {
        snprintf(p_static_cstr_var->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%s", var_name, cstr);
    } else {
        line_num = ((len - 1) / (LINE_MAX_CHAR_NUM - VAR_NAME_LEN - 1)) + 1;
        size_t cur_line = (*(size_t*)(p_static_cstr_var->mp_step));
        if (cur_line > line_num) {
            cur_line = line_num;
        }
        MN_assert(cur_line > 0);

        size_t str_offset = (cur_line - 1) * (LINE_MAX_CHAR_NUM - VAR_NAME_LEN - 1);
        snprintf(p_static_cstr_var->mp_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "%" PRI_VAR_NAME ":%s", var_name,
                 cstr + str_offset);
    }
    snprintf(p_static_cstr_var->mp_step_fmt_buffer, LINE_MAX_CHAR_NUM + 1, "line:%u/%u",
             (*(size_t*)(p_static_cstr_var->mp_step)), line_num);
}

// 以下是各种类型的调整改变的回调函数

static void i8_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        *(int8_t*)(p_static_variable->mp_var_obj) += *(int8_t*)(p_static_variable->mp_step);
    } else {
        *(int8_t*)(p_static_variable->mp_var_obj) -= *(int8_t*)(p_static_variable->mp_step);
    }
}

static void i16_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        *(int16_t*)(p_static_variable->mp_var_obj) += *(int16_t*)(p_static_variable->mp_step);
    } else {
        *(int16_t*)(p_static_variable->mp_var_obj) -= *(int16_t*)(p_static_variable->mp_step);
    }
}

static void i32_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        *(int32_t*)(p_static_variable->mp_var_obj) += *(int32_t*)(p_static_variable->mp_step);
    } else {
        *(int32_t*)(p_static_variable->mp_var_obj) -= *(int32_t*)(p_static_variable->mp_step);
    }
}

static void i64_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        *(int64_t*)(p_static_variable->mp_var_obj) += *(int64_t*)(p_static_variable->mp_step);
    } else {
        *(int64_t*)(p_static_variable->mp_var_obj) -= *(int64_t*)(p_static_variable->mp_step);
    }
}

static void u8_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        *(uint8_t*)(p_static_variable->mp_var_obj) += *(uint8_t*)(p_static_variable->mp_step);
    } else {
        *(uint8_t*)(p_static_variable->mp_var_obj) -= *(uint8_t*)(p_static_variable->mp_step);
    }
}

static void u16_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        *(uint16_t*)(p_static_variable->mp_var_obj) += *(uint16_t*)(p_static_variable->mp_step);
    } else {
        *(uint16_t*)(p_static_variable->mp_var_obj) -= *(uint16_t*)(p_static_variable->mp_step);
    }
}

static void u32_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        *(uint32_t*)(p_static_variable->mp_var_obj) += *(uint32_t*)(p_static_variable->mp_step);
    } else {
        *(uint32_t*)(p_static_variable->mp_var_obj) -= *(uint32_t*)(p_static_variable->mp_step);
    }
}

static void u64_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        *(uint64_t*)(p_static_variable->mp_var_obj) += *(uint64_t*)(p_static_variable->mp_step);
    } else {
        *(uint64_t*)(p_static_variable->mp_var_obj) -= *(uint64_t*)(p_static_variable->mp_step);
    }
}

static void f32_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        *(float*)(p_static_variable->mp_var_obj) += pow(10, *(int*)(p_static_variable->mp_step));
    } else {
        *(float*)(p_static_variable->mp_var_obj) -= pow(10, *(int*)(p_static_variable->mp_step));
    }
}

static void f64_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        *(double*)(p_static_variable->mp_var_obj) += pow(10, *(int*)(p_static_variable->mp_step));
    } else {
        *(double*)(p_static_variable->mp_var_obj) -= pow(10, *(int*)(p_static_variable->mp_step));
    }
}

static void cstr_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        (*(size_t*)(p_static_variable->mp_step))++;
    } else {
        if (*(size_t*)(p_static_variable->mp_step) > 1) {
            (*(size_t*)(p_static_variable->mp_step))--;
        }
    }
}

static void empty_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    ;
}

// 以下是各种类型的步长改变的回调函数

static void step_i8_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        if (*(int8_t*)(p_static_variable->mp_step) <= INT8_MAX / 10) {
            *(int8_t*)(p_static_variable->mp_step) *= 10;
        }
    } else {
        if (*(int8_t*)(p_static_variable->mp_step) != 1) {
            *(int8_t*)(p_static_variable->mp_step) /= 10;
        }
    }
}

static void step_i16_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        if (*(int16_t*)(p_static_variable->mp_step) <= INT16_MAX / 10) {
            *(int16_t*)(p_static_variable->mp_step) *= 10;
        }
    } else {
        if (*(int16_t*)(p_static_variable->mp_step) != 1) {
            *(int16_t*)(p_static_variable->mp_step) /= 10;
        }
    }
}

static void step_i32_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        if (*(int32_t*)(p_static_variable->mp_step) <= INT32_MAX / 10) {
            *(int32_t*)(p_static_variable->mp_step) *= 10;
        }
    } else {
        if (*(int32_t*)(p_static_variable->mp_step) != 1) {
            *(int32_t*)(p_static_variable->mp_step) /= 10;
        }
    }
}

static void step_i64_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        if (*(int64_t*)(p_static_variable->mp_step) <= INT64_MAX / 10) {
            *(int64_t*)(p_static_variable->mp_step) *= 10;
        }
    } else {
        if (*(int64_t*)(p_static_variable->mp_step) != 1) {
            *(int64_t*)(p_static_variable->mp_step) /= 10;
        }
    }
}

static void step_u8_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        if (*(uint8_t*)(p_static_variable->mp_step) <= UINT8_MAX / 10) {
            *(uint8_t*)(p_static_variable->mp_step) *= 10;
        }
    } else {
        if (*(uint8_t*)(p_static_variable->mp_step) != 1) {
            *(uint8_t*)(p_static_variable->mp_step) /= 10;
        }
    }
}

static void step_u16_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        if (*(uint16_t*)(p_static_variable->mp_step) <= UINT16_MAX / 10) {
            *(uint16_t*)(p_static_variable->mp_step) *= 10;
        }
    } else {
        if (*(uint16_t*)(p_static_variable->mp_step) != 1) {
            *(uint16_t*)(p_static_variable->mp_step) /= 10;
        }
    }
}

static void step_u32_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        if (*(uint32_t*)(p_static_variable->mp_step) <= UINT32_MAX / 10) {
            *(uint32_t*)(p_static_variable->mp_step) *= 10;
        }
    } else {
        if (*(uint32_t*)(p_static_variable->mp_step) != 1) {
            *(uint32_t*)(p_static_variable->mp_step) /= 10;
        }
    }
}

static void step_u64_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        if (*(uint64_t*)(p_static_variable->mp_step) <= UINT64_MAX / 10) {
            *(uint64_t*)(p_static_variable->mp_step) *= 10;
        }
    } else {
        if (*(uint64_t*)(p_static_variable->mp_step) != 1) {
            *(uint64_t*)(p_static_variable->mp_step) /= 10;
        }
    }
}

static void step_f32_64_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    if (dir) {
        *(int*)(p_static_variable->mp_step) += 1;
    } else {
        *(int*)(p_static_variable->mp_step) -= 1;
    }
}

static void step_empty_change_callback(struct item_static_variable_t* p_static_variable, bool dir) {
    ;
}

// 用于本item的交互回调函数
static bool item_static_variable_interaction_callback(struct MN_interaction* const p_item_interaction,
                                                      const input_t input) {
    MN_item* p_item = p_item_interaction->mp_memory;
    item_static_variable_t* p_static_var = p_item->mp_memory;
    if (input == VAR_UP) {
        p_static_var->m_var_change_callback(p_static_var, true);
        return true;
    } else if (input == VAR_DOWN) {
        p_static_var->m_var_change_callback(p_static_var, false);
        return true;
    } else if (input == STEP_UP) {
        p_static_var->m_step_change_callback(p_static_var, true);
        return true;
    } else if (input == STEP_DOWN) {
        p_static_var->m_step_change_callback(p_static_var, false);
        return true;
    } else {
        return false;
    }
}

// 用于本item的渲染回调函数
static void item_static_variable_rendering_callback(MN_render* const p_item_render, void* p_y_offset) {
    MN_item* const p_item = p_item_render->mp_memory;
    uint16_t* const p_used_line = p_y_offset;

    item_static_variable_t* p_static_variable = p_item->mp_memory;

    p_static_variable->m_to_string_callback(p_static_variable);
    display_line_text(*p_used_line, p_static_variable->mp_fmt_buffer);

    if (p_item->m_select_flag) {
        display_line_text(0, p_static_variable->mp_step_fmt_buffer);
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

// 用于本item被取消选择时的回调函数
MN_item* create_item_static_variable(const char* const item_name, void* p_var, enum basic_type var_type) {
    // item内部参数的结构体
    item_static_variable_t* p_variable = MN_malloc(sizeof(item_static_variable_t));
    p_variable->m_name = item_name;
    p_variable->m_type = var_type;
    p_variable->mp_var_obj = p_var;
    p_variable->mp_fmt_buffer = MN_malloc(LINE_MAX_CHAR_NUM + 1);
    p_variable->mp_step_fmt_buffer = MN_malloc(LINE_MAX_CHAR_NUM + 1);

    switch (var_type) {
        case TYPE_I8: {
            p_variable->m_to_string_callback = static_i8_to_string_callback;
            p_variable->m_var_change_callback = i8_change_callback;
            p_variable->m_step_change_callback = step_i8_change_callback;
            int8_t* p_step = MN_malloc(sizeof(int8_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_I16: {
            p_variable->m_to_string_callback = static_i16_to_string_callback;
            p_variable->m_var_change_callback = i16_change_callback;
            p_variable->m_step_change_callback = step_i16_change_callback;
            int16_t* p_step = MN_malloc(sizeof(int16_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_I32: {
            p_variable->m_to_string_callback = static_i32_to_string_callback;
            p_variable->m_var_change_callback = i32_change_callback;
            p_variable->m_step_change_callback = step_i32_change_callback;
            int32_t* p_step = MN_malloc(sizeof(int32_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_I64: {
            p_variable->m_to_string_callback = static_i64_to_string_callback;
            p_variable->m_var_change_callback = i64_change_callback;
            p_variable->m_step_change_callback = step_i64_change_callback;
            int64_t* p_step = MN_malloc(sizeof(int64_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_U8: {
            p_variable->m_to_string_callback = static_u8_to_string_callback;
            p_variable->m_var_change_callback = u8_change_callback;
            p_variable->m_step_change_callback = step_u8_change_callback;
            uint8_t* p_step = MN_malloc(sizeof(uint8_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_U16: {
            p_variable->m_to_string_callback = static_u16_to_string_callback;
            p_variable->m_var_change_callback = u16_change_callback;
            p_variable->m_step_change_callback = step_u16_change_callback;
            uint16_t* p_step = MN_malloc(sizeof(uint16_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_U32: {
            p_variable->m_to_string_callback = static_u32_to_string_callback;
            p_variable->m_var_change_callback = u32_change_callback;
            p_variable->m_step_change_callback = step_u32_change_callback;
            uint32_t* p_step = MN_malloc(sizeof(uint32_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_U64: {
            p_variable->m_to_string_callback = static_u64_to_string_callback;
            p_variable->m_var_change_callback = u64_change_callback;
            p_variable->m_step_change_callback = step_u64_change_callback;
            uint64_t* p_step = MN_malloc(sizeof(uint64_t));
            *p_step = 1;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_F32: {
            p_variable->m_to_string_callback = static_f32_to_string_callback;
            p_variable->m_var_change_callback = f32_change_callback;
            p_variable->m_step_change_callback = step_f32_64_change_callback;
            int* p_step = MN_malloc(sizeof(int));
            *p_step = 0;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_F64: {
            p_variable->m_to_string_callback = static_f64_to_string_callback;
            p_variable->m_var_change_callback = f64_change_callback;
            p_variable->m_step_change_callback = step_f32_64_change_callback;
            int* p_step = MN_malloc(sizeof(int));
            *p_step = 0;
            p_variable->mp_step = p_step;
            break;
        }
        case TYPE_BOOL: {
            p_variable->m_to_string_callback = static_bool_to_string_callback;
            p_variable->m_var_change_callback = empty_change_callback;
            p_variable->m_step_change_callback = step_empty_change_callback;
            p_variable->mp_step = NULL;
            break;
        }
        case TYPE_CSTR: {
            p_variable->m_to_string_callback = static_cstr_to_string_callback;
            p_variable->m_var_change_callback = cstr_change_callback;
            p_variable->m_step_change_callback = step_empty_change_callback;
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
