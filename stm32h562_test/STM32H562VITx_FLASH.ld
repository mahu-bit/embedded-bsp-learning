/* 链接脚本: STM32H562VIT6
 * Flash: 2MB  (0x08000000)
 * SRAM:  640KB (0x20000000)
 * 核心:  Cortex-M33
 */

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K
    SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 640K
}

ENTRY(Reset_Handler)

SECTIONS
{
    /* ── 中断向量表: 必须放在 Flash 最开头 ── */
    .isr_vector :
    {
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH

    /* ── 代码 + 常量 ── */
    .text :
    {
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    /* ── 已初始化全局变量: 存 Flash, 加载时复制到 SRAM ── */
    _sidata = LOADADDR(.data);
    .data :
    {
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > SRAM AT> FLASH

    /* ── 未初始化全局变量 (BSS) ── */
    .bss :
    {
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > SRAM

    /* ── 堆栈结束地址 ── */
    _estack = ORIGIN(SRAM) + LENGTH(SRAM);
}
