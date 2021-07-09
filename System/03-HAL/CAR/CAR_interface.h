/**
 * @file CAR_interface.h
 * @author Eslam Khaled (Eslam.kh.kamal@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef CAR_INTERFACE_H
#define CAR_INTERFACE_H

#define CAR_FORWARD         1
#define CAR_BACKWARD        2
#define CAR_RIGHT           3
#define CAR_LEFT            4
#define CAR_STOP            5

void CAR_voidInit();
void CAR_voidSetCarDirection(u8 Copy_u8CarDirection);
void CAR_voidSetCarSpeed(u8 Copy_u8CarSpeed);

extern u8 CAR_SPEED_DefaultValue ;
extern u8 CAR_SPEED_CurrentValue;

extern u8 CAR_DIRECTION_DefaultValue ;
extern u8 CAR_DIRECTION_CurrentValue;

#endif
