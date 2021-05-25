/**
 * @file UDS_DiagnosticSessionControl_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 04-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UDS_DIAGNOSTICSESSIONCONTROL_INTERFACE_H_
#define UDS_DIAGNOSTICSESSIONCONTROL_INTERFACE_H_

#define UDS_SESSION_TIMEOUT					5000

#define UDS_DEFAULT_SESSION					0x01
#define UDS_PROGRAMMING_SESSION				0x02
#define UDS_EXTENDED_SESSION				0x03
#define UDS_SAFETY_SESSION					0x04

u8 UDS_u8ActiveSession = UDS_DEFAULT_SESSION;
u8 UDS_u8SessionTimer = 0;

void UDS_voidDiagnosticSessionControl(INDICATION_SDU* ReceivedMessage);

#endif
