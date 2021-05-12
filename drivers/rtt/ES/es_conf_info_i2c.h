/*
 * Copyright (C) 2021 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 */

#ifndef __ES_CONF_INFO_I2C_H__
#define __ES_CONF_INFO_I2C_H__

#include "es_conf_info_map.h"
#include <ald_i2c.h>
#include <ald_gpio.h>
#include <rtdbg.h>

#define ES_C_I2C_STRETCH                 I2C_NOSTRETCH_DISABLE  
#define ES_C_I2C_NO_STRETCH              I2C_NOSTRETCH_ENABLE

#define ES_C_I2C_GENERALCALL             I2C_GENERALCALL_ENABLE
#define ES_C_I2C_NO_GENERALCALL          I2C_GENERALCALL_DISABLE

 
#define ES_I2C_ADDR_7_MODE                I2C_ADDR_7BIT   
#define ES_I2C_ADDR_10_MODE                I2C_ADDR_10BIT


/* I2C 配置 */

/* codes_main */

#ifndef  ES_DEVICE_NAME_I2C0
#define  ES_DEVICE_NAME_I2C0     "i2c0"
#endif              

#ifndef  ES_DEVICE_NAME_I2C1
#define  ES_DEVICE_NAME_I2C1     "i2c1"
#endif                
   
#ifndef  ES_I2C0_CLK_SPEED
#define ES_I2C0_CLK_SPEED                100000
#endif
#ifndef  ES_I2C0_OWN_ADDR1
#define ES_I2C0_OWN_ADDR1                0x20
#endif
#ifndef  ES_I2C0_GENERAL_CALL
#define ES_I2C0_GENERAL_CALL             ES_C_I2C_NO_GENERALCALL
#endif
#ifndef  ES_I2C0_STRETCH
#define ES_I2C0_STRETCH               ES_C_I2C_STRETCH
#endif
#ifndef ES_I2C0_ADDR_MODE                                            
#define ES_I2C0_ADDR_MODE                ES_I2C_ADDR_7_MODE 
#endif

#ifndef  ES_I2C1_CLK_SPEED
#define ES_I2C1_CLK_SPEED                100000
#endif
#ifndef  ES_I2C1_OWN_ADDR1
#define ES_I2C1_OWN_ADDR1                0x20
#endif
#ifndef  ES_I2C1_GENERAL_CALL
#define ES_I2C1_GENERAL_CALL             ES_C_I2C_NO_GENERALCALL
#endif
#ifndef  ES_I2C1_STRETCH
#define ES_I2C1_STRETCH               ES_C_I2C_STRETCH
#endif 
#ifndef ES_I2C1_ADDR_MODE                                            
#define ES_I2C1_ADDR_MODE                ES_I2C_ADDR_7_MODE 
#endif

                                                 

#endif
