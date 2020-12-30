/**
 * @file SPEED_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief Private file of speed sensor
 * @version 1.0
 * @date 28-12-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef SPEED_PRIVATE_H
#define SPEED_PRIVATE_H

#define SYNCH			0
#define TIMER_DONE		1
#define ASYNCH			2

static u8 MODE;
static u16* Reading = NULL;

static void CALL_BACK_FUNC();

#endif
