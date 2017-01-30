################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/ADC.c \
../SRC/DAC.c \
../SRC/SPI.c \
../SRC/USARTDebug.c \
../SRC/main.c \
../SRC/timer.c 

OBJS += \
./SRC/ADC.o \
./SRC/DAC.o \
./SRC/SPI.o \
./SRC/USARTDebug.o \
./SRC/main.o \
./SRC/timer.o 

C_DEPS += \
./SRC/ADC.d \
./SRC/DAC.d \
./SRC/SPI.d \
./SRC/USARTDebug.d \
./SRC/main.d \
./SRC/timer.d 


# Each subdirectory must supply rules for building sources it contributes
SRC/%.o: ../SRC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\ttruong\Documents\RBELib\include" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=18432000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


