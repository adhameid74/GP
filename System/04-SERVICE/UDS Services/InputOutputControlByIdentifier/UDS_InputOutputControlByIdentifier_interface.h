/**
 * @file UDS_InputOutputControlByIdentifier_program.c
 * @author Eslam Khaled (eslam.kh.kamal@gmail.com)
 * @brief UDS_InputOutputControlByIdentifier service implementation
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UDS_IOCONTROLBYID_INTERFACE_H_
#define UDS_IOCONTROLBYID_INTERFACE_H_

#include "DoCAN_interface.h"

#define returnControlToECU                          0x00
#define resetToDefault                              0x01
#define freezeCurrentState                          0x02
#define shortTermAdjustment                         0x03

/**
 * @brief extern variables should be used in their related drivers 
 * 
 */
extern u16 USONIC1_valueToUse;
extern u16 USONIC2_valueToUse;
extern u8  USONIC1_whatShouldIdo ;
extern u8  USONIC2_whatShouldIdo ;

extern u16 VOLT_valueToUse;
extern u8  VOLT_whatShouldIdo ;

extern u16 SPEED_valueToUse;
extern u8  SPEED_whatShouldIdo ;

extern u16 CAR_SPEED_valueToUse;
extern u16 CAR_DIRECTION_valueToUse;
extern u8  CAR_SPEED_whatShouldIdo ;
extern u8  CAR_DIRECTION_whatShouldIdo;

/**
 * @brief Eexecute the logic of InputOutputControlByIdentifier service
 * 
 * @param ReceivedMessage 
 */
void UDS_voidInputOutputControlByID(INDICATION_SDU* ReceivedMessage);

#endif
