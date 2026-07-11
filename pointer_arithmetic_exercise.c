/*
 * 指针运算练习题 ———— BSP工程师基本功
 *
 * 指针运算在BSP中随处可见：
 *   - 遍历寄存器映射区域
 *   - 解析设备树中的内存块
 *   - memcpy/memset 的底层实现
 *   - 操作外设FIFO缓冲区
 *
 * 当前进度：解引用已学完，本练习聚焦指针运算
 */

#include <stdio.h>
#include <string.h>

/* ================================================================
 * 任务1：数组遍历的三种写法（10分）
 *
 * 用三种方式打印数组所有元素：
 *   a) 下标法     arr[i]
 *   b) 指针偏移   *(ptr + i)
 *   c) 移动指针   *ptr++
 *
 * 提示：移动指针后如果要再打印一次，需要把指针指回开头
 * ================================================================ */
void task1_print_array(void)
{
    int data[] = {10, 20, 30, 40, 50};
    int length = 5;

    // ---- （A）下标法 ----
    printf("下标法:   ");

    // ---- （B）指针偏移法 ----
    printf("指针偏移: ");

    // ---- （C）移动指针法 ----
    printf("移动指针: ");
}

/* ================================================================
 * 任务2：实现简化版 memcpy（15分）
 *
 * BSP 里经常要在内存块之间搬数据（比如从外设 FIFO 搬到 RAM）。
 * 请用指针实现 my_memcpy，行为同标准库 memcpy。
 * 注意：dest 和 src 可能重叠吗？memcpy 不处理重叠，先按不重叠写。
 * ================================================================ */
void my_memcpy(void *dest, const void *src, unsigned int byte_count)
{
    // 提示：用 unsigned char* 逐字节拷贝，循环 byte_count 次
}

void task2_test_memcpy(void)
{
    char src[] = "Hello BSP!";
    char dest[20] = {0};

    my_memcpy(dest, src, sizeof(src));  // 包含结尾的 '\0'
    printf("src  = %s\n", src);
    printf("dest = %s\n", dest);
}

/* ================================================================
 * 任务3：指针相减（10分）
 *
 * 两个同类型指针相减，得到的是两个地址之间"夹了几个元素"，
 * 不是字节数。这点在计算数组长度时超好用。
 *
 * 请实现 strlen 的指针版本：传入字符串首地址，返回字符个数（不含'\0'）
 * ================================================================ */
unsigned int my_strlen(const char *str)
{
    // 提示：用另一个指针走到 '\0'，然后相减
    return 0;
}

void task3_test_strlen(void)
{
    const char *msg = "BSP Engineer";
    printf("字符串: \"%s\", 长度: %u\n", msg, my_strlen(msg));
}

/* ================================================================
 * 任务4：指针与二维数组（15分）
 *
 * BSP场景：一块显存 framebuffer，宽640高480，每个像素4字节。
 * 给定行号 row 和列号 col，计算该像素的地址。
 *
 * base 是显存基地址（用一维数组模拟），pixel_width 是每行像素数。
 * 请实现 pixel_address 函数。
 * ================================================================ */
unsigned int *pixel_address(unsigned int *base, int row, int col, int pixel_width)
{
    // 提示：第 row 行第 col 列 = base + row * pixel_width + col
    return NULL;
}

void task4_test_framebuffer(void)
{
    // 模拟一个 3行 x 4列 的小屏幕，每个像素是一个 unsigned int（4字节）
    unsigned int fb[3][4] = {
        {0x000000, 0x111111, 0x222222, 0x333333},
        {0x444444, 0x555555, 0x666666, 0x777777},
        {0x888888, 0x999999, 0xAAAAAA, 0xBBBBBB},
    };

    // 用 pixel_address 获取 fb[1][2] 的值，预期 = 0x666666
    unsigned int *ptr = pixel_address(&fb[0][0], 1, 2, 4);

    printf("fb[1][2] 预期=0x666666, 实际=0x%06X\n", *ptr);

    // 再试一个：fb[2][3] 预期 = 0xBBBBBB
    ptr = pixel_address(&fb[0][0], 2, 3, 4);
    printf("fb[2][3] 预期=0xBBBBBB, 实际=0x%06X\n", *ptr);
}

/* ================================================================
 * 任务5：指针数组（选做，10分）
 *
 * 用指针数组打印一组字符串。
 * 指针数组在 BSP 中常见：驱动 probe 时的 compatible 字符串匹配表。
 * ================================================================ */
void task5_pointer_array(void)
{
    // 这是一张"兼容性字符串"表，BSP 驱动用它匹配设备树节点
    const char *compatible_list[] = {
        "st,stm32mp1-i2c",
        "arm,pl022-spi",
        "snps,dwmac-4.20a",
        NULL   // 哨兵值，标记表结束
    };

    // 请用指针遍历这张表，逐行打印，遇到 NULL 停止
}

/* ================================================================
 * 主函数
 * ================================================================ */
int main(void)
{
    printf("========== 任务1：数组遍历三种写法 ==========\n");
    task1_print_array();

    printf("\n========== 任务2：实现 my_memcpy ==========\n");
    task2_test_memcpy();

    printf("\n========== 任务3：指针相减实现 strlen ==========\n");
    task3_test_strlen();

    printf("\n========== 任务4：指针与二维数组（显存模拟）==========\n");
    task4_test_framebuffer();

    printf("\n========== 任务5：指针数组（选做）==========\n");
    task5_pointer_array();

    return 0;
}
