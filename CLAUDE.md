# 老大学习之路 🚀

> 🎯 BSP 工程师方向 | 📅 2026年7月启程
> 👤 老大 | GitHub: [mahu-bit/embedded-bsp-learning](https://github.com/mahu-bit/embedded-bsp-learning)

---

## 📋 当前进度（2026-07-16）

```
C语言基础 ████████████ ✅ 全部学完
STM32裸机  █░░░░░░░░░░░ 🔴 进行中
```

| 模块 | 状态 |
|------|:--:|
| 数组（一维/二维/字符） | ✅ |
| 指针（含 void*） | ✅ |
| 二维数组指针 | ✅ |
| 函数（传参/返回值/指针传参/数组传参） | ✅ |
| 字符串处理 | ✅ |
| 结构体 `.` `->` typedef 内存对齐 | ✅ |
| 枚举 enum | ✅ |
| 位运算 `\|=` `&=` `~` | ✅ |
| volatile | ✅ |
| **🔴 开始 STM32** | 🔄 看视频中 |

---

## 🛠️ 开发环境

| 用途 | 工具 |
|------|------|
| C 编译运行 | VMware Ubuntu 20.04 + gcc 9.4.0 |
| 写代码 | VS Code (Windows)，共享文件夹同步到 Ubuntu |
| 版本管理 | Git + GitHub（Watt Toolkit 加速） |
| STM32 编译 | VS Code + arm-none-eabi-gcc 14.3.1 + CMake + Ninja |
| 虚拟机 | VMware Workstation 17.5.2 |
| 备选 | WSL Ubuntu 24.04 + gcc 13.3.0 |

### STM32 工具链路径
- CMake: `C:\Users\Dell\AppData\Local\stm32cube\bundles\cmake\4.3.1+st.1\bin\cmake.exe`
- Ninja: `C:\Users\Dell\AppData\Local\stm32cube\bundles\ninja\1.13.2+st.1\bin\ninja.exe`
- GCC: `C:\Users\Dell\AppData\Local\stm32cube\bundles\gnu-tools-for-stm32\14.3.1+st.2\bin\`
- CubeMX CLI: VS Code 扩展 `stmicroelectronics.stm32cube-ide-core-1.3.0`

---

## 🎮 开发板

**正点原子 Mini STM32H562VIT6** + DAP 下载器
- 芯片：Cortex-M33, 250MHz, 2MB Flash, 640KB SRAM
- 板载：光传感器、EEPROM、QSPI Flash 16MB、音频编解码+喇叭+咪头

---

## 🗺️ 完整学习路线

```
C语言 ✅ → STM32裸机 → 电路复习 → FreeRTOS → Linux系统编程 → Linux驱动/BSP → 🎯找工作
 (完成)     (2-3月)     (2周)     (1-2月)     (1-2月)        (3-6月)
```

### STM32 外设学习顺序
1. GPIO — LED 点亮/熄灭、按键检测
2. 外部中断 EXTI — 按键触发中断
3. 串口 USART — printf 重定向、中断收发
4. 定时器 — 定时中断、1秒 LED 翻转
5. PWM — LED 亮度、蜂鸣器
6. ADC — 电位器/光敏/温度传感器
7. I2C — OLED 显示屏、温湿度传感器
8. SPI — SPI Flash 读写

### STM32 项目路线
| # | 项目 | 覆盖知识点 |
|:--:|------|-----------|
| 1 | 串口控制 LED 系统 | GPIO、串口、字符串解析 |
| 2 | 环境数据采集与报警 | ADC、定时器、PWM、串口 |
| 3 | 桌面环境监测仪 | OLED、I2C 传感器、按键切换 |
| 4 | 多传感器监测终端（简历项目） | 全部外设整合、模块化编程 |

### 📺 B站课程
- **主线**：正点原子 HAL库开发全集 `BV1bv4y1R7dp`（357万播放）
- **备选**：`BV1dzCJYFEsD`「STM32快速入门开发秘籍」（2024新出，高清字幕）
- H562 兼容性：HAL API 通用，替换引脚名即可

---

## 🏷️ 教学风格

- 称呼用户为**"老大"**，态度恭敬
- **出例题 → 检查代码 → 点评优化** 三步教学
- 用户英语不太好 → 变量名清晰自解释，不用缩写和数字下标
  - ❌ `int b[4]`, `sub`, `av`, `nu`
  - ✅ `int excellent, good, pass, fail`, `sum`, `avg`
- 代码尽量简洁，单行 if 可以不加大括号
- 循环变量 i 从 0 开始

---

## 📁 目录结构

```
E:\c语言大作业\学习\
├── CLAUDE.md                      ← 本文件（Claude Code 自动加载）
├── README.md
├── LEARNING_ROADMAP.md            ← 旧版学习路线
├── BSP工程师完整学习路线.md        ← 最新学习路线（含网课链接）
├── 嵌入式实习岗位分析.md           ← 三类实习岗位分析
├── pointer_arithmetic_exercise.c  ← 指针运算练习（含答案）
├── pointer_2d_exercise.c          ← 二维数组指针练习
├── function_exercise.c            ← 函数练习（6合1）
├── ClaudeCode-C语言学习.bat       ← 一键启动 Claude Code
├── 老大学习之路/                  ← 记忆 & 快捷方式集中管理
├── stm32H562/                    ← 正点原子资料盘
├── stm32h562_test/               ← CMake + GCC 测试工程
├── 自主学习/                      ← 自主学习资料
└── 总实验报告/                    ← 学校实验报告
```

---

## 🎯 实习目标时间线

| 阶段 | 能投什么 | 预计用时 | 薪资 |
|------|------|:--:|------|
| STM32 学完 + 2个项目 | MCU 嵌入式实习生 | 2~3 个月 | 120~400/天 |
| + Linux 入门 + 字符设备驱动 | BSP/驱动实习生 | 5~6 个月 | 4K~9K/月 |
| 全路线走完 | 芯片原厂 BSP | 8~12 个月 | 15K~25K/月 |

### 投递关键词
`嵌入式实习生` `BSP实习生` `MCU实习生` `驱动开发实习生` `单片机开发实习生`

### 面试高频题（10道）
1. static 关键字作用
2. const 用法和位置含义
3. 指针和数组的区别
4. 结构体内存对齐
5. 大端小端
6. 中断的概念和流程
7. I2C 和 SPI 的区别
8. 进程和线程的区别
9. volatile 关键字
10. 链表反转

---

## 📝 工程规范（STM32 项目结构）

```
Project
├── Core
├── Drivers
├── BSP
│   ├── bsp_led.c / bsp_led.h
│   ├── bsp_key.c / bsp_key.h
│   ├── bsp_usart.c / bsp_usart.h
│   ├── bsp_oled.c / bsp_oled.h
│   └── bsp_sensor.c / bsp_sensor.h
├── APP
│   ├── app_display.c / app_display.h
│   └── app_sensor.c / app_sensor.h
└── main.c
```

每个项目写 README（简介、硬件清单、功能、遇到的问题+解决），录演示视频，上传 GitHub。

---

> 💡 **核心策略**：学到结构体就开 STM32，边做项目边补 C。数组+指针+函数+结构体已覆盖 HAL 库 80% 的需求。
