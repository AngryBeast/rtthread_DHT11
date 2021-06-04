/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-03     97463       the first version
 */

#include <rtthread.h>

#include "onenet_sent.h"
//#include "onenet.h"
#include "dht11.h"

/* 指向信号量的指针 */
static rt_sem_t mqttinit_sem = RT_NULL;
rt_thread_t mqtt_thread;
/* 线程  入口 */
static void threadonenet_entry(void *param)
{
    /* 永久等待方式接收信号量，若收不到，该线程会一直挂起 */
    rt_sem_take(mqttinit_sem, RT_WAITING_FOREVER);
    /* 后面用不到这个信号量了，把它删除了，回收资源 */
    rt_sem_delete(mqttinit_sem);
    rt_thread_delete(mqtt_thread);
    struct dht11_data* msg;
    extern rt_mailbox_t mbt_8266_dht;

    while (1)
    {
//        if (rt_mb_recv(mbt_8266_dht, (rt_ubase_t*)&msg, RT_WAITING_FOREVER) == RT_EOK)
//        {
//            /* 500ms上传一次数据 */
//            rt_thread_delay(rt_tick_from_millisecond(500));
//            /* 上传发送节点1的数据到OneNet服务器，数据流名字是temperature_p0 */
//            if (onenet_http_upload_digit("temperature", msg->temp) != RT_EOK)
////            if (onenet_mqtt_publish("temperature", &msg->temp,sizeof(msg->temp)) != RT_EOK)
//                rt_kprintf("upload temperature_p0 has an error, try again\n");
//            else
//                rt_kprintf("onenet upload OK >>> temp_p0:%f\n", msg->temp);
//            rt_kprintf("humi = %f\r\n",(double)msg->temp);
//            rt_mp_free(msg); /* 释放内存块 */
//            msg = RT_NULL;   /* 请务必要做 */
//        }


        /* 500ms上传一次数据 */
        rt_thread_delay(rt_tick_from_millisecond(500));
        /* 上传发送节点1的数据到OneNet服务器，数据流名字是temperature_p0 */
        rt_kprintf("try to sent data \r\n");
        if (onenet_http_upload_digit("temperature", 22.8) != RT_EOK)
//            if (onenet_mqtt_publish("temperature", &msg->temp,sizeof(msg->temp)) != RT_EOK)
            rt_kprintf("upload temperature_p0 has an error, try again\n");
        else
            rt_kprintf("onenet upload OK >>> temp_p0:%f\n", msg->temp);
    }
}

int thread_onenet(void)
{
    rt_thread_t onenet_thread;

    onenet_thread = rt_thread_create("onenet_sent",
                                     threadonenet_entry,
                                     RT_NULL,
                                     1024,
                                     RT_THREAD_PRIORITY_MAX / 2,
                                     20);
    if (onenet_thread != RT_NULL)
    {
        rt_thread_startup(onenet_thread);
    }

    return RT_EOK;
}
//INIT_APP_EXPORT(thread_onenet);




static void threadMqtt_entry(void *param)
{
    uint8_t onenet_mqtt_init_failed_times;
    mqttinit_sem = rt_sem_create("mqttinit_sem", 0, RT_IPC_FLAG_FIFO);
    /* mqtt初始化 */

    while (1)
    {
        if (!onenet_mqtt_init())
        {
            /* mqtt初始化成功之后，释放信号量告知onenet_upload_data_thread线程可以上传数据了 */
            rt_sem_release(mqttinit_sem);
            rt_kprintf("release!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n\r\n\r\n");
            return;
        }
        rt_thread_mdelay(100);
//        LOG_E("onenet mqtt init failed %d times", onenet_mqtt_init_failed_times++);
        rt_kprintf("onenet mqtt init failed %d times", onenet_mqtt_init_failed_times++);
    }
}

int thread_mqtt(void)
{


    mqtt_thread = rt_thread_create("mqtt_thread",
                                    threadMqtt_entry,
                                     RT_NULL,
                                     1024,
                                     RT_THREAD_PRIORITY_MAX / 2,
                                     20);
    if (mqtt_thread != RT_NULL)
    {
        rt_thread_startup(mqtt_thread);
    }

    return RT_EOK;
}
//INIT_APP_EXPORT(thread_mqtt);
