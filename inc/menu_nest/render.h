/**
 * ************************************************************************
 * @file render.h
 * @author Thybing (yanbinghao86@gmail.com)
 * @brief 菜单的渲染模块，通过回调函数进行渲染。
 * @version 1.0.0
 * @date 2024-8-13
 * ************************************************************************
 */
#ifndef _MENU_NEST_RENDER_H_
#define _MENU_NEST_RENDER_H_

struct MN_render; // 前向声明

/**
 * ************************************************************************
 * @brief 渲染回调函数类型定义
 * ************************************************************************
 */
typedef void (* rendering_callback_t)(struct MN_render * const, void *);

/**
 * ************************************************************************
 * @brief 渲染模块
 * ************************************************************************
 */
typedef struct MN_render{
    /// @brief 渲染回调函数
    rendering_callback_t m_rendering_callback;

    /// @brief 需要渲染的信息，一般为持有此渲染模块的对象
    void * mp_memory;

    /// @brief 渲染模块自身属性内存，扩展用
    void * mp_attribute;
}MN_render;

/**
 * ************************************************************************
 * @brief 构造一个渲染模块
 * 
 * @param[in] p_memory  需要渲染的信息
 * 
 * @return 新构造的渲染模块
 * ************************************************************************
 */
MN_render * MN_render_create(void * const p_memory);

/**
 * ************************************************************************
 * @brief 销毁一个渲染模块
 * 
 * @param[in] self  指向渲染模块自身
 * 
 * ************************************************************************
 */
void MN_render_destroy(MN_render * const self);

/**
 * ************************************************************************
 * @brief 设置渲染回调函数
 * 
 * @param[in] self  指向渲染模块自身
 * @param[in] callback  渲染回调函数
 * 
 * ************************************************************************
 */
void MN_render_set_rendering_callback(MN_render * const self,const rendering_callback_t callback);

/**
 * ************************************************************************
 * @brief 设置渲染器属性
 * 
 * @param[in] self  指向渲染模块自身
 * @param[in] p_attribute  渲染器属性
 * 
 * ************************************************************************
 */
void MN_render_set_attribute(MN_render * const self,void * const p_attribute);

/**
 * ************************************************************************
 * @brief 获取渲染器属性
 * 
 * @param[in] self  指向渲染模块自身
 * 
 * @return 渲染器属性指针
 * ************************************************************************
 */
void * MN_render_get_attribute(MN_render * const self);

/**
 * ************************************************************************
 * @brief 开始渲染
 * 
 * @param[in] self  指向渲染模块自身
 * @param[in] p_render_param  渲染时所需要的参数
 * ************************************************************************
 */
void MN_render_rendering(MN_render * const self, void * const p_render_param);

#endif //_MENU_NEST_RENDER_H_