/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-04     97463       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "dht11.h"
#include "usart_sent.h"


#define SAMPLE_UART_NAME       "uart3"    /* 串口设备名称 */
static rt_device_t serial;                /* 串口设备句柄 */

void usartsent_thread_entry(void *parameter)
{
    serial = rt_device_find(SAMPLE_UART_NAME);
    rt_device_open(serial, RT_DEVICE_FLAG_INT_RX);

    struct dht11_data* msg;
    extern rt_mailbox_t mbt_8266_dht;

    char sent_data[128];
    while(1)
    {
        if (rt_mb_recv(mbt_8266_dht, (rt_ubase_t*)&msg, RT_WAITING_FOREVER) == RT_EOK)
        {

            //rt_kprintf("temp = %d\r\n",msg->temp);
            rt_kprintf("temp = %d\t",msg->temp);
            rt_kprintf("humi = %d\t",msg->humi);
            rt_kprintf("light = %d\r\n",msg->light);
            sprintf(sent_data,"%d,%d,%d",msg->temp,msg->humi,msg->light);
           // rt_kprintf("String = %s\r\n",sent_data);
            rt_device_write(serial, 0, sent_data, (sizeof(sent_data) - 1));
            memset(sent_data, 0, sizeof(sent_data));

        }

    }


}


int usart_sent(void)
{
    rt_thread_t usartsent_thread;

    usartsent_thread = rt_thread_create("usart_sent",
                                     usartsent_thread_entry,
                                     RT_NULL,
                                     1024,
                                     11,
                                     20);
    if (usartsent_thread != RT_NULL)
    {
        rt_thread_startup(usartsent_thread);
    }

    return RT_EOK;
}
INIT_APP_EXPORT(usart_sent);
