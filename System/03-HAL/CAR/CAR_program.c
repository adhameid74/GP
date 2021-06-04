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

#include "UDS_InputOutputControlByIdentifier_interface.h"

u8 CAR_SPEED_DefaultValue = 60;
u8 CAR_SPEED_CurrentValue;

u8 CAR_DIRECTION_DefaultValue = CAR_STOP;
u8 CAR_DIRECTION_CurrentValue;

void CAR_voidInit()
{
    MOTOR_voidMotorInit();
}
void CAR_voidSetCarDirection(u8 Copy_u8CarDirection)
{
    switch (CAR_DIRECTION_whatShouldIdo)
    {
    case returnControlToECU:
        CAR_DIRECTION_CurrentValue = Copy_u8CarDirection;
        setPinsForDirection(Copy_u8CarDirection);
        break;
    case shortTermAdjustment:
        CAR_DIRECTION_CurrentValue = CAR_DIRECTION_valueToUse;
        setPinsForDirection(CAR_DIRECTION_valueToUse);
        break;
    case freezeCurrentState:
        setPinsForDirection(CAR_DIRECTION_CurrentValue);
        break;
    case resetToDefault:
        CAR_DIRECTION_CurrentValue = CAR_DIRECTION_DefaultValue;
        setPinsForDirection(CAR_DIRECTION_DefaultValue);
        break;
    
    default:
        break;
    }
    
}

void CAR_voidSetCarSpeed(u8 Copy_u8CarSpeed)
{
    switch (CAR_SPEED_whatShouldIdo)
    {
    case returnControlToECU:
        CAR_SPEED_CurrentValue = Copy_u8CarSpeed;
        MOTOR_voidSetMotorSpeed(CAR_RIGHT_MOTORS,Copy_u8CarSpeed);
        MOTOR_voidSetMotorSpeed(CAR_LEFT_MOTORS,Copy_u8CarSpeed);
        break;
    case shortTermAdjustment:
        CAR_SPEED_CurrentValue = CAR_SPEED_valueToUse;
        MOTOR_voidSetMotorSpeed(CAR_RIGHT_MOTORS,CAR_SPEED_valueToUse);
        MOTOR_voidSetMotorSpeed(CAR_LEFT_MOTORS,CAR_SPEED_valueToUse);
        break;
    case freezeCurrentState:
        MOTOR_voidSetMotorSpeed(CAR_RIGHT_MOTORS,CAR_SPEED_CurrentValue);
        MOTOR_voidSetMotorSpeed(CAR_LEFT_MOTORS,CAR_SPEED_CurrentValue);
        break;
    case resetToDefault:
        CAR_SPEED_CurrentValue = CAR_SPEED_DefaultValue;
        MOTOR_voidSetMotorSpeed(CAR_RIGHT_MOTORS,CAR_SPEED_CurrentValue);
        MOTOR_voidSetMotorSpeed(CAR_LEFT_MOTORS,CAR_SPEED_CurrentValue);
        break;
    
    default:
        break;
    }
}
void setPinsForDirection(u8 Copy_u8CarDirection)
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