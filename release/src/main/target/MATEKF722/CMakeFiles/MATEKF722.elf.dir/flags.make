# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# compile ASM with /home/andi/git/inav/tools/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-gcc
# compile C with /home/andi/git/inav/tools/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-gcc
ASM_DEFINES = -DARM_MATH_CM7 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -DFC_VERSION_MAJOR=3 -DFC_VERSION_MINOR=1 -DFC_VERSION_PATCH_LEVEL=0 -DHSE_VALUE=8000000 -DMATEKF722 -DMCU_FLASH_SIZE=512 -DMCU_RAM_SIZE=256 -DSTM32F7 -DSTM32F722xE -DSTM32F722xx -DUNALIGNED_SUPPORT_DISABLE -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DUSE_USB_MSC -D__FORKNAME__=inav -D__FPU_PRESENT=1 -D__REVISION__=\"89168412\" -D__TARGET__=\"MATEKF722\"

ASM_INCLUDES = -I/home/andi/git/inav/src/main/target/MATEKF722 -I/home/andi/git/inav/lib/main/STM32F7/Drivers/STM32F7xx_HAL_Driver/Inc -I/home/andi/git/inav/lib/main/STM32F7/Drivers/CMSIS/Device/ST/STM32F7xx/Include -I/home/andi/git/inav/lib/main/STM32F7/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I/home/andi/git/inav/lib/main/STM32F7/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I/home/andi/git/inav/lib/main/STM32F7/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -I/home/andi/git/inav/lib/main/STM32F7/Middlewares/ST/STM32_USB_Device_Library/Class/CDC_HID/Inc -I/home/andi/git/inav/lib/main/STM32F7/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc -I/home/andi/git/inav/src/main/vcp_hal -I/home/andi/git/inav/lib/main/CMSIS/Core/Include -I/home/andi/git/inav/lib/main/CMSIS/DSP/Include -I/home/andi/git/inav/src/main/target -I/home/andi/git/inav/release/src/main/target/MATEKF722/MATEKF722 -I/home/andi/git/inav/lib -I/home/andi/git/inav/src/main -I/home/andi/git/inav/lib/main/MAVLink

ASM_FLAGS = -DNDEBUG -ffunction-sections -fdata-sections -fno-common -mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-sp-d16 -fsingle-precision-constant -Wdouble-promotion -Os -Wall -Wextra -Wunsafe-loop-optimizations -Wstrict-prototypes -Werror=switch

C_DEFINES = -DARM_MATH_CM7 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -DFC_VERSION_MAJOR=3 -DFC_VERSION_MINOR=1 -DFC_VERSION_PATCH_LEVEL=0 -DHSE_VALUE=8000000 -DMATEKF722 -DMCU_FLASH_SIZE=512 -DMCU_RAM_SIZE=256 -DSTM32F7 -DSTM32F722xE -DSTM32F722xx -DUNALIGNED_SUPPORT_DISABLE -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DUSE_USB_MSC -D__FORKNAME__=inav -D__FPU_PRESENT=1 -D__REVISION__=\"89168412\" -D__TARGET__=\"MATEKF722\"

C_INCLUDES = -I/home/andi/git/inav/src/main/target/MATEKF722 -I/home/andi/git/inav/lib/main/STM32F7/Drivers/STM32F7xx_HAL_Driver/Inc -I/home/andi/git/inav/lib/main/STM32F7/Drivers/CMSIS/Device/ST/STM32F7xx/Include -I/home/andi/git/inav/lib/main/STM32F7/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I/home/andi/git/inav/lib/main/STM32F7/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I/home/andi/git/inav/lib/main/STM32F7/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -I/home/andi/git/inav/lib/main/STM32F7/Middlewares/ST/STM32_USB_Device_Library/Class/CDC_HID/Inc -I/home/andi/git/inav/lib/main/STM32F7/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc -I/home/andi/git/inav/src/main/vcp_hal -I/home/andi/git/inav/lib/main/CMSIS/Core/Include -I/home/andi/git/inav/lib/main/CMSIS/DSP/Include -I/home/andi/git/inav/src/main/target -I/home/andi/git/inav/release/src/main/target/MATEKF722/MATEKF722 -I/home/andi/git/inav/lib -I/home/andi/git/inav/src/main -I/home/andi/git/inav/lib/main/MAVLink

C_FLAGS = -DNDEBUG -flto -fno-fat-lto-objects -ffunction-sections -fdata-sections -fno-common -mthumb -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-sp-d16 -fsingle-precision-constant -Wdouble-promotion -Os -Wall -Wextra -Wunsafe-loop-optimizations -Wstrict-prototypes -Werror=switch -std=gnu99

