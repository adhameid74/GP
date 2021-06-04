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

  #define EEPROM_ADDRESS                    0x0A
  #define EEPROM_APP_START_ADDRESS          0x04
  #define EEPROM_NUM_OF_LINES_ADDRESS       0xFF

  void HEEPROM_voidWriteByte(u8 Copy_u8EepromAddress ,u8 Copy_u8DataAddress ,u8 Copy_u8Data);
  u8 HEEPROM_u8ReadByte(u8 Copy_u8EepromAddress ,u8 Copy_u8DataAddress);
  void HEEPROM_voidWriteWord(u8 Copy_u8EepromAddress ,u8 Copy_u8DataAddress ,u32 Copy_u32Data);
  u32 HEEPROM_u32ReadWord(u8 Copy_u8EepromAddress ,u8 Copy_u8DataAddress);
  #endif