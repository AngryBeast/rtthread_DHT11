/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-02     97463       the first version
 */



#include <rtthread.h>
#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5



ALIGN(RT_ALIGN_SIZE)
static char threadoled_stack[1024];
static struct rt_thread thread2;
/* 线程 2 入口 */
static void threadoled_entry(void *param)
{
    oled_display();
}

int thread_oled(void)
{
    /* 初始化线程 2，名称是 thread2，入口是 thread2_entry */
    rt_thread_init(&thread2,
                   "oled",
                   threadoled_entry,
                   RT_NULL,
                   &threadoled_stack[0],
                   sizeof(threadoled_stack),
                   THREAD_PRIORITY - 1, THREAD_TIMESLICE);
    rt_thread_startup(&thread2);//启动线程

    return 0;
}

INIT_APP_EXPORT(thread_oled);
