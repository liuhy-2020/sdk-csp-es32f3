/*
 * Copyright (C) 2021 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 */

#ifndef __ES_CONF_INFO_PWM_H__
#define __ES_CONF_INFO_PWM_H__

#include "es_conf_info_map.h"
#include <ald_cmu.h>
#include <ald_timer.h>
#include <ald_gpio.h>


#define ES_C_PWM_OC_POL_HIGH   TIMER_OC_POLARITY_HIGH
#define ES_C_PWM_OC_POL_LOW    TIMER_OC_POLARITY_LOW

#define  ES_C_PWM_OC_MODE_PWM1     TIMER_OC_MODE_PWM1
#define  ES_C_PWM_OC_MODE_PWM2     TIMER_OC_MODE_PWM2


    
/* PWM 配置 */


/* codes_main */

#define ES_PWM_OC_POLARITY   ES_C_PWM_OC_POL_HIGH
#define ES_PWM_OC_MODE       ES_C_PWM_OC_MODE_PWM2

#ifndef ES_PWM_OC_POLARITY
#define ES_PWM_OC_POLARITY   ES_C_PWM_OC_POL_HIGH
#endif    
#ifndef ES_PWM_OC_MODE 
#define ES_PWM_OC_MODE       ES_C_PWM_OC_MODE_PWM2
#endif

#ifndef  ES_DEVICE_NAME_AD16C4T0_PWM
#define  ES_DEVICE_NAME_AD16C4T0_PWM     "pwm0"
#endif          
#ifndef  ES_DEVICE_NAME_AD16C4T1_PWM
#define  ES_DEVICE_NAME_AD16C4T1_PWM     "pwm1"
#endif              
#ifndef  ES_DEVICE_NAME_GP32C4T0_PWM
#define  ES_DEVICE_NAME_GP32C4T0_PWM     "pwm2"
#endif              
#ifndef  ES_DEVICE_NAME_GP32C4T1_PWM
#define  ES_DEVICE_NAME_GP32C4T1_PWM     "pwm3"
#endif              
#ifndef  ES_DEVICE_NAME_GP16C4T0_PWM
#define  ES_DEVICE_NAME_GP16C4T0_PWM     "pwm4"
#endif              
#ifndef  ES_DEVICE_NAME_GP16C4T1_PWM
#define  ES_DEVICE_NAME_GP16C4T1_PWM     "pwm5"
#endif              


#endif
