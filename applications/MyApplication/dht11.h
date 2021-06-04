#ifndef DHT11_H_
#define DHT11_H_

#define DHT11_DATA_PIN    GET_PIN(G, 9)
void read_temp_entry(void *parameter);
int dht11_read(void);

struct dht11_data{
    uint8_t temp;    //结构体内用来存储数据的变量
    uint8_t humi;
    uint8_t light;
};

/* 邮箱控制块 */

/* 用于放邮件的内存池 */



/* 邮箱控制块 */
//extern struct rt_mailbox mb;
///* 用于放邮件的内存池 */
//extern char mb_pool[128];

#endif /* APPLICATIONS_OLED_H_ */



