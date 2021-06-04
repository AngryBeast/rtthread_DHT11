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
#include <rtdevice.h>
#include "sensor.h"
#include "sensor_dallas_dht11.h"
#include "drv_gpio.h"
#include "dht11.h"

//#include "onenet.h"


#define LIGHT_PIN        GET_PIN(G,  10)

#define ADC_DEV_NAME        "adc1"      /* ADC 设备名称 */
#define ADC_DEV_CHANNEL     5           /* ADC 通道 */
#define REFER_VOLTAGE       330         /* 参考电压 3.3V,数据精度乘以100保留2位小数*/
#define CONVERT_BITS        (1 << 8)   /* 转换位数为12位 */

/* Modify this pin according to the actual wiring situation */
rt_mailbox_t mbt_8266_dht;
rt_mailbox_t mbt_oled_dht;
rt_mp_t mb_pool;


//static char mb_pool[128];



void read_temp_entry(void *parameter)
{
    struct dht11_data *msg;
    rt_device_t dev = RT_NULL;
    struct rt_sensor_data sensor_data;
    rt_size_t res;
    rt_uint8_t get_data_freq = 1; /* 1Hz */
//    int light_value;     //光照Pin的状态

    //rt_pin_mode(LIGHT_PIN, PIN_MODE_INPUT_PULLUP);  //光照传感器引脚上拉输入

    dev = rt_device_find("temp_dht11");

    if (dev == RT_NULL)
    {
        return;
    }

    if (rt_device_open(dev, RT_DEVICE_FLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("open device failed!\n");
        return;
    }

    rt_device_control(dev, RT_SENSOR_CTRL_SET_ODR, (void *)(&get_data_freq));

    //光照传感器AD
    rt_adc_device_t adc_dev;
    rt_uint32_t value, vol;
    rt_err_t ret = RT_EOK;
    /* 查找设备 */
    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
        return RT_ERROR;
    }

    /* 使能设备 */
    ret = rt_adc_enable(adc_dev, ADC_DEV_CHANNEL);



    mb_pool = rt_mp_create("mp1", 128, sizeof(struct dht11_data));

    mbt_oled_dht = rt_mb_create("mailbox1", 128, RT_IPC_FLAG_FIFO);
    mbt_8266_dht = rt_mb_create("mailbox2", 128, RT_IPC_FLAG_FIFO);

    while (1)
    {
        res = rt_device_read(dev, 0, &sensor_data, 1);

        if (res != 1)
        {
            rt_kprintf("read data failed! result is %d\n", res);
            rt_device_close(dev);
            return;
        }
        else
        {
            if (sensor_data.data.temp >= 0)
            {


                msg = rt_mp_alloc(mb_pool, RT_WAITING_FOREVER);
                msg->temp = (sensor_data.data.temp & 0xffff) >> 0;
                msg->humi = (sensor_data.data.temp & 0xffff0000) >> 16;

                value = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
                vol = value * REFER_VOLTAGE / CONVERT_BITS;
                msg->light = 50- (vol/100);


                rt_mb_send(mbt_oled_dht, (rt_ubase_t)msg);
                rt_mb_send(mbt_8266_dht, (rt_ubase_t)msg);
                msg = NULL;
            }
        }

        rt_thread_delay(1000);
    }
}

static int rt_hw_dht11_port(void)
{
    struct rt_sensor_config cfg;

    cfg.intf.user_data = (void *)DHT11_DATA_PIN;
    rt_hw_dht11_init("dht11", &cfg);

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_dht11_port);



int dht11_read(void)
{
    rt_thread_t dht11_thread;

    dht11_thread = rt_thread_create("dht11",
                                     read_temp_entry,
                                     RT_NULL,
                                     1024,
                                     10,
                                     20);
    if (dht11_thread != RT_NULL)
    {
        rt_thread_startup(dht11_thread);
    }

    return RT_EOK;
}
INIT_APP_EXPORT(dht11_read);


