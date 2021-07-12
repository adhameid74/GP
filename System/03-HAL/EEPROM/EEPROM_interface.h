/// @file I2C_program.c
/**
 *  @Title        : EEPROM Module 
 *  @Filename     : EEPROM_interface.h
 *  @Author       : Ahmed Hendawy
 *  @Origin Date  : 27/12/2020
 *  @Version      : 1.0.0
 *  @Notes        : None 
 *  
 */
  #ifndef EEPROM_INTERFACE_H
  #define EEPROM_INTERFACE_H
  
  #define EEPROM_ADDRESS 0xA0

  #define EEPROM_APP_START_ADDRESS 0x0000
  #define EEPROM_FIRST_ADDRESS 0x0000
  #define EEPROM_LAST_ADDRESS  0xFFFE
  #define EEPROM_SIZE_KB		64
  #define EEPROM_NUMBER_OF_BYTES (EEPROM_LAST_ADDRESS+1)
  #define EEPROM_NUM_OF_LINES_ADDRESS 0xFFFE

  void HEEPROM_voidWriteByte(u8 Copy_u8EepromAddress ,u16 Copy_u16DataAddress ,u8 Copy_u8Data);
  u8 HEEPROM_u8ReadByte(u8 Copy_u8EepromAddress ,u16 Copy_u16DataAddress);
  void HEEPROM_u8DeleteByte(u8 Copy_u8EepromAddress ,u16 Copy_u16DeleteAddress);
  void HEEPROM_voidWriteMultipleBytes(u8 Copy_u8EepromAddress,u16 Copy_u16DataAddress, u16 Copy_u8NumberOfBytes,u8* Copy_u8PtrData);
  void HEEPROM_voidReadMultipleBytes(u8 Copy_u8EepromAddress,u16 Copy_u16DataAddress, u16 Copy_u8NumberOfBytes,u8* Copy_u8PtrData);
  void HEEPROM_voidDeleteMultipleBytes(u8 Copy_u8EepromAddress, u16 Copy_u16StartAddress,u16 Copy_u8NumberOfBytes);
  #endif
