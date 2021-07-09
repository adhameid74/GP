/**
 * @file UDS_ReadDataById_program.c
 * @author Ahmed Hendawy 
 * @brief 
 * @version 0.0
 * @date 02-04-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
 
 #include "STD_TYPES.h"
 #include "BIT_MATH.h"
 
 #include "CAN_interface.h"
 #include "DoCAN_interface.h"
 #include "UDSHandler_interface.h"
 
 #include "UDS_ReadDataById_interface.h"
 #include "UDS_ReadDataById_private.h"
 #include "UDS_ReadDataById_config.h"
 u16 (*GetSpeedValue)(void);
 u16 (*GetVoltValue)(void);
 u32 (*GetFrontDistanceValue)(void);
 u32 (*GetBackDistanceValue)(void) ;
  void UDS_ReadDataById_voidSetCallBackSpeed(u16 (*Fptr)(void)){
	  GetSpeedValue = Fptr ;
  }
 void UDS_ReadDataById_voidSetCallBackFrontDistance( u32 (*Fptr)(void)){
	 GetFrontDistanceValue = Fptr;
 }
 void UDS_ReadDataById_voidSetCallBackBackDistance(u32 (*Fptr)(void) ){
	 GetBackDistanceValue = Fptr;
 }
 void UDS_ReadDataById_voidSetCallBackVolt (u16 (*Fptr)(void)){
	 GetVoltValue = Fptr ; 
 }
 void UDS_voidReadDataById(){
	 u8  i , j = 1;
	 u8  Flag = 0 ;
	 u32 Datau32 ;
	 u16 Datau16 ;
	 u8  DataSize ;
	 u8 NRC = 0; 
	 u8 MessageData[20];
	 for(i = 1 ; i <= Received_Data.Length.u12 ; i++ ){
		 if(Received_Data.Length.u12 < 2 && Received_Data.Length.u12 > 255 ){
			 switch(Received_Data.MessageData[i]){
				 case DID_SPEED: 
				        MessageData[j++] = Received_Data.MessageData[i] ;
				        Datau16 = GetSpeedValue() ;
				        MessageData[j++] = (u8)(Datau16) ;
				        MessageData[j++] = (u8)(Datau16 >> 8) ;
				        break;	 
			     case DID_FRONTDISTANCE: 
				        MessageData[j++] = Received_Data.MessageData[i] ;
				        Datau32 = GetFrontDistanceValue();
				        MessageData[j++] = (u8)(Datau32) ;
				        MessageData[j++] = (u8)(Datau32 >> 8  ) ;
						MessageData[j++] = (u8)(Datau32 >> 16 ) ;
						MessageData[j++] = (u8)(Datau32 >> 24 ) ;
				        break;
				 case DID_BACKDISTANCE: 
				        MessageData[j++] = Received_Data.MessageData[i] ;
				        Datau32 = GetBackDistanceValue();
				        MessageData[j++] = (u8)(Datau32) ;
				        MessageData[j++] = (u8)(Datau32 >> 8  ) ;
				        MessageData[j++] = (u8)(Datau32 >> 16 ) ;
				        MessageData[j++] = (u8)(Datau32 >> 24 ) ;
				 
				        break;	 
			     case DID_VOLT: 
				        MessageData[j++] = Received_Data.MessageData[i] ;
				        Datau16 = GetVoltValue() ;
				        MessageData[j++] = (u8)(Datau16) ;
				        MessageData[j++] = (u8)(Datau16 >> 8) ;
				        break;
				 default : 
				        NRC = requestOutOfRange ;
					    break ;
			 }
		 }
		 else{
			 if(Received_Data.Length.u12 < 2)
				 NRC = incorrectMessageLengthOrInvalidFormat ;
		 }
		 if(NRC != 0)
			 break ;
	 	 
}
     if(NRC != 0){
		 UDSHandler_voidSendNegResponse(ReadDataByIdentifier,NRC);
	 }
	 else {
		 MessageData[0] = 0x62 ;
		 UDSHandler_voidSendPosResponse(MessageData,j-1);
	 }
	  
	 
	 }
 
