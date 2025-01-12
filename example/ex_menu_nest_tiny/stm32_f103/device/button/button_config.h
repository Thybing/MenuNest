#ifndef __BUTTON_CONFIG_H__
#define __BUTTON_CONFIG_H__

#include "stdint.h"

// 如果使用keil，build有可能检测不到宏定义的改动，如果配置改动无效可能需要rebuild

/**
 * ****************************************************************
 * 按键的数量，用户根据实际情况修改 
 * ****************************************************************
 */
#define MAX_BUTTON_NUM (5)

/**
 * ****************************************************************
 * 以下为按键的两个可选项，用户根据实际情况修改 
 * ****************************************************************
 */
// 长按是否需要松开后再触发
#define LONG_TOUCH_NEED_RELEASE (0)  

// 长按是否可以重复触发，需要LONG_TOUCH_NEED_RELEASE为0作为前提
#define LONG_TOUCH_CAN_REPEAT (1)    

/**
 * ****************************************************************
 * 以下为按键相关的时间配置，用户根据实际情况修改 
 * ****************************************************************
 */

// 每一次轮询的时间间隔
static const uint16_t TIME_TURN_QUERY = (10);

// 按键消抖时间，检测到按键后等待一段时间再认为按键有效，作用在按键第一次按下和第一次松开，以及双击的第一次按下时
static const uint16_t TIME_JITTER = (20);

// 长按时间，按键按下超过这个时间认为是长按
static const uint16_t TIME_LONG_TOUCH = (400);

#if !LONG_TOUCH_NEED_RELEASE && LONG_TOUCH_CAN_REPEAT
// 长按重复触发时间，长按后每隔这个时间触发一次长按事件
static const uint16_t TIME_LONG_TOUCH_REPEAT = (500);
#endif

// 双击等待时间，两次按键按下的时间间隔小于这个时间认为是双击
static const uint16_t TIME_WAIT_DBLCLICK = (200);

#endif // __BUTTON_CONFIG_H__
