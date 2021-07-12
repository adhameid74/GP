#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "I2C_interface.h"

#include "EEPROM_interface.h"

void main (){
	RCC_voidIntiSysClock();
	RCC_voidEnableClock(RCC_APB2,2);
	RCC_voidEnableClock(RCC_APB2,3);
	
	RCC_voidEnableClock(RCC_APB1,21);
	//SCL
	Port_SetPinDirection(PB6 , OUTPUT_S10MHZ);
	Port_SetPinMode(PB6,AF_OUTPUT_OPEN_DRAIN);
	//SDA
	Port_SetPinDirection(PB7 , OUTPUT_S10MHZ);
	Port_SetPinMode(PB7,AF_OUTPUT_OPEN_DRAIN);

//	GPIO_voidSetPinDirection(1,6,OUTPUT_S10MHZ,2);
	//GPIO_voidSetPinDirection(1,7,OUTPUT_S10MHZ,2);
	/***************************/
	Port_SetPinDirection(PA0 , OUTPUT_S10MHZ);
	Port_SetPinMode(PA0,GP_OUTPUT_PUSH_PULL);

	Port_SetPinDirection(PA1 , OUTPUT_S10MHZ);
	Port_SetPinMode(PA1,GP_OUTPUT_PUSH_PULL);

	Port_SetPinDirection(PA2 , OUTPUT_S10MHZ);
	Port_SetPinMode(PA2,GP_OUTPUT_PUSH_PULL);

	Port_SetPinDirection(PA3, OUTPUT_S10MHZ);
	Port_SetPinMode(PA3,GP_OUTPUT_PUSH_PULL);
	


	MI2C_voidInit();
	
	u8 Data[]={0x50,0x88,0x1D,0x19};
	u8 Data1[2]={0};
	/*
    MI2C_u8Transmit(0xA0,Data,4);
	Dio_ChannelGroupType Datax={0xF,0,0};

	MI2C_u8ReceiveFromAddress(0xA0,Data1,2,0x050);

	MI2C_u8Receive(0xA0,Data1,1);
	Dio_WriteChannelGroup(&Datax ,Data1[0]);*/
	Dio_ChannelGroupType Datax={0xF,0,0};
	HEEPROM_voidWriteByte(0xA0,0x50,0X3A);
	HEEPROM_voidWriteByte(0xA0,0x51,0X3A);
	HEEPROM_voidWriteByte(0xA0,0x52,0X3A);
	HEEPROM_voidWriteByte(0xA0,0x53,0X3A);
	volatile u8 x= HEEPROM_u8ReadByte(0xA0,0x50);
	Dio_WriteChannelGroup(&Datax ,Data1[0]);
	HEEPROM_voidWriteWord(0xA0,0x20,0x0000001A);
	x= HEEPROM_u8ReadByte(0xA0,0x20);
	x= HEEPROM_u8ReadByte(0xA0,0x21);
	x= HEEPROM_u8ReadByte(0xA0,0x22);
	x= HEEPROM_u8ReadByte(0xA0,0x23);
	volatile u32 z=HEEPROM_u32ReadWord(0xA0,0x50);
	Dio_WriteChannelGroup(&Datax ,Data1[0]);
}
