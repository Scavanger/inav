# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# compile ASM with /home/andi/git/inav/tools/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-gcc
# compile C with /home/andi/git/inav/tools/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-gcc
ASM_DEFINES = -DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -DFC_VERSION_MAJOR=3 -DFC_VERSION_MINOR=1 -DFC_VERSION_PATCH_LEVEL=0 -DHSE_VALUE=8000000 -DMCU_FLASH_SIZE=256 -DSPRACINGF3 -DSTM32F3 -DSTM32F303 -DSTM32F303xC -DUNALIGNED_SUPPORT_DISABLE -DUSE_STDPERIPH_DRIVER -D__FORKNAME__=inav -D__FPU_PRESENT=1 -D__REVISION__=\"89168412\" -D__TARGET__=\"SPRACINGF3\"

ASM_INCLUDES = -I/home/andi/git/inav/src/main/target/SPRACINGF3 -I/home/andi/git/inav/lib/main/STM32F3/Drivers/STM32F30x_StdPeriph_Driver/inc -I/home/andi/git/inav/lib/main/STM32F3/Drivers/CMSIS/Device/ST/STM32F30x -I/home/andi/git/inav/lib/main/STM32F3/Drivers/CMSIS -I/home/andi/git/inav/src/main/vcp -I/home/andi/git/inav/lib/main/CMSIS/Core/Include -I/home/andi/git/inav/lib/main/CMSIS/DSP/Include -I/home/andi/git/inav/src/main/target -I/home/andi/git/inav/release/src/main/target/SPRACINGF3/SPRACINGF3 -I/home/andi/git/inav/lib -I/home/andi/git/inav/src/main -I/home/andi/git/inav/lib/main/MAVLink

ASM_FLAGS = -DNDEBUG -ffunction-sections -fdata-sections -fno-common -mthumb -mcpu=cortex-m4 -march=armv7e-m -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -Wdouble-promotion -Os -Wall -Wextra -Wunsafe-loop-optimizations -Wstrict-prototypes -Werror=switch

C_DEFINES = -DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -DFC_VERSION_MAJOR=3 -DFC_VERSION_MINOR=1 -DFC_VERSION_PATCH_LEVEL=0 -DHSE_VALUE=8000000 -DMCU_FLASH_SIZE=256 -DSPRACINGF3 -DSTM32F3 -DSTM32F303 -DSTM32F303xC -DUNALIGNED_SUPPORT_DISABLE -DUSE_STDPERIPH_DRIVER -D__FORKNAME__=inav -D__FPU_PRESENT=1 -D__REVISION__=\"89168412\" -D__TARGET__=\"SPRACINGF3\"

C_INCLUDES = -I/home/andi/git/inav/src/main/target/SPRACINGF3 -I/home/andi/git/inav/lib/main/STM32F3/Drivers/STM32F30x_StdPeriph_Driver/inc -I/home/andi/git/inav/lib/main/STM32F3/Drivers/CMSIS/Device/ST/STM32F30x -I/home/andi/git/inav/lib/main/STM32F3/Drivers/CMSIS -I/home/andi/git/inav/src/main/vcp -I/home/andi/git/inav/lib/main/CMSIS/Core/Include -I/home/andi/git/inav/lib/main/CMSIS/DSP/Include -I/home/andi/git/inav/src/main/target -I/home/andi/git/inav/release/src/main/target/SPRACINGF3/SPRACINGF3 -I/home/andi/git/inav/lib -I/home/andi/git/inav/src/main -I/home/andi/git/inav/lib/main/MAVLink

C_FLAGS = -DNDEBUG -flto -fno-fat-lto-objects -ffunction-sections -fdata-sections -fno-common -mthumb -mcpu=cortex-m4 -march=armv7e-m -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -Wdouble-promotion -Os -Wall -Wextra -Wunsafe-loop-optimizations -Wstrict-prototypes -Werror=switch -std=gnu99

