/**
 * @file UDS_TransferData_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 12-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UDS_TRANSFERDATA_INTERFACE_H_
#define UDS_TRANSFERDATA_INTERFACE_H_

extern u8 TransferData_u8ExpectedBSC;
extern u32 TransferData_u32ReceivedBytes;
extern u16 TransferData_u16NumOfLines;
extern u16 TransferData_u8NextAddress;

void UDS_voidTransferData(INDICATION_SDU* ReceivedMessage);

#endif
