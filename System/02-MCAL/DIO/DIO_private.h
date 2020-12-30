/*********************************************************************************
*
* Module      : DIO
*
* File name   : DIO_private.c
*
* Description : Header file for DIO Registers and Private Definition   
* 
* Author      : Ahmed Hendawy 
*
* Date        : 11/9/2020
*
**********************************************************************************/
#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H
/*****************************************************************
*                Register Definition                             *
******************************************************************/
/**
 * That is Registers definition for General Purpose Input Output(GPIO) .
 */
typedef struct {
	volatile u32 CRL  ;/**<Configuration Register Low*/
	volatile u32 CRH  ;/**<Configuration Register High*/
	volatile u32 IDR  ;/**<Input Data Register*/
	volatile u32 ODR  ;/**<Output Data Register*/
	volatile u32 BSRR ;/**<Bit Set/Reset Register*/
	volatile u32 BRR  ;/**<Bit Reset Register*/
	volatile u32 LCKR ;/**<Configuration Lock Register*/
}Dio_Regs;


#define PORTA_ADDRESS  0x40010800
#define PORTA          ((volatile Dio_Regs *)PORTA_ADDRESS)

#define PORTB_ADDRESS  0x40010C00
#define PORTB          ((volatile Dio_Regs *)PORTB_ADDRESS)

#define PORTC_ADDRESS  0x40011000
#define PORTC          ((volatile Dio_Regs *)PORTC_ADDRESS)

#endif
