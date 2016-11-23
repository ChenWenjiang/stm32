/**
  ******************************************************************************
  * @file    ARC_RTC.c
  * @author  armrunc (www.armrunc.com)
  * @version V1.0.0
  * @brief   ARC middleware. 
  *          This file provides RTC middleware functions.
  ******************************************************************************
  * @copy
  *
  * For non-commercial research and private study only.
  *
  * <h2><center>&copy; COPYRIGHT www.armrunc.com </center></h2>
  */ 
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "ARC_NVIC_API.h"
#include "ARC_RTC.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup ARC_RTC
  * @{
  */ 

/** @defgroup ARC_RTC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_RTC_Private_Defines
  * @{
  */

/**
  * @}
  */ 

/** @defgroup ARC_RTC_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup ARC_RTC_Private_Variables
  * @{
  */ 
#define FIRSTYEAR   2000        // start year
#define FIRSTDAY    6           // 0 = Sunday
static const uint8_t DaysInMonth[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/**
  * @}
  */

/** @defgroup ARC_RTC_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ARC_RTC_Private_Functions
  * @{
  */

/**
  * @brief  populates time-struct based on counter-value.
  * @param  sec, the time to be converted to RTC struct.
  * @param  *t, pointer to the RTC struct.
  * @retval None
  */
static void counter_to_struct( uint32_t sec, RTC_t *t )
{
    uint16_t day;
    uint8_t year;
    uint16_t dayofyear;
    uint8_t leap400;
    uint8_t month;

    t->sec = sec % 60;
    sec /= 60;
    t->min = sec % 60;
    sec /= 60;
    t->hour = sec % 24;
    day = (uint16_t)(sec / 24);

    t->wday = (day + FIRSTDAY) % 7;     // weekday

    year = FIRSTYEAR % 100;             // 0..99
    leap400 = 4 - ((FIRSTYEAR - 1) / 100 & 3);  // 4, 3, 2, 1

    for(;;) 
    {
        dayofyear = 365;
        if( (year & 3) == 0 ) 
        {
            dayofyear = 366;                    // leap year
            if( year == 0 || year == 100 || year == 200 ) // 100 year exception
            {
                if( --leap400 ) // 400 year exception
                {                   
                    dayofyear = 365;
                }
            }
        }
        if( day < dayofyear ) 
        {
            break;
        }
        day -= dayofyear;
        year++;                     // 00..136 / 99..235
    }
    t->year = year + FIRSTYEAR / 100 * 100; // + century

    if( dayofyear & 1 && day > 58 )    // no leap year and after 28.2.
    {
        day++;          // skip 29.2.
    }

    for( month = 1; day >= DaysInMonth[month-1]; month++ ) 
    {
        day -= DaysInMonth[month-1];
    }

    t->month = month;               // 1..12
    t->mday = day + 1;              // 1..31
}

/*******************************************************************************
* Function Name  : struct_to_counter
* Description    : calculates second-counter from populated time-struct
* Input          : Pointer to time-struct
* Output         : none
* Return         : counter-value (unit seconds, 0 -> 1.1.2000 00:00:00),
*  Based on code from "LalaDumm" found in the mikrocontroller.net forum.
*******************************************************************************/

/**
  * @brief  calculates second-counter from populated time-struct.
  * @param  *t, pointer to the RTC struct.
  * @retval the second that converted from the RTC struct.
  */
static uint32_t struct_to_counter( const RTC_t *t )
{
    uint8_t i;
    uint32_t result = 0;
    uint16_t idx, year;

    year = t->year;

    /* Calculate days of years before */
    result = (uint32_t)year * 365;
    if (t->year >= 1) 
    {
        result += (year + 3) / 4;
        result -= (year - 1) / 100;
        result += (year - 1) / 400;
    }

    /* Start with 2000 a.d. */
    result -= 730485UL;

    /* Make month an array index */
    idx = t->month - 1;

    /* Loop thru each month, adding the days */
    for (i = 0; i < idx; i++) 
    {
        result += DaysInMonth[i];
    }

    /* Leap year? adjust February */
    if (year % 400 == 0 || (year%4 == 0 && year%100 !=0)) 
    {
        ;
    } 
    else 
    {
        if (t->month > 1) 
        {
            result--;
        }
    }

    /* Add remaining days */
    result += t->mday;

    /* Convert to seconds, add all the other stuff */
    result = (result-1) * 86400L + (uint32_t)t->hour * 3600 + (uint32_t)t->min * 60 + t->sec;

    return result;
}

/**
  * @brief  Adjusts time.
  * @param  time_set, the time to be set.
  * @retval None
  */
void ARC_RTC_SetCounter(uint32_t time_set)
{
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
  /* Change the current time */
  RTC_SetCounter(time_set);
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}

/**
  * @brief  sets HW-RTC with values from time-struct.
  * @param  RTC struct
  * @retval None.
  */
void ARC_RTC_settime (const RTC_t *rtc)
{
    uint32_t cnt;
    RTC_t ts;

    cnt = struct_to_counter( rtc ); // non-DST counter-value
    counter_to_struct( cnt, &ts );  // normalize struct (for weekday)
    PWR_BackupAccessCmd(ENABLE);
    ARC_RTC_SetCounter( cnt );
    PWR_BackupAccessCmd(DISABLE);
}

/**
  * @brief  get the current time.
  * @param  *rtc rtc struct of current time
  * @retval None
  */
void ARC_RTC_gettime (RTC_t *rtc)
{
    uint32_t t;

    while ( ( t = RTC_GetCounter() ) != RTC_GetCounter() ) 
    { 
    }
    counter_to_struct( t, rtc ); // get non DST time
}


/**
  * @brief  Configures the RTC, 1 s counter will increas 1024.
  * @param  None
  * @retval None
  */
void ARC_RTC_Configuration(void)
{
    /* Enable PWR and BKP clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);

    /* Reset Backup Domain */
    BKP_DeInit();

    /* Enable LSE */
    RCC_LSEConfig(RCC_LSE_ON);
    /* Wait till LSE is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
    {}

    /* Select LSE as RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

    /* Enable RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Set RTC prescaler: set RTC period to 1sec */
    RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(31+1) */

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
}

/**
  * @brief  Initialize RTC, 1 / 1024 s interval.
  * @param  None
  * @retval None
  */
void ARC_RTC_Init()
{
    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {
        /* Backup data register value is not correct or not yet programmed (when
        the first time the program is executed) */

        /* RTC Configuration */
        ARC_RTC_Configuration();

        ARC_RTC_SetCounter(0x0);

        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
    }
    else
    {
        /* Wait for RTC registers synchronization */
        RTC_WaitForSynchro();
    }

    /* Clear reset flags */
    RCC_ClearFlag();
}

/**
  * @}
  */

/**
  * @}
  */
  
/**
  * @}
  */  
    
/******************* (C) www.armrunc.com *****END OF FILE****/
