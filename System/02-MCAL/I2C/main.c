#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "DIO_interface.h"

void main (){{
	RCC_voidIntiSysClock();
	
	RCC_voidEnableClock(RCC_APB1,21);
	//SCL
	Port_SetPinDirection(PB6 , OUTPUT_S10MHZ);
	Port_SetPinMode(PB6,AF_OUTPUT_OPEN_DRAIN);
	//SDA
	Port_SetPinDirection(PB7 , OUTPUT_S10MHZ);
	Port_SetPinMode(PB7,AF_OUTPUT_OPEN_DRAIN);
	
	MI2C_voidInti();
	
	u8 Data[]={0x00,0x01};
	MI2C_voidTransmit(0xA0,Data);
	
	MI2C_voidReceiveFromAddress(0xA0,Data,1,0x00);
	
	
	
}