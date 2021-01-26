/**********************************************/
/* Author   : Eslam Khaled                    */
/* Date     : 2020-09-03                      */
/* Version  : V01                             */
/**********************************************/
#include  "STD_TYPES.h"
#include  "BIT_MATH.h"

#include  "AFIO_interface.h"
#include  "AFIO_config.h"
#include  "AFIO_private.h"

void AFIO_voidSetEXTIConfig (u8 Copy_u8Line , u8 Copy_u8Port)
{
    if(Copy_u8Line <=3)
    {
        AFIO_EXTICR1 &= ~ ((0b1111)<<(Copy_u8Line*4));
        AFIO_EXTICR1 |=  ((Copy_u8Port)<<(Copy_u8Line*4)); 
    }
    else if(Copy_u8Line <= 7)
    {
        Copy_u8Line -= 3;
        AFIO_EXTICR2 &= ~ ((0b1111)<<(Copy_u8Line*4));
        AFIO_EXTICR2 |=  ((Copy_u8Port)<<(Copy_u8Line*4));
    }
    else if(Copy_u8Line <= 11)
    {
        Copy_u8Line -= 7;
        AFIO_EXTICR3 &= ~ ((0b1111)<<(Copy_u8Line*4));
        AFIO_EXTICR3 |=  ((Copy_u8Port)<<(Copy_u8Line*4));
    }
    else if(Copy_u8Line <= 15)
    {
        Copy_u8Line -= 11;
        AFIO_EXTICR4 &= ~ ((0b1111)<<(Copy_u8Line*4));
        AFIO_EXTICR4 |=  ((Copy_u8Port)<<(Copy_u8Line*4));
    }
}