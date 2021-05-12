/*
 * Copyright (C) 2021 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 */

#ifndef __ES_CONF_INFO_HWTIMER_H__
#define __ES_CONF_INFO_HWTIMER_H__

#include <ald_cmu.h>
#include <ald_timer.h>

#define ES_C_HWTIMER_MODE_UP         HWTIMER_CNTMODE_UP  
#define ES_C_HWTIMER_MODE_DOWN         HWTIMER_CNTMODE_DW

/* HWTIMER 配置 */

/* codes_main */


#ifndef  ES_AD16C4T0_HWTIMER_MODE
#define ES_AD16C4T0_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP  
#endif                
#ifndef  ES_AD16C4T1_HWTIMER_MODE
#define ES_AD16C4T1_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP  
#endif
#ifndef  ES_GP32C4T0_HWTIMER_MODE
#define ES_GP32C4T0_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP  
#endif  
#ifndef  ES_GP32C4T1_HWTIMER_MODE
#define ES_GP32C4T1_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP  
#endif
#ifndef  ES_GP16C4T0_HWTIMER_MODE
#define ES_GP16C4T0_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP  
#endif
#ifndef  ES_GP16C4T1_HWTIMER_MODE
#define ES_GP16C4T1_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP  
#endif
#ifndef  ES_BS16T0_HWTIMER_MODE
#define ES_BS16T0_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP  
#endif
#ifndef  ES_BS16T1_HWTIMER_MODE
#define ES_BS16T1_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP  
#endif






         
#define ES_AD16C4T0_HWTIMER_PRES          1 
#define ES_AD16C4T1_HWTIMER_PRES          1
#define ES_GP16C4T0_HWTIMER_PRES          1
#define ES_GP16C4T1_HWTIMER_PRES          1
#define ES_GP32C4T0_HWTIMER_PRES          1
#define ES_GP32C4T1_HWTIMER_PRES          1
#define ES_BS16T0_HWTIMER_PRES          1
#define ES_BS16T1_HWTIMER_PRES          1

#ifndef  ES_DEVICE_NAME_AD16C4T0_HWTIMER
#define  ES_DEVICE_NAME_AD16C4T0_HWTIMER     "timer0"
#endif                    
#ifndef  ES_DEVICE_NAME_AD16C4T1_HWTIMER
#define  ES_DEVICE_NAME_AD16C4T1_HWTIMER     "timer1"
#endif                
#ifndef  ES_DEVICE_NAME_GP32C4T0_HWTIMER
#define  ES_DEVICE_NAME_GP32C4T0_HWTIMER     "timer2"
#endif                
#ifndef  ES_DEVICE_NAME_GP32C4T1_HWTIMER
#define  ES_DEVICE_NAME_GP32C4T1_HWTIMER     "timer3"
#endif                
#ifndef  ES_DEVICE_NAME_GP16C4T0_HWTIMER
#define  ES_DEVICE_NAME_GP16C4T0_HWTIMER     "timer4"
#endif                
#ifndef  ES_DEVICE_NAME_GP16C4T1_HWTIMER
#define  ES_DEVICE_NAME_GP16C4T1_HWTIMER     "timer5"
#endif                
#ifndef  ES_DEVICE_NAME_BS16T0_HWTIMER
#define  ES_DEVICE_NAME_BS16T0_HWTIMER     "timer6"
#endif                
#ifndef  ES_DEVICE_NAME_BS16T1_HWTIMER
#define  ES_DEVICE_NAME_BS16T1_HWTIMER     "timer7"
#endif                


#endif
