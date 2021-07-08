/// @file I2C_program.c
/**
 *  @Title        : EEPROM Module 
 *  @Filename     : EEPROM_program.c
 *  @Author       : Ahmed Hendawy
 *  @Origin Date  : 27/12/2020
 *  @Version      : 1.0.0
 *  @Notes        : None 
 *  
 */
 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "I2C_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"

  void HEEPROM_voidWriteByte(u8 Copy_u8EepromAddress ,u16 Copy_u16DataAddress ,u8 Copy_u8Data){

	  u8 MSB = (u8)(Copy_u16DataAddress>>8);
	  u8 LSB = (u8)(Copy_u16DataAddress);
	  u8 Data[3]={MSB,LSB,Copy_u8Data};
	  MI2C_voidTransmit(Copy_u8EepromAddress ,Data,3);
	  
  }
  u8 HEEPROM_u8ReadByte(u8 Copy_u8EepromAddress ,u16 Copy_u16DataAddress){
	  u8 Data ;
	  MI2C_voidReceiveFromAddress(Copy_u8EepromAddress ,&Data,1,Copy_u16DataAddress);
	  return Data;
	  
	  
  }
  void HEEPROM_u8DeleteByte(u8 Copy_u8EepromAddress ,u16 Copy_u16DeleteAddress)
  {
	  u8 MSB = (u8)(Copy_u16DeleteAddress>>8);
	  u8 LSB = (u8)(Copy_u16DeleteAddress);
	  u8 Data[3]={MSB,LSB,0xff};
	  MI2C_voidTransmit(Copy_u8EepromAddress ,Data,3);
  }
  void HEEPROM_voidWriteMultipleBytes(u8 Copy_u8EepromAddress,u16 Copy_u16DataAddress, u16 Copy_u8NumberOfBytes,u8* Copy_u8PtrData)
  {
  	  for(u16 i = 0; i<Copy_u8NumberOfBytes; i++)
  	  {
  		HEEPROM_voidWriteByte(Copy_u8EepromAddress,Copy_u16DataAddress+i,Copy_u8PtrData[i]);
		   for (u16 c = 1; c <= 33000; c++)
		   {
			   asm("NOP");
		   }
  	  }
  }
  void HEEPROM_voidReadMultipleBytes(u8 Copy_u8EepromAddress,u16 Copy_u16DataAddress, u16 Copy_u8NumberOfBytes,u8* Copy_u8PtrData)
    {
  	  for(u16 i = 0; i<Copy_u8NumberOfBytes; i++)
  	  {
  		  Copy_u8PtrData[i] = HEEPROM_u8ReadByte(Copy_u8EepromAddress,Copy_u16DataAddress+i);
  	  }
    }

  void HEEPROM_voidDeleteMultipleBytes(u8 Copy_u8EepromAddress, u16 Copy_u16StartAddress,u16 Copy_u8NumberOfBytes)
  {
  	  for(u16 i = 0; i<Copy_u8NumberOfBytes; i++)
  	  {
  		  HEEPROM_u8DeleteByte(Copy_u8EepromAddress,Copy_u16StartAddress+i);
  	  }
  }
