cmake_minimum_required(VERSION 3.20)

# ═══════════════════════════════════════════
#  STM32H562VIT6 裸机最小工程 — 验证工具链
# ═══════════════════════════════════════════

set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# ── 交叉编译工具链 ──
set(TOOLCHAIN_DIR "C:/Users/Dell/AppData/Local/stm32cube/bundles/gnu-tools-for-stm32/14.3.1+st.2")

set(CMAKE_C_COMPILER    "${TOOLCHAIN_DIR}/bin/arm-none-eabi-gcc.exe"   CACHE STRING "" FORCE)
set(CMAKE_ASM_COMPILER  "${TOOLCHAIN_DIR}/bin/arm-none-eabi-gcc.exe"   CACHE STRING "" FORCE)
set(CMAKE_OBJCOPY       "${TOOLCHAIN_DIR}/bin/arm-none-eabi-objcopy.exe")
set(CMAKE_OBJDUMP       "${TOOLCHAIN_DIR}/bin/arm-none-eabi-objdump.exe")
set(CMAKE_SIZE          "${TOOLCHAIN_DIR}/bin/arm-none-eabi-size.exe")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(stm32h562_test C ASM)

# ── CPU 选项 (Cortex-M33 + FPU) ──
set(CPU_FLAGS "-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16")
set(CMAKE_C_FLAGS       "${CPU_FLAGS} -std=gnu11 -Wall -Wextra -ffunction-sections -fdata-sections -O0 -g" CACHE STRING "" FORCE)
set(CMAKE_ASM_FLAGS     "${CPU_FLAGS}" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS
    "${CPU_FLAGS} -specs=nosys.specs -specs=nano.specs -Wl,--gc-sections -Wl,-Map=${PROJECT_NAME}.map"
    CACHE STRING "" FORCE)

# ── 源文件 ──
add_executable(${PROJECT_NAME}
    Core/Src/main.c
    Core/Src/startup_stm32h562xx.s
)

# ── 链接脚本 ──
target_link_options(${PROJECT_NAME} PRIVATE
    -T "${PROJECT_SOURCE_DIR}/STM32H562VITx_FLASH.ld")

# ── 编译后处理 ──
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}>
    COMMENT ">>> 生成 hex / bin 文件")
