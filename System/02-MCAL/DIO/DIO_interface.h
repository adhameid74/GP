/// @file DIO_interface.h
/**
 *  @Title       : DIO Module
 *  @Filename    : DIO_interface.h
 *  @Author      : Ahmed Hendawy
 *  @Origin Date : 11/9/2020
 *  @Version     : 1.0.0
 *  @Notes       : None
 *
 */

#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#include "Dio_cfg.h"

#define INPUT                  0b00 ///< for pin direction .
#define OUTPUT_S10MHZ          0b01 ///< output direction with maximum speed 10 MHz .
#define OUTPUT_S2MHZ           0b10 ///< output direction with maximum speed 2  MHz .
#define OUTPUT_S50MHZ          0b11 ///< output direction with maximum speed 50 MHz .

// configrations for a pin 
#define GP_OUTPUT_PUSH_PULL    0b00
#define GP_OUTPUT_OPEN_DRAIN   0b01
#define AF_OUTPUT_PUSH_PULL    0b10
#define AF_OUTPUT_OPEN_DRAIN   0b11

#define INPUT_ANALOG           0b00
#define INPUT_FLOATING         0b01
#define INPUT_PULL_DOWN        0b100
#define INPUT_PULL_UP          0b101

// IDs for ports
#define PORTAID                0
#define PORTBID                1
#define PORTCID              ` 2

// ID for a pins
#define PA0                    0
#define PA1                    1
#define PA2                    2
#define PA3                    3
#define PA4                    4
#define PA5                    5
#define PA6                    6
#define PA7                    7
#define PA8                    8
#define PA9                    9
#define PA10                   10
#define PA11                   11
#define PA12                   12
#define PA13                   13
#define PA14                   14
#define PA15                   15

#define PB0                    16
#define PB1                    17
#define PB2                    18
#define PB3                    19
#define PB4                    20
#define PB5                    21
#define PB6                    22
#define PB7                    23
#define PB8                    24
#define PB9                    25
#define PB10                   26
#define PB11                   27
#define PB12                   28
#define PB13                   29
#define PB14                   30
#define PB15                   31

#define PC0                    32
#define PC1                    33
#define PC2                    34
#define PC3                    35
#define PC4                    36
#define PC5                    37
#define PC6                    38
#define PC7                    39
#define PC8                    40
#define PC9                    41
#define PC10                   42
#define PC11                   43
#define PC12                   44
#define PC13                   45
#define PC14                   46
#define PC15                   47




/*****************************************************************
*                      Data TYPES                                *
******************************************************************/
typedef u8 Dio_ChannelType ;

typedef u8 Dio_PortType ;

typedef struct{
u16 mask ;
u8 offset ;
Dio_PortType port ;
} Dio_ChannelGroupType ;

typedef u8 Dio_LevelType ;

typedef u16 Dio_PortLevelType;

/*****************************************************************
*                 Function  Prototypes                           *
******************************************************************/

Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId );

void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level);

Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId ) ;

void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level);

Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr );

void Dio_WriteChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level );

//void Dio_GetVersionInfo( Std_VersionInfoType* VersionInfo);

Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId);
//**************************************************************
void Port_SetPinDirection( u8 Pin, u8 Direction);
void Port_SetPinMode( u8 Pin, u8 Mode );
//**************************************************************

#endif
