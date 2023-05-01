################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL_init/Interrupt_Driver/INT_External.c 

OBJS += \
./MCAL_init/Interrupt_Driver/INT_External.o 

C_DEPS += \
./MCAL_init/Interrupt_Driver/INT_External.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL_init/Interrupt_Driver/%.o: ../MCAL_init/Interrupt_Driver/%.c MCAL_init/Interrupt_Driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


