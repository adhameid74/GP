/**********************************************/
/* Author   : Abdallah Hassan                 */
/* Date     : 2020-09-27                      */
/* Version  : V01                             */
/**********************************************/
#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

typedef struct
{
	volatile u32	SR;
	volatile u32	DR;
	volatile u32	BRR;
	volatile u32	CR1;
	volatile u32	CR2;
	volatile u32	CR3;
	volatile u32	GRPR;
}MUART_Type;

#define MUART	((volatile MUART_Type*)0x40013800)
#define MUART2	((volatile MUART_Type*)0x40004400)

#define DTCNUM                     2

#define FAILED_THRESHOLD           10
#define PASSED_THRESHOLD           -10
#define AGING_THRESHOLD            255

//static dtcItem_t UART_DTC[DTCNUM];

#endif
