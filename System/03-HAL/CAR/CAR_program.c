/**
 * @file CAR_program.c
 * @author Eslam Khaled (Eslam.kh.kamal@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "STD_TYPES.h"

#include  "CAR_interface.h"
#include  "CAR_config.h"
#include  "CAR_private.h"

#include "MOTOR_interface.h"

void CAR_voidInit()
{
    MOTOR_voidMotorInit();
}
void CAR_voidSetCarDirection(u8 Copy_u8CarDirection)
{
    switch (Copy_u8CarDirection)
    {
    case CAR_FORWARD:
        MOTOR_voidSetMotorDirection(CAR_RIGHT_MOTORS , MOTOR_DIRECTION_1);
        MOTOR_voidSetMotorDirection(CAR_LEFT_MOTORS , MOTOR_DIRECTION_1);
        break;
     case CAR_BACKWARD:
        MOTOR_voidSetMotorDirection(CAR_RIGHT_MOTORS , MOTOR_DIRECTION_2);
        MOTOR_voidSetMotorDirection(CAR_LEFT_MOTORS , MOTOR_DIRECTION_2);
        break;
     case CAR_RIGHT:
        MOTOR_voidSetMotorDirection(CAR_RIGHT_MOTORS , MOTOR_DIRECTION_0);
        MOTOR_voidSetMotorDirection(CAR_LEFT_MOTORS , MOTOR_DIRECTION_1);
        break;
     case CAR_LEFT:
        MOTOR_voidSetMotorDirection(CAR_RIGHT_MOTORS , MOTOR_DIRECTION_1);
        MOTOR_voidSetMotorDirection(CAR_LEFT_MOTORS , MOTOR_DIRECTION_0);
        break;
     case CAR_STOP:
        MOTOR_voidSetMotorDirection(CAR_RIGHT_MOTORS , MOTOR_DIRECTION_0);
        MOTOR_voidSetMotorDirection(CAR_LEFT_MOTORS , MOTOR_DIRECTION_0);
        break;
    default:
        break;
    }
}

void CAR_voidSetCarSpeed(u8 Copy_u8CarSpeed)
{
    MOTOR_voidSetMotorSpeed(CAR_RIGHT_MOTORS,Copy_u8CarSpeed);
    MOTOR_voidSetMotorSpeed(CAR_LEFT_MOTORS,Copy_u8CarSpeed);
}
