/// @file ClientSecurityAccess_interface.h
/**
 *  @Title        : ClientSecurityAccess Module 
 *  @Filename     : ClientSecurityAccess_interface.h
 *  @Author       : Ahmed Hendawy
 *  @Origin Date  : 1/6/2021
 *  @Version      : 1.0.0
 *  @Notes        : None 
 *  
 */
 
 #ifndef CLIENTSECURITYACCESS_INTERFACE_H
 #define CLIENTSECURITYACCESS_INTERFACE_H
 void SA_voidRequestSeed();
 void SA_voidSendKey(INDICATION_SDU *ReceivedMessage);
 #endif