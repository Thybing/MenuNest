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
#include "assert.h"
#include "stdlib.h"

#define DEBUG

#define MN_PAGE_MAX_NUM 16
#define MN_HISTORY_PAGE_MAX 16
#define MN_INPUT_QUEUE_MAX 16

#ifdef DEBUG
#define MN_assert(x) assert(x);
#else
#define MN_assert(x) 
#endif

#define MN_malloc(x) malloc(x);
#define MN_free(x) free(x)


#endif //_MENU_NEST_COMMON_H_
