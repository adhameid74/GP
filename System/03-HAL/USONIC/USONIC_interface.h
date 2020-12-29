/**
 * @file USONIC_interface.h
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief  TIMER Interface file
 * @version 1
 * @date 2020-12-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef USONIC_INTERFACE_H
#define USONIC_INTERFACE_H




/**
 * @brief  Initilization of the UltraSonic sensor
 * 
 */
void USONIC_voidInit();


/**
 * @brief  Fuction that return the distance to the object in CM with the input Freq to its configrable timer is 8MHZ
 * 
 */
f32 USONIC_f32GetDistance();


#endif
