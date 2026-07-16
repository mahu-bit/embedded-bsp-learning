/**
  * STM32H562VIT6 裸机最小程序
  * 验证交叉编译工具链可用
  *
  * 架构: Cortex-M33, 250MHz, 2MB Flash, 640KB SRAM
  */

/* ── STM32H5 外设基地址 (RM0481 Reference Manual) ── */
#define PERIPH_BASE           0x40000000UL
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)
#define GPIOB_BASE            (AHB1PERIPH_BASE + 0x0400UL)

/* RCC 寄存器 (时钟控制) */
#define RCC_BASE              (AHB1PERIPH_BASE + 0x0000UL)
#define RCC_AHB2ENR           (*(volatile unsigned int *)(RCC_BASE + 0xE0UL))

/* GPIO 寄存器 (通用输入输出) */
typedef struct {
    volatile unsigned int MODER;       /* 模式寄存器     offset: 0x00 */
    volatile unsigned int OTYPER;      /* 输出类型       offset: 0x04 */
    volatile unsigned int OSPEEDR;     /* 输出速度       offset: 0x08 */
    volatile unsigned int PUPDR;       /* 上下拉         offset: 0x0C */
    volatile unsigned int IDR;         /* 输入数据       offset: 0x10 */
    volatile unsigned int ODR;         /* 输出数据       offset: 0x14 */
    volatile unsigned int BSRR;        /* 置位/复位      offset: 0x18 */
    volatile unsigned int LCKR;        /* 锁定           offset: 0x1C */
    volatile unsigned int AFR[2];      /* 复用功能       offset: 0x20-0x24 */
} GPIO_TypeDef;

#define GPIOB  ((GPIO_TypeDef *)GPIOB_BASE)

/* ── 简单延时 (约 n 个周期) ── */
static void delay(volatile unsigned int count)
{
    while (count--) {
        __asm volatile ("nop");
    }
}

/* ── 主函数 ── */
int main(void)
{
    /* 1. 使能 GPIOB 时钟 (AHB2 总线) */
    RCC_AHB2ENR |= (1 << 1);   /* bit1 = GPIOBEN */

    /* 2. 配置 PB0 为输出 (MODER: 01 = 输出模式) */
    GPIOB->MODER  &= ~(3 << 0);    /* 清除 bit1:0 */
    GPIOB->MODER  |=  (1 << 0);    /* 设为 01 = 通用输出 */

    /* 3. 配置 PB0 为推挽输出 */
    GPIOB->OTYPER &= ~(1 << 0);    /* bit0=0: 推挽 */

    /* 4. 主循环 — 软件延时翻转 PB0 */
    volatile unsigned int counter = 0;

    while (1) {
        GPIOB->BSRR = (1 << 0);           /* SET PB0 (高电平) */
        delay(1000000);
        GPIOB->BSRR = (1 << (0 + 16));    /* RESET PB0 (低电平) */
        delay(1000000);
        counter++;
    }

    return 0;
}
