/**
 * @file UDS_DiagnosticSessionControl_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 04-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UDS_DIAGNOSTICSESSIONCONTROL_PRIVATE_H_
#define UDS_DIAGNOSTICSESSIONCONTROL_PRIVATE_H_

#define SID											0x10
#define POS_RESPONSE_SID							0x50
#define POS_RESPONSE_LENGTH							2

static void SendPosResponse(u8 Copy_u8Session);

#endif
