# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# compile ASM with /home/andi/git/inav/tools/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-gcc
# compile C with /home/andi/git/inav/tools/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-gcc
ASM_DEFINES = -DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -DFC_VERSION_MAJOR=3 -DFC_VERSION_MINOR=1 -DFC_VERSION_PATCH_LEVEL=0 -DHSE_VALUE=8000000 -DMCU_FLASH_SIZE=1024 -DMCU_RAM_SIZE=192 -DMSP_FIRMWARE_UPDATE -DSTM32F4 -DSTM32F405xx -DSTM32F40_41xxx -DUNALIGNED_SUPPORT_DISABLE -DUSE_STDPERIPH_DRIVER -DWINGFC -D__FORKNAME__=inav -D__FPU_PRESENT=1 -D__REVISION__=\"89168412\" -D__TARGET__=\"WINGFC\"

ASM_INCLUDES = -I/home/andi/git/inav/src/main/target/FF_F35_LIGHTNING -I/home/andi/git/inav/lib/main/STM32F4/Drivers/STM32F4xx_StdPeriph_Driver/inc -I/home/andi/git/inav/lib/main/STM32F4/Drivers/CMSIS/Device/ST/STM32F4xx -I/home/andi/git/inav/lib/main/STM32F4/Drivers/CMSIS -I/home/andi/git/inav/src/main/vcpf4 -I/home/andi/git/inav/lib/main/STM32_USB_OTG_Driver/inc -I/home/andi/git/inav/lib/main/STM32_USB_Device_Library/Core/inc -I/home/andi/git/inav/lib/main/STM32_USB_Device_Library/Class/cdc/inc -I/home/andi/git/inav/lib/main/STM32_USB_Device_Library/Class/hid/inc -I/home/andi/git/inav/lib/main/STM32_USB_Device_Library/Class/hid_cdc_wrapper/inc -I/home/andi/git/inav/lib/main/STM32_USB_Device_Library/Class/msc/inc -I/home/andi/git/inav/lib/main/CMSIS/Core/Include -I/home/andi/git/inav/lib/main/CMSIS/DSP/Include -I/home/andi/git/inav/src/main/target -I/home/andi/git/inav/debug/src/main/target/FF_F35_LIGHTNING/WINGFC -I/home/andi/git/inav/lib -I/home/andi/git/inav/src/main -I/home/andi/git/inav/lib/main/MAVLink

ASM_FLAGS = -Og -g -ffunction-sections -fdata-sections -fno-common -mthumb -mcpu=cortex-m4 -march=armv7e-m -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -Wdouble-promotion -Wall -Wextra -Wunsafe-loop-optimizations -Wstrict-prototypes -Werror=switch

C_DEFINES = -DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -DFC_VERSION_MAJOR=3 -DFC_VERSION_MINOR=1 -DFC_VERSION_PATCH_LEVEL=0 -DHSE_VALUE=8000000 -DMCU_FLASH_SIZE=1024 -DMCU_RAM_SIZE=192 -DMSP_FIRMWARE_UPDATE -DSTM32F4 -DSTM32F405xx -DSTM32F40_41xxx -DUNALIGNED_SUPPORT_DISABLE -DUSE_STDPERIPH_DRIVER -DWINGFC -D__FORKNAME__=inav -D__FPU_PRESENT=1 -D__REVISION__=\"89168412\" -D__TARGET__=\"WINGFC\"

C_INCLUDES = -I/home/andi/git/inav/src/main/target/FF_F35_LIGHTNING -I/home/andi/git/inav/lib/main/STM32F4/Drivers/STM32F4xx_StdPeriph_Driver/inc -I/home/andi/git/inav/lib/main/STM32F4/Drivers/CMSIS/Device/ST/STM32F4xx -I/home/andi/git/inav/lib/main/STM32F4/Drivers/CMSIS -I/home/andi/git/inav/src/main/vcpf4 -I/home/andi/git/inav/lib/main/STM32_USB_OTG_Driver/inc -I/home/andi/git/inav/lib/main/STM32_USB_Device_Library/Core/inc -I/home/andi/git/inav/lib/main/STM32_USB_Device_Library/Class/cdc/inc -I/home/andi/git/inav/lib/main/STM32_USB_Device_Library/Class/hid/inc -I/home/andi/git/inav/lib/main/STM32_USB_Device_Library/Class/hid_cdc_wrapper/inc -I/home/andi/git/inav/lib/main/STM32_USB_Device_Library/Class/msc/inc -I/home/andi/git/inav/lib/main/CMSIS/Core/Include -I/home/andi/git/inav/lib/main/CMSIS/DSP/Include -I/home/andi/git/inav/src/main/target -I/home/andi/git/inav/debug/src/main/target/FF_F35_LIGHTNING/WINGFC -I/home/andi/git/inav/lib -I/home/andi/git/inav/src/main -I/home/andi/git/inav/lib/main/MAVLink

C_FLAGS = -Og -g -ffunction-sections -fdata-sections -fno-common -mthumb -mcpu=cortex-m4 -march=armv7e-m -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -Wdouble-promotion -Wall -Wextra -Wunsafe-loop-optimizations -Wstrict-prototypes -Werror=switch -std=gnu99

