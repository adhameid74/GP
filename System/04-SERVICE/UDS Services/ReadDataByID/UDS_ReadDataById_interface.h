/**
 * @file UDS_ReadDataById_interface.h
 * @author Ahmed Hendawy 
 * @brief 
 * @version 0.0
 * @date 02-04-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
 #ifndef UDS_READDATABYID_INTERFACE_H
 #define UDS_READDATABYID_INTERFACE_H

 void UDS_ReadDataById_voidSetCallBackSpeed(u16 (*Fptr)(void));
 void UDS_ReadDataById_voidSetCallBackFrontDistance( u32 (*Fptr)(void));
 void UDS_ReadDataById_voidSetCallBackBackDistance(u32 (*Fptr)(void) );
 void UDS_ReadDataById_voidSetCallBackVolt (u16 (*Fptr)(void));
 void UDS_voidReadDataById();
 #endif
 