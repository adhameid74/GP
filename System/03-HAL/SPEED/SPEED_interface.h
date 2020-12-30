/**
 * @file SPEED_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief Interface file of speed sensor
 * @version 1.0
 * @date 28-12-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef SPEED_INTERFACE_H
#define SPEED_INTERFACE_H

/**
 * @brief To be initialezed by user
 * 
 */
typedef struct
{
	u8 PIN; 				// Sensor O/P PIN number
	u8 TIMER_ID;			// Timer to be used in the evaluation process
	u16 Reading;			// The variable which should contain the speed value after the evaluation is done
	u16 EVALUATION_TIME;	// The time of the evaluation process (Number of TICKS)
}SPEED_t;

/**
 * @brief Evaluate the speed in synch function
 * 
 * @param SENSOR pointer the struct that include the sensor information needed
 */
void SPEED_voidGetReadingSynch(SPEED_t* SENSOR);

/**
 * @brief Evaluate the speed in Asynch function
 * 
 * @param SENSOR pointer the struct that include the sensor information needed
 * @param Copy_funcptr pointer to the notification function to be called once the evaluation is done
 */
void SPEED_voidGetReadingAsynch(SPEED_t* SENSOR, void (*Copy_funcptr) (void));

#endif
