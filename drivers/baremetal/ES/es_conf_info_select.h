/*
 * Copyright (C) 2021 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 */

#ifndef __ES_CONF_INFO_SELECT_H__
#define __ES_CONF_INFO_SELECT_H__


#define ES_C_ENABLE     1
#define ES_C_DISABLE    0
    

/* codes_main */

#ifndef ES_USE_ASSERT
#define  ES_USE_ASSERT    ES_C_DISABLE
#endif


#if ES_USE_ASSERT 
    #define USE_ASSERT
#endif

#endif
