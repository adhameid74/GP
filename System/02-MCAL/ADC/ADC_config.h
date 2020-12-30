/**
 * @file ADC_config.h
 * @author Abdallah Hassan (Abdallahhashem029@gmail.com)
 * @brief ADC Configuration file in Stm32f103xxx
 * @version 0.1
 * @date 2020-11-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/*Used for ADC_voidInit Function*/

/*          Choose mode of conversion                  */
/*
1-DISCONTINUOUS_MODE
2-SINGLE_CHANNEL_CONTINUOUS_CONVERSION_MODE
3-SINGLE_CHANNEL_SINGLE_CONVERSION_MODE
4-MULTI_CHANNEL_CONTINUOUS_CONVERSION_MODE
5-MULTI_CHANNEL_SINGLE_CONVERSION_MODE
*/
#define ADC_MODE    SINGLE_CHANNEL_SINGLE_CONVERSION_MODE
/*******************************************************/

/*In Case of choosing DISCONTINUOUS_MODE */
/*regular channels*/
/*
1-ENABLE
2-DISABLE
*/
#define ADC_DISCONTINUOUS_REGULAR		ENABLE
/*********************************************/

/*injected channels*/
/*
1-ENABLE
2-DISABLE
*/
#define ADC_DISCONTINUOUS_INJECTIED		  ENABLE
/**********************************************/

/*number of regular channels to be converted in discontinuous mode*/
/*
From 1 to 8
*/
#define ADC_DISCONTINUOUS_REGULAR_CHANNELS	                       1	
/******************************************************************/



/*choose ADC External trigger for regular channels*/
/*
1-ENABLE
2-DISABLE
*/
#define ADC_EXTERNAL_REGULAR 		          ENABLE
/**************************************************/

/*In case of Enabling the external trigger for regular channles*/
/*choose trigger event*/
/*
1-TIMER1_CC1
2-TIMER1_CC2
3-TIMER1_CC3
4-TIMER2_CC2
5-TIMER3_TRGO
6-TIMER4_CC4
7-EXTI_LINE_11
8-SWSTART
*/
#define ADC_EXTERNAL_REGULAR_SELECT			            SWSTART
/**************************************************************/


/*choose ADC External trigger for injected channels*/
/*
1-ENABLE
2-DISABLE
*/
#define ADC_EXTERNAL_INJECTED 		          DISABLE
/***************************************************/

/*In case of Enabling the external trigger for injected channles*/
/*choose trigger event*/
/*
1-TIMER1_TRGO
2-TIMER1_CC4
3-TIMER2_TRGO
4-TIMER2_CC1
5-TIMER3_CC4
6-TIMER4_TRGO
7-EXTI_LINE_15
8-JSWSTART
*/
#define ADC_EXTERNAL_INJECTED_SELECT			          JSWSTART
/****************************************************************/


/*choose ADC Interrupt End of conversion for regular channels*/
/*
1-ENABLE
2-DISABLE
*/
#define ADC_EOC_REGULAR_INTERRUPT                       DISABLE
/**************************************************************/


/*		choose ADC data alignment		*/
/*
1-RIGHT_ALIGNMENT
2-LEFT_ALIGNMENT
*/
#define ADC_DATA_ALIGN	RIGHT_ALIGNMENT
/***************************************/

/*choose ADC Interrupt End of conversion for injected channels*/
/*
1-ENABLE
2-DISABLE
*/
#define ADC_EOC_INJECTED_INTERRUPT	                     DISABLE
/**************************************************************/


#endif