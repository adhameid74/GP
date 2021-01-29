/**
 * @file CAN_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 26-01-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CAN_PRIVATE_H
#define CAN_PRIVATE_H

typedef struct
{
	u32 TIR;
	u32 TDTR;
	u32 TDLR;
	u32 TDHR;
}CAN_TxMailBox_t;


typedef struct
{
	u32 RIR;
	u32 RDTR;
	u32 RDLR;
	u32 RDHR;
}CAN_FIFOMailBox_t;

typedef struct
{
	u32 MCR;
	u32 MSR;
	u32 TSR;
	u32 RF0R;
	u32 RF1R;
	u32 IER;
	u32 ESR;
	u32 BTR;
	u32 RESERVED0[88];
	CAN_TxMailBox_t TxMailBox[3];
	CAN_FIFOMailBox_t FIFOMailBox[2];
	u32 RESERVED1[12];
	u32 FMR;
	u32 FM1R;
	u32 RESERVED2;
	u32 FS1R;
	u32 RESERVED3;
	u32 FFA1R;
	u32 RESERVED4;
	u32 FA1R;
	u32 RESERVED5[8];
	u32 FilterRegister[28];
}CAN_t;

#define MCR_INRQ				0
#define MCR_SLEEP				1
#define MCR_TXFP				2
#define MCR_RFLM				3
#define MCR_NART				4
#define MCR_AWUM				5
#define MCR_ABOM				6
#define MCR_TTCM				7
#define MCR_RESET				15
#define MCR_DBF					16

#define MSR_INAK				0
#define MSR_SLAK				1
#define MSR_ERRI				2
#define MSR_WKUI				3
#define MSR_SLAKI				4
#define MSR_TXM					8
#define MSR_RXM					9
#define MSR_SAMP				10
#define MSR_RX					11

#define IER_TMEIE				0
#define IER_FMPIE0				1
#define IER_FFIE0				2
#define IER_FOVIE0				3
#define IER_FMPIE1				4
#define IER_FFIE1				5
#define IER_FOVIE1				6
#define IER_EWGIE				8
#define IER_EPVIE				9
#define IER_BOFIE				10
#define IER_LECIE				11
#define IER_ERRIE				15
#define IER_WKUIE				16
#define IER_SLKIE				17

#define BTR_SILM				31
#define BTR_LBKM				30

#define TSR_RQCP0				0
#define TSR_RQCP1				8
#define TSR_RQCP2				16
#define TSR_TME0				26
#define TSR_TME1				27
#define TSR_TME2				28

#define FMR_FINIT				0

#define TIR_TXRQ				0
#define TIR_RTR					1

#define RIR_RTR					1

#define RF0R_RFOM0				5
#define RF0R_FMP_MASK			0x00000003

#define RF1R_RFOM1				5
#define RF1R_FMP_MASK			0x00000003

#define TDTR_DLC_MASK			0x0000000F

#define bxCAN1					((CAN_t *)0x40006400)
#define bxCAN2					((CAN_t *)0x40006800)

#define BY_REQ_ORDER			1
#define BY_IDENTIFIER			2

#define ENABLED					1
#define DISABLED				2

#endif
