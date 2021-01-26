/**********************************************************/
/* Author		: Abdallah Hassan 		*/
/* Date 		: 8/8/2020				*/
/* Version		: V01					*/
/**********************************************************/

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/* Register Definitions */
/*				clock system on processor		    	*/
#define RCC_CR					*((volatile u32*)0x40021000) 
#define RCC_CFGR				*((volatile u32*)0x40021004)
/********************************************************/
#define RCC_CIR					*((volatile u32*)0x40021008)
#define RCC_APB2RSTR			*((volatile u32*)0x4002100C)
#define RCC_APB1RSTR			*((volatile u32*)0x40021010)
#define RCC_AHBENR				*((volatile u32*)0x40021014)
#define RCC_APB2ENR				*((volatile u32*)0x40021018)
#define RCC_APB1ENR				*((volatile u32*)0x4002101C)
#define RCC_BDCR				*((volatile u32*)0x40021020)
#define RCC_CSR					*((volatile u32*)0x40021024)


#define RCC_HSE_CRYSTAL			0
#define RCC_HSE_EC				1
#define RCC_HSI					2
#define RCC_PLL					3

#define RCC_HSE 				0
#define RCC_HSI_OVER_2			1
#define RCC_HSE_OVER_2			2

#define RCC_MULTIPLY_2 			0
#define RCC_MULTIPLY_3 			1
#define RCC_MULTIPLY_4 			2
#define RCC_MULTIPLY_5 			3
#define RCC_MULTIPLY_6 			4
#define RCC_MULTIPLY_7 			5
#define RCC_MULTIPLY_8 			6
#define RCC_MULTIPLY_9 			7
#define RCC_MULTIPLY_10 		8
#define RCC_MULTIPLY_11 		9
#define RCC_MULTIPLY_12 		10
#define RCC_MULTIPLY_13 		11
#define RCC_MULTIPLY_14 		12
#define RCC_MULTIPLY_15			13
#define RCC_MULTIPLY_16 		14

#define RCC_MULT_MASK 			0xffc3ffff



#endif