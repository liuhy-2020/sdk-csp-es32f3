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

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "drv_uart.h"
#include "es_conf_info_map.h"
#include <ald_uart.h>
#include <ald_gpio.h>
#include <ald_cmu.h>

#ifdef RT_USING_CONSOLE

/* es32 uart driver */
struct es32_uart
{
    uart_handle_t huart;
    IRQn_Type irq;
};
struct es32_uart *console_uart = RT_NULL;

static rt_err_t es32f3x_configure(struct es32_uart *uart)
{

    gpio_init_t gpio_initstructure;

    /* Initialize tx pin */
    gpio_initstructure.mode = GPIO_MODE_OUTPUT;
    gpio_initstructure.odos = GPIO_PUSH_PULL;
    gpio_initstructure.pupd = GPIO_PUSH_UP;
    gpio_initstructure.podrv = GPIO_OUT_DRIVE_1;
    gpio_initstructure.nodrv = GPIO_OUT_DRIVE_1;
    gpio_initstructure.flt  = GPIO_FILTER_DISABLE;
    gpio_initstructure.type = GPIO_TYPE_TTL;

    switch((unsigned long)(uart->huart.perh))
    {

#ifdef BSP_USING_UART0
    case ((unsigned long)UART0):
#if  defined(ES_UART0_TX_GPIO_FUNC)&&defined(ES_UART0_TX_GPIO_PORT)&&defined(ES_UART0_TX_GPIO_PIN)
        gpio_initstructure.func = ES_UART0_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART0_TX_GPIO_PORT, ES_UART0_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART0_RX_GPIO_FUNC)&&defined(ES_UART0_RX_GPIO_PORT)&&defined(ES_UART0_RX_GPIO_PIN)        
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART0_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART0_RX_GPIO_PORT, ES_UART0_RX_GPIO_PIN, &gpio_initstructure);
#endif
        ald_cmu_perh_clock_config(CMU_PERH_UART0, ENABLE);
	break;
#endif /* uart0 gpio init */

#ifdef BSP_USING_UART1
    case ((unsigned long)UART1):
#if  defined(ES_UART1_TX_GPIO_FUNC)&&defined(ES_UART1_TX_GPIO_PORT)&&defined(ES_UART1_TX_GPIO_PIN)  
        gpio_initstructure.func = ES_UART1_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART1_TX_GPIO_PORT, ES_UART1_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART1_RX_GPIO_FUNC)&&defined(ES_UART1_RX_GPIO_PORT)&&defined(ES_UART1_RX_GPIO_PIN) 
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART1_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART1_RX_GPIO_PORT, ES_UART1_RX_GPIO_PIN, &gpio_initstructure);
#endif

    ald_cmu_perh_clock_config(CMU_PERH_UART1, ENABLE);
	break;
#endif /* uart1 gpio init */

#ifdef BSP_USING_UART2
    case ((unsigned long)UART2):
#if  defined(ES_UART2_TX_GPIO_FUNC)&&defined(ES_UART2_TX_GPIO_PORT)&&defined(ES_UART2_TX_GPIO_PIN)
        gpio_initstructure.func = ES_UART2_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART2_TX_GPIO_PORT, ES_UART2_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART2_RX_GPIO_FUNC)&&defined(ES_UART2_RX_GPIO_PORT)&&defined(ES_UART2_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART2_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART2_RX_GPIO_PORT, ES_UART2_RX_GPIO_PIN, &gpio_initstructure);
#endif

    ald_cmu_perh_clock_config(CMU_PERH_UART2, ENABLE);
	break;
#endif /* uart2 gpio init */

#ifdef BSP_USING_UART3
    case ((unsigned long)UART3):
#if  defined(ES_UART3_TX_GPIO_FUNC)&&defined(ES_UART3_TX_GPIO_PORT)&&defined(ES_UART3_TX_GPIO_PIN)   
        gpio_initstructure.func = ES_UART3_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART3_TX_GPIO_PORT, ES_UART3_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART3_RX_GPIO_FUNC)&&defined(ES_UART3_RX_GPIO_PORT)&&defined(ES_UART3_RX_GPIO_PIN)
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART3_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART3_RX_GPIO_PORT, ES_UART3_RX_GPIO_PIN, &gpio_initstructure);
#endif

    ald_cmu_perh_clock_config(CMU_PERH_UART3, ENABLE);
	break;
#endif /* uart3 gpio init */

#ifdef BSP_USING_UART4
    case ((unsigned long)UART4):
#if  defined(ES_UART4_TX_GPIO_FUNC)&&defined(ES_UART4_TX_GPIO_PORT)&&defined(ES_UART4_TX_GPIO_PIN)   
        gpio_initstructure.func = ES_UART4_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART4_TX_GPIO_PORT, ES_UART4_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART4_RX_GPIO_FUNC)&&defined(ES_UART4_RX_GPIO_PORT)&&defined(ES_UART4_RX_GPIO_PIN)  
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART4_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART4_RX_GPIO_PORT, ES_UART4_RX_GPIO_PIN, &gpio_initstructure);
#endif

    ald_cmu_perh_clock_config(CMU_PERH_UART4, ENABLE);
	break;
#endif /* uart4 gpio init */

#ifdef BSP_USING_UART5
    case u((unsigned long)UART5):
#if  defined(ES_UART5_TX_GPIO_FUNC)&&defined(ES_UART5_TX_GPIO_PORT)&&defined(ES_UART5_TX_GPIO_PIN)   
        gpio_initstructure.func = ES_UART5_TX_GPIO_FUNC;
        ald_gpio_init(ES_UART5_TX_GPIO_PORT, ES_UART5_TX_GPIO_PIN, &gpio_initstructure);
#endif

#if  defined(ES_UART5_RX_GPIO_FUNC)&&defined(ES_UART5_RX_GPIO_PORT)&&defined(ES_UART5_RX_GPIO_PIN)  
        /* Initialize rx pin ,the same as txpin except mode */
        gpio_initstructure.mode = GPIO_MODE_INPUT;
        gpio_initstructure.func = ES_UART5_RX_GPIO_FUNC;
        ald_gpio_init(ES_UART5_RX_GPIO_PORT, ES_UART5_RX_GPIO_PIN, &gpio_initstructure);
#endif

    ald_cmu_perh_clock_config(CMU_PERH_UART5, ENABLE);
	break;
#endif /* uart5 gpio init */

    default:break;
    }


    ald_uart_tx_fifo_config(&(uart->huart), UART_TXFIFO_EMPTY);
    ald_uart_rx_fifo_config(&(uart->huart), UART_RXFIFO_1BYTE);

    uart->huart.init.mode        = UART_MODE_UART;
    uart->huart.init.baud        = 115200;
    uart->huart.init.word_length = UART_WORD_LENGTH_8B;
    uart->huart.init.stop_bits   = UART_STOP_BITS_1;
    uart->huart.init.parity      = UART_PARITY_NONE;
    uart->huart.init.fctl        = UART_HW_FLOW_CTL_DISABLE;
    ald_uart_init(&(uart->huart));

    /* disable rx irq */
    NVIC_EnableIRQ(uart->irq);
   /* disable interrupt */
    ald_uart_interrupt_config(&(uart->huart), UART_IT_RFTH, ENABLE);

    return RT_EOK;
}

#ifdef BSP_USING_UART0
/* UART0 device driver structure */
struct es32_uart uart0 =
{
    {UART0},
    UART0_IRQn
};

void UART0_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart0.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart0.huart, UART_IF_RFTH);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
/* UART1 device driver structure */
struct es32_uart uart1 =
{
    {UART1},
    UART1_IRQn
};

void UART1_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart1.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart1.huart, UART_IF_RFTH);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
/* UART2 device driver structure */
struct es32_uart uart2 =
{
    {UART2},
    UART2_IRQn
};

void UART2_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart2.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart2.huart, UART_IF_RFTH);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
/* UART3 device driver structure */
struct es32_uart uart3 =
{
    {UART3},
    UART3_IRQn
};

void UART3_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart3.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart3.huart, UART_IF_RFTH);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART3 */

#ifdef BSP_USING_UART4
/* UART4 device driver structure */
struct es32_uart uart4 =
{
    {UART4},
    UART4_IRQn
};

void UART4_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart4.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart4.huart, UART_IF_RFTH);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART4 */

#ifdef BSP_USING_UART5
/* UART5 device driver structure */
struct es32_uart uart5 =
{
    {UART5},
    UART5_IRQn
};

void UART5_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    if ((ald_uart_get_mask_flag_status(&uart5.huart, UART_IF_RFTH)) != RESET)
    {
        ald_uart_clear_flag_status(&uart5.huart, UART_IF_RFTH);
    }
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_UART5 */

int rt_hw_uart_init(void)
{

#ifdef BSP_USING_UART0
    es32f3x_configure(&uart0);
    if(!console_uart)console_uart = &uart0;
#endif /* BSP_USING_UART0 */

#ifdef BSP_USING_UART1
    es32f3x_configure(&uart1);
    if(!console_uart)console_uart = &uart1;
#endif /* BSP_USING_UART1 */

#ifdef BSP_USING_UART2
    es32f3x_configure(&uart2);
    if(!console_uart)console_uart = &uart2;
#endif /* BSP_USING_UART2 */

#ifdef BSP_USING_UART3
    es32f3x_configure(&uart3);
    if(!console_uart)console_uart = &uart3;
#endif /* BSP_USING_UART3 */

#ifdef BSP_USING_UART4
    es32f3x_configure(&uart4);
    if(!console_uart)console_uart = &uart4;
#endif /* BSP_USING_UART4 */

#ifdef BSP_USING_UART5
    es32f3x_configure(&uart5);
    if(!console_uart)console_uart = &uart5;
#endif /* BSP_USING_UART5 */

    return 0;
}
//INIT_BOARD_EXPORT(rt_hw_uart_init);


static int es32f3x_putc(struct es32_uart *uart, char c)
{

    while (ald_uart_get_status(&uart->huart, UART_STATUS_TFEMPTY) == RESET)
        ;
    WRITE_REG(uart->huart.perh->TXBUF, c);

    return 1;
}

void rt_hw_console_output(const char *str)
{
    rt_size_t len = 0;
    char *s =(char*)str;

    len = rt_strlen(str);

    if(!console_uart)return;

while(len--)
{
      if(*s == '\n')es32f3x_putc(console_uart,'\r');
      es32f3x_putc(console_uart,*(s++));
}
}

#ifdef RT_USING_FINSH

static int es32f3x_getc(struct es32_uart *uart)
{
    int ch = -1;

    if (ald_uart_get_status(&uart->huart, UART_STATUS_RFTH))
    {
        ch = (uint8_t)(uart->huart.perh->RXBUF & 0xFF);
    }

    return ch;
}

char rt_hw_console_getchar(void)
{
    if(!console_uart)return -1;
    return es32f3x_getc(console_uart);
}

#endif /* RT_USING_FINSH */

#endif
