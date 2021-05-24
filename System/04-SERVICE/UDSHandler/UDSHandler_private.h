/**
 * @file UDSHandler_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 24-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UDSHANDLER_PRIVATE_H_
#define UDSHANDLER_PRIVATE_H_

#define DiagnosticSessionControl				0x10
#define ClearDiagnosticInformation				0x14
#define ReadDTCInformation						0x19
#define ReadDataByIdentifier					0x22
#define WriteDataByIdentifier					0x2E
#define RequestDownload							0x34
#define TransferData							0x36
#define RequestTransferExit						0x37
#define TesterPresent							0x3E

#define NRC_LENGTH								3
#define NRC_ID									0x7F

#define serviceNotSupported						0x11

#endif
