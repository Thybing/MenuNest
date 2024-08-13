#ifndef _MENU_NEST_PAGE_H_
#define _MENU_NEST_PAGE_H_

#include "menu_nest/item.h"
#include "menu_nest/interaction.h"

struct MN_page; // 前向声明

/**
 * ************************************************************************
 * @brief 页面显示回调函数类型定义
 * ************************************************************************
 */
typedef void (*page_display_callback_t)(struct MN_page * const);

/**
 * ************************************************************************
 * @brief 页面对象结构体
 * ************************************************************************
 */
typedef struct MN_page
{
    /// @brief 物体对象指针数组
    MN_item ** m_items;

    /// @brief 当前物体对象指针
    MN_item * m_current_item;

    /// @brief 物体对象的数量
    uint32_t m_item_count;

    /// @brief 物体对象的最大数量
    uint32_t m_item_count;

    /// @brief 页面显示回调函数
    page_display_callback_t m_display_callback;

    /// @brief 交互模块
    MN_interaction * mp_interaction;
} MN_page;

/**
 * ************************************************************************
 * @brief 创建一个页面对象
 * 
 * @param[in] max_items 最大物体对象数量
 * 
 * @return  创建的页面对象指针
 * ************************************************************************
 */
MN_page * MN_page_create(const uint32_t max_items);

/**
 * ************************************************************************
 * @brief 销毁页面对象
 * 
 * @param[in] self 指向要销毁的页面对象
 * 
 * @warning 请在销毁后将对象指针置空，避免悬空指针
 * ************************************************************************
 */
void MN_page_destroy(MN_page * const self);

/**
 * ************************************************************************
 * @brief 添加物体对象到页面
 * 
 * @param[in] self  指向页面对象
 * @param[in] item  要添加的物体对象
 * 
 * @return 是否成功添加
 * ************************************************************************
 */
bool MN_page_add_item(MN_page * const self, MN_item * const item);

/**
 * ************************************************************************
 * @brief 设置页面显示回调函数
 * 
 * @param[in] self  指向页面对象
 * @param[in] display_callback 页面显示回调函数
 * 
 * ************************************************************************
 */
void MN_page_set_display_callback(MN_page * const self, const page_display_callback_t callback);

/**
 * ************************************************************************
 * @brief 刷新页面显示
 * 
 * @param[in] self  指向页面对象
 * 
 * ************************************************************************
 */
void MN_page_refresh_display(MN_page * const self);

#endif //_MENU_NEST_PAGE_H_
