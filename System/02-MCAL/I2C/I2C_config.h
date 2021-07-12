/**
 *  @Title        : I2C Module 
 *  @Filename     : I2C_config.h
 *  @Author       : Ahmed Hendawy
 *  @Origin Date  : 20/11/2020
 *  @Version      : 1.0.0
 *  @Notes        : None
 *  
 */
 
#ifndef I2C_CONFIG_H
#define I2C_CONFIG_H
 /*SM (Standard Mode)
  *FM (Fast Mode)
  */
 #define I2C_MODE            FM

#define DUTY                 ENABLE
 /************************************************/
 #define ACKNOWLEDGE         ENABLE
 
 #define PEC                 DISABLE
 /*************************************************/
 #define GENERAL_CALL	     DISABLE
 /* You can change it from 2MHZ for SM mode(Standard Mode) 
 * or 4MHZ for FM(Fast Mode) to 50MHZ .
 * Value in MHZ
 */
 #define PERIPHERAL_FREQ     8
 /* Value in KHZ
 */
 #define SCL_FREQ            400
 
 #define ADDRESSING_MODE     ADDDRESS_7BIT
 

 
 #define DUAL_ADDRESS        DISABLE
 
 #define I2C_TIMEOUT        5000
 
#endif 
