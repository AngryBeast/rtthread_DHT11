/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2018-11-19     flybreak     add stm32f407-atk-explorer bsp
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
//#include "dht11.h"
//#include "oled.h"
//#include "onenet_sent.h"

//#include <U8g2lib.h>

/* defined the LED0 pin: PF9 */
#define LED0_PIN    GET_PIN(F, 9)

/*pin:  OLED:   SCL:PB6   SDA:PB7
 *      DHT11:  DATA:PG9
 *      8266    USART3: RX:PB10 TX:PB11
 *      LIGHT:  ADC:    ADC1_IN5    PA5
 */

int main(void)
{
    int count = 1;
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);


//    dht11_read_temp_sample();
//    thread_oled();
//    thread_mqtt();
//    thread_onenet();

    while (count++)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }


    return RT_EOK;
}






