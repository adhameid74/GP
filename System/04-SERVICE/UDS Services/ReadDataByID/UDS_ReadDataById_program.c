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
 
 #include "UDS_ReadDataById_interface.h"
 #include "UDS_ReadDataById_private.h"
 #include "UDS_ReadDataById_config.h"
 
 void UDS_voidReadDataById(){
	 u8 i , j ;
	 u8 Flag = 0 ;
	 for(i = 1 ; i < Received_Data.Length ; i++ ){
		 switch(Received_Data.MessageData[i]){
			 case : getspee
			     break;	 
		     case :
			     break;
			 case : 
			     break;	 
		     case :
			     break;
			 default : 
			     Flag = 1 ;
				 break ;
		 }
		 if(Flag == 0){
			 RequestMassage.MessageData[j] = Received_Data.MessageData[i] ;
		 }
		 
		 
	 }
 }