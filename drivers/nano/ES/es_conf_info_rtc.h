/*
 * Copyright (C) 2021 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 */

#ifndef __ES_CONF_INFO_RTC_H__
#define __ES_CONF_INFO_RTC_H__

#include <ald_cmu.h>
#include <ald_rtc.h>

/* RTC 配置 */

#define ES_C_RTC_SOURCE_LRC      RTC_SOURCE_LRC
#define ES_C_RTC_SOURCE_LOSC      RTC_SOURCE_LOSC

#define ES_RTC_CLK_SOURCE        ES_C_RTC_SOURCE_LOSC

/* codes_main */

#ifndef  ES_DEVICE_NAME_RTC
#define  ES_DEVICE_NAME_RTC     "rtc"
#endif 

#endif
