#ifndef PAGE_BASE_H
#define PAGE_BASE_H

#include "menu_nest/menu.h"
#include "menu_nest_tiny/display.h"

// 一个简单的页面类型，用于显示标题和item，内部的memory存储了一个候选的item索引
/* 
 * 页面的渲染方式是显示标题，然后依次向下调用item的渲染函数，
 *
 * 需要item的渲染函数适配于page_base页面
 * 向每个item的render的回调函数中第二个参数会传入屏幕中已经使用的像素行数，
 * 并且要求这些item的render回调函数只会占用一个CHAR_HEIGHT的高度。
 * 
*/

// 配置是否使用小动画
#define PAGE_BASE_USING_TINY_ANIMATION 1

// 对外接口，创建一个page_base页面
// 强烈建议title为常量字符串
MN_page * create_base_page(const char * const page_title);

#endif // PAGE_BASE_H
