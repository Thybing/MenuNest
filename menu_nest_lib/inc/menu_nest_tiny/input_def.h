#ifndef MENU_NEST_TINY_INPUT_DEF_H
#define MENU_NEST_TINY_INPUT_DEF_H

#include "menu_nest/interaction.h"

// 当按键被触发时，应该向菜单中添加输入事件。 例如: MN_menu_input(BUTTON_0_CLICK);

#define BUTTON_0_CLICK (input_t)0x0
#define BUTTON_1_CLICK (input_t)0x1
#define BUTTON_2_CLICK (input_t)0x2
#define BUTTON_3_CLICK (input_t)0x3

#define BUTTON_0_LONG_PRESS (input_t)0x10
#define BUTTON_1_LONG_PRESS (input_t)0x11
// #define BUTTON_2_LONG_PRESS (input_t)0x12
// #define BUTTON_3_LONG_PRESS (input_t)0x13

// #define BUTTON_0_DOUBLE_CLICK (input_t)0x20
// #define BUTTON_1_DOUBLE_CLICK (input_t)0x21
// #define BUTTON_2_DOUBLE_CLICK (input_t)0x22
// #define BUTTON_3_DOUBLE_CLICK (input_t)0x23

#endif // MENU_NEST_TINY_INPUT_DEF_H
