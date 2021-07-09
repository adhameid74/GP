/**
 * @file USONIC_interface.h
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief  
 * @version 1
 * @date 2020-12-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef USONIC_INTERFACE_H
#define USONIC_INTERFACE_H

#define USONIC1         1
#define USONIC2         2



/**
 * @brief  Initilization of the UltraSonic sensor
 * 
 */
void USONIC_voidInit();


/**
 * @brief  Fuction that return the distance to the object in CM with the input Freq to its configrable timer is 8MHZ
 * 
 */
f32 USONIC_f32GetDistance(u8 Copy_u8UsonicNumber,u8 *DTC_CODE);





#endif
