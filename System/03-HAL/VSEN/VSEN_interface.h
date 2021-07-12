/**
 * @file VSEN_interface.h
 * @author Abdallah Hassan (abdallahhashem029@gmail.com)
 * @brief Interface file for voltage sensor
 * @version 0.1
 * @date 2020-12-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef VSEN_INTERFACE_H
#define VSEN_INTERFACE_H

/**
 * @brief function reads the voltage from the adc channel pin and returns the voltage in mv
 * 
 * @return u16 voltage measured in mv
 */
u16 VSEN_u16ReadVoltage();

#endif
