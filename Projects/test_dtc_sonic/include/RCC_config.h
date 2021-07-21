/**********************************************************/
/* Author		: Abdallah Hassan 		*/
/* Date 		: 8/8/2020				*/
/* Version		: V01					*/
/**********************************************************/
#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/* OPTIONS :
1- RCC_HSE_CRYSTAL
2- RCC_HSE_RC
3- RCC_HSI
4- RCC_PLL
*/
#define RCC_CLOCK_TYPE RCC_HSI

/* OPTIONS :
1- RCC_HSI_OVER_2
2- RCC_HSE
3- RCC_HSE_OVER_2
*/
/* NOTE : ONLY CHOSEN WHEN RCC_CLOCK_TYPE IS RCC_PLL */
#define RCC_PLL_INPUT RCC_HSE

/*OPTIONS :
1-  RCC_MULTIPLY_2
2-  RCC_MULTIPLY_3
3-  RCC_MULTIPLY_4
4-  RCC_MULTIPLY_5
5-  RCC_MULTIPLY_6
6-  RCC_MULTIPLY_7
7-  RCC_MULTIPLY_8
8-  RCC_MULTIPLY_9
9-  RCC_MULTIPLY_10
10- RCC_MULTIPLY_11
11- RCC_MULTIPLY_12
12- RCC_MULTIPLY_13
13- RCC_MULTIPLY_14
14- RCC_MULTIPLY_15
15- RCC_MULTIPLY_16
*/
/* NOTE : ONLY CHOSEN WHEN RCC_CLOCK_TYPE IS RCC_PLL */
#define RCC_PLL_MULTIPLER RCC_MULTIPLY_2


#endif