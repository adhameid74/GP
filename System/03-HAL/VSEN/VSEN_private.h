/**
 * @file VSEN_private.h
 * @author Abdallah Hassan (abdallahhashem029@gmail.com)
 * @brief Private file for voltage sensor
 * @version 0.1
 * @date 2020-12-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef VSEN_PRIVATE_H
#define VSEN_PRIVATE_H

#define VREF_3_3	               1
#define VREF_5		               2

static u8 Flag = 0;

#define DTCNUM                     3

#define FAILED_THRESHOLD           5
#define PASSED_THRESHOLD           -5
#define AGING_THRESHOLD            255

#define HIGH_THRESHOLD             5000
#define LOW_THRESHOLD              3300

static dtcItem_t VSEN_DTC[DTCNUM];
static dtcProperty_t VSEN_PROP[DTCNUM];

static u16 VSEN_u16PVT;

#endif