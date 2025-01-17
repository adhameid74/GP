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

 #include "DoCAN_private.h"
 #include "DoCAN_config.h"
 #include "DoCAN_interface.h"



 void (*MassageIndication)(INDICATION_SDU SDU);
 void (*FlowControlIndication)(void);
 void DoCAN_voidSetCallBackForMassage(void (*FPtr)(INDICATION_SDU SDU)){
	 MassageIndication = FPtr ;
 }

 void DoCAN_voidSetCallBackForFlowControl(void (*FPtr)(void)){
	 FlowControlIndication = FPtr ;
 }
 void DoCAN_voidRequestUsData(REQUEST_SDU SDU){
	 volatile u16 i ,j ;
	 volatile CAN_msg_t Frame ;
	 TX_STATE_t State ;
	 Frame.ID = (u8)SOURCE_ADDRESS ;
	 if(SDU.Length.u12 <= 7){
		 /*Construct Single Frame */
		 Frame.DLC =(u8)SDU.Length.u12 ;
		 Frame.DATA[0] = Frame.DLC ;
		 Frame.DLC++ ;
		 for(i = 0 ; i < SDU.Length.u12 ;i++){
			 Frame.DATA[i+1] = SDU.MessageData[i];
		 }
		 /*Send Frame */
		 State=CAN_u8WriteMsg(&Frame);
	 }
	 else {
		 /*Construct First Frame */
		 Frame.DATA[0] = 0x10 |((u8)(SDU.Length.u12 >> 8));
		 Frame.DATA[1] = (u8)SDU.Length.u12 ;
		 for(i = 1 ; i <= 6 ;i++){
			 Frame.DATA[i+1] = SDU.MessageData[i-1];
		 }
		 Frame.DLC = 8 ; 
		 volatile CAN_msg_t * y = &Frame;
		 State=CAN_u8WriteMsg(&Frame);
		 //if(State = CAN_TX_OK);
		 /*Construct Consective Frames */
		 u8 SeqNumber = 1 ;
		 for (i--; i< SDU.Length.u12 ;){
			 Frame.DATA[0] = 0x20 | SeqNumber ;
			 for(j=0; j < 7 && i < SDU.Length.u12 ; i++,j++){
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
  void DoCAN_voidIndicateUsData(CAN_msg_t CAN_Message){
	  static u16 i ;
	  u16 j ;
	  volatile u12 Length ;
	  volatile u8 seq_number ;
      static u8 Expected_SN = 1 ;
	  if(CAN_Message.ID == SOURCE_ADDRESS ){
		  //Get PCI to know Frame Type
		  u8 PciType = CAN_Message.DATA[0] >> 4 ;
		  Received_Data.SA = CAN_Message.ID ;
		  Received_Data.TA = TARGET_ADDRESS ;
		  if(PciType == 0){
			  //Single Frame
			  Received_Data.Length.u12 = CAN_Message.DLC - 1;
			  if(Received_Data.Length.u12 <= 7){
				  for(i=0 ; i < Received_Data.Length.u12 ; i++ ){
					  Received_Data.MessageData[i] = CAN_Message.DATA[i+1] ;
				  }
				  MassageIndication(Received_Data);
			  }
			  else{
				  //Erorr
			  }
		  }
		  else if (PciType == 1){
			  //First Frame
			  Received_Data.Length.u12  = 0 ;
			  Received_Data.Length.u12  = (CAN_Message.DATA[0] & 0X0F) << 4 ;
			  Received_Data.Length.u12 |= CAN_Message.DATA[1] ;
			  Length.u12 = Received_Data.Length.u12  ;
			  //check Length.u12 > 7 or not
			  for(i = 0 ; i < 6 ; i++){
				 Received_Data.MessageData[i] = CAN_Message.DATA[i+2] ;
			  }
			  Length.u12 -= 6 ;

		  }
		  else if (PciType == 2){
			  //Consective Frame
			  seq_number = CAN_Message.DATA[0] & 0x0F ;
			  if(Expected_SN == seq_number){
				  Expected_SN ++ ;
				  if(Expected_SN == 15 )
					  Expected_SN = 0 ;
				  if(Length.u12 > 8){
					  for (j = 1; j < 8;i++ , j++){
						  Received_Data.MessageData[i] = CAN_Message.DATA[j] ;
					  }
					  Length.u12 -= 8 ;
				  }
				  else {
					  for(j = 1 ;j <= Length.u12 + 1 ; j++ ,i++ ){
						  Received_Data.MessageData[i] = CAN_Message.DATA[j] ;
					  }
					  MassageIndication(Received_Data);
					  i = 0;
				  }
			  }
			  else {
				  //Erorr unExpectedSN
			  }
		  }
		  else if (PciType == 3){
			  //Flow Control Frame
			  Received_FlowControl.FlowStatus = CAN_Message.DATA[0] & 0x0F ;
			  Received_FlowControl.BlockSize = CAN_Message.DATA[1] ;
			  Received_FlowControl.STMin = CAN_Message.DATA[2] ;
			  FlowControlIndication();
		  }
		  else {
			  //Erorr
		  }
	  }

  }
