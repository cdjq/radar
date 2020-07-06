################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../A111_integration/acc_app_integration_stm32.c \
../A111_integration/acc_hal_integration_single_thread_stm32cube_xc111_r4a.c 

OBJS += \
./A111_integration/acc_app_integration_stm32.o \
./A111_integration/acc_hal_integration_single_thread_stm32cube_xc111_r4a.o 

C_DEPS += \
./A111_integration/acc_app_integration_stm32.d \
./A111_integration/acc_hal_integration_single_thread_stm32cube_xc111_r4a.d 


# Each subdirectory must supply rules for building sources it contributes
A111_integration/acc_app_integration_stm32.o: ../A111_integration/acc_app_integration_stm32.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"A111_integration/acc_app_integration_stm32.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
A111_integration/acc_hal_integration_single_thread_stm32cube_xc111_r4a.o: ../A111_integration/acc_hal_integration_single_thread_stm32cube_xc111_r4a.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"A111_integration/acc_hal_integration_single_thread_stm32cube_xc111_r4a.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

