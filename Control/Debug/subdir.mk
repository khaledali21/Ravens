################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Blocks.c \
../DDIO_128.c \
../PWM.c \
../USART_128.c \
../croutine.c \
../gps.c \
../heap_1.c \
../list.c \
../main.c \
../port.c \
../queue.c \
../strTof.c \
../tasks.c \
../timers.c 

OBJS += \
./Blocks.o \
./DDIO_128.o \
./PWM.o \
./USART_128.o \
./croutine.o \
./gps.o \
./heap_1.o \
./list.o \
./main.o \
./port.o \
./queue.o \
./strTof.o \
./tasks.o \
./timers.o 

C_DEPS += \
./Blocks.d \
./DDIO_128.d \
./PWM.d \
./USART_128.d \
./croutine.d \
./gps.d \
./heap_1.d \
./list.d \
./main.d \
./port.d \
./queue.d \
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


