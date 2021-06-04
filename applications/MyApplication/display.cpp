/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-02     97463       the first version
 */


#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <U8g2lib.h>


/*#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <U8g2lib.h>
#include <stdio.h>
#include <drv_soft_i2c.h>*/
#include "drv_common.h"
#include "dht11.h"



// You may reference Drivers/drv_gpio.c for pinout
// In u8x8.h #define U8X8_USE_PINS

//#define OLED_I2C_PIN_SCL                    GET_PIN(B, 6)
//#define OLED_I2C_PIN_SDA                    GET_PIN(B, 7)

#define OLED_I2C_PIN_SCL                    22  // PB6
#define OLED_I2C_PIN_SDA                    23  // PB7

// Check https://github.com/olikraus/u8g2/wiki/u8g2setupcpp for all supported devices
static U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,\
                                         /* clock=*/ OLED_I2C_PIN_SCL,\
                                         /* data=*/ OLED_I2C_PIN_SDA,\
                                         /* reset=*/ U8X8_PIN_NONE);
                                         // All Boards without Reset of the Display


extern "C" void oled_display()
{
    struct dht11_data* msg;
    extern rt_mailbox_t mbt_oled_dht;
    u8g2.begin();
     while(1){

          //rt_kprintf("123");
         //rt_thread_mdelay(100);
//         if (mbt != RT_NULL) {
//             rt_kprintf("\r\n!!!mbt == null\r\n!!!");
//        }
         if (rt_mb_recv(mbt_oled_dht, (rt_ubase_t*)&msg, RT_WAITING_FOREVER) == RT_EOK)
         {
             //rt_kprintf("4566");
//             rt_kprintf("humi = %d\r\n",msg->humi);
//             rt_kprintf("temp = %d\r\n",msg->temp);


             u8g2.clearBuffer();
             u8g2.setFont(u8g2_font_unifont_t_symbols);

             u8g2.setCursor(2, 10);
             u8g2.print("temp == ");
             u8g2.print(msg->temp);

             u8g2.setCursor(2, 31);
             u8g2.print("humi == ");
             u8g2.print(msg->humi);

             u8g2.setCursor(2, 47);
             u8g2.print("light == ");
             u8g2.print(msg->light);
             u8g2.sendBuffer();

             //free(msg);
         }




     }

}

