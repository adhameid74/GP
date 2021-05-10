/**
 * @file DoCAN_interface.h
 * @author Ahmed Hendawy 
 * @brief 
 * @version 0.0
 * @date 22-03-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
 #ifndef DOCAN_INTERFACE_H
 #define DOCAN_INTERFACE_H

 #define SOURCE_ADDRESS 0x55
 #define TARGET_ADDRESS 0x56

 typedef struct {
	 u16 u12:12;
 }u12;
 typedef struct {
	 //Mtype 
	 u8 SA ;
	 u8 TA ;
	 //TAtype
	 //AE  
	 u8* MessageData ;
	 u12 Length ;
	 
 }REQUEST_SDU;
 typedef struct {
	 //Mtype
	 u8 SA ;
	 u8 TA ;
	 //TAtype
	 //AE
	 u8* MessageData ;
	 u12 Length ;
	 RESULT_t Result ;
	 
 }INDICATION_SDU ;
 typedef struct {
	 u8 FlowStatus ;
	 u8 BlockSize  ;
	 u8 STMin      ;
 }FLOWCONTROL_t ;
 FLOWCONTROL_t  Received_FlowControl ;
 INDICATION_SDU Received_Data ;
 REQUEST_SDU RequestMassage ;
 void DoCAN_voidRequestUsData(REQUEST_SDU SDU);
 void DoCAN_voidIndicateUsData();
 void DoCAN_voidSetCallBackForMassage(void (*FPtr)(void));
 void DoCAN_voidSetCallBackForFlowControl(void (*FPtr)(void));
 
 
 #endif
 
