/**
 * ************************************************************************
 * @file interaction.h
 * @author Thybing (yanbinghao86@gmail.com)
 * @brief 交互模块，通过回调函数对输入进行处理。
 * @version 1.0.0
 * @date 2024-8-11
 * ************************************************************************
 */
#ifndef _MENU_NEST_INTERACTION_H_
#define _MENU_NEST_INTERACTION_H_
#include "stdint.h"

/**
 * ************************************************************************
 * @brief 输入类型
 * ************************************************************************
 */
typedef uint32_t input_t;

struct MN_interaction;//前向声明
/**
 * ************************************************************************
 * @brief 交互处理回调函数类型
 * @note  需要struct MN_interaction的前向声明 
 * ************************************************************************
 */
typedef void (* handle_callback_t)(struct MN_interaction * const,const input_t);

/**
 * ************************************************************************
 * @brief 交互模块
 * ************************************************************************
 */
typedef struct MN_interaction
{
    /// @brief 交互处理回调函数
    handle_callback_t m_handle_callback;
    /// @brief 可操作内存
    void * mp_op_memory;
}MN_interaction;

/**
 * ************************************************************************
 * @brief 构造一个交互模块对象并返回
 * 
 * @param[in] p_op_memory   构造时传入可被交互模块操作的内存空间
 * 
 * @return  申请的交互模块对象
 * ************************************************************************
 */
MN_interaction * MN_create_interaction(void * const p_op_memory);

/**
 * ************************************************************************
 * @brief 析构交互模块
 * 
 * @param[in] self 指向调用对象
 * 
 * @warning 请在析构后将对象指针置空，避免出现悬挂指针
 * ************************************************************************
 */
void MN_destroy_interaction(MN_interaction * const self);

/**
 * ************************************************************************
 * @brief 设置交互回调函数
 * 
 * @param[in] self  指向调用对象
 * @param[in] handle_callback  新的回调函数
 * 
 * ************************************************************************
 */
void MN_set_handle_callback(MN_interaction * const self,const handle_callback_t handle_callback);

/**
 * ************************************************************************
 * @brief  处理输入
 * 
 * @param[in] self  指向调用对象
 * @param[in] input  输入
 * 
 * ************************************************************************
 */
void MN_handle_input(MN_interaction * const self,const input_t input);

#endif //_MENU_NEST_INTERACTION_H_
