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

  void HEEPROM_voidWriteByte(u8 Copy_u8EepromAddress ,u8 Copy_u8DataAddress ,u8 Copy_u8Data){
	  u8 Data[2]={Copy_u8DataAddress,Copy_u8Data};
	  MI2C_voidTransmit(Copy_u8EepromAddress ,Data,2);
	  
  }
  u8 HEEPROM_u8ReadByte(u8 Copy_u8EepromAddress ,u8 Copy_u8DataAddress){
	  u8 Data ;
	  MI2C_voidReceiveFromAddress(Copy_u8EepromAddress ,&Data,1,Copy_u8DataAddress);
	  return Data;
	  
	  
  }
  void HEEPROM_voidWriteWord(u8 Copy_u8EepromAddress ,u8 Copy_u8DataAddress ,u32 Copy_u32Data){
	  u8 Data[5];
	  Data[0]=Copy_u8DataAddress;
	  Data[1]=(u8)(Copy_u32Data &0xFF);
	  Data[2]=(u8)(Copy_u32Data >> 8 &0xFF);
	  Data[3]=(u8)(Copy_u32Data >> 16 &0xFF);
	  Data[4]=(u8)(Copy_u32Data >> 24 &0xFF);
	  MI2C_voidTransmit(Copy_u8EepromAddress,Data,5);
	  
		
	}
  u32 HEEPROM_u32ReadWord(u8 Copy_u8EepromAddress ,u8 Copy_u8DataAddress){
	  u8 Data[4];
	  u32 Temp;

	  /*
	   * read wrong data
	   * MI2C_voidReceiveFromAddress(Copy_u8EepromAddress ,Data,4,Copy_u8DataAddress);
	  Temp =Data[0] | Data[1] << 8 |Data[2] << 16 |Data[3] << 24 ;
	  return Temp ;*/
	  for(Temp=0;Temp<4;Temp++){

		  Data[Temp]=HEEPROM_u8ReadByte(Copy_u8EepromAddress,Copy_u8DataAddress+Temp);
	  }
	  Temp =Data[0] | Data[1] << 8 |Data[2] << 16 |Data[3] << 24 ;
	  return Temp ;
	  
  }
