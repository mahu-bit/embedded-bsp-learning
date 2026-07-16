/**
  * 最小启动文件 — STM32H562VIT6 (Cortex-M33)
  * 只包含复位处理和默认中断处理
  */
    .syntax unified
    .arch   armv8-m.main
    .cpu    cortex-m33
    .thumb

    .global _estack
    .global Reset_Handler
    .global Default_Handler

/* ── 函数声明 ── */
    .weak   main
    .type   main, %function

/* ── 中断向量表 ── */
    .section .isr_vector, "a"
    .align 2

    .globl  __isr_vector
__isr_vector:
    .long   _estack                         /*  0: 栈顶指针 */
    .long   Reset_Handler                   /*  1: 复位 */
    .long   Default_Handler                 /*  2: NMI */
    .long   Default_Handler                 /*  3: HardFault */
    .long   Default_Handler                 /*  4: MemManage */
    .long   Default_Handler                 /*  5: BusFault */
    .long   Default_Handler                 /*  6: UsageFault */
    .long   0                               /*  7: (保留) */
    .long   0                               /*  8: (保留) */
    .long   0                               /*  9: (保留) */
    .long   0                               /* 10: (保留) */
    .long   Default_Handler                 /* 11: SVCall */
    .long   Default_Handler                 /* 12: DebugMon */
    .long   0                               /* 13: (保留) */
    .long   Default_Handler                 /* 14: PendSV */
    .long   Default_Handler                 /* 15: SysTick */
    /* 外设中断 (最小实现只放占位) */
    .rept   128
    .long   Default_Handler
    .endr

/* ── 复位处理 — 初始化 BSS/Data, 跳转 main ── */
    .section .text.Reset_Handler
    .type   Reset_Handler, %function
Reset_Handler:
    /* 设置栈指针 (启动时硬件已从向量表加载, 这里再确保一次) */
    ldr     sp, =_estack

    /* 复制 .data 段: Flash → SRAM */
    ldr     r0, =_sdata       /* 目标 (SRAM) */
    ldr     r1, =_edata       /* 目标结束 */
    ldr     r2, =_sidata      /* 源 (Flash) */
    cmp     r0, r1
    beq     clear_bss
copy_data:
    ldr     r3, [r2], #4
    str     r3, [r0], #4
    cmp     r0, r1
    bne     copy_data

clear_bss:
    ldr     r0, =_sbss
    ldr     r1, =_ebss
    movs    r2, #0
    cmp     r0, r1
    beq     call_main
zero_bss:
    str     r2, [r0], #4
    cmp     r0, r1
    bne     zero_bss

call_main:
    bl      main
    b       .

/* ── 默认中断处理 — 死循环 ── */
    .section .text.Default_Handler, "ax"
    .type   Default_Handler, %function
Default_Handler:
    b       .
