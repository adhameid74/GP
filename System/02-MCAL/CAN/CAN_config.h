/**
 * @file CAN_config.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 26-01-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CAN_CONFIG_H
#define CAN_CONFIG_H

#define CAN_CLK										8000000UL

/**
 * Options:
 * BY_REQ_ORDER
 * BY_IDENTIFIER
 */
#define TX_FIFO_PRIORITY							BY_REQ_ORDER

#define RX_FIFO_LOCK_ON_OVERRUN						DISABLED

#define AUTO_RETRANSMISSION							DISABLED

#define AUTO_WAKEUP									ENABLED

#define AUTO_BUS_OFF_MANAGEMENT						ENABLED

#define TIME_TRIGGERED_COMMUNICATION_MODE			DISABLED

#define DEBUG_FREEZE								DISABLED
/**************************************************************************************/
/**
 * @brief CAN interrupts Configurations
 * 
 */
#define TX_MAILBOX_EMPTY_INT						DISABLED

#define FIFO0_MSG_PENDING_INT						ENABLED

#define FIFO0_FULL_INT								DISABLED

#define FIFO0_OVERRUN_INT							DISABLED

#define FIFO1_MSG_PENDING_INT						DISABLED

#define FIFO1_FULL_INT								DISABLED

#define FIFO1_OVERRUN_INT							DISABLED

#define ERROR_WARNING_INT							DISABLED

#define ERROR_PASSIVE_INT							DISABLED

#define BUS_OFF_INT									DISABLED

#define LAST_ERROR_CODE_INT							DISABLED

#define ERROR_INT									DISABLED

#define WAKEUP_INT									DISABLED

#define SLEEP_INT									DISABLED

#endif
