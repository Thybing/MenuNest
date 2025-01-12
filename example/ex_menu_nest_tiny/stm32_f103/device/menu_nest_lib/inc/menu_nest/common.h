/**
 * ************************************************************************
 * @file common.h
 * @author Thybing (yanbinghao86@gmail.com)
 * @brief 宏定义、配置选项等。
 * @version 1.0.0
 * @date 2024-12-7
 * ************************************************************************
 */

#ifndef _MENU_NEST_COMMON_H_
#define _MENU_NEST_COMMON_H_

#include "stdint.h"
#include "stdbool.h"

#include "menu_nest/heap.h"

#define MN_PAGE_MAX_NUM 16
#define MN_HISTORY_PAGE_MAX 16
#define MN_INPUT_QUEUE_MAX 16

#define MN_assert(x) if(!(x)) {while(1);}

#define MN_malloc(x) MN_heap_malloc(x);
#define MN_free(x) MN_heap_free(x)

#endif //_MENU_NEST_COMMON_H_
