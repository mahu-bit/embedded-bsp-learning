# 嵌入式 Linux / BSP 学习之路

> 🎯 方向：**BSP 工程师**
> 📅 开始日期：2026年7月
> 👤 学习者：Dell
> 🔗 GitHub：[mahu-bit/embedded-bsp-learning](https://github.com/mahu-bit/embedded-bsp-learning)

---

## 📖 学习路线

### 第一阶段：C 语言基础 ✅ 已完成

| 模块 | 状态 |
|------|:--:|
| 数组（一维/二维/字符数组） | ✅ |
| 指针运算（含 void*、指针比较） | ✅ |
| 二维数组指针 | ✅ |
| 函数（传参/返回值/指针传参/数组传参/递归） | ✅ |
| 字符串处理（strcpy/strcmp/strcat...） | ✅ |
| 结构体 `.` `->` typedef 内存对齐 | ✅ |
| 枚举 enum | ✅ |
| 位运算 `\|=` `&=` `~` | ✅ |
| volatile | ✅ |

### 第二阶段：STM32 单片机 🔴 进行中

| 事项 | 状态 |
|------|:--:|
| 开发板（正点原子 Mini STM32H562VIT6） | ✅ 已到货 |
| 开发环境（VS Code + GCC + CMake + Ninja） | ✅ 已配好 |
| 看正点原子 HAL 库视频教程 | 🔄 进行中 |
| 点亮第一个 LED | ⬜ |
| 串口打印 | ⬜ |

> 外设学习顺序：GPIO → EXTI → USART → 定时器 → PWM → ADC → I2C → SPI

### 第三阶段：电路基础复习
### 第四阶段：FreeRTOS
### 第五阶段：Linux 系统编程
### 第六阶段：Linux 驱动 & BSP

> 完整路线见 [BSP工程师完整学习路线.md](./BSP工程师完整学习路线.md)

---

## 📁 目录说明

```
├── README.md                        # 本文件
├── CLAUDE.md                        # 项目上下文（Claude Code 自动加载）
├── BSP工程师完整学习路线.md           # 详细学习路线（含网课链接）
├── 嵌入式实习岗位分析.md              # 实习调研报告
├── pointer_arithmetic_exercise.c     # 指针运算练习
├── pointer_2d_exercise.c            # 二维数组指针练习
├── function_exercise.c              # 函数练习（6合1）
├── 老大学习之路/                     # 快速参考 & 记忆
├── stm32h562_test/                  # STM32 CMake + GCC 测试工程
└── 自主学习/                         # 自主学习资料
```

---

## 🛠️ 练习清单

- [x] `pointer_arithmetic_exercise.c` — 指针六种运算 + memcpy/strlen/framebuffer
- [x] `pointer_2d_exercise.c` — 二维数组四种遍历方式
- [x] `function_exercise.c` — 函数六道练习题（传参/返回值/指针/数组/冒泡排序）
- [x] 位运算模拟寄存器 — set_bit / clear_bit / toggle_bit / read_bit

---

## 🛠️ 开发环境

| 用途 | 工具 |
|------|------|
| C 编译运行 | VMware Ubuntu 20.04 + gcc 9.4.0 |
| 写代码 | VS Code（Windows），共享文件夹同步 |
| STM32 编译 | VS Code + arm-none-eabi-gcc 14.3.1 + CMake + Ninja |
| 版本管理 | Git + GitHub（Watt Toolkit 加速） |

## 🎮 开发板

**正点原子 Mini STM32H562VIT6** + DAP 下载器
- 芯片：Cortex-M33, 250MHz, 2MB Flash, 640KB SRAM
- 板载：光传感器、EEPROM、QSPI Flash 16MB、音频编解码

---

## 🏷️ 技术栈

`C语言` `STM32` `ARM Cortex-M33` `HAL库` `CMake` `Linux内核` `设备树` `BSP`
