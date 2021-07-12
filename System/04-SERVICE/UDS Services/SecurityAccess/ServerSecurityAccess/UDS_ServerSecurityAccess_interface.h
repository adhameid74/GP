/// @file ServerSecurityAccess_interface.h
/**
 *  @Title        : ServerSecurityAccess Module 
 *  @Filename     : ServerSecurityAccess_interface.h
 *  @Author       : Ahmed Hendawy
 *  @Origin Date  : 1/6/2021
 *  @Version      : 1.0.0
 *  @Notes        : None 
 *  
 */
 
 #ifndef SERVERSECURITYACCESS_INTERFACE_H
 #define SERVERSECURITYACCESS_INTERFACE_H
 extern  u8  LockingFlag ;
 void SA_voidExecuteSecurityAccess(INDICATION_SDU *ReceivedMessage);

 #endif