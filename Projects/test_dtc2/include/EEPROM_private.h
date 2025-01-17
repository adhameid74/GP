/// @file I2C_program.c
/**
 *  @Title        : EEPROM Module 
 *  @Filename     : EEPROM_private.h
 *  @Author       : Ahmed Hendawy
 *  @Origin Date  : 27/12/2020
 *  @Version      : 1.0.0
 *  @Notes        : None 
 *  
 */
 
  #ifndef EEPROM_PRIVATE_H
  #define EEPROM_PRIVATE_H
  void delay(void)
	{
		for (u16 c = 1; c <= 33000; c++)
		{
			asm("NOP");
		}
	}
  
  #endif