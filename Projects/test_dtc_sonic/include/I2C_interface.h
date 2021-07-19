/// @file I2C_interface..h
/**
 *  @Title        : I2C Module 
 *  @Filename     : I2C_interface.h
 *  @Author       : Ahmed Hendawy
 *  @Origin Date  : 20/11/2020
 *  @Version      : 1.0.0
 *  @Notes        : None
 *  
 */
 
#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H
 
 #define NULL ((void *)0)
 void MI2C_voidInti();
 void MI2C_voidTransmit(u8 Copy_u8SlaveAddress , u8 *DataToTransmit,u8 Copy_u8NumberOfData);
 void MI2C_voidReceive (u8 Copy_u8SlaveAddress , u8 *DataToReceive ,u8 Copy_u8NumberOfData);
 void MI2C_voidReceiveFromAddress(u8 Copy_u8SlaveAddress , u8 *DataToReceive ,u8 Copy_u8NumberOfData,u16 Copy_u16AddressOfLocation);
 
 
#endif 
