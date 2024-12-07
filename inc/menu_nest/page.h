/**
 * ************************************************************************
 * @file page.h
 * @author Thybing (yanbinghao86@gmail.com)
 * @brief 菜单的页面对象
 * @version 1.0.0
 * @date 2024-8-12
 * ************************************************************************
 */
#ifndef _MENU_NEST_PAGE_H_
#define _MENU_NEST_PAGE_H_

#include "menu_nest/item.h"
#include "menu_nest/interaction.h"

#define MN_CONFIG_PAGE_TITLE_MAX_LEN 32

/**
 * ************************************************************************
 * @brief 页面对象结构体
 * ************************************************************************
 */
typedef struct MN_page
{
    /// @brief 页面的标题
    char * m_title;

    /// @brief 物体对象指针数组
    MN_item ** mpp_items;

    /// @brief 当前物体对象下标，-1表示未选择
    int32_t m_current_index;

    /// @brief 物体对象的数量
    uint32_t m_item_count;

    /// @brief 物体对象的最大数量
    uint32_t m_item_max;

    /// @brief 交互模块
    MN_interaction * mp_interaction;

    /// @brief 渲染/显示模块
    MN_render * mp_render;
} MN_page;

/**
 * ************************************************************************
 * @brief 创建一个页面对象
 * 
 * @param[in] title 页面的标题
 * @param[in] max_items 最大物体对象数量
 * 
 * @return  创建的页面对象指针
 * ************************************************************************
 */
MN_page * MN_page_create(const char * const title, const uint32_t max_items);

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
 * ************************************************************************
 */
void MN_page_add_item(MN_page * const self, MN_item * const item);


/**
 * ************************************************************************
 * @brief 选择页面中的物体对象
 * 
 * @param[in] self  指向页面对象
 * @param[in] index  要选择的物体对象的下标。(超出有效范围算作取消选择)
 * 
 * @return 选择的物体对象指针(取消选择返回NULL)
 * ************************************************************************
 */
MN_item * MN_page_select_item(MN_page * const self,const int32_t index);

#endif //_MENU_NEST_PAGE_H_
