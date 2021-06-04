/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-03     97463       the first version
 */
#ifndef APPLICATIONS_ONENET_SENT_H_
#define APPLICATIONS_ONENET_SENT_H_


static void threadonenet_entry(void *param);
int thread_onenet(void);

static void threadMqtt_entry(void *param);
int thread_mqtt(void);

#endif /* APPLICATIONS_ONENET_SENT_H_ */
