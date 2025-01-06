#ifndef ITEM_CSTR_H
#define ITEM_CSTR_H

#include "menu_nest/menu.h"

// 创建一个字符串item，传入的参数是字符串的地址。内部回调函数符合page_base的要求。
MN_item * create_cstr_item(const char * const item_name,char * cstr);

#endif // ITEM_CSTR_H
