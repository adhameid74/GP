/// @file I2C_program.c
/**
 *  @Title        : I2C Module 
 *  @Filename     : I2C_program.c
 *  @Author       : Ahmed Hendawy
 *  @Origin Date  : 20/11/2020
 *  @Version      : 1.0.0
 *  @Notes        : None 
 *  
 */
 
//******************Includes*****************
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"


void MI2C_voidInit(){
	// Setting peripheral freq 
	I2C1->CR2 = PERIPHERAL_FREQ ;
	// Setting SCL freq
    #if I2C_MODE==SM
	I2C1->CCR =(u16)(0.5 *(PERIPHERAL_FREQ *1000 /SCL_FREQ)) | (I2C_MODE <<15);
	// Setting Rising time that detect stretching
	I2C1->TRISE = PERIPHERAL_FREQ + 1;
    #elif I2C_MODE==FM && DUTY==DISABLE
	I2C1->CCR =(u16)(PERIPHERAL_FREQ *1000 /3*SCL_FREQ) | (I2C_MODE <<15);
	I2C1->TRISE = (300*PERIPHERAL_FREQ/1000)+1;
    #elif  I2C_MODE==FM && DUTY==ENABLE
	I2C1->CCR =(u16)(PERIPHERAL_FREQ *1000 /25*SCL_FREQ) | (I2C_MODE <<15) |(DUTY <<14);
	I2C1->TRISE = (300*PERIPHERAL_FREQ/1000)+1;
	#endif


	//Enable peripheral 
	SET_BIT(I2C1->CR1,0);
	
	I2C1->CR1 = I2C1->CR1 |(ACKNOWLEDGE <<10);
	
	I2C1->OAR1 =(ADDDRESS_7BIT<<15)|(1<<14);
	

	
	
}
void MI2C_voidTransmit(u8 Copy_u8SlaveAddress , u8 *DataToTransmit,u8 Copy_u8NumberOfData){
	u8 i;
	volatile u32 x ;
	//Enable I2C
	SET_BIT(I2C1->CR1,0);
	if(Copy_u8NumberOfData > 0 ){

		//Generate start condition 
		SET_BIT(I2C1->CR1,8);
		//Wait until start bit generated
		while(GET_BIT(I2C1->SR1,0) ==0);
		//write slave address on bus
		I2C1->DR = Copy_u8SlaveAddress ;
		//Wait until address transmited
		while(GET_BIT(I2C1->SR1,1) ==0);
		x=I2C1->SR2;
		//Transmit  Data 
		// And condition for clear bit 1 in SR1(ADDR) and check for controller in master mode .
		i=0;
		while(i<Copy_u8NumberOfData){
			if( GET_BIT(I2C1->SR1,7)){
				
			    I2C1->DR  = DataToTransmit[i];
			    while( GET_BIT(I2C1->SR1,7) == 0);
			    i++;
			}
			
			
		}
		//Generate stop condition 
		SET_BIT(I2C1->CR1,9);
		
		
		
	}
	
	
}
 void MI2C_voidReceive (u8 Copy_u8SlaveAddress , u8 *DataToReceive ,u8 Copy_u8NumberOfData ){
	u8 i; 
	volatile u32 x ;
	Copy_u8SlaveAddress = Copy_u8SlaveAddress |1 ;
	 
	//Generate start condition 
	SET_BIT(I2C1->CR1,8);
	//Wait until start bit generated
	while(GET_BIT(I2C1->SR1,0) ==0);
	//write slave address on bus
	I2C1->DR = Copy_u8SlaveAddress ;
	//Wait until address transmited
	while(GET_BIT(I2C1->SR1,1) ==0 );
	x=I2C1->SR2;
    //Disable ACKNOWLEDGE for one byte reception.
    if(Copy_u8NumberOfData == 1){
		CLR_BIT(I2C1->CR1 ,10); 		
	}

    for(i=0 ; i < Copy_u8NumberOfData ;i++){
		//Disable ACKNOWLEDGE for last byte reception.
		if(i == Copy_u8NumberOfData-1){
			CLR_BIT(I2C1->CR1 ,10);
		}
		while(GET_BIT(I2C1->SR1 , 6) == 0);
		
		DataToReceive[i] = I2C1->DR ;
		i++;
		
	}
	//Generate stop condition 
	SET_BIT(I2C1->CR1,9);
	
	 
 }
  void MI2C_voidReceiveFromAddress(u8 Copy_u8SlaveAddress , u8 *DataToReceive ,u8 Copy_u8NumberOfData,u8 Copy_u8AddressOfLocation){
	u8 i;
	volatile u32 x ;
	SET_BIT(I2C1->CR1,0);
	//Generate start condition 
	SET_BIT(I2C1->CR1,8);  
	//Wait until start bit generated
	while(GET_BIT(I2C1->SR1,0) ==0);	
	//write slave address on bus
	I2C1->DR = Copy_u8SlaveAddress ;
	//Wait until address transmited
	while(GET_BIT(I2C1->SR1,1) ==0  );
	x=I2C1->SR2;
	
	//Write MS Byte on bus
	//I2C1->DR = (Copy_u16AddressOfLocation >>8) & 0xFF;
	//while(GET_BIT(I2C1->SR1,7) ==0);
	//Write LS Byte on bus
	I2C1->DR = Copy_u8AddressOfLocation ;
	while(GET_BIT(I2C1->SR1,7) ==0);

	//Generate  start condition 
	SET_BIT(I2C1->CR1,8); 
	//Wait until start bit generated
	while(GET_BIT(I2C1->SR1,0) ==0);	
	Copy_u8SlaveAddress =Copy_u8SlaveAddress | 1 ;
	//write slave address on bus
	I2C1->DR = Copy_u8SlaveAddress ;
	//Wait until address transmited
	while(GET_BIT(I2C1->SR1,1) ==0  );
	x=I2C1->SR2;
	


    for(i=0 ; i < Copy_u8NumberOfData ;i++){
    	//Disable ACKNOWLEDGE for last byte reception.
        if(i==Copy_u8NumberOfData-1){
    			CLR_BIT(I2C1->CR1 ,10);
    		}


		while(GET_BIT(I2C1->SR1 , 6) == 0);
		
		DataToReceive[i] = I2C1->DR ;

		
	}
	//Generate stop condition 
	SET_BIT(I2C1->CR1,9);
  }

