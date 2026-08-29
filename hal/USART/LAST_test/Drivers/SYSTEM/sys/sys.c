/**
 ****************************************************************************************************
 * @file        sys.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-06-10
 * @brief       系统初始化代码(包括时钟配置/中断管理等)
 * @license     Copyright (c) 2023-2035, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32H5开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:zhengdianyuanzi.tmall.com
 *
 * 修改说明
 * V1.0 20230610
 * 第一次发布
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"


/**
 * @brief       设置中断向量表偏移地址
 * @param       baseaddr: 基址
 * @param       offset: 偏移量
 * @retval      无
 */
void sys_nvic_set_vector_table(uint32_t baseaddr, uint32_t offset)
{
    /* 设置NVIC的向量表偏移寄存器,VTOR低9位保留,即[8:0]保留 */
    SCB->VTOR = baseaddr | (offset & (uint32_t)0xFFFFFE00);
}

/**
 * @brief       执行: WFI指令(执行完该指令进入低功耗状态, 等待中断唤醒)
 * @param       无
 * @retval      无
 */
void sys_wfi_set(void)
{
    __ASM volatile("wfi");
}

/**
 * @brief       关闭所有中断(但是不包括fault和NMI中断)
 * @param       无
 * @retval      无
 */
void sys_intx_disable(void)
{
    __ASM volatile("cpsid i");
}

/**
 * @brief       开启所有中断
 * @param       无
 * @retval      无
 */
void sys_intx_enable(void)
{
    __ASM volatile("cpsie i");
}

/**
 * @brief       设置栈顶地址
 * @note        左侧的红X, 属于MDK误报, 实际是没问题的
 * @param       addr: 栈顶地址
 * @retval      无
 */
void sys_msr_msp(uint32_t addr)
{
    __set_MSP(addr);    /* 设置栈顶地址 */
}

/**
 * @brief       时钟设置函数
 * @param       plln: PLL1倍频系数(PLL倍频), 取值范围: 4~512.
 * @param       pllm: PLL1预分频系数(进PLL之前的分频), 取值范围: 1~63.
 * @param       pllp: PLL1的p分频系数(PLL之后的分频), 分频后作为系统时钟, 取值范围: 2~128.(且必须是2的倍数)
 * @param       pllq: PLL1的q分频系数(PLL之后的分频), 取值范围: 1~128.
 * @note
 *
 *              Fvco: VCO频率
 *              Fsys: 系统时钟频率, 也是PLL1的p分频输出时钟频率
 *              Fq:   PLL1的q分频输出时钟频率
 *              Fs:   PLL输入时钟频率, 可以是HSI, CSI, HSE等.
 *              Fvco = Fs * (plln / pllm);
 *              Fsys = Fvco / pllp = Fs * (plln / (pllm * pllp));
 *              Fq   = Fvco / pllq = Fs * (plln / (pllm * pllq));
 *
 *              外部晶振为 8M的时候, 推荐值: plln = 250, pllm = 4, pllp = 2, pllq = 2.
 *              得到:Fvco = 8 * (250 / 4) = 500Mhz
 *                   Fsys = pll1_p_ck = 500 / 2 = 250Mhz
 *                   Fq   = pll1_q_ck = 500 / 2 = 250Mhz
 *
 *              H563默认需要配置的频率如下:
 *              CPU频率(rcc_c_ck) = SYSCLK = 250Mhz
 *              AHB1/2/3(rcc_hclk1/2/3) = 250Mhz
 *              APB1/2/3(rcc_pclk1/2/3) = 250Mhz
 *
 * @retval      错误代码: 0, 成功; 1, 错误;
 */
uint8_t sys_stm32_clock_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq)
{
    HAL_StatusTypeDef ret = HAL_OK;
    RCC_OscInitTypeDef rcc_osc_init = {0};
    RCC_ClkInitTypeDef rcc_clk_init = {0};

    /* 配置主稳压器输出的电压级别，VOS = 0, Scale0, 1.35V内核电压，使用最高主频250MHz */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0); 
    while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

    /* 配置PLL1时钟 */
    rcc_osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;      /* 时钟源为HSE */
    rcc_osc_init.HSEState = RCC_HSE_ON;                        /* 打开HSE */
    rcc_osc_init.PLL.PLLState = RCC_PLL_ON;                    /* 打开PLL1 */
    rcc_osc_init.PLL.PLLSource = RCC_PLL1_SOURCE_HSE;          /* PLL1 时钟源选择HSE */
    rcc_osc_init.PLL.PLLM = pllm;                              /* PLL1 预分频系数(PLL之前的分频) */
    rcc_osc_init.PLL.PLLN = plln;                              /* PLL1 N倍频系数 */
    rcc_osc_init.PLL.PLLP = pllp;                              /* PLL1 P分频系数 */
    rcc_osc_init.PLL.PLLQ = pllq;                              /* PLL1 Q分频系数 */
    rcc_osc_init.PLL.PLLR = 2;                                 /* PLL1 R分频系数 */
    rcc_osc_init.PLL.PLLRGE = RCC_PLL1_VCIRANGE_1;
    rcc_osc_init.PLL.PLLVCOSEL = RCC_PLL1_VCORANGE_WIDE;
    rcc_osc_init.PLL.PLLFRACN = 0;
    ret = HAL_RCC_OscConfig(&rcc_osc_init);                    /* 初始化 */

    if (ret != HAL_OK)
    {
        return 1;
    }

    /*
     *  配置系统时钟来源和各总线时钟预分频系数
     *  配置系统时钟为250MHz
     *  配置AHB总线时钟为250Mhz,对应AHB1、AHB2和AHB3总线
     *  配置APB1总线时钟为250MHz
     *  配置APB2总线时钟为250MHz
     *  配置APB3总线时钟为250MHz
     */
    rcc_clk_init.ClockType      = RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_HCLK
                                  |RCC_CLOCKTYPE_PCLK1
                                  |RCC_CLOCKTYPE_PCLK2
                                  |RCC_CLOCKTYPE_PCLK3;
    rcc_clk_init.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    rcc_clk_init.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    rcc_clk_init.APB1CLKDivider = RCC_HCLK_DIV1;
    rcc_clk_init.APB2CLKDivider = RCC_HCLK_DIV1;
    rcc_clk_init.APB3CLKDivider = RCC_HCLK_DIV1;
    ret = HAL_RCC_ClockConfig(&rcc_clk_init, FLASH_LATENCY_5);

    if (ret != HAL_OK)
    {
        return 1;
    }

    return 0;
}





