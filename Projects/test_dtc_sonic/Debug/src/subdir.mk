################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CAN_program.c \
../src/DIO_program.c \
../src/DTC_program.c \
../src/DoCAN_program.c \
../src/EEPROM_program.c \
../src/I2C_program.c \
../src/NVIC_program.c \
../src/RCC_program.c \
../src/TIMER_program.c \
../src/UART_program.c \
../src/UDSHandler_program.c \
../src/UDS_ClearDiagnosticInformation_program.c \
../src/UDS_ControlDTCSetting_program.c \
../src/UDS_DiagnosticSessionControl_program.c \
../src/UDS_ECUReset_program.c \
../src/UDS_ReadDTCInformation_program.c \
../src/UDS_ReadDataById_program.c \
../src/UDS_RequestDownload_program.c \
../src/UDS_RequestTransferExit_program.c \
../src/UDS_TesterPresent_program.c \
../src/UDS_TransferData_program.c \
../src/UDS_WriteDataById_program.c \
../src/USONIC_program.c \
../src/main.c 

OBJS += \
./src/CAN_program.o \
./src/DIO_program.o \
./src/DTC_program.o \
./src/DoCAN_program.o \
./src/EEPROM_program.o \
./src/I2C_program.o \
./src/NVIC_program.o \
./src/RCC_program.o \
./src/TIMER_program.o \
./src/UART_program.o \
./src/UDSHandler_program.o \
./src/UDS_ClearDiagnosticInformation_program.o \
./src/UDS_ControlDTCSetting_program.o \
./src/UDS_DiagnosticSessionControl_program.o \
./src/UDS_ECUReset_program.o \
./src/UDS_ReadDTCInformation_program.o \
./src/UDS_ReadDataById_program.o \
./src/UDS_RequestDownload_program.o \
./src/UDS_RequestTransferExit_program.o \
./src/UDS_TesterPresent_program.o \
./src/UDS_TransferData_program.o \
./src/UDS_WriteDataById_program.o \
./src/USONIC_program.o \
./src/main.o 

C_DEPS += \
./src/CAN_program.d \
./src/DIO_program.d \
./src/DTC_program.d \
./src/DoCAN_program.d \
./src/EEPROM_program.d \
./src/I2C_program.d \
./src/NVIC_program.d \
./src/RCC_program.d \
./src/TIMER_program.d \
./src/UART_program.d \
./src/UDSHandler_program.d \
./src/UDS_ClearDiagnosticInformation_program.d \
./src/UDS_ControlDTCSetting_program.d \
./src/UDS_DiagnosticSessionControl_program.d \
./src/UDS_ECUReset_program.d \
./src/UDS_ReadDTCInformation_program.d \
./src/UDS_ReadDataById_program.d \
./src/UDS_RequestDownload_program.d \
./src/UDS_RequestTransferExit_program.d \
./src/UDS_TesterPresent_program.d \
./src/UDS_TransferData_program.d \
./src/UDS_WriteDataById_program.d \
./src/USONIC_program.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


