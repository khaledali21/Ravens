################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Control.lss \

FLASH_IMAGE += \
Control.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: Control.elf secondary-outputs

# Tool invocations
Control.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Control.map -L/usr/lib -mmcu=atmega128 -o "Control.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Control.lss: Control.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Control.elf  >"Control.lss"
	@echo 'Finished building: $@'
	@echo ' '

Control.hex: Control.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Control.elf  "Control.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Control.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 Control.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: Control.elf
	@echo 'Invoking: AVRDude'
	E:\Embedded Course\Tools\SDK\IMT_SDK_Win_64\WinAVR\bin\avrdude -pm128 -Uflash:w:Control.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Control.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
