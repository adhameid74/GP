/**
 * @file CAN_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 26-01-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "NVIC_interface.h"

#include "CAN_interface.h"
#include "CAN_private.h"
#include "CAN_config.h"


void CAN_voidInit()
{
	u32 Local_u32BaudRate = (CAN_CLK / 18) / 500000;

	Port_SetPinDirection(PA12, OUTPUT_S50MHZ);
	Port_SetPinMode(PA12, AF_OUTPUT_PUSH_PULL);
	Port_SetPinDirection(PA11, INPUT);
	Port_SetPinMode(PA11, INPUT_FLOATING);

	NVIC_voidEnableInterrupt(NVIC_USB_HP_CAN_TX);
	NVIC_voidEnableInterrupt(NVIC_USB_LP_CAN_RX0);

	CLR_BIT(bxCAN1->MCR, MCR_SLEEP);
	SET_BIT(bxCAN1->MCR, MCR_INRQ);

	#if TX_FIFO_PRIORITY == BY_REQ_ORDER
		SET_BIT(bxCAN1->MCR, MCR_TXFP);
	#elif TX_FIFO_PRIORITY == BY_IDENTIFIER
		CLR_BIT(bxCAN1->MCR, MCR_TXFP);
	#else
		#error "Wrong Configuration of TX_FIFO_PRIORITY"
	#endif

	#if RX_FIFO_LOCK_ON_OVERRUN == ENABLED
		SET_BIT(bxCAN1->MCR, MCR_RFLM);
	#elif RX_FIFO_LOCK_ON_OVERRUN == DISABLED
		CLR_BIT(bxCAN1->MCR, MCR_RFLM);
	#else
		#error "Wrong Configuration of RX_FIFO_LOCK_ON_OVERRUN"
	#endif

	#if AUTO_RETRANSMISSION == ENABLED
		CLR_BIT(bxCAN1->MCR, MCR_NART);
	#elif AUTO_RETRANSMISSION == DISABLED
		SET_BIT(bxCAN1->MCR, MCR_NART);
	#else
		#error "Wrong Configuration of AUTO_RETRANSMISSION"
	#endif

	#if AUTO_WAKEUP == ENABLED
		SET_BIT(bxCAN1->MCR, MCR_AWUM);
	#elif AUTO_WAKEUP == DISABLED
		CLR_BIT(bxCAN1->MCR, MCR_AWUM);
	#else
		#error "Wrong Configuration of AUTO_WAKEUP"
	#endif

	#if AUTO_BUS_OFF_MANAGEMENT == ENABLED
		SET_BIT(bxCAN1->MCR, MCR_ABOM);
	#elif AUTO_BUS_OFF_MANAGEMENT == DISABLED
		CLR_BIT(bxCAN1->MCR, MCR_ABOM);
	#else
		#error "Wrong Configuration of AUTO_BUS_OFF_MANAGEMENT"
	#endif

	#if TIME_TRIGGERED_COMMUNICATION_MODE == ENABLED
		SET_BIT(bxCAN1->MCR, MCR_TTCM);
	#elif TIME_TRIGGERED_COMMUNICATION_MODE == DISABLED
		CLR_BIT(bxCAN1->MCR, MCR_TTCM);
	#else
		#error "Wrong Configuration of TIME_TRIGGERED_COMMUNICATION_MODE"
	#endif

	#if DEBUG_FREEZE == ENABLED
		SET_BIT(bxCAN1->MCR, MCR_DBF);
	#elif DEBUG_FREEZE == DISABLED
		CLR_BIT(bxCAN1->MCR, MCR_DBF);
	#else
		#error "Wrong Configuration of DEBUG_FREEZE"
	#endif
/*******************************************************************************/
	#if TX_MAILBOX_EMPTY_INT == ENABLED
		SET_BIT(bxCAN1->IER, IER_TMEIE);
	#elif TX_MAILBOX_EMPTY_INT == DISABLED
		CLR_BIT(bxCAN1->IER, IER_TMEIE);
	#else
		#error "Wrong Configuration of TX_MAILBOX_EMPTY_INT"
	#endif

	#if FIFO0_MSG_PENDING_INT == ENABLED
		SET_BIT(bxCAN1->IER, IER_FMPIE0);
	#elif FIFO0_MSG_PENDING_INT == DISABLED
		CLR_BIT(bxCAN1->IER, IER_FMPIE0);
	#else
		#error "Wrong Configuration of FIFO0_MSG_PENDING_INT"
	#endif

	#if FIFO0_FULL_INT == ENABLED
		SET_BIT(bxCAN1->IER, IER_FFIE0);
	#elif FIFO0_FULL_INT == DISABLED
		CLR_BIT(bxCAN1->IER, IER_FFIE0);
	#else
		#error "Wrong Configuration of FIFO0_FULL_INT"
	#endif

	#if FIFO0_OVERRUN_INT == ENABLED
		SET_BIT(bxCAN1->IER, IER_FOVIE0);
	#elif FIFO0_OVERRUN_INT == DISABLED
		CLR_BIT(bxCAN1->IER, IER_FOVIE0);
	#else
		#error "Wrong Configuration of FIFO0_OVERRUN_INT"
	#endif

	#if FIFO1_MSG_PENDING_INT == ENABLED
		SET_BIT(bxCAN1->IER, IER_FMPIE1);
	#elif FIFO1_MSG_PENDING_INT == DISABLED
		CLR_BIT(bxCAN1->IER, IER_FMPIE1);
	#else
		#error "Wrong Configuration of FIFO1_MSG_PENDING_INT"
	#endif

	#if FIFO1_FULL_INT == ENABLED
		SET_BIT(bxCAN1->IER, IER_FFIE1);
	#elif FIFO1_FULL_INT == DISABLED
		CLR_BIT(bxCAN1->IER, IER_FFIE1);
	#else
		#error "Wrong Configuration of FIFO1_FULL_INT"
	#endif

	#if FIFO1_OVERRUN_INT == ENABLED
		SET_BIT(bxCAN1->IER, IER_FOVIE1);
	#elif FIFO1_OVERRUN_INT == DISABLED
		CLR_BIT(bxCAN1->IER, IER_FOVIE1);
	#else
		#error "Wrong Configuration of FIFO1_OVERRUN_INT"
	#endif

	#if ERROR_WARNING_INT == ENABLED
		SET_BIT(bxCAN1->IER, IER_EWGIE);
	#elif ERROR_WARNING_INT == DISABLED
		CLR_BIT(bxCAN1->IER, IER_EWGIE);
	#else
		#error "Wrong Configuration of ERROR_WARNING_INT"
	#endif

	#if ERROR_PASSIVE_INT == ENABLED
		SET_BIT(bxCAN1->IER, IER_EPVIE);
	#elif ERROR_PASSIVE_INT == DISABLED
		CLR_BIT(bxCAN1->IER, IER_EPVIE);
	#else
		#error "Wrong Configuration of ERROR_PASSIVE_INT"
	#endif

	#if BUS_OFF_INT == ENABLED
		SET_BIT(bxCAN1->IER, IER_BOFIE);
	#elif BUS_OFF_INT == DISABLED
		CLR_BIT(bxCAN1->IER, IER_BOFIE);
	#else
		#error "Wrong Configuration of BUS_OFF_INT"
	#endif

	#if LAST_ERROR_CODE_INT == ENABLED
		SET_BIT(bxCAN1->IER, IER_LECIE);
	#elif LAST_ERROR_CODE_INT == DISABLED
		CLR_BIT(bxCAN1->IER, IER_LECIE);
	#else
		#error "Wrong Configuration of LAST_ERROR_CODE_INT"
	#endif

	#if ERROR_INT == ENABLED
		SET_BIT(bxCAN1->IER, IER_ERRIE);
	#elif ERROR_INT == DISABLED
		CLR_BIT(bxCAN1->IER, IER_ERRIE);
	#else
		#error "Wrong Configuration of ERROR_INT"
	#endif

	#if WAKEUP_INT == ENABLED
		SET_BIT(bxCAN1->IER, IER_WKUIE);
	#elif WAKEUP_INT == DISABLED
		CLR_BIT(bxCAN1->IER, IER_WKUIE);
	#else
		#error "Wrong Configuration of WAKEUP_INT"
	#endif

	#if SLEEP_INT == ENABLED
		SET_BIT(bxCAN1->IER, IER_SLKIE);
	#elif SLEEP_INT == DISABLED
		CLR_BIT(bxCAN1->IER, IER_SLKIE);
	#else
		#error "Wrong Configuration of SLEEP_INT"
	#endif

	bxCAN1->BTR &= ~(((        0x03) << 24) | ((        0x07) << 20) | ((         0x0F) << 16) | (          0x1FF));
	bxCAN1->BTR |=  ((((4-1) & 0x03) << 24) | (((5-1) & 0x07) << 20) | (((12-1) & 0x0F) << 16) | ((Local_u32BaudRate-1) & 0x1FF));

	SET_BIT(bxCAN1->FMR, FMR_FINIT);
	for(u8 Local_u8Index=0;Local_u8Index<=27;Local_u8Index++)
	{
		bxCAN1->FilterRegister[Local_u8Index] = 0;
	}
	bxCAN1->FM1R = 0x0FFFFFFF;
	bxCAN1->FS1R = 0;
	CLR_BIT(bxCAN1->FMR, FMR_FINIT);
}

void CAN_voidWaitReady(u8 Copy_u8MailBoxID)
{
	switch(Copy_u8MailBoxID)
	{
	case CAN_MAILBOX0:
		while(GET_BIT(bxCAN1->TSR, TSR_TME0) == 0);
		break;
	case CAN_MAILBOX1:
		while(GET_BIT(bxCAN1->TSR, TSR_TME1) == 0);
		break;
	case CAN_MAILBOX2:
		while(GET_BIT(bxCAN1->TSR, TSR_TME2) == 0);
		break;
	}
}

TX_STATE_t CAN_u8WriteMsg(CAN_msg_t* Copy_ptrMsg)
{
	u8 Local_u8MailBoxID;
	for(Local_u8MailBoxID=CAN_MAILBOX0;Local_u8MailBoxID<=CAN_MAILBOX2;Local_u8MailBoxID++)
	{
		if( (GET_BIT(bxCAN1->TSR, (TSR_TME0+Local_u8MailBoxID))) == 1)
		{
			break;
		}
	}
	if(Local_u8MailBoxID > CAN_MAILBOX2)
	{
		return CAN_TX_FAIL;
	}

	bxCAN1->TxMailBox[Local_u8MailBoxID].TIR = 0;
	bxCAN1->TxMailBox[Local_u8MailBoxID].TIR |= (u32)(Copy_ptrMsg->ID << 21);
	if(Copy_ptrMsg->RTR == CAN_REMOTE_FRAME)
	{
		SET_BIT(bxCAN1->TxMailBox[Local_u8MailBoxID].TIR, TIR_RTR);
	}
	else
	{
		bxCAN1->TxMailBox[Local_u8MailBoxID].TDLR = ((u32)Copy_ptrMsg->DATA[3] << 24) | ((u32)Copy_ptrMsg->DATA[2] << 16) | ((u32)Copy_ptrMsg->DATA[1] << 8) | ((u32)Copy_ptrMsg->DATA[0]);
		bxCAN1->TxMailBox[Local_u8MailBoxID].TDHR = ((u32)Copy_ptrMsg->DATA[7] << 24) | ((u32)Copy_ptrMsg->DATA[6] << 16) | ((u32)Copy_ptrMsg->DATA[5] << 8) | ((u32)Copy_ptrMsg->DATA[4]);
	}

	bxCAN1->TxMailBox[Local_u8MailBoxID].TDTR &= ~TDTR_DLC_MASK;
	bxCAN1->TxMailBox[Local_u8MailBoxID].TDTR |= Copy_ptrMsg->DLC;

	SET_BIT(bxCAN1->IER, IER_TMEIE);
	SET_BIT(bxCAN1->TxMailBox[Local_u8MailBoxID].TIR, TIR_TXRQ);
	return CAN_TX_OK;
}

void CAN_voidReadMsg(CAN_msg_t* Copy_ptrMsg, u8 Copy_u8FIFOID)
{
	Copy_ptrMsg->ID = 0x000007FF & (bxCAN1->FIFOMailBox[Copy_u8FIFOID].RIR >> 21);
	Copy_ptrMsg->RTR = GET_BIT(bxCAN1->FIFOMailBox[Copy_u8FIFOID].RIR, RIR_RTR);
	Copy_ptrMsg->DLC = 0x0000000F & bxCAN1->FIFOMailBox[Copy_u8FIFOID].RDTR;

	Copy_ptrMsg->DATA[0] = 0x000000FF & (bxCAN1->FIFOMailBox[Copy_u8FIFOID].RDLR);
	Copy_ptrMsg->DATA[1] = 0x000000FF & (bxCAN1->FIFOMailBox[Copy_u8FIFOID].RDLR >> 8);
	Copy_ptrMsg->DATA[2] = 0x000000FF & (bxCAN1->FIFOMailBox[Copy_u8FIFOID].RDLR >> 16);
	Copy_ptrMsg->DATA[3] = 0x000000FF & (bxCAN1->FIFOMailBox[Copy_u8FIFOID].RDLR >> 24);

	Copy_ptrMsg->DATA[4] = 0x000000FF & (bxCAN1->FIFOMailBox[Copy_u8FIFOID].RDHR);
	Copy_ptrMsg->DATA[5] = 0x000000FF & (bxCAN1->FIFOMailBox[Copy_u8FIFOID].RDHR >> 8);
	Copy_ptrMsg->DATA[6] = 0x000000FF & (bxCAN1->FIFOMailBox[Copy_u8FIFOID].RDHR >> 16);
	Copy_ptrMsg->DATA[7] = 0x000000FF & (bxCAN1->FIFOMailBox[Copy_u8FIFOID].RDHR >> 24);

	if(Copy_u8FIFOID == CAN_FIFO0)
	{
		SET_BIT(bxCAN1->RF0R, RF0R_RFOM0);
	}
	else
	{
		SET_BIT(bxCAN1->RF1R, RF1R_RFOM1);
	}
}

void CAN_voidWriteFilter(CAN_filter_t* Copy_ptrFilter)
{
	static u8 Local_u8FilterIndex = 0;
	u32 Local_u32ID = 0;

	if(Local_u8FilterIndex > 55)
	{
		return;
	}

	if( (Local_u8FilterIndex % 2) == 0)
	{
		Local_u32ID  |= (u32)(Copy_ptrFilter->ID << 21);
		if(Copy_ptrFilter->RTR == 1)
		{
			SET_BIT(Local_u32ID, 20);
		}
	}
	else
	{
		Local_u32ID  |= (u32)(Copy_ptrFilter->ID << 5);
		if(Copy_ptrFilter->RTR == 1)
		{
			SET_BIT(Local_u32ID, 4);
		}
	}

	SET_BIT(bxCAN1->FMR, FMR_FINIT);
	CLR_BIT(bxCAN1->FA1R, (Local_u8FilterIndex/4));

	bxCAN1->FilterRegister[ (Local_u8FilterIndex/2) ] |= Local_u32ID;
	if(Copy_ptrFilter->FIFO_ID == CAN_FIFO0)
	{
		CLR_BIT(bxCAN1->FFA1R, (Local_u8FilterIndex/4));
	}
	else if(Copy_ptrFilter->FIFO_ID == CAN_FIFO1)
	{
		SET_BIT(bxCAN1->FFA1R, (Local_u8FilterIndex/4));
	}
	CLR_BIT(bxCAN1->FMR, FMR_FINIT);
	SET_BIT(bxCAN1->FA1R, (Local_u8FilterIndex/4));
	Local_u8FilterIndex++;
}

void CAN_voidSetTestMode(u8 Copy_u8TestMode)
{
	CLR_BIT(bxCAN1->MCR, MCR_SLEEP);
	SET_BIT(bxCAN1->MCR, MCR_INRQ);
	switch(Copy_u8TestMode)
	{
	case CAN_SILENT_MODE:
		SET_BIT(bxCAN1->BTR, BTR_SILM);
		CLR_BIT(bxCAN1->BTR, BTR_LBKM);
		break;
	case CAN_LOOP_BACK_MODE:
		CLR_BIT(bxCAN1->BTR, BTR_SILM);
		SET_BIT(bxCAN1->BTR, BTR_LBKM);
		break;
	case CAN_SILENT_LOOP_BACK_MODE:
		SET_BIT(bxCAN1->BTR, BTR_SILM);
		SET_BIT(bxCAN1->BTR, BTR_LBKM);
		break;
	case CAN_EXIT_TEST_MODE:
		CLR_BIT(bxCAN1->BTR, BTR_SILM);
		CLR_BIT(bxCAN1->BTR, BTR_LBKM);
		break;
	}
}

void CAN_voidStart()
{
	CLR_BIT(bxCAN1->MCR, MCR_SLEEP);
	CLR_BIT(bxCAN1->MCR, MCR_INRQ);
	while(GET_BIT(bxCAN1->MSR, MSR_INAK) != 0);
}

void USB_HP_CAN1_TX_IRQHandler()
{
	if(GET_BIT(bxCAN1->TSR, TSR_RQCP0) == 1)
	{
		SET_BIT(bxCAN1->TSR, TSR_RQCP0);
	}
	if(GET_BIT(bxCAN1->TSR, TSR_RQCP1) == 1)
	{
		SET_BIT(bxCAN1->TSR, TSR_RQCP1);
	}
	if(GET_BIT(bxCAN1->TSR, TSR_RQCP2) == 1)
	{
		SET_BIT(bxCAN1->TSR, TSR_RQCP2);
	}
	CLR_BIT(bxCAN1->IER, IER_TMEIE);
}

void USB_LP_CAN1_RX0_IRQHandler()
{
	if( (bxCAN1->RF0R & RF0R_FMP_MASK) != 0)
	{
		CAN_voidReadMsg(&CAN_RECIEVED_MSG, CAN_FIFO0);
	}
	asm("NOP");
}

void CAN1_RX1_IRQHandler()
{
	if( (bxCAN1->RF1R & RF1R_FMP_MASK) != 0)
	{
		CAN_voidReadMsg(&CAN_RECIEVED_MSG, CAN_FIFO1);
	}
	asm("NOP");
}
