################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include A111_integration/subdir.mk
-include A111_examples/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
PCR102_SWV20.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
PCR102_SWV20.list \

OBJCOPY_BIN += \
PCR102_SWV20.bin \


# All Target
all:
	+@make --no-print-directory main-build && make --no-print-directory post-build

# Main-build Target
main-build: PCR102_SWV20.elf secondary-outputs

# Tool invocations
PCR102_SWV20.elf: $(OBJS) $(USER_OBJS) ../STM32L431RC_FLASH.ld
	arm-none-eabi-gcc -o "PCR102_SWV20.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"../STM32L431RC_FLASH.ld" --specs=nosys.specs -Wl,-Map="PCR102_SWV20.map" -Wl,--gc-sections -static -L"C:\Users\Administrator.DESKTOP-4OCOQKF\Desktop\PCR102_Truestudio_v_2_0\PCR102_SWV20\A111_rss\lib" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

PCR102_SWV20.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "PCR102_SWV20.list"
	@echo 'Finished building: $@'
	@echo ' '

PCR102_SWV20.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "PCR102_SWV20.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	arm-none-eabi-objcopy.exe -O ihex "PCR102_SWV20.elf" "PCR102_SWV20.hex"
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
