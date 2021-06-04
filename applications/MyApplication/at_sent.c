/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-04     97463       the first version
 */


#include "at_sent.h"
#include <at_device_esp8266.h>
#include <rtthread.h>
#include <at.h>   /* AT 组件头文件 */


#define LOG_TAG                        "at.sample.esp"
#include <at_log.h>

#define ESP8266_SAMPLE_DEIVCE_NAME     "esp8266"




void atsent_thread_entry(void *parameter)
{

//    struct at_device_esp8266 *esp8266 = &esp0;
//
//
//
//    at_device_register(&(esp8266->device),
//                        esp8266->device_name,
//                        esp8266->client_name,
//                        AT_DEVICE_CLASS_ESP8266,
//                        (void *) esp8266);


    rt_thread_delay(8000);
    const char *line_buffer = RT_NULL;
    at_response_t resp = RT_NULL;

    /* 创建响应结构体，设置最大支持响应数据长度为 512 字节，响应数据行数无限制，超时时间为 5 秒 */
    resp = at_create_resp(512, 0, rt_tick_from_millisecond(5000));
    if (!resp)
    {
        rt_kprintf("No memory for response structure!");
        //return -RT_ENOMEM;
    }

    //while(1)

        //at_exec_cmd(resp, "AT+CIPSTART=\"TCP\",\"api.heclouds.com\",8181");
        /* 发送 AT 命令并接收 AT Server 响应数据，数据及信息存放在 resp 结构体中 */

//        if (at_exec_cmd(resp, "AT") != RT_EOK)


    if (at_exec_cmd(resp, "AT+CIPMAX=0") != RT_EOK)
    {
        rt_kprintf("AT client send commands failed, response error or timeout !");
        //return -ET_ERROR;
    }
    for(rt_size_t line_num = 1; line_num <= resp->line_counts; line_num++)
    {
        if((line_buffer = at_resp_get_line(resp, line_num)) != RT_NULL)
        {
            rt_kprintf("line %d buffer : %s\r\n", line_num, line_buffer);
        }
    }
    rt_thread_delay(2000);

        if (at_exec_cmd(resp, "AT+CWMODE=1") != RT_EOK)
        {
            rt_kprintf("AT client send commands failed, response error or timeout !");
            //return -ET_ERROR;
        }
        for(rt_size_t line_num = 1; line_num <= resp->line_counts; line_num++)
        {
            if((line_buffer = at_resp_get_line(resp, line_num)) != RT_NULL)
            {
                rt_kprintf("line %d buffer : %s\r\n", line_num, line_buffer);
            }
        }
        rt_thread_delay(2000);



        if (at_exec_cmd(resp, "AT+CIPSERVER=0") != RT_EOK)
        {
            rt_kprintf("AT client send commands failed, response error or timeout !");
            //return -ET_ERROR;
        }
        for(rt_size_t line_num = 1; line_num <= resp->line_counts; line_num++)
        {
            if((line_buffer = at_resp_get_line(resp, line_num)) != RT_NULL)
            {
                rt_kprintf("line %d buffer : %s\r\n", line_num, line_buffer);
            }
        }
        rt_thread_delay(2000);


        if (at_exec_cmd(resp, "AT+CIPMODE=1") != RT_EOK)
        {
            rt_kprintf("AT client send commands failed, response error or timeout !");
            //return -ET_ERROR;
        }
        for(rt_size_t line_num = 1; line_num <= resp->line_counts; line_num++)
        {
            if((line_buffer = at_resp_get_line(resp, line_num)) != RT_NULL)
            {
                rt_kprintf("line %d buffer : %s\r\n", line_num, line_buffer);
            }
        }
        rt_thread_delay(2000);

        if (at_exec_cmd(resp, "AT+CIPSTART=\"TCP\",\"api.heclouds.com\",8181") != RT_EOK)
        {
            rt_kprintf("AT client send commands failed, response error or timeout !");
            //return -ET_ERROR;
        }
        for(rt_size_t line_num = 1; line_num <= resp->line_counts; line_num++)
        {
            if((line_buffer = at_resp_get_line(resp, line_num)) != RT_NULL)
            {
                rt_kprintf("line %d buffer : %s\r\n", line_num, line_buffer);
            }
        }


        /* 命令发送成功 */
        //rt_kprintf("AT Client send commands to AT Server success!");
        //at_resp_get_line(resp,1);
//        rt_kprintf("try to sent");
//        rt_kprintf(resp->buf);
        rt_thread_delay(2000);



    while(1)
    {


        /* 发送 AT 命令并接收 AT Server 响应数据，数据及信息存放在 resp 结构体中 */
        if (at_exec_cmd(resp, "AT") != RT_EOK)
        {
            rt_kprintf("AT client send commands failed, response error or timeout !");
            //return -ET_ERROR;
        }

        /* 命令发送成功 */
        rt_kprintf("AT Client send commands to AT Server success!");

        rt_thread_delay(1000);
    }


    /* 删除响应结构体 */
    at_delete_resp(resp);

    return RT_EOK;
}


int at_sent(void)
{
    rt_thread_t atsent_thread;

    atsent_thread = rt_thread_create("at_sent",
                                     atsent_thread_entry,
                                     RT_NULL,
                                     1024,
                                     RT_THREAD_PRIORITY_MAX / 2,
                                     20);
    if (atsent_thread != RT_NULL)
    {
        rt_thread_startup(atsent_thread);
    }

    return RT_EOK;
}
//INIT_APP_EXPORT(at_sent);
