/**
 * @file DoCAN_program.c
 * @author Ahmed Hendawy 
 * @brief 
 * @version 0.0
 * @date 22-03-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
 #include "STD_TYPES.h"
 #include "BIT_MATH.h"
 
 #include "CAN_interface.h"
 
 #include "DoCAN_interface.h"
 #include "DoCAN_private.h"
 #include "DoCAN_config.h"
 void (*MassageIndication)(void);
 void (*FlowControlIndication)(void);
 void DoCAN_voidSetCallBackForMassage(void (*FPtr)(void)){
	 MassageIndication = FPtr ;
 }
 
 void DoCAN_voidSetCallBackForFlowControl(void (*FPtr)(void)){
	 FlowControlIndication = FPtr ;
 }
 void DoCAN_voidRequestUsData(REQUEST_SDU SDU){
	 u16 i ,j ;
	 CAN_msg_t Frame ;
	 TX_STATE_t State ;
	 Frame.ID = SOURCE_ADDRESS ;
	 if(SDU.Length <= 7){
		 /*Construct Single Frame */
		 Frame.DLC =(u8)(SDU.Length &0x007) ;
		 Frame.DATA[0] = Frame.DLC ;
		 Frame.DLC++ ;
		 for(i = 0 ; i < SDU.Length ;i++){
			 Frame.DATA[i+1] = SDU.MessageData[i];
		 }
		 /*Send Frame */
		 State=CAN_u8WriteMsg(&Frame);
	 }
	 else {
		 /*Construct First Frame */
		 Frame.DATA[0] = 0x10 |((u8)(SDU.Length >> 8));
		 Frame.DATA[1] = (u8)SDU.Length ;
		 for(i = 1 ; i <= 6 ;i++){
			 Frame.DATA[i+1] = SDU.MessageData[i-1];
		 }
		 Frame.DLC = 8 ; 
		 State=CAN_u8WriteMsg(&Frame);
		 /*Construct Consective Frames */
		 u8 SeqNumber = 1 ;
		 NumByteLastCf = SDU.Length % 8;
		 for (i--; i< SDU.Length ;){
			 Frame.DATA[0] = 0x20 | SeqNumber ;
			 for(j=0; j < 7 && i < SDU.Length ; i++,j++){
				 Frame.DATA[j+1] = SDU.MessageData[i];
			 }
			 if(j < 7)
				 Frame.DLC = j+1 ; 
			 /*Send Frame */
			 State=CAN_u8WriteMsg(&Frame);
			 SeqNumber++;
			 if(SeqNumber >=15)
				 SeqNumber = 0 ;
		 }	 		 
	 }
 }
  void DoCAN_voidIndicateUsData(){
	  static u16 i ;
	  u16 j ;
      static u8 Expected_SN = 1 ;	  
	  if(CAN_RECIEVED_MSG.ID == SOURCE_ADDRESS ){
		  //Get PCI to know Frame Type 
		  u8 PciType = CAN_RECIEVED_MSG.Data[0] >> 4 ;
		  Received_Data.SA = CAN_RECIEVED_MSG.ID ;
		  Received_Data.TA = TARGET_ADDRESS ;
		  if(PciType == 0){
			  //Single Frame 
			  
			  if(Received_Data.Length >= 8){
				  Received_Data.Length = CAN_RECIEVED_MSG.DLC - 1;
				  for(i=0 ; i < Received_Data.Length ; i++ ){
					  Received_Data.MessageData[i] = CAN_RECIEVED_MSG.DATA[i+1] ;
				  }
				  MassageIndication();
			  }
			  else{
				  //Erorr
			  }
		  }
		  else if (PciType == 1){
			  //First Frame 
			  Received_Data.Length =  (u12)(((CAN_RECIEVED_MSG.DATA[0] << 8) 0x0F) | CAN_RECIEVED_MSG.DATA[1]) ;
			  //check Length > 7 or not 
			  for(i = 0 ; i < 6 ; i++){
				 Received_Data.MessageData[i] = CAN_RECIEVED_MSG.DATA[i+2] ; 
			  }
			  Received_Data.Length -= 6 ; 
			  
		  }
		  else if (PciType == 2){
			  //Consective Frame 
			  if(Expected_SN == CAN_RECIEVED_MSG.DATA[0] & 0x0F){
				  Expected_SN ++ ;
				  if(Expected_SN == 15 )
					  Expected_SN = 0 ;
				  if(Received_Data.Length > 8){
					  for (j = 1; j < 8;i++ , j++){
						  Received_Data.MessageData[i] = CAN_RECIEVED_MSG.DATA[j] ;
					  }
					  Received_Data.Length -= 8 ;
				  }
				  else {
					  for(j = 1 ;j <= Received_Data.Length ; j++ ,i++ ){
						  Received_Data.MessageData[i] = CAN_RECIEVED_MSG.DATA[j] ;
					  }
					  MassageIndication();
					  i = 0;
				  }
			  }
			  else {
				  //Erorr unExpectedSN
			  }
		  }
		  else if (PciType == 3){
			  //Flow Control Frame 
			  Received_FlowControl.FlowStatus = CAN_RECIEVED_MSG.DATA[0] & 0x0F ;
			  Received_FlowControl.BlockSize = CAN_RECIEVED_MSG.DATA[1] ;
			  Received_FlowControl.STMin = CAN_RECIEVED_MSG.DATA[2] ;
			  FlowControlIndication();
		  }
		  else {
			  //Erorr
		  }
	  }
	  
  }
