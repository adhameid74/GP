/// @file DIO_program.c
/**
 *  @Title       : DIO Module
 *  @Filename    : DIO_program.c
 *  @Author      : Ahmed Hendawy
 *  @Origin Date : 11/9/2020
 *  @Version     : 1.0.0
 *  @Notes       : None
 *
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "Dio_config.h"



/*****************************************************************
*                  Follow Autosar                                *
******************************************************************/


/*****************************************************************
 *  Function : Dio_ReadChannel().
 */
/**
 *  \b Description :
 *
 *  This function is used to read the state of a single channel which
 *  ID pass to it .
 *
 *  PRE_CONDITOIN  : Channel must be configuerd .
 *  POST_CONDITION : None .
 *
 *  @param [in] Cha...nnelId is the number of pin which we want to read it's state .
 *
 *  @return it's the state of the pin .
 *
 *  \b Example :
 *  @code
 *  Dio_LevelType State =Dio_ReadChannel(PORTA0);
 *
 *  @endocde
 *
 *
 */
Dio_LevelType Dio_ReadChannel( Dio_ChannelType ChannelId ){
	
	Dio_LevelType Temp ;
	
	if(ChannelId < 16 )
		Temp = GET_BIT(PORTA -> IDR , ChannelId % 16 ) ;
	else if(ChannelId < 32)
		Temp = GET_BIT(PORTB -> IDR , ChannelId % 16 ) ;
	else if(ChannelId < 48)
		Temp = GET_BIT(PORTC -> IDR , ChannelId % 16 ) ;
	return Temp ;
}
/*****************************************************************
 *  Function : Dio_WriteChannel().
 */
/**
 *  \Description :
 *  This function is used to write to the pin which number
 *  is the ChannelId .
 *
 *  PRE_CONDITOIN  : Channel must be configuerd .
 *  POST_CONDITION : None .
 *
 *  @param [in]  ChannelId is the number of pin which we want to write to  ot .
 *  @param [in]  Level is the state will be written to the pin .
 *  @return      None
 *  \b Example :
 *  @code
 *  Dio_LevelType State = ON ;
 *  Dio_WriteChannel(PORTA0 , State );
 *  @endocde
 */

void Dio_WriteChannel( Dio_ChannelType ChannelId, Dio_LevelType Level){

	if(ChannelId < 16 ){
		if(Level == 1)
			SET_BIT(PORTA ->BSRR ,ChannelId % 16 );
        else if(Level == 0)	
            SET_BIT(PORTA ->BSRR ,(ChannelId % 16)+16);
	}
	else if(ChannelId < 32){
		if(Level == 1)
			SET_BIT(PORTB ->BSRR ,ChannelId % 16 );
        else if(Level == 0)	
            SET_BIT(PORTB ->BSRR ,(ChannelId % 16)+16);			
	}
		
	else if(ChannelId < 48){
		if(Level == 1)
			SET_BIT(PORTC ->BSRR ,ChannelId % 16 );
        else if(Level == 0)	
            SET_BIT(PORTC ->BSRR ,(ChannelId % 16)+16);			
	}
			
}

/*****************************************************************
 *  Function : Dio_ReadPort().
 */
/**
 *  @Description  :
 *
 *  This function is used to read the stats of pins which their
 *  port is PortId .
 *
 *  PRE_CONDITOIN  : Port must be configuerd .
 *  POST_CONDITION : None .
 *
 *  @param [in] PortId is the number of port that we need to know it's pin states .
 *  @return States of Pins of PortId .
 *
 *  \b Example :
 *  @code
 *  Dio_PortLevelType State =Dio_ReadPort(PORTA)  ;
 *
 *  @endocde
 *
 */
Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId ) {
	
	Dio_PortLevelType Temp ;
	
	if(PortId == 0 )
		Temp = PORTA -> IDR ;
	else if(PortId  == 1)
		Temp = PORTB -> IDR ;
	else if(PortId == 2)
		Temp = PORTC -> IDR ;
	return Temp ;
	
}
/*****************************************************************
 *  Function : Dio_WritePort().
 */
/**
 *  @Description  :
 *
 *  This function is used to write states to a port which
 *  it's number is PortId.
 *
 *
 *  PRE_CONDITOIN  : Port must be configuerd .
 *  POST_CONDITION : None .
 *
 *  @param [in] PortId is the number of port that we need to change it's pin states .
 *  @param [in] Level  is the states of pins that we nedd to change them .
 *  @return States of Pins of PortId .
 *
 *  \b Example :
 *  @code
 *  Dio_PortLevelType Level =0xFE00  ;
 *  Dio_WritePort(PORTA ,State);
 *  @endocde
 *
 */

void Dio_WritePort( Dio_PortType PortId, Dio_PortLevelType Level){
	
	if(PortId == 0 )
		PORTA -> ODR = Level;
	else if(PortId  == 1)
		PORTB -> ODR = Level;
	else if(PortId == 2)
		PORTC -> ODR = Level;
	
}
/*****************************************************************
 *  Function : Dio_ReadChannelGroup().
 */
/**
 *  @Description  :
 *
 *   This function is used to read the states for a group of  pins .
 *
 *
 *  PRE_CONDITOIN  : Port must be configuerd .
 *  POST_CONDITION : None .
 *
 *  @param [in] ChannelGroupIdPtr is a pointer point to a struct that contine offset of  the pins ,thier mask
 *   and their port for the group that we need to read .
 *  @return States for agroup of pins .
 *
 *  \b Example :
 *  @code
 *  Dio_ChannelGroupType Group ={0xFF ,0 , PORTA};
 *  Dio_ChannelGroupType *Ptr = &Group ;
 *  Dio_PortLevelType State =Dio_ReadChannelGroup(Ptr);
 *
 *  @endocde
 *
 */

Dio_PortLevelType Dio_ReadChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr ){
	
	Dio_PortLevelType Temp ;
	Dio_PortLevelType Mask = (ChannelGroupIdPtr -> mask )<< ChannelGroupIdPtr -> offset;
	if(ChannelGroupIdPtr -> port == 0)
		Temp = (PORTA -> IDR) & Mask ;
	else if(ChannelGroupIdPtr -> port == 1)
		Temp = (PORTB -> IDR) & Mask ;
	else if(ChannelGroupIdPtr -> port == 2)
		Temp = (PORTC -> IDR) & Mask ;
	
	return Temp ;
}
/*****************************************************************
 *  Function : Dio_WriteChannelGroup().
 */
/**
 *  @Description  :
 *
 *  This function is used to write the stats of pins which their
 *  port is PortId .
 *
 *  PRE_CONDITOIN  : Port must be configuerd .
 *  POST_CONDITION : None .
 *
 *  @param [out] ChannelGroupIdPtr is a pointer point to a struct contine offset of  the pins ,thier mask and their port .
 *  @param [in] Level is the states for the group that we need to write to it .
 *  @return  void .
 *
 *  \b Example :
 *  @code
 *  Dio_PortLevelType State =Dio_ReadPort(PORTA)  ;
 *
 *  @endocde
 *
 */
void Dio_WriteChannelGroup( const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level ){
	
	Dio_PortLevelType Temp ;
	
	Dio_PortLevelType Mask = ~((ChannelGroupIdPtr -> mask )<< ChannelGroupIdPtr -> offset);
	Temp = PORTA -> ODR  & Mask ;
	
	Mask = Mask | (Level << ChannelGroupIdPtr -> offset );
	PORTA -> ODR = Temp | Mask ;
	
	
}
/*****************************************************************
 *  Function : Dio_GetVersionInfo().
 */
/**
 *  @Description  :
 *
 *  PRE_CONDITOIN  : Port must be configuerd .
 *  POST_CONDITION : None .
 *
 *  @param [in] VersionInfo
 *  @return void .
 *
 *  \b Example :
 *  @code
 *
 *
 *  @endocde
 *
 */
//void Dio_GetVersionInfo( Std_VersionInfoType* VersionInfo){}
/*****************************************************************
 *  Function : Dio_FlipChannel().
 */
/**
 *  @Description  :
 *
 *  PRE_CONDITOIN  : Port must be configuerd .
 *  POST_CONDITION : None .
 *
 *  @param [in] ChannelId .
 *  @return .
 *
 *  \b Example :
 *  @code
 *
 *
 *  @endocde
 *
 */
Dio_LevelType Dio_FlipChannel( Dio_ChannelType ChannelId){

	Dio_LevelType Temp ;

	if(ChannelId < 16 ){
		Temp = GET_BIT(PORTA -> ODR , ChannelId % 16 );
		if(Temp == 0)
			SET_BIT(PORTA ->BSRR ,ChannelId % 16 );
        else if(Temp == 1)
            SET_BIT(PORTA ->BSRR ,(ChannelId % 16)+16);
	}
	else if(ChannelId < 32){
		Temp = GET_BIT(PORTB -> ODR , ChannelId % 16 );
		if(Temp ==0 )
			SET_BIT(PORTB ->BSRR ,ChannelId % 16 );
        else if(Temp == 1)
            SET_BIT(PORTB ->BSRR ,(ChannelId % 16)+16);
	}

	else if(ChannelId < 48){
		Temp = GET_BIT(PORTB -> ODR , ChannelId % 16 );
		if(Temp == 0)
			SET_BIT(PORTC ->BSRR ,ChannelId % 16 );
        else if(Temp == 1)
            SET_BIT(PORTC ->BSRR ,(ChannelId % 16)+16);
	}

	return Temp;
}
//*********************************************************************
//                      Not Follow Autosar
//*********************************************************************

/*****************************************************************
 *  Function : Port_SetPinDirection().
 */
/**
 *  @Description  :
 *
 *  This function is used to determine the direction of pin .
 *
 *  PRE_CONDITOIN  : None .
 *  POST_CONDITION : None .
 *
 *  @param [in] Pin is the Id of physical pin we want to determineit's direction .
 *  @param [in] Direction  .
 *  @return void .
 *
 *  \b Example :
 *  @code
 *
 *  Port_SetPinDirection(PA0,OUTPUT_S10MHZ);
 *
 *  @endocde
 *
 */
void Port_SetPinDirection( u8 Pin, u8 Direction){

    u8 Temp = Pin %16 ;
	if(Pin < 16 ){
		if(Temp < 8){
			PORTA -> CRL &= ~(0xF << 4*Temp);
			PORTA -> CRL |= Direction << 4 * Temp ;
		}
		else{
			PORTA -> CRH &= ~(0xF << 4*(Temp - 8));
			PORTA -> CRH |= Direction << 4 * (Temp - 8) ;

		}
	}
	else if(Pin < 32){
		if(Temp < 8){
			PORTB -> CRL &= ~(0xF << 4*Temp);
			PORTB -> CRL |= Direction << 4 * Temp ;
		}
		else{
			PORTB -> CRH &= ~(0xF << 4*(Temp - 8));
			PORTB -> CRH |= Direction << 4 * (Temp - 8) ;
		}
	}
	else if(Pin < 48){
		if(Temp < 8){
			PORTC -> CRL &= ~(0xF << 4*Temp);
			PORTC -> CRL |= Direction << 4 * Temp ;
		}
		else{
			PORTC -> CRH &= ~(0xF << 4*(Temp - 8));
			PORTC -> CRH |= Direction << 4 * (Temp - 8) ;
		}
	}
}
/*****************************************************************
 *  Function : Port_SetPinMode().
 */
/**
 *  @Description  :
 *
 *  PRE_CONDITOIN  : None .
 *  POST_CONDITION : None .
 *
 *  @param [in] Pin is the Id of physical pin we want to determineit's direction .
 *   @param [in] Mode.
 *  @return void.
 *
 *  \b Example :
 *  @code
 *
 *  Port_SetPinMode( PA0 ,GP_OUTPUT_PUSH_PULL );
 *
 *  @endocde
 *
 */
void Port_SetPinMode( u8 Pin, u8 Mode ){
	u8 Local_Mode =0xFF;
	u8 Temp = Pin %16 ;
	if(Mode == INPUT_PULL_DOWN || Mode ==INPUT_PULL_UP){

		Local_Mode = Mode & 0x01 ;
		Mode = Mode >> 1 ;
	}

	if(Pin < 16 ){
		if(Local_Mode !=0xFF){
			if(Local_Mode ==0x01)
				SET_BIT(PORTA ->ODR ,Temp);
			else
				CLR_BIT(PORTA ->ODR ,Temp);

		}
		if(Temp < 8){
			CLR_BIT (PORTA -> CRL, 4*Temp + 2);
			PORTA -> CRL |= Mode << 4 * Temp + 2;

			}
		else {
			Temp =Temp - 8 ;
			CLR_BIT (PORTA -> CRH,4* Temp + 2);
			PORTA -> CRH |= Mode << 4 * Temp + 2 ;

			}

	}
	else if(Pin < 32){
		if(Local_Mode !=0xFF){
			if(Local_Mode ==0x01)
				SET_BIT(PORTB ->ODR ,Temp);
			else
				CLR_BIT(PORTB ->ODR ,Temp);

		}
		if(Temp < 8){
			CLR_BIT (PORTB -> CRL,4* Temp + 2);
			PORTB -> CRL |= Mode << 4 * Temp + 2;
			}
		else{
			Temp =Temp - 8 ;
			CLR_BIT (PORTB -> CRH,4* Temp + 2);
     		PORTB -> CRH |= Mode << 4 *Temp + 2;
			}

	}
	else if(Pin < 48){
		if(Local_Mode !=0xFF){
			if(Local_Mode ==0x01)
				SET_BIT(PORTC ->ODR ,Temp);
			else
				CLR_BIT(PORTC ->ODR ,Temp);

		}
		if(Temp < 8){
			CLR_BIT (PORTC -> CRL, 4*Temp + 2);
			PORTC -> CRL |= Mode << 4 * Temp + 2 ;
		}
		else{
			Temp =Temp - 8 ;
			CLR_BIT (PORTC -> CRH, 4*Temp + 2);
			PORTC -> CRH |= Mode << 4 *Temp+ 2;
			}

	}


}
