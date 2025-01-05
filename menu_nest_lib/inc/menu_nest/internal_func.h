/**
 * ************************************************************************
 * @file internal_func.h
 * @author Thybing
 * @brief  该头文件包含MenuNest库的内部函数声明，
 * @note   用于该库内部的c文件进行include，不建议用户直接调用这些函数，否则可能会跳过已经设计好的核心流程造成回调不触发，也不建议include此头文件。
 * @version 1.0.0
 * @date 2025-01-06
 * ************************************************************************
 */
#ifndef MENU_NEST_INTERNAL_FUNC_H
#define MENU_NEST_INTERNAL_FUNC_H

#include "menu_nest/item.h"
#include "menu_nest/render.h"
#include "menu_nest/interaction.h"


/**
 * ************************************************************************
 * @brief 物体对象进入选中状态(已经选中的物体对象再次调用时无效)
 * @internal  仅供内部调用
 * 
 * @param[in] self  指向要选择的物体对象
 * 
 * @return 选择物体对象时调用的回调函数on_select的返回值
 * ************************************************************************
 */
void * MN_item_select(MN_item * const self);


/**
 * ************************************************************************
 * @brief 物体对象取消选中状态(没有被选中的物体调用无效)
 * @internal  仅供内部调用
 * 
 * @param[in] self  指向要取消选择的物体对象
 * 
 * @return 取消选择物体对象时调用的回调函数on_unselect返回值
 * ************************************************************************
 */
void * MN_item_unselect(MN_item * const self);


/**
 * ************************************************************************
 * @brief  处理输入
 * @internal  仅供内部调用
 * 
 * @param[in] self  指向调用对象
 * @param[in] input  输入
 * 
 * @return 输入模块是否捕获此输入，捕获返回true，否则返回false
 * ************************************************************************
 */
bool MN_interaction_handle_input(MN_interaction * const self,const input_t input);

/**
 * ************************************************************************
 * @brief 开始渲染
 * @internal  仅供内部调用
 * 
 * @param[in] self  指向渲染模块自身
 * @param[in] p_render_param  渲染时所需要的参数
 * ************************************************************************
 */
void MN_render_rendering(MN_render * const self, void * const p_render_param);

#endif // MENU_NEST_INTERNAL_FUNC_H
