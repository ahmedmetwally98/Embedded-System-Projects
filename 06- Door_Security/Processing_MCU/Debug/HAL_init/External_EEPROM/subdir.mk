################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL_init/External_EEPROM/external_eeprom.c 

OBJS += \
./HAL_init/External_EEPROM/external_eeprom.o 

C_DEPS += \
./HAL_init/External_EEPROM/external_eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
HAL_init/External_EEPROM/%.o: ../HAL_init/External_EEPROM/%.c HAL_init/External_EEPROM/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


