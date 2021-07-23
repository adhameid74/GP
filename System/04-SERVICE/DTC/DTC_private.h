/**
 * @file DTC_private.h
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief  
 * @version 1
 * @date 2021-5-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef DTC_PRIVATE_H
#define DTC_PRIVATE_H

#define BITS_WarningIndicatorRequested		            0		
#define BITS_IsCritical						            1
#define BITS_AutoRestore						        2		
#define BITS_PowerOff						            3

#define STATUS_TestFailed						        0
#define STATUS_ConfirmedDTC					            1
#define STATUS_TestFailedThisOperationCycle	            2
#define STATUS_WarningIndicatorRequested		        3
#define STATUS_TestNotCompletedThisOperationCycle       4

#define NOTIFICATION_MSG_ID			                    0x20

void dtcSetFault(dtcItem_t* it);
void dtcSetPassed(dtcItem_t* it);

#endif
