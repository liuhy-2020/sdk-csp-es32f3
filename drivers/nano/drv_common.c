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
#if  ( defined(CHIP_NAME_ES32F3696LT) || defined(CHIP_NAME_ES32F3696LX) )
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
    SysTick_Config(ald_cmu_get_sys_clock() / RT_TICK_PER_SECOND);
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    ald_inc_tick();
    rt_tick_increase();
    /* leave interrupt */
    rt_interrupt_leave();
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
void hw_board_init(char *clock_src, int32_t clock_src_freq, int32_t clock_target_freq)
{
    /* NVIC Configuration */
    NVIC_Configuration();
    /*System Clock Configuration */
    SystemClock_Config(clock_src,clock_src_freq,clock_target_freq*1000000);
    /* Configure the SysTick */
    SysTick_Configuration();

#ifdef RT_USING_CONSOLE
    extern int rt_hw_uart_init(void);
    rt_hw_uart_init();
#endif
}

/**
 * This function will delay for some us.
 *
 * @param us the delay time of us
 */
void rt_hw_us_delay(rt_uint32_t us)
{
    unsigned int start, now, delta, reload, us_tick;
    start = SysTick->VAL;
    reload = SysTick->LOAD;
    us_tick = ald_cmu_get_sys_clock() / 1000000UL;
    do
    {
        now = SysTick->VAL;
        delta = start > now ? start - now : reload + start - now;
    }
    while (delta <  us_tick * us);
}
