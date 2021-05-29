/**
 * @file FPEC_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 0.1
 * @date 29-05-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef FPEC_PRIVATE_H_
#define FPEC_PRIVATE_H_

#define FPEC_ACR                    *((volatile u32*)0x40022000)
#define ACR_PRFTBS					5
#define ACR_PRFTBE					4
#define ACR_HLFCYA					3
#define ACR_LTNC2					2
#define ACR_LTNC1					1
#define ACR_LTNC0					0

#define FPEC_KEYR                   *((volatile u32*)0x40022004)
#define FPEC_OPTKEYR                *((volatile u32*)0x40022008)

#define FPEC_SR                     *((volatile u32*)0x4002200C)
#define SR_EOP						5
#define SR_WRPRTERR					4
#define SR_PGERR					2
#define SR_BSY						0

#define FPEC_CR                     *((volatile u32*)0x40022010)
#define CR_EOPIE					12
#define CR_ERRIE					10
#define CR_OPTWRE					9
#define CR_LOCK						7
#define CR_STRT						6
#define CR_OPTER					5
#define CR_OPTPG					4
#define CR_MER						2
#define CR_PER						1
#define CR_PG						0

#define FPEC_AR                     *((volatile u32*)0x40022014)

#define FPEC_OBR                    *((volatile u32*)0x4002201C)
#define OBR_nRST_STDBY				4
#define OBR_nRST_STOP				3
#define OBR_WDG_SW					2
#define OBR_RDPRT					1
#define OBR_OPTERR					0

#define FPEC_WRPR                   *((volatile u32*)0x40022020)

#define KEY1						0x45670123
#define KEY2						0xCDEF89AB

#endif
