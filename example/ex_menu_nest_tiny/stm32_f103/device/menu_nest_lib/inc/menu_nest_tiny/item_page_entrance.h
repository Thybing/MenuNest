#ifndef ITEM_PAGE_ENTRANCE_H
#define ITEM_PAGE_ENTRANCE_H

#include "menu_nest/menu.h"

// 创建一个页面入口，此item的渲染函数适配于page_base类型的页面，内部的渲染回调函数适配page_base页面
MN_item * create_item_page_entrance(const char * const item_name, MN_page * p_target_page);

#endif // ITEM_PAGE_ENTRANCE_H
