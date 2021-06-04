/**
 * @file UDSHandler_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 24-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef UDSHANDLER_INTERFACE_H_
#define UDSHANDLER_INTERFACE_H_

#define DiagnosticSessionControl                            0x10
#define ClearDiagnosticInformation                          0x14
#define ReadDTCInformation                                  0x19
#define ReadDataByIdentifier                                0x22
#define WriteDataByIdentifier                               0x2E
#define RequestUpload                                       0x35
#define TransferData                                        0x36
#define RequestTransferExit                                 0x37
#define TesterPresent                                       0x3E
#define ECUReset											0x11
#define InputOutputControlByIdentifier						0x2F

#define generalReject										0x10
#define subFunctionNotSupported								0x12
#define incorrectMessageLengthOrInvalidFormat				0x13
#define conditionsNotCorrect								0x22
#define requestSequenceError								0x24
#define requestOutOfRange									0x31
#define securityAccessDenied								0x33
#define invalidKey											0x35
#define exceedNumberOfAttempts								0x36
#define requiredTimeDelayNotExpired							0x37
#define uploadDownloadNotAccepted							0x70
#define transferDataSuspended								0x71
#define generalProgrammingFailure							0x72
#define wrongBlockSequenceCounter							0x73
#define requestCorrectlyReceived_ResponsePending			0x78
#define subFunctionNotSupportedInActiveSession				0x7E
#define serviceNotSupportedInActiveSession					0x7F
#define voltageTooHigh										0x92
#define voltageTooLow										0x93

#define DID_SPEED                                           0x01
#define DID_FRONTDISTANCE                                   0x02
#define DID_BACKDISTANCE                                    0x03
#define DID_VOLT                                            0x04
#define DID_ZONE_1                                          0x05
#define DID_ZONE_2                                          0x06
#define DID_UART1                                           0x07
#define DID_UART2                                           0x08                                          
#define DID_TIMER2                                          0x09 
#define DID_TIMER3                                          0x0A 
#define DID_TIMER4                                          0x0B  
#define DID_ADC                                             0x0C   
#define DID_CAR_DIRECTION                                   0x0D
#define DID_CAR_SPEED                                       0x0E




void UDSHandler_voidCallService(INDICATION_SDU ReceivedMessage);
void UDSHandler_voidSendNegResponse(u8 Copy_u8SID, u8 Copy_u8NRC);
void UDSHandler_voidSendPosResponse(u8* Copy_pu8Message, u8 Copy_u8Length);

#endif
