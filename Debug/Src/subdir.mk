################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/global.c \
../Src/gpio.c \
../Src/main.c \
../Src/radar.c \
../Src/rtu.c \
../Src/spi.c \
../Src/stm32l4xx_hal_msp.c \
../Src/stm32l4xx_it.c \
../Src/system_stm32l4xx.c \
../Src/tim.c \
../Src/usart.c 

OBJS += \
./Src/global.o \
./Src/gpio.o \
./Src/main.o \
./Src/radar.o \
./Src/rtu.o \
./Src/spi.o \
./Src/stm32l4xx_hal_msp.o \
./Src/stm32l4xx_it.o \
./Src/system_stm32l4xx.o \
./Src/tim.o \
./Src/usart.o 

C_DEPS += \
./Src/global.d \
./Src/gpio.d \
./Src/main.d \
./Src/radar.d \
./Src/rtu.d \
./Src/spi.d \
./Src/stm32l4xx_hal_msp.d \
./Src/stm32l4xx_it.d \
./Src/system_stm32l4xx.d \
./Src/tim.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/global.o: ../Src/global.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/global.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/gpio.o: ../Src/gpio.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/main.o: ../Src/main.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/radar.o: ../Src/radar.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/radar.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/rtu.o: ../Src/rtu.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/rtu.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/spi.o: ../Src/spi.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/spi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/stm32l4xx_hal_msp.o: ../Src/stm32l4xx_hal_msp.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/stm32l4xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/stm32l4xx_it.o: ../Src/stm32l4xx_it.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/stm32l4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/system_stm32l4xx.o: ../Src/system_stm32l4xx.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/system_stm32l4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/tim.o: ../Src/tim.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/tim.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/usart.o: ../Src/usart.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/usart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

