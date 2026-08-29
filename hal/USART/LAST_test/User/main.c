/**LED_ON / LED_OFF / LED_BLINK 5
 ****************************************************************************************************
 * @file     main.c
 * @author   正点原子团队(ALIENTEK)
 * @version  V1.0
 * @date     2023-06-10
 * @brief    串口通信 实验
 * @license  Copyright (c) 2023-2035, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 STM32H5开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:zhengdianyuanzi.tmall.com
 * 
 ****************************************************************************************************
 */
#include <stdio.h>
#include <string.h>   
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"  
void handle_command(uint8_t l){
//step1 拆分命令串为命令于数字
char command[20];
int blink_num;
if(sscanf((char*)g_usart_rx_buf,"%19s %d",command,&blink_num)==2){
if(strcmp(command,"LED_BLINK")==0){
//进行频闪
for(int k=0;k<blink_num;k++){
LED0(0);
delay_ms(100);
LED0(1);
delay_ms(100);
}
}
else{
printf("输入错误1\r\n");
}
}

else if(strcmp((char*)g_usart_rx_buf,"LED_ON")==0)
{
LED0(0);
printf("LED打开\r\n");
}
 else if(strcmp((char*)g_usart_rx_buf,"LED_OFF")==0)
{
LED0(1);
printf("LED关闭\r\n");
}
 else if(strcmp((char*)g_usart_rx_buf,"LED_TOGGLE")==0)
{
LED0_TOGGLE();
printf("LED翻转\r\n");
}
else{
printf("输入错误2\r\n");
}
g_usart_rx_sta = 0;
}
int main(void)
{
    uint8_t len;
    uint16_t times = 0;

    HAL_Init();                                             /* HAL库初始化 */
    HAL_ICACHE_Enable();                                    /* 使能指令缓存 */
    sys_stm32_clock_init(250, 4, 2, 2);                     /* 系统时钟初始化, 250Mhz */
    delay_init(250);                                        /* 延时初始化 */
    usart_init(115200);                                     /* 串口初始化 */
    led_init();                                             /* LED初始化 */
    uint8_t led_mode=0;
    while(1)
    {
        if (g_usart_rx_sta & 0x8000)                        /* 接收到了数据 */
        {
            len = g_usart_rx_sta & 0x3fff;                  /* 得到此次接收到的数据长度 */
            printf("\r\n收到:\r\n");

            HAL_UART_Transmit(&g_uart1_handle,(uint8_t*)g_usart_rx_buf,len,1000);  /* 发送接收到的数据 */
            while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);         /* 等待发送结束 */
            
            printf("\r\n\r\n");                                                    /* 插入换行 */
            handle_command(len);
        }
        else
        {
            times++;

            if (times % 5000 == 0)
            {
                printf("\r\n串口通信实验\r\n");
            }

            if (times % 200 == 0) printf("请输入数据,以回车键结束\r\n");

            if (times % 30  == 0) LED1_TOGGLE();                                  /* 闪烁LED,提示系统正在运行. */

            delay_ms(10);
        }
    }
}






