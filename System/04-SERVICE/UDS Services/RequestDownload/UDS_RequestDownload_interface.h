/**
 * @file UDS_RequestDownload_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 04-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UDS_REQUESTDOWNLOAD_INTERFACE_H_
#define UDS_REQUESTDOWNLOAD_INTERFACE_H_

#define maxNumberOfBlockLength						50

u32 RequestDownload_u32Size;
u8 RequestDownload_u8ActiveFlag = 0;

void UDS_voidRequestDownload(INDICATION_SDU* ReceivedMessage);

#endif
