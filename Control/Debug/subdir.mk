################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Blocks.c \
../DDIO_128.c \
../MPU.c \
../PWM.c \
../USART_128.c \
../croutine.c \
../estimation.c \
../gps.c \
../heap_1.c \
../i2c.c \
../list.c \
../main.c \
../port.c \
../queue.c \
../quickmath.c \
../strTof.c \
../tasks.c \
../timers.c 

OBJS += \
./Blocks.o \
./DDIO_128.o \
./MPU.o \
./PWM.o \
./USART_128.o \
./croutine.o \
./estimation.o \
./gps.o \
./heap_1.o \
./i2c.o \
./list.o \
./main.o \
./port.o \
./queue.o \
./quickmath.o \
./strTof.o \
./tasks.o \
./timers.o 

C_DEPS += \
./Blocks.d \
./DDIO_128.d \
./MPU.d \
./PWM.d \
./USART_128.d \
./croutine.d \
./estimation.d \
./gps.d \
./heap_1.d \
./i2c.d \
./list.d \
./main.d \
./port.d \
./queue.d \
./quickmath.d \
./strTof.d \
./tasks.d \
./timers.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega128 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


