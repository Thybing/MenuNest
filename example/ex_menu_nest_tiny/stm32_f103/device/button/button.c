#include "button/button.h"

#include "button/button_config.h"

enum {  // 按键状态机
    FREE = 0,
    JITTER,
    PRESS,
    RELEASE,
    DBLJITTER,
    DBLPRESS
} button_condi[MAX_BUTTON_NUM];

union {  // 按键状态计时器
    uint16_t jitter;
    uint16_t press;
    uint16_t release;
    uint16_t dbljitter;
    uint16_t dblpress;
} condi_time[MAX_BUTTON_NUM];

static BUTTON_ACT button_act[MAX_BUTTON_NUM];  // 记录每个按键状态

// 按键询问结果数组
static uint8_t* button_query_array = NULL;
static uint8_t button_query_array_default[MAX_BUTTON_NUM];

void set_button_query_array(uint8_t* i_button_query_array) {
    if (i_button_query_array == NULL) {
        button_query_array = button_query_array_default;
    } else {
        button_query_array = i_button_query_array;
    }
}

// 按键动作的事件函数指针，按键电平的询问函数指针
static void (*button_event_func[MAX_BUTTON_NUM][3])();
static uint8_t (*button_query_func[MAX_BUTTON_NUM])();

// 函数指针的默认值,事件函数为空函数,电平询问函数始终返回0
static void void_button_event_func() {}
static uint8_t void_button_query_func() {
    return 0;
}

// 按键初始化函数
void button_init() {
    button_query_array = button_query_array_default;
    for (uint8_t i = 0; i < MAX_BUTTON_NUM; i++) {
        button_act[i] = NONE;
        button_condi[i] = FREE;
        button_query_func[i] = void_button_query_func;
        for (uint8_t j = 0; j < 3; j++) {
            button_event_func[i][j] = void_button_event_func;
        }
    }
}

// 设置按键的询问函数(默认始终返回0)
void set_button_query_func(uint8_t i_button, button_query_func_callback_t i_button_query_func) {
    button_query_func[i_button] = i_button_query_func;
}
// 设置按键的事件函数(默认空函数)
void set_button_event_func(uint8_t i_button, BUTTON_ACT i_button_act,
                           button_event_func_callback_t i_button_event_func) {
    button_event_func[i_button][i_button_act] = i_button_event_func;
}

// 轮询函数,放入定时器中轮询
void button_turn_query() {
    if (button_query_array == button_query_array_default) {
        for (uint8_t i = 0; i < MAX_BUTTON_NUM; i++) {
            button_query_array[i] = (*(button_query_func[i]))();
        }
    }
    for (uint8_t i = 0; i < MAX_BUTTON_NUM; i++) {
        switch (button_condi[i]) {
            case FREE:
                if (button_query_array[i] == 1) {
                    button_condi[i] = JITTER;
                    condi_time[i].jitter = 0;
                }
                break;
            case JITTER:
                condi_time[i].jitter += TIME_TURN_QUERY;
                if (condi_time[i].jitter > TIME_JITTER) {
                    if (button_query_array[i] == 1) {
                        button_condi[i] = PRESS;
                        condi_time[i].press = 0;
                    } else {
                        button_condi[i] = FREE;
                    }
                }
                break;
            case PRESS:
                condi_time[i].press += TIME_TURN_QUERY;

#if LONG_TOUCH_NEED_RELEASE  // 长按需要松开后再触发
                if (button_query_array[i] == 0) {
                    if (condi_time[i].press < TIME_LONG_TOUCH) {
                        button_condi[i] = RELEASE;
                        condi_time[i].release = 0;
                    } else {
                        button_condi[i] = FREE;
                        button_act[i] = LONG_TOUCH;
                    }
                }
#else                      // LONG_TOUCH_NEED_RELEASE // 长按不需要松开即可触发
                if (button_query_array[i] == 0) {
                    if (condi_time[i].press < TIME_LONG_TOUCH) {
                        button_condi[i] = RELEASE;
                        condi_time[i].release = 0;
                    }
                    // 松手时间超过长按时间，说明触发过长按事件。直接将状态置为FREE
                    else {
                        button_condi[i] = FREE;
                    }
                }

                // 无论是否松手，长按时间第一次超过长按阈值时，触发长按事件
                if (condi_time[i].press >= TIME_LONG_TOUCH && condi_time[i].press - TIME_TURN_QUERY < TIME_LONG_TOUCH) {
                    button_act[i] = LONG_TOUCH;
                }
#if LONG_TOUCH_CAN_REPEAT  // 长按可以重复触发
                else if (condi_time[i].press >= TIME_LONG_TOUCH + TIME_LONG_TOUCH_REPEAT &&
                         (condi_time[i].press - TIME_LONG_TOUCH) % TIME_LONG_TOUCH_REPEAT < TIME_TURN_QUERY) {
                    button_act[i] = LONG_TOUCH;
                }
#endif                     // LONG_TOUCH_CAN_REPEAT

#endif  // LONG_TOUCH_NEED_RELEASE
                break;
            case RELEASE:
                condi_time[i].release += TIME_TURN_QUERY;
                if (condi_time[i].release <= TIME_WAIT_DBLCLICK) {
                    if (condi_time[i].release <= TIME_JITTER) {
                        break;
                    }
                    if (button_query_array[i] == 1) {
                        button_condi[i] = DBLJITTER;
                        condi_time[i].dbljitter = 0;
                    }
                } else {
                    button_condi[i] = FREE;
                    button_act[i] = CLICK;
                }
                break;
            case DBLJITTER:
                condi_time[i].dbljitter += TIME_TURN_QUERY;
                if (condi_time[i].dbljitter > TIME_JITTER) {
                    if (button_query_array[i] == 1) {
                        button_condi[i] = DBLPRESS;
                        condi_time[i].dblpress = 0;
                    } else {
                        button_condi[i] = FREE;
                        button_act[i] = CLICK;
                    }
                }
                break;
            case DBLPRESS:
                condi_time[i].dblpress += TIME_TURN_QUERY;
                if (button_query_array[i] == 0) {
                    button_condi[i] = FREE;
                    button_act[i] = DBLCLICK;
                }
                break;
        }
    }
    // 执行事件回调
    for (uint8_t i = 0; i < MAX_BUTTON_NUM; i++) {
        if (button_act[i] != NONE) {
            (*(button_event_func[i][button_act[i]]))();
            button_act[i] = NONE;
        }
    }
}
