/// @file ServerSecurityAccess_program.c
/**
 *  @Title        : ServerSecurityAccess Module 
 *  @Filename     : ServerSecurityAccess_program.c
 *  @Author       : Ahmed Hendawy
 *  @Origin Date  : 1/6/2021
 *  @Version      : 1.0.0
 *  @Notes        : None 
 *  
 */
 
 #include "STD_TYPES.h"
 #include "BIT_MATH.h"
 
 #include <stdio.h>
 #include <stdlib.h>
 #include<time.h>
 
 #include "CAN_interface.h"
 #include "DoCAN_interface.h"
 #include "UDSHandler_interface.h"
 
 #include "ServerSecurityAccess_interface.h"
 #include "ServerSecurityAccess_private.h"
 #include "ServerSecurityAccess_config.h"
 u8 Seed ; 
 u8 ExpectedKey = 0 ;
 u8 AccessState = 0 ;
 u8 NumberofAttempts = 0 ;
 u8 Level ; 
 u8 LockingFlag = 1 ;
 
 
 static void SA_voidSendSeed(){
	 //Generate Requsted seed 
	 srand(time(0)) ;
	 Seed = rand() % 100;
	 //Generate ExpectedKey for the seed
	 ExpectedKey = Seed + 2 ;
	 u8 Data[3] ={0x67 Level Seed};
	 //Send Seed
	 UDSHandler_voidSendPosResponse(Data,3);
 
 }
 void SA_voidExecuteSecurityAccess(INDICATION_SDU *ReceivedMessage){
	 
	 if(ReceivedMessage.Length.u12 == 2 || ReceivedMessage.Length.u12 == 3){
		 if(ReceivedMessage.MessageData[1] !=0 && ReceivedMessage.MessageData[1] < 3){
			 if(ReceivedMessage.Length.u12 == 2 && ReceivedMessage.MessageData[1] == 0x01 ){
				 //requested Seed 
				 if(AccessState == 0){
					 AccessState = 1 ;
					 Level =  ReceivedMessage.MessageData[1] ;
					 SA_voidSendSeed();									 
				 }
				 else {
					 UDSHandler_voidSendNegResponse(0x27,conditionsNotCorrect);
				 }
			 }
			 else if(ReceivedMessage.Length.u12 == 3 && ReceivedMessage.MessageData[1] == 0x02){
				 // key Sended
				 if(AccessState == 1){
					if(ReceivedMessage.MessageData[2] == ExpectedKey ){
						//Unlock security 
						LockingFlag = 0 ; 
						AccessState = 0;
						//Global variable
						u8 Data[2]={0x67 0x02};
						UDSHandler_voidSendPosResponse(Data,2);
					}
					else {
						NumberofAttempts ++;
						if(NumberofAttempts < 5 ){
							UDSHandler_voidSendNegResponse(0x27,invalidKey);
						}
						else {
							UDSHandler_voidSendNegResponse(0x27,exceedNumberOfAttempts);
							/*Time OUT */
						}
					}
				 }
				 else {
					 
					 UDSHandler_voidSendNegResponse(0x27,requestSequenceError);
				 }
				 
			 }
			 else {
				 UDSHandler_voidSendNegResponse(0x27,incorrectMessageLengthOrInvalidFormat);
			 }
		 }
		 else {
			 UDSHandler_voidSendNegResponse(0x27,subFunctionNotSupported);
		 }
	 }
	 else {
		 UDSHandler_voidSendNegResponse(0x27,incorrectMessageLengthOrInvalidFormat);
	 }
 }

	 
 