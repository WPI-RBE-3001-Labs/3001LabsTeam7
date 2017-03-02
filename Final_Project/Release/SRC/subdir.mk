################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/ADC.c \
../SRC/DAC.c \
../SRC/PID.c \
../SRC/Periph.c \
../SRC/SPI.c \
../SRC/USARTDebug.c \
../SRC/buttons.c \
../SRC/current.c \
../SRC/final.c \
../SRC/kinematics.c \
../SRC/lab2.c \
../SRC/main.c \
../SRC/matlab.c \
../SRC/motors.c \
../SRC/ports.c \
../SRC/pot.c \
../SRC/sensors.c \
../SRC/servo.c \
../SRC/timer.c 

OBJS += \
./SRC/ADC.o \
./SRC/DAC.o \
./SRC/PID.o \
./SRC/Periph.o \
./SRC/SPI.o \
./SRC/USARTDebug.o \
./SRC/buttons.o \
./SRC/current.o \
./SRC/final.o \
./SRC/kinematics.o \
./SRC/lab2.o \
./SRC/main.o \
./SRC/matlab.o \
./SRC/motors.o \
./SRC/ports.o \
./SRC/pot.o \
./SRC/sensors.o \
./SRC/servo.o \
./SRC/timer.o 

C_DEPS += \
./SRC/ADC.d \
./SRC/DAC.d \
./SRC/PID.d \
./SRC/Periph.d \
./SRC/SPI.d \
./SRC/USARTDebug.d \
./SRC/buttons.d \
./SRC/current.d \
./SRC/final.d \
./SRC/kinematics.d \
./SRC/lab2.d \
./SRC/main.d \
./SRC/matlab.d \
./SRC/motors.d \
./SRC/ports.d \
./SRC/pot.d \
./SRC/sensors.d \
./SRC/servo.d \
./SRC/timer.d 


# Each subdirectory must supply rules for building sources it contributes
SRC/%.o: ../SRC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\coshea\Desktop\3001_Workspace\RBELib\include\RBELib" -I"C:\Users\coshea\Desktop\3001_Workspace\3001LabsTeam7\Lab2\include" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=18432000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


