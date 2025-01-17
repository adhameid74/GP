################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CAN_program.c \
../src/DIO_program.c \
../src/DoCAN_program.c \
../src/GW_main.c \
../src/NVIC_program.c \
../src/RCC_program.c \
../src/UART_program.c 

OBJS += \
./src/CAN_program.o \
./src/DIO_program.o \
./src/DoCAN_program.o \
./src/GW_main.o \
./src/NVIC_program.o \
./src/RCC_program.o \
./src/UART_program.o 

C_DEPS += \
./src/CAN_program.d \
./src/DIO_program.d \
./src/DoCAN_program.d \
./src/GW_main.d \
./src/NVIC_program.d \
./src/RCC_program.d \
./src/UART_program.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


