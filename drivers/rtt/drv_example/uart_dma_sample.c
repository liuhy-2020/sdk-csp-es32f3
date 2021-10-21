/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-15     misonyo      first implementation.
 */
/*
 * 程序清单：这是一个 串口 设备使用例程
 * 例程导出了 uart_sample 命令到控制终端
 * 命令调用格式：uart_sample uart2
 * 命令解释：命令第二个参数是要使用的串口设备名称，为空则使用默认的串口设备
 * 程序功能：通过串口输出字符串"hello RT-Thread!"，然后错位输出输入的字符
*/

#include <rtthread.h>
#include <rtdevice.h>
#define SAMPLE_UART_NAME       "uart1"      /* 串口设备名称 */

/* 用于接收消息的信号量 */
static rt_sem_t drx_sem;
static rt_device_t dserial;

/* 接收数据回调函数 */
static rt_err_t duart_input(rt_device_t dev, rt_size_t size)
{
    /* 串口接收到数据后产生中断，调用此回调函数，然后发送接收信号量 */
    rt_sem_release(drx_sem);
    return RT_EOK;
}

static void dserial_thread_entry(void *parameter)
{
    char buf[17];
    uint32_t len;
    uint32_t i;
    while (1)
    {
        /* 从串口读取一个字节的数据，没有读取到则等待接收信号量 */
        while ((len = rt_device_read(dserial, -1, buf, 16)) == 0)
        {
            /* 阻塞等待接收信号量，等到信号量后再次读取数据 */
            rt_sem_take(drx_sem, RT_WAITING_FOREVER);
        }
        /* 读取到的数据通过串口错位输出 */
        buf[len]=0;
        rt_kprintf("Recv:%s\n",buf);
        if (buf[0]=='q' && buf[1] == 'q')
        {
            rt_device_close(dserial);
            rt_sem_detach(drx_sem);
            rt_kprintf("duart quit\n");
            break;
        }
        for (i=0;i<len;i++)
            buf[i]+=1;
        rt_device_write(dserial, 0, buf, len);
        if (buf[0]=='r' && buf[1] == 'R')
        {
            rt_device_close(dserial);
            rt_sem_detach(drx_sem);
            
            rt_kprintf("duart quit\n");
            break;
        }
    }
}

static int duart(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    char uart_name[RT_NAME_MAX];
    char str[] = "hello RT-Thread!\r\n";
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;  /* 初始化配置参数 */
    if (argc == 2)
    {
        rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(uart_name, SAMPLE_UART_NAME, RT_NAME_MAX);
    }
    if (dserial)
    {
        rt_device_close(dserial);
    }
    /* 查找串口设备 */
    dserial = rt_device_find(uart_name);
    config.bufsz = 32;
    
    if (!dserial)
    {
        rt_kprintf("find %s failed!\n", uart_name);
        return RT_ERROR;
    }
    rt_device_control(dserial,RT_DEVICE_CTRL_CONFIG,&config);
    /* 打开串口设备 */
    if (RT_EOK!=rt_device_open(dserial, RT_DEVICE_FLAG_DMA_TX|RT_DEVICE_FLAG_DMA_RX))
    {
        rt_kprintf("error open serial\n");
        rt_device_close(dserial);
        dserial = NULL;
        return -1;
    }
    
    /* 初始化信号量 */
    if (drx_sem)
        return RT_EOK;
    drx_sem = rt_sem_create("rxd_sem", 0, RT_IPC_FLAG_FIFO);
    /* 设置接收回调函数 */
    rt_device_set_rx_indicate(dserial, duart_input);
    rt_device_write(dserial, 0, str, (sizeof(str) - 1));
    rt_thread_delay(100);

    /* 创建 serial 线程 */
    rt_thread_t thread = rt_thread_create("serial", dserial_thread_entry, RT_NULL, 1024, 5, 10);
    /* 创建成功则启动线程 */
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        ret = RT_ERROR;
    }
    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(duart, uart device sample);
