#ifndef PAGE_HIBERNATE_H
#define PAGE_HIBERNATE_H

#include "menu_nest/menu.h"

// 创建一个休眠页面。其实是一个没有任何item的页面。并且其渲染函数是空函数，交互函数仅有退出休眠的功能。
// on_forward_callback是进入休眠页面时的回调函数。例如可以在回调函数中清屏，显示休眠字样等。
// 并且有一个默认的休眠页面，可以直接调用into_hibernate_page(NULL)进入默认的休眠页面。
MN_page * create_page_hibernate(const char * const title, MN_page_action_callback_t on_forward_callback);

// 进入休眠页面，传入NULL会进入默认的休眠页面。可以使用find_page函数找到自己创建的休眠页面。
void into_hibernate_page(MN_page * p_page);

#endif // PAGE_HIBERNATE_H
