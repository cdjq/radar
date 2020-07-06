################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../A111_examples/example_assembly_test.c \
../A111_examples/example_detector_distance_peak.c \
../A111_examples/example_detector_presence.c \
../A111_examples/example_service_envelope.c \
../A111_examples/example_service_iq.c \
../A111_examples/example_service_power_bins.c \
../A111_examples/example_service_sparse.c \
../A111_examples/ref_app_smart_presence.c 

OBJS += \
./A111_examples/example_assembly_test.o \
./A111_examples/example_detector_distance_peak.o \
./A111_examples/example_detector_presence.o \
./A111_examples/example_service_envelope.o \
./A111_examples/example_service_iq.o \
./A111_examples/example_service_power_bins.o \
./A111_examples/example_service_sparse.o \
./A111_examples/ref_app_smart_presence.o 

C_DEPS += \
./A111_examples/example_assembly_test.d \
./A111_examples/example_detector_distance_peak.d \
./A111_examples/example_detector_presence.d \
./A111_examples/example_service_envelope.d \
./A111_examples/example_service_iq.d \
./A111_examples/example_service_power_bins.d \
./A111_examples/example_service_sparse.d \
./A111_examples/ref_app_smart_presence.d 


# Each subdirectory must supply rules for building sources it contributes
A111_examples/example_assembly_test.o: ../A111_examples/example_assembly_test.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"A111_examples/example_assembly_test.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
A111_examples/example_detector_distance_peak.o: ../A111_examples/example_detector_distance_peak.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"A111_examples/example_detector_distance_peak.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
A111_examples/example_detector_presence.o: ../A111_examples/example_detector_presence.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"A111_examples/example_detector_presence.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
A111_examples/example_service_envelope.o: ../A111_examples/example_service_envelope.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"A111_examples/example_service_envelope.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
A111_examples/example_service_iq.o: ../A111_examples/example_service_iq.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"A111_examples/example_service_iq.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
A111_examples/example_service_power_bins.o: ../A111_examples/example_service_power_bins.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"A111_examples/example_service_power_bins.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
A111_examples/example_service_sparse.o: ../A111_examples/example_service_sparse.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"A111_examples/example_service_sparse.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
A111_examples/ref_app_smart_presence.o: ../A111_examples/ref_app_smart_presence.c
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_examples" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_integration" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/include" -I"C:/Users/Administrator.DESKTOP-4OCOQKF/Desktop/PCR102_Truestudio_v_2_0/PCR102_SWV20/A111_rss/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"A111_examples/ref_app_smart_presence.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

