#ifndef ITEM_AUTO_VARIABLE_H
#define ITEM_AUTO_VARIABLE_H

#include "menu_nest/menu.h"
#include "menu_nest_tiny/item_static_variable.h"

// 自动变量(局部变量)的item，用于在页面中显示自动变量的值。实际上是对静态变量item的封装。
// 目的是用于调试，无需将变量声明成全局的变量，查看自动变量的值。必要时可以修改自动变量的值。类似一个探针。
// 调试使用，不建议大量使用，因为查找需要耗费时间，并且无法直接在菜单上进行修改，需要拷贝，如果需要长期使用请直接使用静态变量。

// 另外，下面的get和refresh函数，理论上对于一个变量只会使用其中的一个，不会同时使用两个。
// get用来临时的调整变量的值，refresh用来更新变量的值到菜单中。

// 再次强调，这个功能一般是用于调试的。

// 创建一个自动变量item，传入的参数是自动变量的地址及其类型。
MN_item * create_item_auto_variable(const char * const item_name, void * p_auto_var, enum basic_type var_type);

// 通过页面标题和item名字获取item的自动变量的拷贝的指针，获取的是菜单中的拷贝值如果需要使用则要将返回值拷贝回原变量。
// 目的是用来调试，简单的修改临时变量的值。
const void * get_item_auto_variable_ptr(const char * const page_title, const char * const item_name);

// 更新自动变量的值到菜单中，传入的参数是页面标题，item名字，自动变量的地址及其类型。
// 目的是用来调试，将自动变量的值更新到菜单中，方便查看。
void refresh_item_auto_variable(const char * const page_title, const char * const item_name, const void * const p_var , enum basic_type var_type);

#endif // ITEM_AUTO_VARIABLE_H
