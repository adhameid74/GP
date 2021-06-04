/**
 * @file FPEC_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 0.1
 * @date 29-05-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef FPEC_INTERFACE_H_
#define FPEC_INTERFACE_H_

void FPEC_voidErasePage(u8 Copy_u8PageNumber);
void FPEC_voidEraseAppArea();
void FPEC_voidMassErase();
void FPEC_voidWriteArea(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length);

#endif
