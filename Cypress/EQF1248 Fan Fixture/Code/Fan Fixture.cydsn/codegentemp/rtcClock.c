/*******************************************************************************
* File Name: rtcClock.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the RTC Component.
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "rtcClock.h"
#include "CyLib.h"

/* Function Prototypes */
static void  rtcClock_SetInitValues(void)     ;
static uint8 rtcClock_DayOfWeek(uint8 dayOfMonth, uint8 month, uint16 year)
                                                      ;
#if (1u == rtcClock_DST_FUNC_ENABLE)
    static void  rtcClock_DSTDateConversion(void) ;
#endif /* 1u == rtcClock_DST_FUNC_ENABLE */


/* Variables were not initialized */
uint8 rtcClock_initVar = 0u;

/* Time and date variables
* Initial value are: Second = 0-59, Minute = 0-59, Hour = 0-23, DayOfWeek = 1-7,
* DayOfMonth = 1-31, DayOfYear = 1-366, Month = 1-12, Year = 1900-2200.
*/
rtcClock_TIME_DATE rtcClock_currentTimeDate = {0u, 0u, 0u, 1u, 1u, 1u, 1u, 1900u};

/* Alarm time and date variables
* Initial value are: Second = 0-59, Minute = 0-59, Hour = 0-23, DayOfWeek = 1-7,
* DayOfMonth = 1-31, DayOfYear = 1-366, Month = 1-12, Year = 1900-2200.
*/
rtcClock_TIME_DATE rtcClock_alarmCfgTimeDate = {0u, 0u, 0u, 1u, 1u, 1u, 1u, 1900u};

#if (1u == rtcClock_DST_FUNC_ENABLE) /* DST enabled */

    /* Define DST format: '0' - fixed, '1' - relative */
    volatile uint8 rtcClock_dstModeType = 0u;

    /* Hour 0-23, DayOfWeek 1-7, Week 1-5, DayOfMonth 1-31, Month 1-12 */
    rtcClock_DSTIME rtcClock_dstTimeDateStart = {0u, 1u, 1u, 1u, 1u};
    rtcClock_DSTIME rtcClock_dstTimeDateStop = {0u, 1u, 1u, 1u, 1u};

    /* Number of Hours to add/dec to time */
    volatile uint8 rtcClock_dstOffsetMin = 0u;
    volatile uint8 rtcClock_dstStartStatus = 0u;
    volatile uint8 rtcClock_dstStopStatus = 0u;

#endif /* 1u == rtcClock_DST_FUNC_ENABLE*/

/* Mask Registers */
volatile uint8 rtcClock_alarmCfgMask = 0u;
volatile uint8 rtcClock_alarmCurStatus = 0u;
volatile uint8 rtcClock_intervalCfgMask = 0u;

/* Status & Control Variables */
volatile uint8 rtcClock_statusDateTime = 0u;

/* Month Day Array - number of days in the months */
const uint8 CYCODE rtcClock_daysInMonths[rtcClock_MONTHS_IN_YEAR] = {
    rtcClock_DAYS_IN_JANUARY,
    rtcClock_DAYS_IN_FEBRUARY,
    rtcClock_DAYS_IN_MARCH,
    rtcClock_DAYS_IN_APRIL,
    rtcClock_DAYS_IN_MAY,
    rtcClock_DAYS_IN_JUNE,
    rtcClock_DAYS_IN_JULY,
    rtcClock_DAYS_IN_AUGUST,
    rtcClock_DAYS_IN_SEPTEMBER,
    rtcClock_DAYS_IN_OCTOBER,
    rtcClock_DAYS_IN_NOVEMBER,
    rtcClock_DAYS_IN_DECEMBER};


/*******************************************************************************
* Function Name:   rtcClock_Start
********************************************************************************
*
* Summary:
*  Enables RTC component: configures counter, setup interrupts, done all
*  required calculation and starts counter.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time rtcClock_Start() is called. This allows for
*  component initialization without re-initialization in all subsequent calls
*  to the rtcClock_Start() routine.
*
*  rtcClock_currentTimeDate, rtcClock_dstTimeDateStart,
*  rtcClock_dstTimeDateStop, rtcClock_dstTimeDateStart,
*  rtcClock_alarmCfgTimeDate, rtcClock_statusDateTime,
*  rtcClock_dstStartStatus, rtcClock_dstStopStatus,
*  rtcClock_alarmCurStatus: global variables are modified by the
*  functions called from rtcClock_Init().
*
* Reentrant:
*  No.
*
* Side Effects:
*  Enables for the one pulse per second (for the RTC component) and
*  Central Time Wheel (for the Sleep Timer component) signals to wake up device
*  from the low power (Sleep and Alternate Active) modes and leaves them
*  enabled.
*
*  The Power Manager API has the higher priority on resource usage: it is NOT
*  guaranteed that the Sleep Timer's configuration will be the same on exit
*  from the Power Manager APIs as on the entry. To prevent this use the Sleep
*  Timer's Sleep() - to save configuration and stop the component and Wakeup()
*  function to restore configuration and enable the component.
*
*  The Sleep Timer and Real Time Clock (RTC) components could be configured as
*  a wake up source from the low power modes only both at once.
*
*******************************************************************************/
void rtcClock_Start(void) 
{
    /* Execute once in normal flow */
    if(0u == rtcClock_initVar)
    {
        rtcClock_Init();
        rtcClock_initVar = 1u;
    }

    /* Enable component's operation */
    rtcClock_Enable();
}


/*******************************************************************************
* Function Name: rtcClock_Stop
********************************************************************************
*
* Summary:
*  Stops the RTC component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Leaves the one pulse per second (for the RTC component) and the Central Time
*  Wheel (for the Sleep Timer component) signals to wake up device from the low
*  power (Sleep and Alternate Active) modes enabled after Sleep Time component
*  is stopped.
*
*******************************************************************************/
void rtcClock_Stop(void) 
{
    uint8 interruptState;

    /* Disable the interrupt. */
    CyIntDisable(rtcClock_ISR_NUMBER);

    /* Enter critical section */
    interruptState = CyEnterCriticalSection();

    /* Stop one pulse per second counter and interrupt */
    rtcClock_OPPS_CFG_REG &= (uint8)(~(rtcClock_OPPSIE_EN_MASK | rtcClock_OPPS_EN_MASK));

    /* Exit critical section */
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name:   rtcClock_EnableInt
********************************************************************************
*
* Summary:
*  Enables interrupts of RTC Component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void rtcClock_EnableInt(void) 
{
    /* Enable the interrupt */
    CyIntEnable(rtcClock_ISR_NUMBER);
}


/*******************************************************************************
* Function Name:   rtcClock_DisableInt
********************************************************************************
*
* Summary:
*  Disables interrupts of RTC Component, time and date stop running.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void rtcClock_DisableInt(void) 
{
    /* Disable the interrupt. */
    CyIntDisable(rtcClock_ISR_NUMBER);
}


#if (1u == rtcClock_DST_FUNC_ENABLE)
    /*******************************************************************************
    * Function Name:   rtcClock_DSTDateConversion
    ********************************************************************************
    *
    * Summary:
    * Converts relative to absolute date.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  rtcClock_dstTimeDateStart.Month,
    *  rtcClock_dstTimeDateStart.DayOfWeek,
    *  rtcClock_dstTimeDateStart.Week,
    *  rtcClock_dstTimeDateStop.Month,
    *  rtcClock_dstTimeDateStop.DayOfWeek,
    *  rtcClock_dstTimeDateStop.Week,
    *  rtcClock_currentTimeDate.Year: these global variables are
    *  used to correct day of week.
    *
    *  rtcClock_dstTimeDateStart.DayOfMonth,
    *  rtcClock_dstTimeDateStop.DayOfMonth: these global variables are
    *  modified after convertion.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    static void rtcClock_DSTDateConversion(void) 
    {
        uint8 week = 1u;
        uint8 day = 1u;
        uint8 dayOfWeek;

        /* Get day of week */
        dayOfWeek = rtcClock_DayOfWeek(day, rtcClock_dstTimeDateStart.Month,
                                                    rtcClock_currentTimeDate.Year) + 1u;

        #if (0u != rtcClock_START_OF_WEEK)
        /* Normalize day of week if Start of week is not Sunday */
        if(dayOfWeek > rtcClock_START_OF_WEEK)
        {
            #if (6u != rtcClock_START_OF_WEEK)
                /* Start of week is not Saturday  */
                dayOfWeek -= rtcClock_START_OF_WEEK;
            #else /* 6u == rtcClock_START_OF_WEEK */
                /* Start of week is Saturday  */
                dayOfWeek = 1u; /* Set day of week to Monday */
            #endif /* 6u != rtcClock_START_OF_WEEK */
        }
        else
        {
            #if (1u != rtcClock_START_OF_WEEK)
                /* Start of week is not Monday  */
                dayOfWeek = (rtcClock_DAYS_IN_WEEK - rtcClock_START_OF_WEEK) - dayOfWeek;
            #else /* 1u == rtcClock_START_OF_WEEK */
                /* Start of week is Monday  */
                dayOfWeek = 5u; /* Set day of week to Friday */
            #endif /* 1u != rtcClock_START_OF_WEEK */
        }
        #endif /* 0u != rtcClock_START_OF_WEEK */

        /* Correct if out of DST range */
        while(dayOfWeek != rtcClock_dstTimeDateStart.DayOfWeek)
        {
            day++;
            dayOfWeek++;
            if(dayOfWeek > rtcClock_WEEK_ELAPSED)
            {
                dayOfWeek = 1u;
                week++;
            }
        }

        while(week != rtcClock_dstTimeDateStart.Week)
        {
            day += rtcClock_DAYS_IN_WEEK;
            week++;
        }
        rtcClock_dstTimeDateStart.DayOfMonth = day;

        /* Stop of DST time */
        week = 1u;
        day = 1u;

        dayOfWeek = rtcClock_DayOfWeek(day, rtcClock_dstTimeDateStop.Month,
                                                    rtcClock_currentTimeDate.Year) + 1u;
        #if (0u != rtcClock_START_OF_WEEK)
        /* Normalize day of week if Start of week is not Sunday */
        if(dayOfWeek > rtcClock_START_OF_WEEK)
        {
            #if (6u != rtcClock_START_OF_WEEK)
                /* Start of week is not Saturday  */
                dayOfWeek -= rtcClock_START_OF_WEEK;
            #else /* 6u == rtcClock_START_OF_WEEK */
                /* Start of week is Saturday  */
                dayOfWeek = 1u; /* Set day of week to Monday */
            #endif /* 6u != rtcClock_START_OF_WEEK */
        }
        else
        {
            #if (1u != rtcClock_START_OF_WEEK)
                /* Start of week is not Monday  */
                dayOfWeek = (rtcClock_DAYS_IN_WEEK - rtcClock_START_OF_WEEK) - dayOfWeek;
            #else /* 1u == rtcClock_START_OF_WEEK */
                /* Start of week is Monday  */
                dayOfWeek = 5u; /* Set day of week to Friday */
            #endif /* 1u != rtcClock_START_OF_WEEK */
        }
        #endif /* 0u != rtcClock_START_OF_WEEK */

        while(dayOfWeek != rtcClock_dstTimeDateStop.DayOfWeek)
        {
            day++;
            dayOfWeek++;
            if(dayOfWeek > rtcClock_WEEK_ELAPSED)
            {
                dayOfWeek = 1u;
                week++;
            }
        }

        while(week != rtcClock_dstTimeDateStop.Week)
        {
            day += rtcClock_DAYS_IN_WEEK;
            week++;
        }

        rtcClock_dstTimeDateStop.DayOfMonth = day;
    }
#endif /* 1u == rtcClock_DST_FUNC_ENABLE */


/*******************************************************************************
* Function Name:   rtcClock_Init
********************************************************************************
*
* Summary:
*  Calculates required date and flags, sets interrupt vector and priority.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate, rtcClock_dstTimeDateStart,
*  rtcClock_dstTimeDateStop, rtcClock_dstTimeDateStart,
*  rtcClock_alarmCfgTimeDate, rtcClock_statusDateTime,
*  rtcClock_dstStartStatus, rtcClock_dstStartStatus,
*  rtcClock_dstStopStatus, rtcClock_alarmCurStatus:
*  global variables are used by the rtcClock_SetInitValues().
*
*  rtcClock_dstTimeDateStart, rtcClock_currentTimeDate:
*  rtcClock_statusDateTime, rtcClock_dstStartStatus,
*  rtcClock_dstStartStatus, rtcClock_dstStopStatus,
*  rtcClock_alarmCurStatus: are modified by the
*  rtcClock_SetInitValues() function.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_Init(void) 
{
    /* Start calculation of required date and flags */
    rtcClock_SetInitValues();

    /* Disable Interrupt. */
    CyIntDisable(rtcClock_ISR_NUMBER);

    /* Set the ISR to point to the RTC_SUT_isr Interrupt. */
    (void) CyIntSetVector(rtcClock_ISR_NUMBER, & rtcClock_ISR);

    /* Set the priority. */
    CyIntSetPriority(rtcClock_ISR_NUMBER, rtcClock_ISR_PRIORITY);
}


/*******************************************************************************
* Function Name: rtcClock_Enable
********************************************************************************
*
* Summary:
*  Enables the interrupts, one pulse per second and interrupt generation on OPPS
*  event.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Enables for the one pulse per second and central time wheel signals to wake
*  up device from the low power (Sleep and Alternate Active) modes and leaves
*  them enabled.
*
*******************************************************************************/
void rtcClock_Enable(void) 
{
    uint8 interruptState;

    /* Enter critical section */
    interruptState = CyEnterCriticalSection();

    /* Enable one pulse per second event and interrupt */
    rtcClock_OPPS_CFG_REG |= (rtcClock_OPPS_EN_MASK | rtcClock_OPPSIE_EN_MASK);

    /* Exit critical section */
    CyExitCriticalSection(interruptState);

    /* Enable interrupt */
    CyIntEnable(rtcClock_ISR_NUMBER);
}


/*******************************************************************************
* Function Name:   rtcClock_ReadTime
********************************************************************************
*
* Summary:
*  Returns a pointer to the current time and date structure.
*
* Parameters:
*  None.
*
* Return:
*  rtcClock_currentTimeDate: pointer to the global structure with the
*  current date and time values.
*
* Global variables:
*  rtcClock_currentTimeDate: global variable with current date and
*   time is used.
*
* Side Effects:
*  You should disable the interrupt for the RTC component before calling any
*  read API to avoid an RTC Counter increment in the middle of a time or date
*  read operation. Re-enable the interrupts after the data is read.
*
*******************************************************************************/
rtcClock_TIME_DATE * rtcClock_ReadTime(void) 
{
    /* Returns a pointer to the current time and date structure */
    return (&rtcClock_currentTimeDate);
}


/*******************************************************************************
* Function Name:   rtcClock_WriteTime
********************************************************************************
*
* Summary:
*  Writes time and date values as current time and date. Only
*  passes Milliseconds(optionally), Seconds, Minutes, Hours, Month,
*  Day Of Month and Year.
*
* Parameters:
*  timeDate: Pointer to rtcClock_TIME_DATE global structure where new
*  values of time and date are stored.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate: global structure is modified with the new
*  values of current date and time.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteTime(const rtcClock_TIME_DATE * timeDate)
     
{
    /* Disable Interrupt of RTC Component */
    rtcClock_DisableInt();

    /* Write current time and date */
    rtcClock_currentTimeDate.Sec = timeDate->Sec;
    rtcClock_currentTimeDate.Min = timeDate->Min;
    rtcClock_currentTimeDate.Hour = timeDate->Hour;
    rtcClock_currentTimeDate.DayOfMonth = timeDate->DayOfMonth;
    rtcClock_currentTimeDate.Month = timeDate->Month;
    rtcClock_currentTimeDate.Year = timeDate->Year;

    /* Enable Interrupt of RTC Component */
    rtcClock_EnableInt();
}


/*******************************************************************************
* Function Name:   rtcClock_WriteSecond
********************************************************************************
*
* Summary:
*  Writes Sec software register value.
*
* Parameters:
*  second: Seconds value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate.Sec: global structure's field where current
*  second's value is modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteSecond(uint8 second) 
{
    /* Save seconds to the current time and date structure */
    rtcClock_currentTimeDate.Sec = second;
}


/*******************************************************************************
* Function Name:   rtcClock_WriteMinute
********************************************************************************
*
* Summary:
*  Writes Minute value in minutes counter register.
*
* Parameters:
*  minute: Minutes value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate.Min: global structure's field where
*  current minute's value is modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteMinute(uint8 minute) 
{
    /* Save minutes to the current time and date structure */
    rtcClock_currentTimeDate.Min = minute;
}


/*******************************************************************************
* Function Name:   rtcClock_WriteHour
********************************************************************************
*
* Summary:
*  Writes Hour software register value.
*
* Parameters:
*  hour: Hours value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate.Hour: global structure's field where
*  current hour's value is modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteHour(uint8 hour) 
{
    /* Save hours to the current time and date structure */
    rtcClock_currentTimeDate.Hour = hour;
}


/*******************************************************************************
* Function Name:   rtcClock_WriteDayOfMonth
********************************************************************************
*
* Summary:
*  Writes DayOfMonth software register value.
*
* Parameters:
*  dayOfMonth: Day Of Month value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate.DayOfMonth: global structure's field where
*  current day of month's value is modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteDayOfMonth(uint8 dayOfMonth) 
{
    /* Save day of month to the current time and date structure */
    rtcClock_currentTimeDate.DayOfMonth = dayOfMonth;
}


/*******************************************************************************
* Function Name:   rtcClock_WriteMonth
********************************************************************************
*
* Summary:
*  Writes Month software register value.
*
* Parameters:
*  month: Month value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate.Month: global structure's field where
*  current day of month's value is modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteMonth(uint8 month) 
{
    /* Save months to the current time and date structure */
    rtcClock_currentTimeDate.Month = month;
}


/*******************************************************************************
* Function Name:   rtcClock_WriteYear
********************************************************************************
*
* Summary:
*  Writes Year software register value.
*
* Parameters:
*  year: Years value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate.Year: global structure's field where
*  current year's value is modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteYear(uint16 year) 
{
    /* Save years to the current time and date structure */
    rtcClock_currentTimeDate.Year = year;
}


/*******************************************************************************
* Function Name:   rtcClock_WriteAlarmSecond
********************************************************************************
*
* Summary:
*  Writes Alarm Sec software register value.
*
* Parameters:
*  second: Alarm Seconds value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate.Sec: this global variable is used for
*  comparison while setting and clearing seconds alarm status variable.
*
*  rtcClock_alarmCfgTimeDate.Sec: this global variable is modified to
*  store of the new seconds alarm.
*
*  rtcClock_alarmCurStatus: this global variable could be changed if
*  second's alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteAlarmSecond(uint8 second) 
{
    rtcClock_alarmCfgTimeDate.Sec = second;

    /* Check second alarm */
    if(rtcClock_alarmCfgTimeDate.Sec == rtcClock_currentTimeDate.Sec)
    {
        /* Set second alarm */
        rtcClock_alarmCurStatus |= rtcClock_ALARM_SEC_MASK;
    }
    else /* no second alarm */
    {
        /* Clear second alarm */
        rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_SEC_MASK);
    }
}


/*******************************************************************************
* Function Name:   rtcClock_WriteAlarmMinute
********************************************************************************
*
* Summary:
*  Writes Alarm Min software register value.
*
* Parameters:
*  minute: Alarm minutes value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate.Min: this global variable is used for
*  comparison while setting and clearing minutes alarm status variable.
*
*  rtcClock_alarmCfgTimeDate.Min: this global variable is modified to
*  store of the new minutes alarm.
*
*  rtcClock_alarmCurStatus: this global variable could be changed if
*  minute's alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteAlarmMinute(uint8 minute) 
{
    rtcClock_alarmCfgTimeDate.Min = minute;

    /* Check minute alarm */
    if(rtcClock_alarmCfgTimeDate.Min == rtcClock_currentTimeDate.Min)
    {
        /* Set minute alarm */
        rtcClock_alarmCurStatus |= rtcClock_ALARM_MIN_MASK;
    }
    else /* no minute alarm */
    {
        /* Clear minute alarm */
        rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_MIN_MASK);
    }
}


/*******************************************************************************
* Function Name:   rtcClock_WriteAlarmHour
********************************************************************************
*
* Summary:
*  Writes Alarm Hour software register value.
*
* Parameters:
*  hour: Alarm hours value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate.Hour: this global variable is used for
*  comparison while setting and clearing hours alarm status variable.
*
*  rtcClock_alarmCfgTimeDate.Hour: this global variable is modified to
*  store of the new hours alarm.
*
*  rtcClock_alarmCurStatus: this global variable could be changed if
*  hours alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteAlarmHour(uint8 hour) 
{
    rtcClock_alarmCfgTimeDate.Hour = hour;

    /* Check hour alarm */
    if(rtcClock_alarmCfgTimeDate.Hour == rtcClock_currentTimeDate.Hour)
    {
        /* Set hour alarm */
        rtcClock_alarmCurStatus |= rtcClock_ALARM_HOUR_MASK;
    }
    else /* no hour alarm */
    {
        /* Clear hour alarm */
        rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_HOUR_MASK);
    }
}


/*******************************************************************************
* Function Name:   rtcClock_WriteAlarmDayOfMonth
********************************************************************************
*
* Summary:
*  Writes Alarm DayOfMonth software register value.
*
* Parameters:
*  dayOfMonth: Alarm day of month value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate.DayOfMonth: this global variable is used for
*  comparison while setting and clearing day of month alarm status variable.
*
*  rtcClock_alarmCfgTimeDate.DayOfMonth: this global variable is
*  modified to store of the new day of month alarm.
*
*  rtcClock_alarmCurStatus: this global variable could be changed if
*  day of month alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteAlarmDayOfMonth(uint8 dayOfMonth) 
{
    rtcClock_alarmCfgTimeDate.DayOfMonth = dayOfMonth;

    /* Check day of month alarm */
    if(rtcClock_alarmCfgTimeDate.DayOfMonth == rtcClock_currentTimeDate.DayOfMonth)
    {
        /* Set day of month alarm */
        rtcClock_alarmCurStatus |= rtcClock_ALARM_DAYOFMONTH_MASK;
    }
    else /* no day of month alarm */
    {
        /* Clear day of month alarm */
        rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_DAYOFMONTH_MASK);
    }
}


/*******************************************************************************
* Function Name:   rtcClock_WriteAlarmMonth
********************************************************************************
*
* Summary:
*  Writes Alarm Month software register value.
*
* Parameters:
*  month: Alarm month value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate.Month: this global variable is used for
*  comparison while setting and clearing month alarm status variable.
*
*  rtcClock_alarmCfgTimeDate.Month: this global variable is modified
*  to store of the new month alarm.
*
*  rtcClock_alarmCurStatus: this global variable could be changed if
*  month alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteAlarmMonth(uint8 month) 
{
    rtcClock_alarmCfgTimeDate.Month = month;

    /* Check month alarm */
    if(rtcClock_alarmCfgTimeDate.Month == rtcClock_currentTimeDate.Month)
    {
        /* Set month alarm */
        rtcClock_alarmCurStatus |= rtcClock_ALARM_MONTH_MASK;
    }
    else /* no month alarm */
    {
        /* Clear month alarm */
        rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_MONTH_MASK);
    }
}


/*******************************************************************************
* Function Name:   rtcClock_WriteAlarmYear
********************************************************************************
*
* Summary:
*  Writes Alarm Year software register value.
*
* Parameters:
*  year: Alarm year value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate.Year: this global variable is used for
*  comparison while setting and clearing year alarm status variable.
*
*  rtcClock_alarmCfgTimeDate.Year: this global variable is modified
*  to store of the new year alarm.
*
*  rtcClock_alarmCurStatus: this global variable could be changed if
*  year alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteAlarmYear(uint16 year) 
{
   rtcClock_alarmCfgTimeDate.Year = year;

    /* Check year alarm */
    if(rtcClock_alarmCfgTimeDate.Year == rtcClock_currentTimeDate.Year)
    {
        /* Set year alarm */
        rtcClock_alarmCurStatus |= rtcClock_ALARM_YEAR_MASK;
    }
    else /* no year alarm */
    {
        /* Set year alarm */
        rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_YEAR_MASK);
    }
}


/*******************************************************************************
* Function Name:   rtcClock_WriteAlarmDayOfWeek
********************************************************************************
*
* Summary:
*   Writes Alarm DayOfWeek software register value.
*   Days values {Sun = 1, Mon = 2, Tue = 3, Wen = 4, Thu = 5, Fri = 6, Sat = 7}
*
* Parameters:
*  dayOfWeek: Alarm day of week value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate.DayOfWeek: this global variable is used for
*  comparison while setting and clearing day of week alarm status variable.
*
*  rtcClock_alarmCfgTimeDate.DayOfWeek: this global variable is modified
*  to store of the new day of week alarm.
*
*  rtcClock_alarmCurStatus: this global variable could be changed if
*  day of week alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteAlarmDayOfWeek(uint8 dayOfWeek) 
{
    rtcClock_alarmCfgTimeDate.DayOfWeek = dayOfWeek;

    /* Check day of week alarm */
    if(rtcClock_alarmCfgTimeDate.DayOfWeek == rtcClock_currentTimeDate.DayOfWeek)
    {
        /* Set day of week alarm */
        rtcClock_alarmCurStatus |= rtcClock_ALARM_DAYOFWEEK_MASK;
    }
    else /* no day of week alarm */
    {
        /* Set day of week alarm */
        rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_DAYOFWEEK_MASK);
    }
}


/*******************************************************************************
* Function Name:   rtcClock_WriteAlarmDayOfYear
********************************************************************************
*
* Summary:
*  Writes Alarm DayOfYear software register value.
*
* Parameters:
*  dayOfYear: Alarm day of year value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate.DayOfYear: this global variable is used for
*  comparison while setting and clearing day of year alarm status variable.
*
*  rtcClock_alarmCfgTimeDate.DayOfYear: this global variable is modified
*  to store of the new day of year alarm.
*
*  rtcClock_alarmCurStatus: this global variable could be changed if
*  day of year alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteAlarmDayOfYear(uint16 dayOfYear) 
{
  rtcClock_alarmCfgTimeDate.DayOfYear = dayOfYear;

    /* Check day of year alarm */
    if(rtcClock_alarmCfgTimeDate.DayOfYear == rtcClock_currentTimeDate.DayOfYear)
    {
        /* Set day of year alarm */
        rtcClock_alarmCurStatus |= rtcClock_ALARM_DAYOFYEAR_MASK;
    }
    else /* no day of year alarm */
    {
        /* Set day of year alarm */
        rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_DAYOFYEAR_MASK);
    }
}


/*******************************************************************************
* Function Name:   rtcClock_ReadSecond
********************************************************************************
*
* Summary:
*  Reads Sec software register value.
*
* Parameters:
*  None.
*
* Return:
*  Current seconds value.
*
* Global variables:
*  rtcClock_currentTimeDate.Sec: the current second's value is used.
*
*******************************************************************************/
uint8 rtcClock_ReadSecond(void) 
{
    /* Return current second */
    return (rtcClock_currentTimeDate.Sec);
}


/*******************************************************************************
* Function Name:   rtcClock_ReadMinute
********************************************************************************
*
* Summary:
*  Reads Min software register value.
*
* Parameters:
*  None.
*
* Return:
*  Current field's value is returned.
*
* Global variables:
*  rtcClock_currentTimeDate.Min: the current field's value is used.
*
*******************************************************************************/
uint8 rtcClock_ReadMinute(void) 
{
    /* Return current minute */
    return (rtcClock_currentTimeDate.Min);
}


/*******************************************************************************
* Function Name:   rtcClock_ReadHour
********************************************************************************
*
* Summary:
*  Reads Hour software register value.
*
* Parameters:
*  None.
*
* Return:
*  Current hour's value.
*
* Global variables:
*  rtcClock_currentTimeDate.Hour: the current field's value is used.
*
*******************************************************************************/
uint8 rtcClock_ReadHour(void) 
{
    /* Return current hour */
    return (rtcClock_currentTimeDate.Hour);
}


/*******************************************************************************
* Function Name:   rtcClock_ReadDayOfMonth
********************************************************************************
*
* Summary:
*  Reads DayOfMonth software register value.
*
* Parameters:
*  None.
*
* Return:
*  Current value of the day of month.
*  returned.
*
* Global variables:
*  rtcClock_currentTimeDate.DayOfMonth: the current day of month's
*  value is used.
*
*******************************************************************************/
uint8 rtcClock_ReadDayOfMonth(void) 
{
    /* Return current day of the month */
    return (rtcClock_currentTimeDate.DayOfMonth);
}


/*******************************************************************************
* Function Name:   rtcClock_ReadMonth
********************************************************************************
*
* Summary:
*  Reads Month software register value.
*
* Parameters:
*  None.
*
* Return:
*  Current value of the month.
*
* Global variables:
*  rtcClock_currentTimeDate.Month: the current month's value is used.
*
*******************************************************************************/
uint8 rtcClock_ReadMonth(void) 
{
    /* Return current month */
    return (rtcClock_currentTimeDate.Month);
}


/*******************************************************************************
* Function Name:   rtcClock_ReadYear
********************************************************************************
*
* Summary:
*  Reads Year software register value.
*
* Parameters:
*  None.
*
* Return:
*  Current value of the year.
*
* Global variables:
*  rtcClock_currentTimeDate.Year: the current year's value is used.
*
*******************************************************************************/
uint16 rtcClock_ReadYear(void) 
{
    /* Return current year */
    return (rtcClock_currentTimeDate.Year);
}


/*******************************************************************************
* Function Name:   rtcClock_ReadAlarmSecond
********************************************************************************
*
* Summary:
*  Reads Alarm Sec software register value.
*
* Parameters:
*  None.
*
* Return:
*  Current alarm value of the seconds.
*
* Global variables:
*  rtcClock_alarmCfgTimeDate.Sec: the current second alarm value is
*  used.
*
********************************************************************************/
uint8 rtcClock_ReadAlarmSecond(void) 
{
    /* Return current alarm second */
    return (rtcClock_alarmCfgTimeDate.Sec);
}


/*******************************************************************************
* Function Name:   rtcClock_ReadAlarmMinute
********************************************************************************
*
* Summary:
*  Reads Alarm Min software register value.
*
* Parameters:
*  None.
*
* Return:
*  Current alarm value of the minutes.
*
* Global variables:
*  rtcClock_alarmCfgTimeDate.Min: the current minute alarm is used.
*
*******************************************************************************/
uint8 rtcClock_ReadAlarmMinute(void) 
{
    /* Return current alarm minute */
    return (rtcClock_alarmCfgTimeDate.Min);
}


/*******************************************************************************
* Function Name:   rtcClock_ReadAlarmHour
********************************************************************************
*
* Summary:
*  Reads Alarm Hour software register value.
*
* Parameters:
*  None.
*
* Return:
*  Current alarm value of the hours.
*
* Global variables:
*  rtcClock_alarmCfgTimeDate.Hour: the current hour alarm value is used.
*
*******************************************************************************/
uint8 rtcClock_ReadAlarmHour(void) 
{
    /* Return current alarm hour */
    return (rtcClock_alarmCfgTimeDate.Hour);
}


/*******************************************************************************
* Function Name:   rtcClock_ReadAlarmDayOfMonth
********************************************************************************
*
* Summary:
*  Reads Alarm DayOfMonth software register value.
*
* Parameters:
*  None.
*
* Return:
*  Current alarm value of the day of month.
*
* Global variables:
*  rtcClock_alarmCfgTimeDate.DayOfMonth: the current day of month alarm
*  value is used.
*
*******************************************************************************/
uint8 rtcClock_ReadAlarmDayOfMonth(void) 
{
    /* Return current alarm day of month */
    return (rtcClock_alarmCfgTimeDate.DayOfMonth);
}


/*******************************************************************************
* Function Name:   rtcClock_ReadAlarmMonth
********************************************************************************
*
* Summary:
*  Reads Alarm Month software register value.
*
* Parameters:
*  None.
*
* Return:
*  Current alarm value of the month.
*
* Global variables:
*  rtcClock_alarmCfgTimeDate.Month: the current month alarm value is
*  used.
*
*******************************************************************************/
uint8 rtcClock_ReadAlarmMonth(void) 
{
    /* Return current alarm month */
    return (rtcClock_alarmCfgTimeDate.Month);
}


/*******************************************************************************
* Function Name:   rtcClock_ReadAlarmYear
********************************************************************************
*
* Summary:
*  Reads Alarm Year software register value.
*
* Parameters:
*  None.
*
* Return:
*  Current alarm value of the years.
*
* Global variables:
*  rtcClock_alarmCfgTimeDate.Year: the current year alarm value is used.
*
*******************************************************************************/
uint16 rtcClock_ReadAlarmYear(void) 
{
    /* Return current alarm year */
    return (rtcClock_alarmCfgTimeDate.Year);
}


/*******************************************************************************
* Function Name:   rtcClock_ReadAlarmDayOfWeek
********************************************************************************
*
* Summary:
*  Reads Alarm DayOfWeek software register value.
*
* Parameters:
*  None.
*
* Return:
*  Current alarm value of the day of week.
*
* Global variables:
*  rtcClock_alarmCfgTimeDate.DayOfWeek: the current day of week alarm
*  value is used.
*
*******************************************************************************/
uint8 rtcClock_ReadAlarmDayOfWeek(void) 
{
    /* Return current alarm day of the week */
    return (rtcClock_alarmCfgTimeDate.DayOfWeek);
}


/*******************************************************************************
* Function Name:   rtcClock_ReadAlarmDayOfYear
********************************************************************************
*
* Summary:
*  Reads Alarm DayOfYear software register value.
*
* Parameters:
*  None.
*
* Return:
*  Current alarm value of the day of year.
*
* Global variables:
*  rtcClock_alarmCfgTimeDate.DayOfYear: the current day of year alarm
*  value is used.
*
*******************************************************************************/
uint16 rtcClock_ReadAlarmDayOfYear(void) 
{
    /* Return current alarm day of the year */
    return  (rtcClock_alarmCfgTimeDate.DayOfYear);
}


/*******************************************************************************
* Function Name:   rtcClock_WriteAlarmMask
********************************************************************************
*
* Summary:
*  Writes the Alarm Mask software register with 1 bit per time/date entry. Alarm
*  true when all masked time/date values match Alarm values.
*
* Parameters:
*  mask: Alarm Mask software register value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_alarmCfgMask: global variable which stores masks for
*  time/date alarm configuration is modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteAlarmMask(uint8 mask) 
{
    rtcClock_alarmCfgMask = mask;
}


/*******************************************************************************
* Function Name:   rtcClock_WriteIntervalMask
********************************************************************************
*
* Summary:
*  Writes the Interval Mask software register with 1 bit per time/date entry.
*  Interrupt true when any masked time/date overflow occur.
*
* Parameters:
*  mask: Alarm Mask software register value.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_intervalCfgMask: this global variable is modified - the new
*  value of interval mask is stored here.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rtcClock_WriteIntervalMask(uint8 mask) 
{
    rtcClock_intervalCfgMask = mask;
}


/*******************************************************************************
* Function Name:   rtcClock_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the Status software register which has flags for DST
*  (DST), Leap Year (LY) and AM/PM (AM_PM), Alarm active (AA).
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_statusDateTime: global variable is modified - active alarm
*  status bit is cleared.
*
* Reentrant:
*  No.
*
* Side Effects:
*  Alarm active(AA) flag clear after read.
*
*******************************************************************************/
uint8 rtcClock_ReadStatus(void) 
{
    uint8 status;

    /* Save status */
    status = (uint8)rtcClock_statusDateTime;

    /* Clean AA flag after read of Status Register */
    rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_AA);

    return (status);
}


/*******************************************************************************
* Function Name:   rtcClock_DayOfWeek
********************************************************************************
*
* Summary:
*  Calculates Day Of Week value use Zeller's congruence.
*
* Parameters:
*  dayOfMonth: Day Of Month value.
*  month: Month value.
*  year: Year value.
*
* Return:
*  Day Of Week value.
*
*******************************************************************************/
static uint8 rtcClock_DayOfWeek(uint8 dayOfMonth, uint8 month, uint16 year)

{
    /* Calculated sequence ((31 * month) / 12) mod 7 from the Zeller's congruence */
    static const uint8 CYCODE rtcClock_monthTemplate[rtcClock_MONTHS_IN_YEAR] =
                                                            {0u, 3u, 2u, 5u, 0u, 3u, 5u, 1u, 4u, 6u, 2u, 4u};

    /* It is simpler to handle the modified year, which is year - 1 during
    * January and February
    */
    if(month < rtcClock_MARCH)
    {
        year = year - 1u;
    }

    /* For Gregorian calendar: d = (day + y + y/4 - y/100 + y/400 + (31*m)/12) mod 7 */
    return ((uint8)(((year + (((year/4u) - (year/100u)) + (year/400u))) +
    (((uint16)rtcClock_monthTemplate[month - 1u]) + ((uint16) dayOfMonth))) % rtcClock_DAYS_IN_WEEK));
}


/*******************************************************************************
* Function Name:   rtcClock_SetInitValues
********************************************************************************
*
* Summary:
*    Does all initial calculation.
*    - Set LP Year flag;
*    - Set AM/PM flag;
*    - DayOfWeek;
*    - DayOfYear;
*    - Set DST flag;
*    - Convert relative to absolute date.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  rtcClock_currentTimeDate, rtcClock_dstTimeDateStart,
*  rtcClock_dstTimeDateStop, rtcClock_dstTimeDateStart,
*  rtcClock_alarmCfgTimeDate, rtcClock_statusDateTime,
*  rtcClock_dstStartStatus, rtcClock_dstStartStatus,
*  rtcClock_dstStopStatus, rtcClock_alarmCurStatus:
*  global variables are used while the initial calculation.
*
* rtcClock_dstTimeDateStart, rtcClock_currentTimeDate,
*  rtcClock_statusDateTime, rtcClock_dstStartStatus,
*  rtcClock_dstStartStatus, rtcClock_dstStopStatus,
*  rtcClock_alarmCurStatus: global variables are modified with the
*  initial calculated data.
*
* Reentrant:
*  No.
*
*******************************************************************************/
static void rtcClock_SetInitValues(void) 
{
    uint8 i;
    uint8 rtcClock_alarmCfgMaskTemp;

    /* Clears day of month counter */
    rtcClock_currentTimeDate.DayOfYear = 0u;

    /* Increments day of year value with day in current month */
    rtcClock_currentTimeDate.DayOfYear += rtcClock_currentTimeDate.DayOfMonth;

    /* Check leap year */
    if(1u == rtcClock_LEAP_YEAR(rtcClock_currentTimeDate.Year))
    {
        /* Set LP Year flag */
        rtcClock_statusDateTime |= rtcClock_STATUS_LY;
    }   /* leap year flag was set */
    else
    {
        /* Clear LP Year flag */
        rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_LY);
    }   /* leap year flag was cleared */

    /* Day of Year */
    for(i = 0u; i < (rtcClock_currentTimeDate.Month - 1u); i++)
    {
        /* Increment on days in passed months */
        rtcClock_currentTimeDate.DayOfYear += rtcClock_daysInMonths[i];
    }   /* day of year is calculated */

    /* Leap year check */
    if(0u != rtcClock_IS_BIT_SET(rtcClock_statusDateTime, rtcClock_STATUS_LY))
    {
        /* Leap day check */
        if(rtcClock_currentTimeDate.Month > rtcClock_FEBRUARY)
        {
            /* Add leap day */
            rtcClock_currentTimeDate.DayOfYear++;
        }   /* Do nothing for non leap day */
    }   /* Do nothing for not leap year */

    /* DayOfWeek */
    rtcClock_currentTimeDate.DayOfWeek = rtcClock_DayOfWeek(
                                                                        rtcClock_currentTimeDate.DayOfMonth,
                                                                        rtcClock_currentTimeDate.Month,
                                                                        rtcClock_currentTimeDate.Year) + 1u;

    if(rtcClock_currentTimeDate.DayOfWeek > rtcClock_START_OF_WEEK)
    {
        rtcClock_currentTimeDate.DayOfWeek -= rtcClock_START_OF_WEEK;
    }
    else
    {
        rtcClock_currentTimeDate.DayOfWeek = rtcClock_DAYS_IN_WEEK -
                                        (rtcClock_START_OF_WEEK - rtcClock_currentTimeDate.DayOfWeek);
    }

    #if (1u == rtcClock_DST_FUNC_ENABLE)

        /* If DST values is given in a relative manner, converts to the absolute values */
        if(0u != rtcClock_IS_BIT_SET(rtcClock_dstModeType, rtcClock_DST_RELDATE))
        {
            rtcClock_DSTDateConversion();
        }

        /* Sets DST status respect to the DST start date and time */
        if(rtcClock_currentTimeDate.Month > rtcClock_dstTimeDateStart.Month)
        {
            rtcClock_statusDateTime |= rtcClock_STATUS_DST;
        }
        else if(rtcClock_currentTimeDate.Month == rtcClock_dstTimeDateStart.Month)
        {
            if(rtcClock_currentTimeDate.DayOfMonth > rtcClock_dstTimeDateStart.DayOfMonth)
            {
                rtcClock_statusDateTime |= rtcClock_STATUS_DST;
            }
            else if(rtcClock_currentTimeDate.DayOfMonth == rtcClock_dstTimeDateStart.DayOfMonth)
            {
                if(rtcClock_currentTimeDate.Hour > rtcClock_dstTimeDateStart.Hour)
                {
                    rtcClock_statusDateTime |= rtcClock_STATUS_DST;
                }
            }
            else
            {
                /* Do nothing if current day of month is less than DST stop day of month */
            }
        }
        else
        {
            /* Do nothing if current month is before than DST stop month */
        }

        /* Clears DST status respect to the DST start date and time */
        if(rtcClock_currentTimeDate.Month > rtcClock_dstTimeDateStop.Month)
        {
            rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_DST);
        }
        else if(rtcClock_currentTimeDate.Month == rtcClock_dstTimeDateStop.Month)
        {
            if(rtcClock_currentTimeDate.DayOfMonth > rtcClock_dstTimeDateStop.DayOfMonth)
            {
                rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_DST);
            }
            else if(rtcClock_currentTimeDate.DayOfMonth == rtcClock_dstTimeDateStop.DayOfMonth)
            {
                if(rtcClock_currentTimeDate.Hour > rtcClock_dstTimeDateStop.Hour)
                {
                    rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_DST);
                }
            }
            else
            {
                /* Do nothing if current day of month is less than DST stop day of month */
            }
        }
        else
        {
            /* Do nothing if current month is before than DST stop month */
        }

        /* Clear DST start/stop statuses */
        rtcClock_dstStartStatus = 0u;
        rtcClock_dstStopStatus = 0u;

        /* Sets DST stop status month flag if DST stop month is equal to the
        * current month, otherwise clears that flag.
        */
        if(rtcClock_dstTimeDateStop.Month == rtcClock_currentTimeDate.Month)
        {
            rtcClock_dstStopStatus |= rtcClock_DST_MONTH;
        }
        else
        {
            rtcClock_dstStopStatus &= (uint8)(~rtcClock_DST_MONTH);
        }

        /* Sets DST start status month flag if DST start month is equal to the
        * current month, otherwise clears that flag.
        */
        if(rtcClock_dstTimeDateStart.Month == rtcClock_currentTimeDate.Month)
        {
            rtcClock_dstStartStatus |= rtcClock_DST_MONTH;
        }
        else
        {
            rtcClock_dstStartStatus &= (uint8)(~rtcClock_DST_MONTH);
        }

        /* Sets DST stop status day of month flag if DST stop day of month is
        * equal to the current day of month, otherwise clears that flag.
        */
        if(rtcClock_dstTimeDateStop.DayOfMonth == rtcClock_currentTimeDate.DayOfMonth)
        {
            rtcClock_dstStopStatus |= rtcClock_DST_DAYOFMONTH;
        }
        else
        {
            rtcClock_dstStopStatus &= (uint8)(~rtcClock_DST_DAYOFMONTH);
        }

        /* Sets DST start status day of month flag if DST start day of month is
        * equal to the current day of month, otherwise clears that flag.
        */
        if(rtcClock_dstTimeDateStart.DayOfMonth == rtcClock_currentTimeDate.DayOfMonth)
        {
            rtcClock_dstStartStatus |= rtcClock_DST_DAYOFMONTH;
        }
        else
        {
            rtcClock_dstStartStatus &= (uint8)(~rtcClock_DST_DAYOFMONTH);
        }

        /* Sets DST stop status hour flag if DST stop hour is equal to the
        * current hour, otherwise clears that flag.
        */
        if(rtcClock_dstTimeDateStop.Hour == rtcClock_currentTimeDate.Hour)
        {
            rtcClock_dstStopStatus |= rtcClock_DST_HOUR;
        }
        else
        {
            rtcClock_dstStopStatus &= (uint8)(~rtcClock_DST_HOUR);
        }

        /* Sets DST start status hour flag if DST start hour is equal to the
        * current hour, otherwise clears that flag.
        */
        if(rtcClock_dstTimeDateStart.Hour == rtcClock_currentTimeDate.Hour)
        {
            rtcClock_dstStartStatus |= rtcClock_DST_HOUR;
        }
        else
        {
            rtcClock_dstStartStatus &= (uint8)(~rtcClock_DST_HOUR);
        }

        /* DST Enable ? */
        if(0u != rtcClock_IS_BIT_SET(rtcClock_dstModeType, rtcClock_DST_ENABLE))
        {
            if(0u != rtcClock_IS_BIT_SET(rtcClock_statusDateTime, rtcClock_STATUS_DST))
            {
                if(0u != rtcClock_IS_BIT_SET(rtcClock_dstStartStatus,
                        (rtcClock_DST_HOUR | rtcClock_DST_DAYOFMONTH | rtcClock_DST_MONTH)))
                {
                    /* Subtract current minutes value with minutes value, what
                    *  are out of full hour in DST offset.
                    */
                    rtcClock_currentTimeDate.Min -= rtcClock_dstOffsetMin %
                                                            (rtcClock_HOUR_ELAPSED + 1u);

                    /* If current minutes value is greater than number of
                    * minutes in hour - could be only if hour's value is negative
                    */
                    if(rtcClock_currentTimeDate.Min > rtcClock_HOUR_ELAPSED)
                    {
                        /* Adjust current minutes value. Convert to the positive. */
                        rtcClock_currentTimeDate.Min = rtcClock_HOUR_ELAPSED -
                                                               ((uint8)(~rtcClock_currentTimeDate.Min));

                        /* Decrement current hours value. */
                        rtcClock_currentTimeDate.Hour--;
                    }

                    /* Subtract current hours value with hours value, what
                    *  are full part of hours in DST offset.
                    */
                    rtcClock_currentTimeDate.Hour -= rtcClock_dstOffsetMin /
                                                             (rtcClock_HOUR_ELAPSED + 1u);

                    /* Check if current hour's value is negative */
                    if(rtcClock_currentTimeDate.Hour > rtcClock_DAY_ELAPSED)
                    {
                        /* Adjust hour */
                        rtcClock_currentTimeDate.Hour = rtcClock_DAY_ELAPSED -
                                                                ((uint8)(~rtcClock_currentTimeDate.Hour));

                        /* Decrement day of month, year and week */
                        rtcClock_currentTimeDate.DayOfMonth--;
                        rtcClock_currentTimeDate.DayOfYear--;
                        rtcClock_currentTimeDate.DayOfWeek--;

                        if(0u == rtcClock_currentTimeDate.DayOfWeek)
                        {
                            rtcClock_currentTimeDate.DayOfWeek = rtcClock_DAYS_IN_WEEK;
                        }

                        if(0u == rtcClock_currentTimeDate.DayOfMonth)
                        {
                            /* Decrement months value */
                            rtcClock_currentTimeDate.Month--;

                            /* The current month is month before 1st one. */
                            if(0u == rtcClock_currentTimeDate.Month)
                            {
                                /* December is the month before January */
                                rtcClock_currentTimeDate.Month = rtcClock_DECEMBER;
                                rtcClock_currentTimeDate.DayOfMonth =
                                            rtcClock_daysInMonths[rtcClock_currentTimeDate.Month - 1u];

                                /* Decrement years value */
                                rtcClock_currentTimeDate.Year--;
                                if(1u == rtcClock_LEAP_YEAR(rtcClock_currentTimeDate.Year))
                                {
                                    /* Set leap year status flag */
                                    rtcClock_statusDateTime |= rtcClock_STATUS_LY;
                                    rtcClock_currentTimeDate.DayOfYear = rtcClock_DAYS_IN_LEAP_YEAR;
                                }
                                else
                                {
                                    /* Clear leap year status flag */
                                    rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_LY);
                                    rtcClock_currentTimeDate.DayOfYear = rtcClock_DAYS_IN_YEAR;
                                }
                            }   /* 0u == rtcClock_currentTimeDate.Month */
                            else
                            {
                                rtcClock_currentTimeDate.DayOfMonth =
                                            rtcClock_daysInMonths[rtcClock_currentTimeDate.Month - 1u];
                            }   /* 0u != End of rtcClock_currentTimeDate.Month */
                        }   /* 0u == End of rtcClock_currentTimeDate.DayOfMonth */
                    }   /* End of rtcClock_currentTimeDate.Hour > rtcClock_DAY_ELAPSED */

                    /* Clear DST status flag */
                    rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_DST);
                    /* Clear DST stop status */
                    rtcClock_dstStopStatus = 0u;
                }
            }
            else    /* Current time and date DO NOT match DST time and date */
            {
                if(0u != rtcClock_IS_BIT_SET(rtcClock_dstStartStatus, rtcClock_DST_HOUR |
                                                     rtcClock_DST_DAYOFMONTH | rtcClock_DST_MONTH))
                {
                    /* Add Hour and Min */
                    rtcClock_currentTimeDate.Min +=
                                                rtcClock_dstOffsetMin % (rtcClock_HOUR_ELAPSED + 1u);

                    if(rtcClock_currentTimeDate.Min > rtcClock_HOUR_ELAPSED)
                    {
                        /* Adjust Min */
                        rtcClock_currentTimeDate.Min -= (rtcClock_HOUR_ELAPSED + 1u);
                        rtcClock_currentTimeDate.Hour++;
                    }

                    rtcClock_currentTimeDate.Hour +=
                                                rtcClock_dstOffsetMin / (rtcClock_HOUR_ELAPSED + 1u);
                    if(rtcClock_currentTimeDate.Hour > rtcClock_DAY_ELAPSED)
                    {
                        /* Adjust hour, add day */
                        rtcClock_currentTimeDate.Hour -= (rtcClock_DAY_ELAPSED + 1u);
                        rtcClock_currentTimeDate.DayOfMonth++;
                        rtcClock_currentTimeDate.DayOfYear++;
                        rtcClock_currentTimeDate.DayOfWeek++;

                        if(rtcClock_currentTimeDate.DayOfWeek > rtcClock_WEEK_ELAPSED)
                        {
                            rtcClock_currentTimeDate.DayOfWeek = 1u;
                        }

                        if(rtcClock_currentTimeDate.DayOfMonth >
                                            rtcClock_daysInMonths[rtcClock_currentTimeDate.Month - 1u])
                        {
                            rtcClock_currentTimeDate.Month++;
                            rtcClock_currentTimeDate.DayOfMonth = 1u;

                            /* Has new year come? */
                            if(rtcClock_currentTimeDate.Month > rtcClock_YEAR_ELAPSED)
                            {
                                /* Set first month of the year */
                                rtcClock_currentTimeDate.Month = rtcClock_JANUARY;

                                /* Increment year */
                                rtcClock_currentTimeDate.Year++;

                                /* Update leap year status */
                                if(1u == rtcClock_LEAP_YEAR(rtcClock_currentTimeDate.Year))
                                {
                                    /* LP - true, else - false */
                                    rtcClock_statusDateTime |= rtcClock_STATUS_LY;
                                }
                                else
                                {
                                    rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_LY);
                                }

                                /* Set day of year to the first one */
                                rtcClock_currentTimeDate.DayOfYear = 1u;
                            }
                        }
                    }
                    rtcClock_statusDateTime |= rtcClock_STATUS_DST;
                    rtcClock_dstStartStatus = 0u;
                }
            }
        }
    #endif /* 1u == rtcClock_DST_FUNC_ENABLE */

    /* Set AM/PM flag */
    if(rtcClock_currentTimeDate.Hour < rtcClock_HALF_OF_DAY_ELAPSED)
    {
        /* AM Hour 00:00-11:59, flag zero */
        rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_AM_PM);
    }
    else
    {
        /* PM Hour 12:00 - 23:59, flag set */
        rtcClock_statusDateTime |= rtcClock_STATUS_AM_PM;
    }

    /* Alarm calculation */

    /* Alarm SEC */
    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask, rtcClock_ALARM_SEC_MASK))
    {
        if(rtcClock_alarmCfgTimeDate.Sec == rtcClock_currentTimeDate.Sec)
        {
            /* Set second alarm */
            rtcClock_alarmCurStatus |= rtcClock_ALARM_SEC_MASK;
        }
        else
        {
            /* Clear second alarm */
            rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_SEC_MASK);
        }
    }

    /* Alarm MIN */
    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask, rtcClock_ALARM_MIN_MASK))
    {
        if(rtcClock_alarmCfgTimeDate.Min == rtcClock_currentTimeDate.Min)
        {
            /* Set minute alarm */
            rtcClock_alarmCurStatus |= rtcClock_ALARM_MIN_MASK;
        }
        else
        {
            /* Clear minute alarm */
            rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_MIN_MASK);
        }
    }

    /* Alarm HOUR */
    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask, rtcClock_ALARM_HOUR_MASK))
    {
        if(rtcClock_alarmCfgTimeDate.Hour == rtcClock_currentTimeDate.Hour)
        {
            /* Set hour alarm */
            rtcClock_alarmCurStatus |= rtcClock_ALARM_HOUR_MASK;
        }
        else
        {
            /* Clear hour alarm */
            rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_HOUR_MASK);
        }
    }

    /* Alarm DAYOFWEEK */
    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask, rtcClock_ALARM_DAYOFWEEK_MASK))
    {
        if(rtcClock_alarmCfgTimeDate.DayOfWeek == rtcClock_currentTimeDate.DayOfWeek)
        {
            /* Set day of week alarm */
            rtcClock_alarmCurStatus |= rtcClock_ALARM_DAYOFWEEK_MASK;
        }
        else
        {
            /* Clear day of week alarm */
            rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_DAYOFWEEK_MASK);
        }
    }

    /* Alarm DAYOFYEAR */
    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask, rtcClock_ALARM_DAYOFYEAR_MASK))
    {
        if(rtcClock_alarmCfgTimeDate.DayOfYear == rtcClock_currentTimeDate.DayOfYear)
        {
            /* Set day of year alarm */
            rtcClock_alarmCurStatus |= rtcClock_ALARM_DAYOFYEAR_MASK;
        }
        else
        {
            /* Clear day of year alarm */
            rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_DAYOFYEAR_MASK);
        }
    }

    /* Alarm DAYOFMONTH */
    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask, rtcClock_ALARM_DAYOFMONTH_MASK))
    {
        if(rtcClock_alarmCfgTimeDate.DayOfMonth == rtcClock_currentTimeDate.DayOfMonth)
        {
            /* Set day of month alarm */
            rtcClock_alarmCurStatus |= rtcClock_ALARM_DAYOFMONTH_MASK;
        }
           else
        {
            /* Clear day of month alarm */
            rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_DAYOFMONTH_MASK);
        }
    }

    /* Alarm MONTH */
    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask, rtcClock_ALARM_MONTH_MASK))
    {
        if(rtcClock_alarmCfgTimeDate.Month == rtcClock_currentTimeDate.Month)
        {
            /* Set month alarm */
            rtcClock_alarmCurStatus |= rtcClock_ALARM_MONTH_MASK;
        }
        else
        {
            /* Clear month alarm */
            rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_MONTH_MASK);
        }
    }

    /* Alarm YEAR */
    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask, rtcClock_ALARM_YEAR_MASK))
    {
        if(rtcClock_alarmCfgTimeDate.Year == rtcClock_currentTimeDate.Year)
        {
            /* Set year alarm */
            rtcClock_alarmCurStatus |= rtcClock_ALARM_YEAR_MASK;
        }
        else
        {
            /* Clear year alarm */
            rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_YEAR_MASK);
        }
    }

    rtcClock_alarmCfgMaskTemp = rtcClock_alarmCfgMask;
    /* Set Alarm flag event */
    rtcClock_SET_ALARM(rtcClock_alarmCfgMaskTemp,
                               rtcClock_alarmCurStatus,
                               rtcClock_statusDateTime);
}


#if (1u == rtcClock_DST_FUNC_ENABLE)
    /*******************************************************************************
    * Function Name:   rtcClock_WriteDSTMode
    ********************************************************************************
    *
    * Summary:
    *  Writes the DST mode software register. That enables or disables DST changes
    *  and sets the date mode to fixed date or relative date. Only generated if DST
    *  enabled.
    *
    * Parameters:
    *  mode: DST Mode software register value.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  rtcClock_dstModeType: global variable is modified with the new
    *  DST mode type: relative or fixed.
    *
    *  rtcClock_dstTimeDateStart.Month,
    *  rtcClock_dstTimeDateStart.DayOfWeek,
    *  rtcClock_dstTimeDateStart.Week:
    *  rtcClock_dstTimeDateStop.Month,
    *  rtcClock_dstTimeDateStop.DayOfWeek,
    *  rtcClock_dstTimeDateStop.Week,
    *  rtcClock_currentTimeDate.Year: for the day of week correction,
    *   they are used by rtcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rtcClock_dstTimeDateStart.DayOfMonth,
    *  rtcClock_dstTimeDateStop.DayOfMonth: updated after convertion by
    *  the rtcClock_DSTDateConversion() function if DST mode is
    *  configured to be relative.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rtcClock_WriteDSTMode(uint8 mode) 
    {
        /* Set DST mode */
        rtcClock_dstModeType = mode;

        if(0u != rtcClock_IS_BIT_SET(mode, rtcClock_DST_RELDATE))
        {
            /* Convert DST date */
            rtcClock_DSTDateConversion();
        }
    }


    /*******************************************************************************
    * Function Name:   rtcClock_WriteDSTStartHour
    ********************************************************************************
    *
    * Summary:
    *  Writes the DST Start Hour software register. Used for absolute date entry.
    *  Only generated if DST is enabled.
    *
    * Parameters:
    *  hour: DST Start Hour software register value.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  rtcClock_dstTimeDateStart.Hour: global variable is modified with
    *  the new value.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rtcClock_WriteDSTStartHour(uint8 hour) 
    {
        /* Set DST Start Hour */
        rtcClock_dstTimeDateStart.Hour = hour;
    }


    /*******************************************************************************
    * Function Name:   rtcClock_WriteDSTStartOfMonth
    ********************************************************************************
    *
    * Summary:
    *  Writes the DST Start DayOfMonth software register. Used for absolute date
    *  entry. Only generated if DST is enabled.
    *
    * Parameters:
    *  dayOfMonth: DST Start DayOfMonth software register value.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  rtcClock_dstTimeDateStart.DayOfMonth: global variable is modified
    *  with the new value.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rtcClock_WriteDSTStartDayOfMonth(uint8 dayOfMonth)
         
    {
        /* Set DST Start day of month */
        rtcClock_dstTimeDateStart.DayOfMonth = dayOfMonth;
    }


    /*******************************************************************************
    * Function Name:   rtcClock_WriteDSTStartMonth
    ********************************************************************************
    *
    * Summary:
    *  Writes the DST Start Month software register. Used for absolute date entry.
    *  Only generated if DST is enabled.
    *
    * Parameters:
    *  month: DST Start month software register value.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  rtcClock_dstTimeDateStart.Month: global variable is modified
    *  with the new value.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rtcClock_WriteDSTStartMonth(uint8 month) 
    {
        /* Set DST Start month */
        rtcClock_dstTimeDateStart.Month = month;
    }


    /*******************************************************************************
    * Function Name:   rtcClock_WriteDSTStartDayOfWeek
    ********************************************************************************
    *
    * Summary:
    *  Writes the DST Start DayOfWeek software register. Used for absolute date
    *  entry. Only generated if DST is enabled.
    *
    * Parameters:
    *  dayOfWeek: DST start day of week software register value.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  rtcClock_dstModeType: global variable, where DST mode type:
    *  relative or fixed is stored.
    *
    *  rtcClock_dstTimeDateStart.Month,
    *  rtcClock_dstTimeDateStart.DayOfWeek,
    *  rtcClock_dstTimeDateStart.Week,
    *  rtcClock_dstTimeDateStop.Month,
    *  rtcClock_dstTimeDateStop.DayOfWeek,
    *  rtcClock_dstTimeDateStop.Week: for the day of week correction,
    *   they are used by rtcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rtcClock_currentTimeDate.Year: for the day of week calculation,
    *   it is used by rtcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rtcClock_dstTimeDateStart.DayOfWeek: global variable is modified
    *  with the new day of week value.
    *
    *  rtcClock_dstTimeDateStart.DayOfMonth and
    *  rtcClock_dstTimeDateStop.DayOfMonth are modified by
    *  the rtcClock_DSTDateConversion() function if DST mode is
    *  configured to be relative.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rtcClock_WriteDSTStartDayOfWeek(uint8 dayOfWeek)
         
    {
        /* Set DST Start day of week */
        rtcClock_dstTimeDateStart.DayOfWeek = dayOfWeek;

        if(0u != rtcClock_IS_BIT_SET(rtcClock_dstModeType, rtcClock_DST_RELDATE))
        {
            /* Convert DST date */
            rtcClock_DSTDateConversion();
        }
    }


    /*******************************************************************************
    * Function Name:   rtcClock_WriteDSTStartWeek
    ********************************************************************************
    *
    * Summary:
    *  Writes the DST Start Week software register. Used for absolute date entry.
    *  Only generated if DST is enabled.
    *
    * Parameters:
    *  week: DST start week software register value.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  rtcClock_dstTimeDateStart.Week: global variable is modified with
    *   the new week's value of the DST start time/date.
    *
    *  rtcClock_dstTimeDateStart.DayOfMonth,
    *  rtcClock_dstTimeDateStop.DayOfMonth: is modified after convertion
    *  by the rtcClock_DSTDateConversion() function if DST mode is
    *  configured to be relative.
    *
    *  rtcClock_dstModeType: global variable is used for theDST mode
    *   type: relative or fixed store.
    *
    *  rtcClock_dstTimeDateStart.Month,
    *  rtcClock_dstTimeDateStart.DayOfWeek,
    *  rtcClock_dstTimeDateStart.Week: for the day of week correction,
    *   they are used by rtcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rtcClock_dstTimeDateStop.Month,
    *  rtcClock_dstTimeDateStop.DayOfWeek,
    *  rtcClock_dstTimeDateStop.Week: for the day of week correction,
    *   they are used by rtcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rtcClock_currentTimeDate.Year: for the day of week calculation,
    *   it is used by rtcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rtcClock_WriteDSTStartWeek(uint8 week) 
    {
        /* Set DST Start week */
        rtcClock_dstTimeDateStart.Week = week;

        if(0u != rtcClock_IS_BIT_SET(rtcClock_dstModeType, rtcClock_DST_RELDATE))
        {
            /* Convert DST date */
            rtcClock_DSTDateConversion();
        }
    }


    /*******************************************************************************
    * Function Name:   rtcClock_WriteDSTStopHour
    ********************************************************************************
    *
    * Summary:
    *  Writes the DST Stop Hour software register. Used for absolute date entry.
    *  Only generated if DST is enabled.
    *
    * Parameters:
    *  hour: DST stop hour software register value.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  RTC_dstTimeDateStart.Hour: global variable is modified with the new hour
    *   of the DST start time/date.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rtcClock_WriteDSTStopHour(uint8 hour) 
    {
        /* Set DST Stop hour */
        rtcClock_dstTimeDateStop.Hour = hour;
    }


    /*******************************************************************************
    * Function Name:   rtcClock_WriteDSTStopDayOfMonth
    ********************************************************************************
    *
    * Summary:
    *  Writes the DST Stop DayOfMonth software register. Used for absolute date
    *  entry. Only generated if DST is enabled.
    *
    * Parameters:
    *  dayOfMonth: DST stop day of month software register value.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  rtcClock_dstTimeDateStop.DayOfMonth: global variable is modified
    *  where new day of month's value of the DST stop time/date.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rtcClock_WriteDSTStopDayOfMonth(uint8 dayOfMonth)
         
    {
        /* Set DST Start day of month */
        rtcClock_dstTimeDateStop.DayOfMonth = dayOfMonth;
    }


    /*******************************************************************************
    * Function Name:   rtcClock_WriteDSTStopMonth
    ********************************************************************************
    *
    * Summary:
    *  Writes the DST Stop Month software  register. Used for absolute date entry.
    *  Only generated if DST is enabled.
    *
    * Parameters:
    *  month: DST Stop Month software register value.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  rtcClock_dstTimeDateStop.Month: global variable is modified with
    *   the new month of the DST stop time/date.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rtcClock_WriteDSTStopMonth(uint8 month) 
    {
        /* Set DST Stop month */
        rtcClock_dstTimeDateStop.Month = month;
    }


    /*******************************************************************************
    * Function Name:   rtcClock_WriteDSTStopDayOfWeek
    ********************************************************************************
    *
    * Summary:
    *  Writes the DST Stop DayOfWeek software register. Used for relative date
    *  entry. Only generated if DST is enabled.
    *
    * Parameters:
    *  dayOfWeek: DST stop day of week software register value.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  rtcClock_dstTimeDateStop.DayOfWeek: global variable is modified
    *   with the day of week of the DST stop time/date.
    *
    *  rtcClock_dstModeType: global variable is used to store DST mode
    *   type: relative or fixed.
    *
    *  rtcClock_dstTimeDateStart.Month,
    *  rtcClock_dstTimeDateStart.DayOfWeek,
    *  rtcClock_dstTimeDateStart.Week,
    *  rtcClock_dstTimeDateStop.Month,
    *  rtcClock_dstTimeDateStop.DayOfWeek,
    *  rtcClock_dstTimeDateStop.Weekfor the day of week correction,
    *   they are used by rtcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rtcClock_currentTimeDate.Year: for the day of week calculation,
    *   it is used by rtcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rtcClock_dstTimeDateStop.DayOfWeek: global variable is modified
    *  with the new day of week's value.
    *
    *  rtcClock_dstTimeDateStart.DayOfMonth and
    *  rtcClock_dstTimeDateStop.DayOfMonth are modified by
    *  the rtcClock_DSTDateConversion() function if DST mode is
    *  configured to be relative.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rtcClock_WriteDSTStopDayOfWeek(uint8 dayOfWeek)
         
    {
        /* Set DST Stop day of week */
        rtcClock_dstTimeDateStop.DayOfWeek = dayOfWeek;

        if(0u != rtcClock_IS_BIT_SET(rtcClock_dstModeType, rtcClock_DST_RELDATE))
        {
            /* Convert DST date */
            rtcClock_DSTDateConversion();
        }
    }


    /*******************************************************************************
    * Function Name:   rtcClock_WriteDSTStopWeek
    ********************************************************************************
    *
    * Summary:
    *  Writes the DST Stop Week software register. Used for relative date entry.
    *  Only generated if DST is enabled.
    *
    * Parameters:
    *  week: DST stop week software register value.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  rtcClock_dstTimeDateStop.Week: global variable used to store the
    *  DST stop time/date is stored.
    *
    *  rtcClock_dstModeType: global variable is used to store DST mode
    *   type: relative or fixed.
    *
    *  rtcClock_dstTimeDateStart.Month,
    *  rtcClock_dstTimeDateStart.DayOfWeek,
    *  rtcClock_dstTimeDateStart.Week,
    *  rtcClock_dstTimeDateStop.Month,
    *  rtcClock_dstTimeDateStop.DayOfWeek,
    *  rtcClock_dstTimeDateStop.Week: used for the day of week correction,
    *   they are used by rtcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rtcClock_currentTimeDate.Year: for the day of week calculation,
    *   it is used by rtcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rtcClock_dstTimeDateStop.Week: global variable is modified with
    *  the new value.
    *
    *  rtcClock_dstTimeDateStart.DayOfMonth and
    *  rtcClock_dstTimeDateStop.DayOfMonth are modified by
    *  the rtcClock_DSTDateConversion() function if DST mode is
    *  configured to be relative.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rtcClock_WriteDSTStopWeek(uint8 week) 
    {
        /* Set DST Stop week */
        rtcClock_dstTimeDateStop.Week = week;

        if(0u != rtcClock_IS_BIT_SET(rtcClock_dstModeType, rtcClock_DST_RELDATE))
        {
            /* Convert DST date */
            rtcClock_DSTDateConversion();
        }
    }


    /*******************************************************************************
    * Function Name:   rtcClock_WriteDSTOffset
    ********************************************************************************
    *
    * Summary:
    *  Writes the DST Offset register. Allows a configurable increment or decrement
    *  of time between 0 and 255 minutes. Increment occurs on DST Start and
    *  decrement on DST Stop. Only generated if DST is enabled.
    *
    * Parameters:
    *  offset: The DST offset to be saved.
    *
    * Return:
    *  None.
    *
    * Global variables:
    *  rtcClock_dstOffsetMin: global variable is modified with the new
    *  DST offset value (in minutes).
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rtcClock_WriteDSTOffset(uint8 offset) 
    {
        /* Set DST offset */
        rtcClock_dstOffsetMin = offset;
    }

#endif /* 1u == rtcClock_DST_FUNC_ENABLE */


/* [] END OF FILE */
