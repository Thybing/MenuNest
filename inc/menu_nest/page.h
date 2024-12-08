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

struct MN_page;

typedef void * ((*MN_page_action_callback_t)(MN_page * const,void *)) ;

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
    int32_t m_cur_item_index;

    /// @brief 物体对象的数量
    uint32_t m_item_num;

    /// @brief 物体对象的最大数量
    uint32_t m_item_max_num;

    /// @brief 交互模块
    MN_interaction * mp_interaction;

    /// @brief 渲染/显示模块
    MN_render * mp_render;

    /// @brief 在进入时调用
    MN_page_action_callback_t mp_on_forward;

    /// @brief 在返回时调用
    MN_page_action_callback_t mp_on_back;
} MN_page;

/**
 * ************************************************************************
 * @brief 创建一个页面对象（如果存在相同标题则直接返回存在的页面）
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
 * @param[in] p_item  要添加的物体对象
 * 
 * @note 如果添加的物体的name已经在该页面中添加过，那么本次添加无效。
 * ************************************************************************
 */
void MN_page_add_item(MN_page * const self, MN_item * const p_item);


/**
 * ************************************************************************
 * @brief 在页面中以物体名寻找物体
 * 
 * @param[in] self  指向页面对象
 * @param[in] item_name  要寻找的物体名
 * 
 * @note 如果添加的物体的name已经在该页面中添加过，那么本次添加无效。
 * ************************************************************************
 */
MN_item * MN_page_find_item(MN_page * const self, const char * const item_name);


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
MN_item * MN_page_select_item(MN_page * const self, const int32_t index);

/**
 * ************************************************************************
 * @brief 通过物体名称选择物体对象
 * 
 * @param[in] self  指向页面对象
 * @param[in] item_name  要选择的物体对象的名称。(超出有效范围算作取消选择)
 * 
 * @return 选择的物体对象指针(取消选择返回NULL)
 * ************************************************************************
 */
MN_item * MN_page_select_item_name(MN_page * const self, const char * item_name);

/**
 * ************************************************************************
 * @brief 通过标题title查找页面
 * 
 * @param[in] title 要查找的标题
 * 
 * @return 查找到的页面的指针（如果没有查找到则返回NULL）
 * ************************************************************************
 */
MN_page * MN_find_page(const char * const title);

#endif //_MENU_NEST_PAGE_H_
