################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL_init/DIO_Driver/hal_DIO.c 

OBJS += \
./MCAL_init/DIO_Driver/hal_DIO.o 

C_DEPS += \
./MCAL_init/DIO_Driver/hal_DIO.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL_init/DIO_Driver/%.o: ../MCAL_init/DIO_Driver/%.c MCAL_init/DIO_Driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


