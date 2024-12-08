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

typedef void * ((*MN_item_action_t)(struct MN_item * const,void *)) ;

/**
 * ************************************************************************
 * @brief 物体对象
 * ************************************************************************
 */
typedef struct MN_item
{
    /// @brief 物体名称
    const char * m_name;

    /// @brief 交互模块
    MN_interaction * mp_interaction;

    /// @brief 渲染/显示模块
    MN_render * mp_render;

    /// @brief 在被选中时调用
    MN_item_action_t mp_on_select;

    /// @brief 在取消选中时调用
    MN_item_action_t mp_on_unselect;

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
 * @warning 请在销毁后将对象指针置空，避免悬空指针
 * ************************************************************************
 */
void MN_item_destroy(MN_item * const self);

#endif //_MENU_NEST_ITEM_H_