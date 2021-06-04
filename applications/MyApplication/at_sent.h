/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-04     97463       the first version
 */
#ifndef PACKAGES_MYAPPLICATION_AT_SENT_H_
#define PACKAGES_MYAPPLICATION_AT_SENT_H_

#include "at_sent.h"
#include <at_device_esp8266.h>
#include <rtthread.h>
#include <at.h>   /* AT 组件头文件 */


#define LOG_TAG                        "at.sample.esp"
#include <at_log.h>

#define ESP8266_SAMPLE_DEIVCE_NAME     "esp8266"



void atsent_thread_entry(void *parameter);
int at_sent(void);


static struct at_device_esp8266 esp0 =
{
    ESP8266_SAMPLE_DEIVCE_NAME,
    ESP8266_SAMPLE_CLIENT_NAME,

    ESP8266_SAMPLE_WIFI_SSID,
    ESP8266_SAMPLE_WIFI_PASSWORD,
    ESP8266_SAMPLE_RECV_BUFF_LEN,
};


#endif /* PACKAGES_MYAPPLICATION_AT_SENT_H_ */
