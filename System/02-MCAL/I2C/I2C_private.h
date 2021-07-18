/**
 *  @Title        : I2C Module 
 *  @Filename     : I2C_private.h
 *  @Author       : Ahmed Hendawy
 *  @Origin Date  : 20/11/2020
 *  @Version      : 1.0.0
 *  @Notes        : None
 *  
 */
 
#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H

typedef struct{
	volatile u32 CR1   ;
	volatile u32 CR2   ;
	volatile u32 OAR1  ;
	volatile u32 OAR2  ;
	volatile u32 DR    ;
	volatile u32 SR1   ;
	volatile u32 SR2   ;
	volatile u32 CCR   ;
	volatile u32 TRISE ;	
}I2C_Regs;

#define I2C1_ADDRESS   0x40005400
#define I2C1           ((volatile I2C_Regs *)I2C1_ADDRESS)


#define I2C2_ADDRESS   0x40005800
#define I2C2           ((volatile I2C_Regs *)I2C2_ADDRESS)

#define SM               0
#define FM               1

#define ENABLE           1
#define DISABLE          0
 
#define ADDDRESS_7BIT    0
 
 #define DTCNUM                     4

#define FAILED_THRESHOLD           10
#define PASSED_THRESHOLD           -10
#define AGING_THRESHOLD            255

static dtcItem_t I2C_DTC[DTCNUM];
static dtcProperty_t I2C_PROP[DTCNUM];

#endif 
