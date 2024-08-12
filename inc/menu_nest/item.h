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

struct MN_item; //前向声明
/**
 * ************************************************************************
 * @brief 显示回调函数类型定义
 * ************************************************************************
 */
typedef void (* item_display_callback_t)(struct MN_item * const);

/**
 * ************************************************************************
 * @brief 物体对象
 * ************************************************************************
 */
typedef struct MN_item
{
    /// @brief 交互模块
    MN_interaction * mp_interaction;

    /// @brief 显示回调函数
    item_display_callback_t m_display_callback;

    /// @brief 指向内存空间的指针，指向不同的类型的内存生成不同的物体对象
    void * mp_memory;
} MN_item;

/**
 * ************************************************************************
 * @brief 创建一个物体对象
 * 
 * @param[in] p_memory  指向分配给对象的内存空间
 * 
 * @return  创建的物体对象指针
 * ************************************************************************
 */
MN_item * MN_item_create(void * const p_memory);

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

/**
 * ************************************************************************
 * @brief 设置显示回调函数
 * 
 * @param[in] self  指向物体对象
 * @param[in] display_callback 显示回调函数
 * 
 * ************************************************************************
 */
void MN_item_set_display_callback(MN_item * const self, const item_display_callback_t callback);

/**
 * ************************************************************************
 * @brief 设置交互处理回调函数
 * 
 * @param[in] self  指向物体对象
 * @param[in] handle_callback  交互处理回调函数
 * 
 * ************************************************************************
 */
void MN_item_set_handle_callback(MN_item * const self, const handle_callback_t callback);

/**
 * ************************************************************************
 * @brief 刷新显示
 * 
 * @param[in] self  指向物体对象
 * 
 * ************************************************************************
 */
void MN_item_refresh_display(MN_item * const self);

#endif //_MENU_NEST_ITEM_H_