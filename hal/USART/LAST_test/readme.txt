串口命令控制 LED（带参数）— LAST_test
========================================

【简介】
第二个「举一反三」工程。在第一个工程（串口控制 LED，固定命令）的基础上，
升级为带参数的命令解析：同一个命令可以带不同的数字参数，产生不同效果。

通过串口助手发送文本命令，控制板载 LED0 亮灭 / 闪烁。

【硬件清单】
开发板：正点原子 Mini STM32H562VIT6（Cortex-M33, 250MHz, 2MB Flash）
下载器：DAP
LED0  ：PB4（受控 LED）
LED1  ：PB5（系统运行指示，每 300ms 翻转）
串口  ：USART1，PA9(TX) / PA10(RX)，115200 8N1

【功能】
LED_ON         LED0 常亮
LED_OFF        LED0 熄灭
LED_TOGGLE     LED0 翻转一次
LED_BLINK n    LED0 闪烁 n 次（每次 = 亮 100ms + 灭 100ms）

其他：收到数据会原样回显；LED1 每 300ms 翻转，提示系统在运行。

【技术点】
1. 串口中断接收状态机
   HAL_UART_RxCpltCallback 逐字节接收，遇 \r\n 判定一帧结束（见 usart.c）
2. sscanf 拆「命令 + 参数」
   sscanf("%19s %d", 命令, &参数) 一步完成拆分 + 字符串转整数
   返回 2 = 带参数，返回 1 = 只有命令
3. printf 重定向
   重写 fputc，把字符发到串口

【遇到的问题 + 解决】
1. 怎么把命令和参数分开？
   第一版手数下标（命令占 0~8、参数从第 10 位取），命令名长度一变就崩
   -> 改用 sscanf("%19s %d")，%s 自动吃到空格，%d 自动跳过空格读数字
2. %s 会栈溢出
   %s 无宽度限制，超长输入会写穿数组
   -> 限定 %19s（最多 19 字符 + \0）
3. printf 输出不换行
   fputc 没把 \n 转成 \r\n，串口助手里输出挤在一行
   -> 字符串统一带 \r\n

【工程结构】
User/main.c                   主逻辑：命令解析 + LED 控制
Drivers/SYSTEM/               手写模板（sys / delay / usart）
Drivers/BSP/LED/              LED 驱动
Drivers/STM32H5xx_HAL_Driver/ HAL 库
Projects/MDK-ARM/             Keil 工程

路线：手写 HAL 模板（不用 CubeMX），骨架抄、驱动半抄、业务自写。
