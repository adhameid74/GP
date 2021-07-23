/**
 * @file SPEED_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief Private file of speed sensor
 * @version 2.01
 * @date 26-05-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef SPEED_PRIVATE_H
#define SPEED_PRIVATE_H

static u8 Flag = 0;

#define DTCNUM                     3

#define FAILED_THRESHOLD           25
#define PASSED_THRESHOLD           -10
#define AGING_THRESHOLD            255

#define SPEED_LOW_THRESHOLD        50
#define SPEED_LIMIT                125

static dtcItem_t SPEED_DTC[DTCNUM];
static dtcProperty_t SPEED_PROP[DTCNUM];

static SPEED_u16PVT;

#endif
