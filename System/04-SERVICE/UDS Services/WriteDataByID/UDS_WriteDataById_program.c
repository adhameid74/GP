/**
 * @file UDS_WriteDataById_program.c
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
 
 #include "UDS_ReadDataById_interface.h"
 #include "UDS_ReadDataById_private.h"
 #include "UDS_ReadDataById_config.h"
  void UDS_WRITEDATABYID_voidSetCallBackZone1(void (*Fptr)(u32 Data)){
	  SetZone1 = Fptr ;
  }
 void UDS_WRITEDATABYID_voidSetCallBackZone2(void (*Fptr)(u32 Data)){
	 SetZone2 = Fptr ;
  }
 void (*SetZone1)(u32 Data);
 void (*SetZone2)(u32 Data);
 
 void UDS_voidWriteDataById(){
	 u32 Data ;
	 u8 i ;
	 u8 j = 1 ; 
	 u8 NRC = 0; 
	 u8 MessageData[20];
	 for (i = 1 , j=0;i < Received_Data.Length ; i++ ,j++){
		 if(Received_Data.Length < 2 && Received_Data.Length > 255){
			 switch (Received_Data.MessageData[i]){
			    case ZONE_1:
				      MessageData[j++] = Received_Data.MessageData[i] ;
			 	      Data = (u32)(Received_Data.MessageData[++i]);
			 	      Data = Data |(u32)(Received_Data.MessageData[++i] << 8);
			 		  Data = Data |(u32)(Received_Data.MessageData[++i] << 16);
			 		  Data = Data |(u32)(Received_Data.MessageData[++i] << 24);
			 		  SetZone1(Data);
			 	      break ;
			   
			    case ZONE_2:
				      MessageData[j++] = Received_Data.MessageData[i] ;
			 	      Data = (u32)(Received_Data.MessageData[++i]);
			          Data = Data |(u32)(Received_Data.MessageData[++i] << 8);			
			 	      Data = Data |(u32)(Received_Data.MessageData[++i] << 16);
			 		  Data = Data |(u32)(Received_Data.MessageData[++i] << 24);
			 		  SetZone2(Data);
			          break;	
			    default :
				      NRC = requestOutOfRange ;
			 	      break;
			 	
		 }
		 else {
			 	NRC = incorrectMessageLengthOrInvalidFormat ; 
			 
		 }
		 if(NRC !=0)
			 break;
  
	 }
	 
 }
     if(NRC != 0){
		 UDSHandler_voidSendNegResponse(WRITE_DATA_BY_ID,NRC);
	 }
	 else {
		 MessageData[0] = 0x6E ;
		 UDSHandler_voidSendPosResponse(MessageData,j-1);
	 }

 }