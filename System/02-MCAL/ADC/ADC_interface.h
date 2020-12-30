/**
 * @file ADC_interface.h
 * @author Abdallah Hassan (Abdallahhashem029@gmail.com)
 * @brief ADC interface file in Stm32f103xxx
 * @version 0.1
 * @date 2020-11-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

/**
 * @brief initialization function for ADC, 
 * Can be configured using the configuration file
 */
void ADC_voidInit(void);

/**
 * @brief Assign the sequence length and sequence of regular channels to be converted by the adc
 * 
 * @param Copy_u8SeqLength      from 1 to 16 conversions
 * @param Copy_u8SeqChannels    array that holds the sequence of channels respectively
 */
void ADC_voidAssignRegularSequence(u8 Copy_u8SeqLength, u8 Copy_u8SeqChannels[]);

/**
 * @brief Assign the sequence length and sequence of injected channels to be converted by the adc
 * 
 * @param Copy_u8SeqLength      from 1 to 4 conversions
 * @param Copy_u8SeqChannels    array that holds the sequence of channels respectively
 */
void ADC_voidAssignInjectedSequence(u8 Copy_u8SeqLength, u8 Copy_u8SeqChannels[]);

/**
 * @brief Sets the function address to be called when the adc ends conversion for regular channels
 * 
 * @param Copy_Notification pointer to function which will be called and holds the value of the conversion
 */
void ADC_voidSetCallBackRegular(void (*Copy_Notification)(u16));

/**
 * @brief Software Start for the regular channels conversion
 * 
 */
void ADC_voidStartRegularConversion();

/**
 * @brief Polling function which reads the regular channel that has been converted
 * 
 * @return u16 value of converted regular channel
 */
u16 ADC_u16ReadRegularSync();


#endif