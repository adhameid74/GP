/**
 * @file USONIC_private.h
 * @author Ahmed M.Abdelfattah (ahmedm7md24@gmail.com)
 * @brief  
 * @version 1
 * @date 2020-12-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef USONIC_private_H
#define USONIC_private_H

#define DTCNUM                     8
#define FAILED_THRESHOLD           25
#define PASSED_THRESHOLD           -25
#define AGING_THRESHOLD            255

//static void voidTimeOut (void);

static dtcItem_t dtc_usonic[DTCNUM];
static dtcProperty_t USONIC_PROP[DTCNUM];

static f32 USONIC1_f32LastValue;
static f32 USONIC2_f32LastValue;

f32 USONIC1_f32DefaultValue =200;
f32 USONIC2_f32DefaultValue =200;

#endif
