/**
 * @file UDS_WriteDataById_interface.h
 * @author Ahmed Hendawy 
 * @brief 
 * @version 0.0
 * @date 02-04-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
 #ifndef UDS_WRITEDATABYID_INTERFACE_H
 #define UDS_WRITEDATABYID_INTERFACE_H
 void UDS_WRITEDATABYID_voidSetCallBackZone1(void (*Fptr)(u32 Data));
 void UDS_WRITEDATABYID_voidSetCallBackZone2(void (*Fptr)(u32 Data));
 void UDS_voidWriteDataById();
 #endif
 