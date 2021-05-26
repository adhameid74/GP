/**
 * @file SPEED_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief Interface file of speed sensor
 * @version 2.01
 * @date 26-05-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef SPEED_INTERFACE_H
#define SPEED_INTERFACE_H

u16 SPEED_u16Reading = 0;

/**
 * @brief Evaluate the speed in Asynch function
 */
void SPEED_voidGetReadingAsynch();

#endif
