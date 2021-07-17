/**
 * @file UDS_ControlDTCSetting_interface.h
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief  
 * @version 1
 * @date 2020-7-13
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef UDS_ControlDTCSetting_INTERFACE_H
#define UDS_ControlDTCSetting_INTERFACE_H

extern u8 UDS_u8DTCSetting;

#define DTC_SETTING_ON                      0x01
#define DTC_SETTING_OFF                     0x02

void UDS_voidControlDTCSetting(INDICATION_SDU* ReceivedMessage);

#endif
