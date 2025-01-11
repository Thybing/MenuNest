#ifndef MENU_NEST_TINY_INPUT_DEF_H
#define MENU_NEST_TINY_INPUT_DEF_H

#include "menu_nest/interaction.h"

/* 以下是menu_nest_tiny中使用的输入事件定义
 * 用户可以根据自己的需求或者更改更多的输入事件。
 * 按键事件会在menu_nest_tiny的各个c文件内转化各自的输入事件。
 * 所以如果要对按键事件进行更改，则也需要在menu_nest_tiny的c文件内进行更改,它们被定义在c文件的开头(如果有)。
 */

// 当按键被触发时，应该向菜单中添加输入事件。 例如: MN_menu_input(BUTTON_0_CLICK);

#define BUTTON_0_CLICK ((input_t)0x0)
#define BUTTON_1_CLICK ((input_t)0x1)
#define BUTTON_2_CLICK ((input_t)0x2)
#define BUTTON_3_CLICK ((input_t)0x3)

#define BUTTON_0_LONG_PRESS ((input_t)0x10)
#define BUTTON_1_LONG_PRESS ((input_t)0x11)

// 以上是目前在menu_nest_tiny中已经使用的输入事件。

#define BUTTON_2_LONG_PRESS ((input_t)0x12)
#define BUTTON_3_LONG_PRESS ((input_t)0x13)

#define BUTTON_0_DOUBLE_CLICK ((input_t)0x20)
#define BUTTON_1_DOUBLE_CLICK ((input_t)0x21)
#define BUTTON_2_DOUBLE_CLICK ((input_t)0x22)
#define BUTTON_3_DOUBLE_CLICK ((input_t)0x23)

#endif // MENU_NEST_TINY_INPUT_DEF_H
