# EXTI 巩固项目：按键中断（举一反三）🌙

> 日期：2026-08-18 晚
> 前置：已学完第 61 讲中断、写过第一个中断代码 `D:\hal\ZHONGDUAN`
> 目标：从「单键翻转 LED」扩展到「三键 + 标志位 + 状态机 + 串口」

---

## 🎯 核心巩固点

你第一个代码学会的是「**单键 + 下降沿 + 回调里做事**」。
今晚举一反三，要练三个进阶：

1. **多条 EXTI 线**（3 个键，含共用中断线 EXTI15_10）
2. **上升沿 vs 下降沿**（WKUP 是上升沿，另外两个是下降沿）
3. **中断里只置标志位**（改掉在回调里 `delay_ms` 的坏习惯）← 面试必问

---

## 🔌 硬件引脚表（正点原子 Mini STM32H562）

| 按键 | 引脚 | 触发沿 | 按下电平 | EXTI 线 | 中断服务函数 |
|:--|:--|:--|:--|:--|:--|
| KEY0 | PA1  | 下降沿 | 低(0) | EXTI1 | `EXTI1_IRQHandler` |
| KEY1 | PA15 | 下降沿 | 低(0) | EXTI15 | `EXTI15_IRQHandler` |
| WKUP | PA0  | 上升沿 | 高(1) | EXTI0 | `EXTI0_IRQHandler` |

| LED | 引脚 | 颜色 | 点亮电平 |
|:--|:--|:--|:--|
| LED0 | PB4 | 红 | 0（共阳极）|
| LED1 | PB5 | 绿 | 0（共阳极）|

> ⚠️ 重点：H562 是 Cortex-M33，EXTI0~15 **每条线独立一条中断**（不像 F1/H7 那样 10~15 挤在一条 `EXTI15_10_IRQHandler`）。
> 所以 PA15 对应的是 `EXTI15_IRQHandler`，别照搬网课里 F1 的 `EXTI15_10_IRQHandler`。

---

## 🏗️ 工程结构（照你之前的 BSP 分层来）

```
D:\hal\EXTI_Challenge\        ← 全英文路径，MDK Browse Info 不崩
├── Drivers/BSP/
│   ├── LED/  led.c led.h     ← 直接从 ZHONGDUAN 复制
│   ├── KEY/  key.c key.h     ← 从 GPIO/LED_BEEP 复制（含 3 键引脚宏）
│   └── EXTI/ exti.c exti.h   ← 今晚重点改这里
└── User/main.c
```

---

## 🥇 第一关（必做）：三键中断，各管各的灯

**要求**
- KEY0 按下 → 翻转 LED0（红）
- KEY1 按下 → 翻转 LED1（绿）
- WKUP 按下 → 两个灯全关

**练什么**
- `exti_init()` 里一次配 3 条线：PA1 下降沿+上拉、PA15 下降沿+上拉、PA0 上升沿+下拉
- 开 3 个 NVIC：`EXTI0_IRQn`、`EXTI1_IRQn`、`EXTI15_IRQn`
- 写 3 个中断服务函数，每个里面调 `HAL_GPIO_EXTI_IRQHandler(...)`
- 下降沿进 `HAL_GPIO_EXTI_Falling_Callback`，上升沿进 `HAL_GPIO_EXTI_Rising_Callback`，各自用 `if(GPIO_Pin == ...)` 区分是哪个键

> 💡 提示：WKUP 是**上升沿**，回调在 `HAL_GPIO_EXTI_Rising_Callback` 里写，别写错到 Falling 里。

---

## 🥈 第二关（必做，今晚的重头戏）：中断只置标志位

**为什么**
第一关和 ZHONGDUAN 都在回调里 `delay_ms(20)` + 做动作。
回调是跑在**中断上下文**里的，中断里 delay 会卡住其他中断和主循环——这是坏习惯，面试官一问就露馅。

**正确姿势**
- 回调里只做一件事：给一个 `volatile` 全局标志位置 1
- 消抖、读电平、做动作全部搬到 `while(1)` 主循环里

**骨架（自己补全）**
```c
volatile uint8_t key0_flag = 0;   // 学过 volatile，现在派上用场

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_1)  key0_flag = 1;   // 只置标志，别的啥也不干
}

// main 里
while (1)
{
    if (key0_flag)
    {
        key0_flag = 0;
        delay_ms(20);                          // 消抖放主循环，安全
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0)
            LED0_TOGGLE();
    }
}
```

**练什么**
- `volatile` 为什么必须加（编译器优化问题，面试第 9 题）
- 三个键各一个标志位 `key0_flag / key1_flag / wkup_flag`

---

## 🥉 第三关（选做，加分）：状态机 + 串口打印

**要求**
- KEY0 每按一下，LED 模式循环切换：`OFF → SLOW → FAST → ON → OFF`
- 串口 `printf` 实时打印当前模式名

**复用**
- 这个逻辑你 08-11 已经用轮询写过一次（按键计数四模式 LED），现在用**中断**触发它
- 模式用 `enum`（学过）定义，比魔法数字清晰

**练什么**
- `enum` 状态机 + 中断标志位 + 串口 `printf`，三者合一——这就是简历项目「环境监测终端」的雏形

```c
typedef enum { MODE_OFF, MODE_SLOW, MODE_FAST, MODE_ON } led_mode_t;
led_mode_t mode = MODE_OFF;
// KEY0 中断里置 key0_flag，主循环里 mode = (mode + 1) % 4，再 switch 实现
```

---

## ✅ 今晚验收标准

| 关卡 | 现象 | 完成 |
|:--|:--|:--:|
| 第一关 | 三个键分别控制三个动作 | ⬜ |
| 第二关 | 改成标志位后功能不变，主循环才处理 | ⬜ |
| 第三关 | 按键循环切模式 + 串口打印模式名 | ⬜ |

> 每关烧录一次，录 10 秒短视频（GitHub 项目 README 要用的素材）。

---

## 📌 今晚避坑清单

1. **PB4 是 JTAG NJTRST 引脚** —— 如果 LED0 不亮，是 JTAG 没释放（正点原子 `sys` 初始化一般已处理，但要知道这回事）。
2. **PA15 写进 `EXTI1_IRQHandler` 是错的** —— 它属于 `EXTI15_IRQHandler`（H562 每条 EXTI 线独立，不是 F1 的 `EXTI15_10`）。
3. **WKUP 是上升沿**，配成下降沿永远不触发。
4. **标志位一定要 `volatile`**，否则开优化后可能不更新。
5. 中断回调里**别再 delay**，这是今晚要改掉的核心习惯。
