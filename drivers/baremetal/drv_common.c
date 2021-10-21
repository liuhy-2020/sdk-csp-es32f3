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

#include "drv_common.h"
#include "board.h"
#include "drv_uart.h"
#include <ald_cmu.h>
#include "es_conf_info_cmu.h"

volatile unsigned int tick_ms = 0U;

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif /* RT_USING_FINSH */

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
}

/*******************************************************************************
 * Function Name  : SystemClock_Configuration
 * Description    : Configures the System Clock.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void  SystemClock_Config(char* clock_src,int32_t clock_src_freq,int32_t clock_target_freq )
{   
	SYSCFG_UNLOCK();
#if  ES_CMU_LRC_EN   
    SET_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);
#else
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_LRCEN_MSK);
#endif  /*ES_CMU_LRC_EN*/  
 
#if ES_CMU_LOSC_EN 
    SET_BIT(CMU->CLKENR, CMU_CLKENR_LOSCEN_MSK);
#else
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_LOSCEN_MSK);
#endif  /*ES_CMU_LOSC_EN*/    
    
#if ES_CMU_HRC_EN     
    SET_BIT(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK);
#else
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_HRCEN_MSK);
#endif  /*ES_CMU_HRC_EN*/    
    
#if ES_CMU_HOSC_EN     
    SET_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
#else
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_HOSCEN_MSK);
#endif  /*ES_CMU_HOSC_EN*/    

	SYSCFG_LOCK();

#if  ES_CMU_PLL1_EN  
    /*PLL的源必须是4M*/
    ald_cmu_pll1_config(ES_PLL1_REFER_CLK, ES_PLL1_OUT_CLK);
    
    #if ES_CMU_PLL1_SAFE_EN
        ald_cmu_pll_safe_config(ENABLE);
    #else
        ald_cmu_pll_safe_config(DISABLE);
    #endif
    
#else
    CLEAR_BIT(CMU->CLKENR, CMU_CLKENR_PLL1EN_MSK);
#endif  /*ES_CMU_PLL1_EN*/ 
    
    ald_cmu_clock_config(ES_SYS_CLK_SOURSE, ES_SYS_CLK);
    
    ald_cmu_div_config(CMU_SYS,ES_CMU_SYS_DIV);
    ald_cmu_div_config(CMU_HCLK_1,ES_CMU_HCLK_1_DIV);
    ald_cmu_div_config(CMU_HCLK_2,ES_CMU_HCLK_2_DIV);
    ald_cmu_div_config(CMU_PCLK_1,ES_CMU_PCLK_1_DIV);
    ald_cmu_div_config(CMU_PCLK_2,ES_CMU_PCLK_2_DIV);
    
    ald_cmu_perh_clock_config(CMU_PERH_ALL, ENABLE);
    
/*低功耗时钟使能*/    
#ifdef RT_USING_PM
        SYSCFG_UNLOCK();
        SET_BIT(CMU->LPENR, CMU_LPENR_LRCEN_MSK);
        SET_BIT(CMU->LPENR, CMU_LPENR_LOSCEN_MSK);
        SET_BIT(CMU->LPENR, CMU_LPENR_HRCEN_MSK);
        SET_BIT(CMU->LPENR, CMU_LPENR_HOSCEN_MSK);
        SYSCFG_LOCK();
#endif
}

/*******************************************************************************
 * Function Name  : SysTick_Configuration
 * Description    : Configures the SysTick for OS tick.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void  SysTick_Configuration(void)
{
    /* ticks = sysclk / RT_TICK_PER_SECOND */
    SysTick_Config(ald_cmu_get_sys_clock() / 1000UL);
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    tick_ms++;
}

/**
 * This is the cmu interrupt service.
 *
 */
void CMU_Handler(void)
{
    ald_cmu_irq_handler();
}
/*@}*/
/**
 * This function will initial ES32F3 board.
 */
void clk_init(char *clock_src, int32_t clock_src_freq, int32_t clock_target_freq)
{
    /* NVIC Configuration */
    NVIC_Configuration();
    /*System Clock Configuration */
    SystemClock_Config(clock_src,clock_src_freq,clock_target_freq*1000000);
    /* Configure the SysTick */
    SysTick_Configuration();
}

/**
 * This function will delay for some ms.
 *
 * @param us the delay time of ms
 */
void wait_ms(uint32_t ms)
{
    unsigned int start, now, delta;
    start = tick_ms;
    do
    {
        now = tick_ms;
        delta = start < now ? now - start : (0xFFFFFFFF - start) + now + 1;
    }
    while (delta <  ms);
}

int uart_init()
{
    rt_hw_uart_init();
    return 0;
}
