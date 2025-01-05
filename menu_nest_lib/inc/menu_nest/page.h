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

struct MN_page; // 前向声明

/// @brief 页面对象的回调函数类型
typedef void * ((*MN_page_action_callback_t)(struct MN_page * const,void *)) ;

/**
 * ************************************************************************
 * @brief 页面对象结构体
 * @note 会以[get,set]标注用户的直接读写权限，没有标注为的成员变量为内部使用，不建议用户直接操作
 * ************************************************************************
 */
typedef struct MN_page
{
    /// @brief 页面的标题
    /// @note  [get] 页面的标题，建议使用静态字符串，set应该在MN_page_create时一并设置
    const char * m_title;

    /// @brief 物体对象指针数组
    /// @note  [get] 用户可以访问到物体对象指针数组，不建议用户进行set操作，set请用MN_page_add_item
    MN_item ** mpp_items;

    /// @brief 当前物体对象下标，-1表示未选择
    /// @note  [get] 用户可以访问到当前物体对象下标，由MN_page_select_item和MN_page_unselect_item维护
    int32_t m_cur_item_index;

    /// @brief 物体对象的数量
    /// @note  [get] 用户可以访问到物体对象的数量，不建议用户进行set操作，其值由MN_page_add_item维护
    uint32_t m_item_num;

    /// @brief 物体对象的最大数量
    /// @note  [get] 用户可以访问到物体对象的最大数量，不建议用户进行set操作，其值由MN_page_create设置
    uint32_t m_item_max_num;

    /// @brief 交互模块
    /// @note  [get] 用户可以访问到交互模块，不建议用户进行set操作，MN_page_create时自动生成
    MN_interaction * mp_interaction;

    /// @brief 渲染/显示模块
    /// @note  [get] 用户可以访问到显示模块，不建议用户进行set操作，MN_page_create时自动生成
    MN_render * mp_render;

    /// @brief 在进入本页面时调用
    /// @note  [get,set] 用户可以自定义回调函数并设置
    MN_page_action_callback_t mp_on_forward;

    /// @brief 在返回上个页面时调用
    /// @note  [get,set] 用户可以自定义回调函数并设置
    MN_page_action_callback_t mp_on_retreat;

    /// @brief 在从本页面前往其他页面时调用
    /// @note  [get,set] 用户可以自定义回调函数并设置
    MN_page_action_callback_t mp_on_forward_to_other_page;

    /// @brief 在从其他页面返回至本页面时调用
    /// @note  [get,set] 用户可以自定义回调函数并设置
    MN_page_action_callback_t mp_on_retreat_from_other_page;

    /// @brief 在选中物体时调用
    /// @note  [get,set] 用户可以自定义回调函数并设置
    MN_page_action_callback_t mp_on_select_item;

    /// @brief 在取消选中物体时调用
    /// @note  [get,set] 用户可以自定义回调函数并设置
    MN_page_action_callback_t mp_on_unselect_item;

    /// @brief 页面的内存，作为拓展使用
    /// @note  [get,set] 用户可以自定义拓展用内存空间并访问和设置
    void * mp_memory;
} MN_page;

/**
 * ************************************************************************
 * @brief 创建一个页面对象（如果存在相同标题则直接返回存在的页面）
 * 
 * @param[in] title 页面的标题，请用静态字符串
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
 * @brief 在页面中以物体名寻找物体，找到返回物体指针，找不到返回NULL
 * 
 * @param[in] self  指向页面对象
 * @param[in] item_name  要寻找的物体名
 * 
 * ************************************************************************
 */
MN_item * MN_page_find_item(MN_page * const self, const char * const item_name);


/**
 * ************************************************************************
 * @brief 选择页面中的物体对象
 * 
 * @param[in] self  指向页面对象
 * @param[in] index  要选择的物体对象的下标。(超出有效范围或者已经选中时无效)
 * 
 * @details 先对选中物体调用MN_item_select，然后调用页面的on_select_item回调函数。(如果之前有选中物体，会先取消选中)
 * @return 调用页面的on_select_item回调函数的返回值
 * ************************************************************************
 */
void * MN_page_select_item(MN_page * const self, const int32_t index);

/**
 * ************************************************************************
 * @brief 通过物体名称选择物体对象
 * 
 * @param[in] self  指向页面对象
 * @param[in] item_name  要选择的物体对象的名称。
 * 
 * @return 返回等价的MN_page_select_item的返回值
 * ************************************************************************
 */
void * MN_page_select_item_by_name(MN_page * const self, const char * item_name);

/**
 * ************************************************************************
 * @brief 取消选择页面中的物体对象
 * 
 * @param[in] self  指向页面对象
 * 
 * @details 先对选中物体调用MN_item_unselect，然后调用页面的on_unselect_item回调函数
 * @return 选择物体对象时调用页面的on_unselect_item回调函数的返回值
 * ************************************************************************
 */
void * MN_page_unselect_item(MN_page * const self);

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
