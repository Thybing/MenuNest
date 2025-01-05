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
 * @note  会以[get,set]标注用户的直接读写权限，没有标注为的成员变量为内部使用，不建议用户直接操作
 * ************************************************************************
 */
typedef struct MN_item
{
    /// @brief 物体名称
    /// @note  [get] 建议使用静态字符串，set操作应使用MN_item_create在创建时一并设置
    const char * m_name;

    /// @brief 是否处于选中状态中的标志位
    /// @note  internal 仅供内部调用
    bool m_select_flag;

    /// @brief 交互模块
    /// @note  [get] create时自动生成，不建议用户进行set操作
    MN_interaction * mp_interaction;

    /// @brief 渲染模块
    /// @note  [get] create时自动生成，不建议用户进行set操作
    MN_render * mp_render;

    /// @brief 在被选中时调用的回调函数
    /// @note  [get,set] 用户可以自定义回调函数并设置
    MN_item_on_select_callback_t mp_on_select;

    /// @brief 在取消选中时调用的回调函数
    /// @note  [get,set] 用户可以自定义回调函数并设置
    MN_item_on_unselect_callback_t mp_on_unselect;

    /// @brief 指向内存空间的指针，指向不同的类型的内存生成不同的物体对象
    /// @note  [get] 用户可以访问到内存空间，不建议用户进行set操作，set建议直接使用MN_item_create
    void * mp_memory;
} MN_item;

/**
 * ************************************************************************
 * @brief 创建一个物体对象
 * 
 * @param[in] name 物体的名称，建议使用静态字符串
 * @param[in] p_memory  物体对象所持有的实际物体
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

#endif //_MENU_NEST_ITEM_H_