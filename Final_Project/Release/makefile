################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include SRC/subdir.mk
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
Final_Project_3001.lss \

FLASH_IMAGE += \
Final_Project_3001.hex \

EEPROM_IMAGE += \
Final_Project_3001.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Final_Project_3001.elf secondary-outputs

# Tool invocations
Final_Project_3001.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Final_Project_3001.map -Wl,-u,vfprintf -lprintf_flt -lm -L"C:\Users\coshea\Desktop\3001_Workspace\RBELib\Release" -mmcu=atmega644p -o "Final_Project_3001.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Final_Project_3001.lss: Final_Project_3001.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Final_Project_3001.elf  >"Final_Project_3001.lss"
	@echo 'Finished building: $@'
	@echo ' '

Final_Project_3001.hex: Final_Project_3001.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Final_Project_3001.elf  "Final_Project_3001.hex"
	@echo 'Finished building: $@'
	@echo ' '

Final_Project_3001.eep: Final_Project_3001.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Final_Project_3001.elf  "Final_Project_3001.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Final_Project_3001.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega644p Final_Project_3001.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Final_Project_3001.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
