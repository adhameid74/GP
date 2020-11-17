/**********************************************/
/* Author   : Eslam Khaled                    */
/* Date     : 8 Aug 2020                      */
/* Version  : V01                             */
/**********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

/// <summary>
/// 
/// </summary>
/// <param name="Copy_u8BusId"></param>
/// <param name="Copy_u8PerId"></param>
EnableClock    (u8 Copy_u8BusId, u8 Copy_u8PerId)
{
    if(Copy_u8BusId <= 31)
    {
        switch (Copy_u8BusId)
        {
        case RCC_AHB:
            SET_BIT(RCC_AHBENR , Copy_u8PerId);
            break;
        case RCC_APB1:
            SET_BIT(RCC_APB1ENR , Copy_u8PerId);
            break;
        case RCC_APB2:
            SET_BIT(RCC_APB2ENR , Copy_u8PerId);
            break;
        
        default:
            break;
        }

    }
    else
    {
        /* Return Error */
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="Copy_u8BusId"></param>
/// <param name="Copy_u8PerId"></param>
void RCC_voidDisableClock    (u8 Copy_u8BusId, u8 Copy_u8PerId)
{
    if(Copy_u8BusId <= 31)
    {
        switch (Copy_u8BusId)
        {
        case RCC_AHB:
            CLR_BIT(RCC_AHBENR , Copy_u8PerId);
            break;
        case RCC_APB1:
            CLR_BIT(RCC_APB1ENR , Copy_u8PerId);
            break;
        case RCC_APB2:
            CLR_BIT(RCC_APB2ENR , Copy_u8PerId);
            break;
        
        default:
            break;
        }

    }
    else
    {
        /* Return Error */
    }
    
    
}

/// <summary>
/// 
/// </summary>
/// <param name=""></param>
void RCC_voidInitSysClock(void)
{ 
    #if RCC_CLOCK_TYPE   == RCC_HSE_CRYSTAL
        RCC_CR   = 0X00010000;                      // Enable HSE with no bypass
        RCC_CFGR = 0X00000001;                      // HSE Selected as system clock

    #elif RCC_CLOCK_TYPE == RCC_HSE_RC
        RCC_CR   = 0X00050000;                      // Enable HSE with bypass
        RCC_CFGR = 0X00000001;                      // HSE Selected as system clock

    #elif RCC_CLOCK_TYPE == RCC_HSI
        RCC_CR   = 0X00000081;                      // Enable HSI with Zero trimming
        RCC_CFGR = 0X00000000;                      // HSI Selected as system clock

    #elif RCC_CLOCK_TYPE == RCC_PLL  
        RCC_CR = 0X01000000;                        // Enable PLL
        #if RCC_PLL_INPUT == RCC_PLL_HSI_DIV_2 
            #if RCC_MUL_VALUE   == 2
                RCC_CFGR = 0x00000002;
            #elif RCC_MUL_VALUE == 3
                RCC_CFGR = 0x00040002;
            #elif RCC_MUL_VALUE == 4
                RCC_CFGR = 0x00080002;
            #elif RCC_MUL_VALUE == 5
                RCC_CFGR = 0x000c0002;
            #elif RCC_MUL_VALUE == 6
                RCC_CFGR = 0x00100002;
            #elif RCC_MUL_VALUE == 7
                RCC_CFGR = 0x00140002;
            #elif RCC_MUL_VALUE == 8
                RCC_CFGR = 0x00180002;
            #elif RCC_MUL_VALUE == 9
                RCC_CFGR = 0x001c0002;
            #elif RCC_MUL_VALUE == 10
                RCC_CFGR = 0x00200002;
            #elif RCC_MUL_VALUE == 11
                RCC_CFGR = 0x00240002;
            #elif RCC_MUL_VALUE == 12
                RCC_CFGR = 0x00280002;
            #elif RCC_MUL_VALUE == 13
                RCC_CFGR = 0x002c0002;
            #elif RCC_MUL_VALUE == 14
                RCC_CFGR = 0x00300002;
            #elif RCC_MUL_VALUE == 15
                RCC_CFGR = 0x00340002;
            #elif RCC_MUL_VALUE == 16
                RCC_CFGR = 0x00380002;
            #endif

        #elif RCC_PLL_INPUT == RCC_PLL_HSE_DIV_2
            #if RCC_MUL_VALUE   == 2
                RCC_CFGR = 0x00030002;
            #elif RCC_MUL_VALUE == 3
                RCC_CFGR = 0x00070002;
            #elif RCC_MUL_VALUE == 4
                RCC_CFGR = 0x000B0002;
            #elif RCC_MUL_VALUE == 5
                RCC_CFGR = 0x000F0002;
            #elif RCC_MUL_VALUE == 6
                RCC_CFGR = 0x00130002;
            #elif RCC_MUL_VALUE == 7
                RCC_CFGR = 0x00170002;
            #elif RCC_MUL_VALUE == 8
                RCC_CFGR = 0x001B0002;
            #elif RCC_MUL_VALUE == 9
                RCC_CFGR = 0x001F0002;
            #elif RCC_MUL_VALUE == 10
                RCC_CFGR = 0x00230002;
            #elif RCC_MUL_VALUE == 11
                RCC_CFGR = 0x00270002;
            #elif RCC_MUL_VALUE == 12
                RCC_CFGR = 0x002B0002;
            #elif RCC_MUL_VALUE == 13
                RCC_CFGR = 0x002F0002;
            #elif RCC_MUL_VALUE == 14
                RCC_CFGR = 0x00330002;
            #elif RCC_MUL_VALUE == 15
                RCC_CFGR = 0x00370002;
            #elif RCC_MUL_VALUE == 16
                RCC_CFGR = 0x003B0002;
            #endif

        #elif RCC_PLL_INPUT == RCC_HSE
            #if RCC_MUL_VALUE   == 2
                RCC_CFGR = 0x00010002;
            #elif RCC_MUL_VALUE == 3
                RCC_CFGR = 0x00050002;
            #elif RCC_MUL_VALUE == 4
                RCC_CFGR = 0x00090002;
            #elif RCC_MUL_VALUE == 5
                RCC_CFGR = 0x000D0002;
            #elif RCC_MUL_VALUE == 6
                RCC_CFGR = 0x00110002;
            #elif RCC_MUL_VALUE == 7
                RCC_CFGR = 0x00150002;
            #elif RCC_MUL_VALUE == 8
                RCC_CFGR = 0x00190002;
            #elif RCC_MUL_VALUE == 9
                RCC_CFGR = 0x001D0002;
            #elif RCC_MUL_VALUE == 10
                RCC_CFGR = 0x00210002;
            #elif RCC_MUL_VALUE == 11
                RCC_CFGR = 0x00250002;
            #elif RCC_MUL_VALUE == 12
                RCC_CFGR = 0x00290002;
            #elif RCC_MUL_VALUE == 13
                RCC_CFGR = 0x002D0002;
            #elif RCC_MUL_VALUE == 14
                RCC_CFGR = 0x00310002;
            #elif RCC_MUL_VALUE == 15
                RCC_CFGR = 0x00350002;
            #elif RCC_MUL_VALUE == 16
                RCC_CFGR = 0x00390002;
            #endif
          
        #endif
    #else
        #error ("Wrong Clock Type Options : RCC_HSE_CRYSTAL, RCC_HSE_RC RCC_HSI, RCC_PLL ")
    #endif
    
}