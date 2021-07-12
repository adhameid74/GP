/// @file ClientSecurityAccess_program.c
/**
 *  @Title        : ClientSecurityAccess Module 
 *  @Filename     : ClientSecurityAccess_program.c
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
 
 #include "ClientSecurityAccess_interface.h"
 #include "ClientSecurityAccess_private.h"
 #include "ClientSecurityAccess_config.h"
 
  void SA_voidRequestSeed(){
	 REQUEST_SDU Message ;
	 Message.SA = SOURCE_ADDRESS;
	 Message.TA = TARGET_ADDRESS; 
	 Message.MessageData[0] = 0x27 ;
	 Message.MessageData[1] = 0x01 ;
	 Message.Length.u12 = 2 ;
	 DoCAN_voidRequestUsData(Message);
 }
 void SA_voidSendKey(INDICATION_SDU *ReceivedMessage){
	 REQUEST_SDU Message ;
	 Message.SA = SOURCE_ADDRESS;
	 Message.TA = TARGET_ADDRESS; 
	 Message.MessageData[0] = 0x27 ;
	 Message.MessageData[1] = 0x02 ;
	 Message.MessageData[1] = ReceivedMessage.MessageData[2] + 2 ;
	 Message.Length.u12 = 3 ;
	 DoCAN_voidRequestUsData(Message);
 }
 void SA_voidUnlockSecurityLevel(){
	 
	 
	 
 }