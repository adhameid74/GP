/**
 * @file CAN_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 26-01-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

typedef u8 TX_STATE_t;

/**
 * @brief Macros of frame types (RTR)
 * 
 */
#define CAN_DATA_FRAME       			0
#define CAN_REMOTE_FRAME		     	1

/**
 * @brief Macros of test modes
 * 
 */
#define CAN_SILENT_MODE		 			0
#define CAN_LOOP_BACK_MODE	 			1
#define CAN_SILENT_LOOP_BACK_MODE	 	2
#define CAN_EXIT_TEST_MODE				3

/**
 * @brief Macros of TX mailboxes
 * 
 */
#define CAN_MAILBOX0					0
#define CAN_MAILBOX1					1
#define CAN_MAILBOX2					2

/**
 * @brief Macros of RX FIFOs
 * 
 */
#define CAN_FIFO0						0
#define CAN_FIFO1						1

/**
 * @brief Macros of TX state
 * 
 */
#define CAN_TX_OK						0
#define CAN_TX_FAIL						1

typedef struct
{
	u8 ID;			// Identifier
	u8 DATA[8];		// 8 Bytes of data
	u8 DLC;			// Length of data
	u8 RTR;			// Frame type (CAN_DATA_FRAME or CAN_REMOTE_FRAME)
}CAN_msg_t;

typedef struct
{
	u8 ID;			// Identifier
	u8 RTR;			// Frame type (CAN_DATA_FRAME or CAN_REMOTE_FRAME)
	u8 FIFO_ID;		// RX FIFO ID (CAN_FIFO0 or CAN_FIFO1)
}CAN_filter_t;

CAN_msg_t CAN_RECIEVED_MSG;

/**
 * @brief Initialization function of CAN peripheral
 * 
 */
void CAN_voidInit();

/**
 * @brief Busy wait until the desired TX mailbox is empty
 * 
 * @param Copy_u8MailBoxID TX mailbox (ex: CAN_MAILBOX1)
 */
void CAN_voidWaitReady(u8 Copy_u8MailBoxID);

/**
 * @brief Requests to transmit a message
 * 
 * @param Copy_ptrMsg The message struct to be transmitted
 * @return u8 Transmission state (CAN_TX_OK: Successful, CAN_TX_FAIL: Failed as there's no empty mailbox)
 */
TX_STATE_t CAN_u8WriteMsg(CAN_msg_t* Copy_ptrMsg);

/**
 * @brief Reads a received message through CAN bus
 * 
 * @param Copy_ptrMsg Received message
 * @param Copy_u8FIFOID RX FIFO ID (ex: CAN_FIFO0)
 */
void CAN_voidReadMsg(CAN_msg_t* Copy_ptrMsg, u8 Copy_u8FIFOID);

/**
 * @brief Writes filter desired information
 * 
 * @param Copy_ptrFilter Information to be set
 */
void CAN_voidWriteFilter(CAN_filter_t* Copy_ptrFilter);

/**
 * @brief controls the CAN test mode
 * 
 * @param Copy_u8TestMode The desired test mode (ex: CAN_SILENT_LOOP_BACK_MODE)
 */
void CAN_voidSetTestMode(u8 Copy_u8TestMode);

void CAN_voidStart();

#endif
