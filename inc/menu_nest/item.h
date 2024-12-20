/**
 * ************************************************************************
 * @file item.h
 * @author Thybing (yanbinghao86@gmail.com)
 * @brief 菜单的物体对象
 * @version 1.0.0
 * @date 2024-8-12
 * ************************************************************************
 */
#ifndef _MENU_NEST_ITEM_H_
#define _MENU_NEST_ITEM_H_

#include "stdint.h"
#include "menu_nest/interaction.h"
#include "menu_nest/render.h"

struct MN_item;

typedef void * ((*MN_item_on_select_callback_t)(struct MN_item * const)) ;
typedef void * ((*MN_item_on_unselect_callback_t)(struct MN_item * const)) ;

/**
 * ************************************************************************
 * @brief 物体对象
 * ************************************************************************
 */
typedef struct MN_item
{
    /// @brief 物体名称
    const char * m_name;

    /// @brief 是否处于选中状态中的标志位
    bool m_select_flag;

    /// @brief 交互模块
    MN_interaction * mp_interaction;

    /// @brief 渲染模块
    MN_render * mp_render;

    /// @brief 在被选中时调用的回调函数
    MN_item_on_select_callback_t mp_on_select;

    /// @brief 在取消选中时调用的回调函数
    MN_item_on_unselect_callback_t mp_on_unselect;

    /// @brief 指向内存空间的指针，指向不同的类型的内存生成不同的物体对象
    void * mp_memory;
} MN_item;

/**
 * ************************************************************************
 * @brief 创建一个物体对象
 * 
 * @param[in] name 物体的名称
 * @param[in] p_memory  指向分配给对象的内存空间
 * 
 * @return  创建的物体对象指针
 * ************************************************************************
 */
MN_item * MN_item_create(const char * const name, void * const p_memory);

/**
 * ************************************************************************
 * @brief 销毁物体对象
 * 
 * @param[in] self 指向要销毁的物体对象
 * 
 * ************************************************************************
 */
void MN_item_destroy(MN_item * const self);

/**
 * ************************************************************************
 * @brief 物体对象进入选中状态(已经选中的物体对象再次进入选中状态时不会调用回调函数)
 * 
 * @param[in] self  指向要选择的物体对象
 * 
 * @return 选择物体对象时调用的回调函数返回的指针
 * ************************************************************************
 */
void * MN_item_select(MN_item * const self);


/**
 * ************************************************************************
 * @brief 物体对象取消选中状态(已经取消选中的物体对象再次取消选中状态时不会调用回调函数)
 * 
 * @param[in] self  指向要取消选择的物体对象
 * 
 * @return 取消选择物体对象时调用的回调函数返回的指针
 * ************************************************************************
 */
void * MN_item_unselect(MN_item * const self);

#endif //_MENU_NEST_ITEM_H_