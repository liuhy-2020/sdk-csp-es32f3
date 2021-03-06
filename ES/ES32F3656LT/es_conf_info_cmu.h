/*
 * Copyright (C) 2021 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 */

#ifndef __ES_CONF_INFO_CMU_H__
#define __ES_CONF_INFO_CMU_H__


#include <ald_cmu.h> 
#include "board.h"


/* 时钟树 配置 */

#define   ES_C_MUL_9          CMU_PLL1_OUTPUT_36M
#define   ES_C_MUL_12         CMU_PLL1_OUTPUT_48M
#define   ES_C_MUL_18         CMU_PLL1_OUTPUT_72M
#define   ES_C_MUL_24         CMU_PLL1_OUTPUT_96M 

#define  ES_C_DIV_1          CMU_DIV_1  
#define  ES_C_DIV_2          CMU_DIV_2 
#define  ES_C_DIV_4          CMU_DIV_4 
#define  ES_C_DIV_8          CMU_DIV_8 
#define  ES_C_DIV_16          CMU_DIV_16 
#define  ES_C_DIV_32          CMU_DIV_32 
#define  ES_C_DIV_64          CMU_DIV_64 
#define  ES_C_DIV_128          CMU_DIV_128 
#define  ES_C_DIV_256          CMU_DIV_256 
#define  ES_C_DIV_512          CMU_DIV_512 
#define  ES_C_DIV_1024          CMU_DIV_1024 
#define  ES_C_DIV_2048          CMU_DIV_2048 
#define  ES_C_DIV_4096          CMU_DIV_4096 

#define  ES_C_HOSC_DIV_1        CMU_PLL1_INPUT_HOSC
#define  ES_C_HOSC_DIV_2        CMU_PLL1_INPUT_HOSC_2
#define  ES_C_HOSC_DIV_3        CMU_PLL1_INPUT_HOSC_3
#define  ES_C_HOSC_DIV_4        CMU_PLL1_INPUT_HOSC_4
#define  ES_C_HOSC_DIV_5        CMU_PLL1_INPUT_HOSC_5
#define  ES_C_HOSC_DIV_6        CMU_PLL1_INPUT_HOSC_6
#define  ES_C_HRC_DIV_6         CMU_PLL1_INPUT_HRC_6





#define   ES_PLL1_REFER_CLK           ES_C_HOSC_DIV_3
#define   ES_PLL1_OUT_CLK             ES_C_MUL_18
#define   ES_CMU_PLL1_EN              ES_C_ENABLE
#define   ES_CMU_PLL1_SAFE_EN         ES_C_DISABLE
#define   ES_CMU_LOSC_EN              ES_C_ENABLE
#define   ES_CMU_LRC_EN               ES_C_ENABLE
#define   ES_CMU_HOSC_EN              ES_C_ENABLE
#define   ES_CMU_HRC_EN               ES_C_ENABLE
#define   ES_CMU_SYS_DIV              ES_C_DIV_1
#define   ES_CMU_HCLK_1_DIV           ES_C_DIV_2
#define   ES_CMU_HCLK_2_DIV           ES_C_DIV_2
#define   ES_CMU_PCLK_1_DIV           ES_C_DIV_2
#define   ES_CMU_PCLK_2_DIV           ES_C_DIV_4
#define   ES_SYS_CLK_SOURSE           CMU_CLOCK_PLL1
#define   ES_PLL_CLK                  72000000
#define   ES_SYS_SOURCE_CLK           72000000
#define   ES_SYS_CLK                  72000000
#define   ES_PCLK1_CLK                36000000
#define   ES_PCLK2_CLK                18000000
#define   ES_HCLK1_CLK                36000000
#define   ES_HCLK2_CLK                36000000
#define   ES_CMU_EXTERN_CLK_LOSC      32768
#define   ES_CMU_EXTERN_CLK_HOSC      12000000



#endif
