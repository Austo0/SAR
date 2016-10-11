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
Interupts.lss \

FLASH_IMAGE += \
Interupts.hex \

EEPROM_IMAGE += \
Interupts.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Interupts.elf secondary-outputs

# Tool invocations
Interupts.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Interupts.map -mmcu=atmega328p -o "Interupts.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Interupts.lss: Interupts.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Interupts.elf  >"Interupts.lss"
	@echo 'Finished building: $@'
	@echo ' '

Interupts.hex: Interupts.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Interupts.elf  "Interupts.hex"
	@echo 'Finished building: $@'
	@echo ' '

Interupts.eep: Interupts.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Interupts.elf  "Interupts.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Interupts.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Interupts.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Interupts.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
