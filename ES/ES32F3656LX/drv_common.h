/*
 * Copyright (C) 2021 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0 
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-04-20     liuhy         the first version
 */

#ifndef __DRV_COMMON_H__
#define __DRV_COMMON_H__


#ifdef ES32F36xx
#include <es32f36xx.h>
#define ES32F3_FLASH_SIZE    0x80000
#define ES32F3_FLASH_END     (0x00000000 + ES32F3_FLASH_SIZE)
#define ES32F3_SRAM_SIZE    0x10000
#define ES32F3_SRAM_END     (0x20000000 + ES32F3_SRAM_SIZE)
#endif

#if defined(__CC_ARM) || defined(__CLANG_ARM)
    extern int Image$$RW_IRAM1$$ZI$$Limit;
    #define HEAP_BEGIN  ((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
    #pragma section="HEAP"
    #define HEAP_BEGIN  (__segment_end("HEAP"))
#else
    extern int __bss_end;
    #define HEAP_BEGIN  ((void *)&__bss_end)
#endif

#define HEAP_END    ES32F3_SRAM_END

void rt_hw_board_init(void);

#endif

