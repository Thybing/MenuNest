/**
 * ****************************************************************
 * @file button.h
 * @auther: Thybing
 * @brief 按键驱动头文件
 * @version 1.0.0
 * @date 2024-04-01
 * ****************************************************************
 */
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "stdbool.h"
#include "stddef.h"
#include "stdint.h"

// 按键事件类型
typedef enum BUTTON_ACT {
    CLICK = 0,   // 单击
    LONG_TOUCH,  // 长按
    DBLCLICK,    // 双击

    // NONE为内部使用，请勿使用
    NONE = -1
} BUTTON_ACT;

/**
 * @brief 按键询问回调函数类型

 * @return uint8_t 按键状态,按下返回1,未按下返回0

 * @example
 * uint8_t button_0_query_func(){
 *    return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
 * }
 *
 */
typedef uint8_t (*button_query_func_callback_t)();

/**
 * @brief 按键事件回调函数类型

 * @example
 * void button_0_event_func(){
 *    // do something
 * }
 *
 */
typedef void (*button_event_func_callback_t)();

/**
 * @brief 按键初始化函数，要在以下所有函数使用前调用
 */
void button_init();

/**
 * @brief 设置按键的询问函数
 *
 * @param[in] i_button 按键编号
 * @param[in] i_button_query_func 按键询问函数，参见 button_query_func_callback_t
 *
 * @example
 * set_button_query_func(0, button_0_query_func);
 */
void set_button_query_func(uint8_t i_button, button_query_func_callback_t i_button_query_func);

/**
 * @brief 设置按键的询问结果数组
 * 
 * 可以直接设置按键询问结果的数组,代替询问函数的结果(等价于设置了所有的询问函数的为返回数组的对应位数)。
 * 设为NULL时启用询问函数(默认初始化中已经包含)，是为了简化使用矩阵按键等无法直接使用获取电平的函数的情况。
 * 
 * @param[in] i_button_query_array 按键询问结果数组
 * 
 * @warning 请保证数组长度大于按键数量,并且数组的生命周期大于按键的生命周期。
 * 
 * @example 
 * // 例如这是一个矩阵按键的询问结果数组，你需要自行在定时器中更新该数组，并且保证每个数字的更新频率为 TIME_TURN_QUERY ms
 * uint8_t button_query_array[16];
 * set_button_query_array(button_query_array);
 */
void set_button_query_array(uint8_t* i_button_query_array);

/**
 * @brief 设置按键的事件函数
 * 
 * @param[in] i_button 按键编号
 * @param[in] i_button_act 按键事件类型
 * @param[in] i_button_event_func 按键事件函数，参见 button_event_func_callback_t
 * 
 * @example
 * set_button_event_func(0, CLICK, button_0_event_func);
 */
void set_button_event_func(uint8_t i_button, BUTTON_ACT i_button_act, button_event_func_callback_t i_button_event_func);

/**
 * @brief 按键轮询函数
 * 
 * 请将该函数放入定时器中,每 TIME_TURN_QUERY ms 执行一次
 */
void button_turn_query();

#endif  //__BUTTON_H__
