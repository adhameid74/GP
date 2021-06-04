/**
 * @file UDS_TesterPresent_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 09-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UDS_IOCONTROLBYID_INTERFACE_H_
#define UDS_IOCONTROLBYID_INTERFACE_H_

#define returnControlToECU                          0x00
#define resetToDefault                              0x01
#define freezeCurrentState                          0x02
#define shortTermAdjustment                         0x03


extern u16 USONIC1_valueToUse;
extern u16 USONIC2_valueToUse;
extern u8  USONIC1_whatShouldIdo ;
extern u8  USONIC2_whatShouldIdo ;

extern u16 VOLT_valueToUse;
extern u8  VOLT_whatShouldIdo ;

extern u16 CAR_SPEED_valueToUse;
extern u16 CAR_DIRECTION_valueToUse;
extern u8  CAR_SPEED_whatShouldIdo ;
extern u8  CAR_DIRECTION_whatShouldIdo;




void UDS_voidInputOutputControlByID(INDICATION_SDU* ReceivedMessage);

#endif
