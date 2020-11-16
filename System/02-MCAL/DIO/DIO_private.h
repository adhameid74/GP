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

typedef struct {
	u32 CRL  ;
	u32 CRH  ;
	u32 IDR  ;
	u32 ODR  ;
	u32 BSRR ;
	u32 BRR  ;
	u32 LCKR ;
}Dio_Regs;

#define PORTA_ADDRESS  0x40010800
#define PORTA          ((volatile Dio_Regs *)PORTA_ADDRESS)

#define PORTB_ADDRESS  0x40010C00
#define PORTB          ((volatile Dio_Regs *)PORTB_ADDRESS)

#define PORTC_ADDRESS  0x40011000
#define PORTC          ((volatile Dio_Regs *)PORTC_ADDRESS)

#endif