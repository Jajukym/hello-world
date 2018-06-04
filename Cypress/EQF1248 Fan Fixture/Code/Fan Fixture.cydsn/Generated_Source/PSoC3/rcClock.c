/*******************************************************************************
* File Name: rcClock.c
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

#include "rcClock.h"
#include "CyLib.h"

/* Function Prototypes */
static void  rcClock_SetInitValues(void)     ;
static uint8 rcClock_DayOfWeek(uint8 dayOfMonth, uint8 month, uint16 year)
                                                      ;
#if (1u == rcClock_DST_FUNC_ENABLE)
    static void  rcClock_DSTDateConversion(void) ;
#endif /* 1u == rcClock_DST_FUNC_ENABLE */


/* Variables were not initialized */
uint8 rcClock_initVar = 0u;

/* Time and date variables
* Initial value are: Second = 0-59, Minute = 0-59, Hour = 0-23, DayOfWeek = 1-7,
* DayOfMonth = 1-31, DayOfYear = 1-366, Month = 1-12, Year = 1900-2200.
*/
rcClock_TIME_DATE rcClock_currentTimeDate = {0u, 0u, 0u, 1u, 1u, 1u, 1u, 1900u};

/* Alarm time and date variables
* Initial value are: Second = 0-59, Minute = 0-59, Hour = 0-23, DayOfWeek = 1-7,
* DayOfMonth = 1-31, DayOfYear = 1-366, Month = 1-12, Year = 1900-2200.
*/
rcClock_TIME_DATE rcClock_alarmCfgTimeDate = {0u, 0u, 0u, 1u, 1u, 1u, 1u, 1900u};

#if (1u == rcClock_DST_FUNC_ENABLE) /* DST enabled */

    /* Define DST format: '0' - fixed, '1' - relative */
    volatile uint8 rcClock_dstModeType = 0u;

    /* Hour 0-23, DayOfWeek 1-7, Week 1-5, DayOfMonth 1-31, Month 1-12 */
    rcClock_DSTIME rcClock_dstTimeDateStart = {0u, 1u, 1u, 1u, 1u};
    rcClock_DSTIME rcClock_dstTimeDateStop = {0u, 1u, 1u, 1u, 1u};

    /* Number of Hours to add/dec to time */
    volatile uint8 rcClock_dstOffsetMin = 0u;
    volatile uint8 rcClock_dstStartStatus = 0u;
    volatile uint8 rcClock_dstStopStatus = 0u;

#endif /* 1u == rcClock_DST_FUNC_ENABLE*/

/* Mask Registers */
volatile uint8 rcClock_alarmCfgMask = 0u;
volatile uint8 rcClock_alarmCurStatus = 0u;
volatile uint8 rcClock_intervalCfgMask = 0u;

/* Status & Control Variables */
volatile uint8 rcClock_statusDateTime = 0u;

/* Month Day Array - number of days in the months */
const uint8 CYCODE rcClock_daysInMonths[rcClock_MONTHS_IN_YEAR] = {
    rcClock_DAYS_IN_JANUARY,
    rcClock_DAYS_IN_FEBRUARY,
    rcClock_DAYS_IN_MARCH,
    rcClock_DAYS_IN_APRIL,
    rcClock_DAYS_IN_MAY,
    rcClock_DAYS_IN_JUNE,
    rcClock_DAYS_IN_JULY,
    rcClock_DAYS_IN_AUGUST,
    rcClock_DAYS_IN_SEPTEMBER,
    rcClock_DAYS_IN_OCTOBER,
    rcClock_DAYS_IN_NOVEMBER,
    rcClock_DAYS_IN_DECEMBER};


/*******************************************************************************
* Function Name:   rcClock_Start
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
*  rcClock_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time rcClock_Start() is called. This allows for
*  component initialization without re-initialization in all subsequent calls
*  to the rcClock_Start() routine.
*
*  rcClock_currentTimeDate, rcClock_dstTimeDateStart,
*  rcClock_dstTimeDateStop, rcClock_dstTimeDateStart,
*  rcClock_alarmCfgTimeDate, rcClock_statusDateTime,
*  rcClock_dstStartStatus, rcClock_dstStopStatus,
*  rcClock_alarmCurStatus: global variables are modified by the
*  functions called from rcClock_Init().
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
void rcClock_Start(void) 
{
    /* Execute once in normal flow */
    if(0u == rcClock_initVar)
    {
        rcClock_Init();
        rcClock_initVar = 1u;
    }

    /* Enable component's operation */
    rcClock_Enable();
}


/*******************************************************************************
* Function Name: rcClock_Stop
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
void rcClock_Stop(void) 
{
    uint8 interruptState;

    /* Disable the interrupt. */
    CyIntDisable(rcClock_ISR_NUMBER);

    /* Enter critical section */
    interruptState = CyEnterCriticalSection();

    /* Stop one pulse per second counter and interrupt */
    rcClock_OPPS_CFG_REG &= (uint8)(~(rcClock_OPPSIE_EN_MASK | rcClock_OPPS_EN_MASK));

    /* Exit critical section */
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name:   rcClock_EnableInt
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
void rcClock_EnableInt(void) 
{
    /* Enable the interrupt */
    CyIntEnable(rcClock_ISR_NUMBER);
}


/*******************************************************************************
* Function Name:   rcClock_DisableInt
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
void rcClock_DisableInt(void) 
{
    /* Disable the interrupt. */
    CyIntDisable(rcClock_ISR_NUMBER);
}


#if (1u == rcClock_DST_FUNC_ENABLE)
    /*******************************************************************************
    * Function Name:   rcClock_DSTDateConversion
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
    *  rcClock_dstTimeDateStart.Month,
    *  rcClock_dstTimeDateStart.DayOfWeek,
    *  rcClock_dstTimeDateStart.Week,
    *  rcClock_dstTimeDateStop.Month,
    *  rcClock_dstTimeDateStop.DayOfWeek,
    *  rcClock_dstTimeDateStop.Week,
    *  rcClock_currentTimeDate.Year: these global variables are
    *  used to correct day of week.
    *
    *  rcClock_dstTimeDateStart.DayOfMonth,
    *  rcClock_dstTimeDateStop.DayOfMonth: these global variables are
    *  modified after convertion.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    static void rcClock_DSTDateConversion(void) 
    {
        uint8 week = 1u;
        uint8 day = 1u;
        uint8 dayOfWeek;

        /* Get day of week */
        dayOfWeek = rcClock_DayOfWeek(day, rcClock_dstTimeDateStart.Month,
                                                    rcClock_currentTimeDate.Year) + 1u;

        #if (0u != rcClock_START_OF_WEEK)
        /* Normalize day of week if Start of week is not Sunday */
        if(dayOfWeek > rcClock_START_OF_WEEK)
        {
            #if (6u != rcClock_START_OF_WEEK)
                /* Start of week is not Saturday  */
                dayOfWeek -= rcClock_START_OF_WEEK;
            #else /* 6u == rcClock_START_OF_WEEK */
                /* Start of week is Saturday  */
                dayOfWeek = 1u; /* Set day of week to Monday */
            #endif /* 6u != rcClock_START_OF_WEEK */
        }
        else
        {
            #if (1u != rcClock_START_OF_WEEK)
                /* Start of week is not Monday  */
                dayOfWeek = (rcClock_DAYS_IN_WEEK - rcClock_START_OF_WEEK) - dayOfWeek;
            #else /* 1u == rcClock_START_OF_WEEK */
                /* Start of week is Monday  */
                dayOfWeek = 5u; /* Set day of week to Friday */
            #endif /* 1u != rcClock_START_OF_WEEK */
        }
        #endif /* 0u != rcClock_START_OF_WEEK */

        /* Correct if out of DST range */
        while(dayOfWeek != rcClock_dstTimeDateStart.DayOfWeek)
        {
            day++;
            dayOfWeek++;
            if(dayOfWeek > rcClock_WEEK_ELAPSED)
            {
                dayOfWeek = 1u;
                week++;
            }
        }

        while(week != rcClock_dstTimeDateStart.Week)
        {
            day += rcClock_DAYS_IN_WEEK;
            week++;
        }
        rcClock_dstTimeDateStart.DayOfMonth = day;

        /* Stop of DST time */
        week = 1u;
        day = 1u;

        dayOfWeek = rcClock_DayOfWeek(day, rcClock_dstTimeDateStop.Month,
                                                    rcClock_currentTimeDate.Year) + 1u;
        #if (0u != rcClock_START_OF_WEEK)
        /* Normalize day of week if Start of week is not Sunday */
        if(dayOfWeek > rcClock_START_OF_WEEK)
        {
            #if (6u != rcClock_START_OF_WEEK)
                /* Start of week is not Saturday  */
                dayOfWeek -= rcClock_START_OF_WEEK;
            #else /* 6u == rcClock_START_OF_WEEK */
                /* Start of week is Saturday  */
                dayOfWeek = 1u; /* Set day of week to Monday */
            #endif /* 6u != rcClock_START_OF_WEEK */
        }
        else
        {
            #if (1u != rcClock_START_OF_WEEK)
                /* Start of week is not Monday  */
                dayOfWeek = (rcClock_DAYS_IN_WEEK - rcClock_START_OF_WEEK) - dayOfWeek;
            #else /* 1u == rcClock_START_OF_WEEK */
                /* Start of week is Monday  */
                dayOfWeek = 5u; /* Set day of week to Friday */
            #endif /* 1u != rcClock_START_OF_WEEK */
        }
        #endif /* 0u != rcClock_START_OF_WEEK */

        while(dayOfWeek != rcClock_dstTimeDateStop.DayOfWeek)
        {
            day++;
            dayOfWeek++;
            if(dayOfWeek > rcClock_WEEK_ELAPSED)
            {
                dayOfWeek = 1u;
                week++;
            }
        }

        while(week != rcClock_dstTimeDateStop.Week)
        {
            day += rcClock_DAYS_IN_WEEK;
            week++;
        }

        rcClock_dstTimeDateStop.DayOfMonth = day;
    }
#endif /* 1u == rcClock_DST_FUNC_ENABLE */


/*******************************************************************************
* Function Name:   rcClock_Init
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
*  rcClock_currentTimeDate, rcClock_dstTimeDateStart,
*  rcClock_dstTimeDateStop, rcClock_dstTimeDateStart,
*  rcClock_alarmCfgTimeDate, rcClock_statusDateTime,
*  rcClock_dstStartStatus, rcClock_dstStartStatus,
*  rcClock_dstStopStatus, rcClock_alarmCurStatus:
*  global variables are used by the rcClock_SetInitValues().
*
*  rcClock_dstTimeDateStart, rcClock_currentTimeDate:
*  rcClock_statusDateTime, rcClock_dstStartStatus,
*  rcClock_dstStartStatus, rcClock_dstStopStatus,
*  rcClock_alarmCurStatus: are modified by the
*  rcClock_SetInitValues() function.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_Init(void) 
{
    /* Start calculation of required date and flags */
    rcClock_SetInitValues();

    /* Disable Interrupt. */
    CyIntDisable(rcClock_ISR_NUMBER);

    /* Set the ISR to point to the RTC_SUT_isr Interrupt. */
    (void) CyIntSetVector(rcClock_ISR_NUMBER, & rcClock_ISR);

    /* Set the priority. */
    CyIntSetPriority(rcClock_ISR_NUMBER, rcClock_ISR_PRIORITY);
}


/*******************************************************************************
* Function Name: rcClock_Enable
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
void rcClock_Enable(void) 
{
    uint8 interruptState;

    /* Enter critical section */
    interruptState = CyEnterCriticalSection();

    /* Enable one pulse per second event and interrupt */
    rcClock_OPPS_CFG_REG |= (rcClock_OPPS_EN_MASK | rcClock_OPPSIE_EN_MASK);

    /* Exit critical section */
    CyExitCriticalSection(interruptState);

    /* Enable interrupt */
    CyIntEnable(rcClock_ISR_NUMBER);
}


/*******************************************************************************
* Function Name:   rcClock_ReadTime
********************************************************************************
*
* Summary:
*  Returns a pointer to the current time and date structure.
*
* Parameters:
*  None.
*
* Return:
*  rcClock_currentTimeDate: pointer to the global structure with the
*  current date and time values.
*
* Global variables:
*  rcClock_currentTimeDate: global variable with current date and
*   time is used.
*
* Side Effects:
*  You should disable the interrupt for the RTC component before calling any
*  read API to avoid an RTC Counter increment in the middle of a time or date
*  read operation. Re-enable the interrupts after the data is read.
*
*******************************************************************************/
rcClock_TIME_DATE * rcClock_ReadTime(void) 
{
    /* Returns a pointer to the current time and date structure */
    return (&rcClock_currentTimeDate);
}


/*******************************************************************************
* Function Name:   rcClock_WriteTime
********************************************************************************
*
* Summary:
*  Writes time and date values as current time and date. Only
*  passes Milliseconds(optionally), Seconds, Minutes, Hours, Month,
*  Day Of Month and Year.
*
* Parameters:
*  timeDate: Pointer to rcClock_TIME_DATE global structure where new
*  values of time and date are stored.
*
* Return:
*  None.
*
* Global variables:
*  rcClock_currentTimeDate: global structure is modified with the new
*  values of current date and time.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteTime(const rcClock_TIME_DATE * timeDate)
     
{
    /* Disable Interrupt of RTC Component */
    rcClock_DisableInt();

    /* Write current time and date */
    rcClock_currentTimeDate.Sec = timeDate->Sec;
    rcClock_currentTimeDate.Min = timeDate->Min;
    rcClock_currentTimeDate.Hour = timeDate->Hour;
    rcClock_currentTimeDate.DayOfMonth = timeDate->DayOfMonth;
    rcClock_currentTimeDate.Month = timeDate->Month;
    rcClock_currentTimeDate.Year = timeDate->Year;

    /* Enable Interrupt of RTC Component */
    rcClock_EnableInt();
}


/*******************************************************************************
* Function Name:   rcClock_WriteSecond
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
*  rcClock_currentTimeDate.Sec: global structure's field where current
*  second's value is modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteSecond(uint8 second) 
{
    /* Save seconds to the current time and date structure */
    rcClock_currentTimeDate.Sec = second;
}


/*******************************************************************************
* Function Name:   rcClock_WriteMinute
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
*  rcClock_currentTimeDate.Min: global structure's field where
*  current minute's value is modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteMinute(uint8 minute) 
{
    /* Save minutes to the current time and date structure */
    rcClock_currentTimeDate.Min = minute;
}


/*******************************************************************************
* Function Name:   rcClock_WriteHour
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
*  rcClock_currentTimeDate.Hour: global structure's field where
*  current hour's value is modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteHour(uint8 hour) 
{
    /* Save hours to the current time and date structure */
    rcClock_currentTimeDate.Hour = hour;
}


/*******************************************************************************
* Function Name:   rcClock_WriteDayOfMonth
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
*  rcClock_currentTimeDate.DayOfMonth: global structure's field where
*  current day of month's value is modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteDayOfMonth(uint8 dayOfMonth) 
{
    /* Save day of month to the current time and date structure */
    rcClock_currentTimeDate.DayOfMonth = dayOfMonth;
}


/*******************************************************************************
* Function Name:   rcClock_WriteMonth
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
*  rcClock_currentTimeDate.Month: global structure's field where
*  current day of month's value is modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteMonth(uint8 month) 
{
    /* Save months to the current time and date structure */
    rcClock_currentTimeDate.Month = month;
}


/*******************************************************************************
* Function Name:   rcClock_WriteYear
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
*  rcClock_currentTimeDate.Year: global structure's field where
*  current year's value is modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteYear(uint16 year) 
{
    /* Save years to the current time and date structure */
    rcClock_currentTimeDate.Year = year;
}


/*******************************************************************************
* Function Name:   rcClock_WriteAlarmSecond
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
*  rcClock_currentTimeDate.Sec: this global variable is used for
*  comparison while setting and clearing seconds alarm status variable.
*
*  rcClock_alarmCfgTimeDate.Sec: this global variable is modified to
*  store of the new seconds alarm.
*
*  rcClock_alarmCurStatus: this global variable could be changed if
*  second's alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteAlarmSecond(uint8 second) 
{
    rcClock_alarmCfgTimeDate.Sec = second;

    /* Check second alarm */
    if(rcClock_alarmCfgTimeDate.Sec == rcClock_currentTimeDate.Sec)
    {
        /* Set second alarm */
        rcClock_alarmCurStatus |= rcClock_ALARM_SEC_MASK;
    }
    else /* no second alarm */
    {
        /* Clear second alarm */
        rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_SEC_MASK);
    }
}


/*******************************************************************************
* Function Name:   rcClock_WriteAlarmMinute
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
*  rcClock_currentTimeDate.Min: this global variable is used for
*  comparison while setting and clearing minutes alarm status variable.
*
*  rcClock_alarmCfgTimeDate.Min: this global variable is modified to
*  store of the new minutes alarm.
*
*  rcClock_alarmCurStatus: this global variable could be changed if
*  minute's alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteAlarmMinute(uint8 minute) 
{
    rcClock_alarmCfgTimeDate.Min = minute;

    /* Check minute alarm */
    if(rcClock_alarmCfgTimeDate.Min == rcClock_currentTimeDate.Min)
    {
        /* Set minute alarm */
        rcClock_alarmCurStatus |= rcClock_ALARM_MIN_MASK;
    }
    else /* no minute alarm */
    {
        /* Clear minute alarm */
        rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_MIN_MASK);
    }
}


/*******************************************************************************
* Function Name:   rcClock_WriteAlarmHour
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
*  rcClock_currentTimeDate.Hour: this global variable is used for
*  comparison while setting and clearing hours alarm status variable.
*
*  rcClock_alarmCfgTimeDate.Hour: this global variable is modified to
*  store of the new hours alarm.
*
*  rcClock_alarmCurStatus: this global variable could be changed if
*  hours alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteAlarmHour(uint8 hour) 
{
    rcClock_alarmCfgTimeDate.Hour = hour;

    /* Check hour alarm */
    if(rcClock_alarmCfgTimeDate.Hour == rcClock_currentTimeDate.Hour)
    {
        /* Set hour alarm */
        rcClock_alarmCurStatus |= rcClock_ALARM_HOUR_MASK;
    }
    else /* no hour alarm */
    {
        /* Clear hour alarm */
        rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_HOUR_MASK);
    }
}


/*******************************************************************************
* Function Name:   rcClock_WriteAlarmDayOfMonth
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
*  rcClock_currentTimeDate.DayOfMonth: this global variable is used for
*  comparison while setting and clearing day of month alarm status variable.
*
*  rcClock_alarmCfgTimeDate.DayOfMonth: this global variable is
*  modified to store of the new day of month alarm.
*
*  rcClock_alarmCurStatus: this global variable could be changed if
*  day of month alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteAlarmDayOfMonth(uint8 dayOfMonth) 
{
    rcClock_alarmCfgTimeDate.DayOfMonth = dayOfMonth;

    /* Check day of month alarm */
    if(rcClock_alarmCfgTimeDate.DayOfMonth == rcClock_currentTimeDate.DayOfMonth)
    {
        /* Set day of month alarm */
        rcClock_alarmCurStatus |= rcClock_ALARM_DAYOFMONTH_MASK;
    }
    else /* no day of month alarm */
    {
        /* Clear day of month alarm */
        rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_DAYOFMONTH_MASK);
    }
}


/*******************************************************************************
* Function Name:   rcClock_WriteAlarmMonth
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
*  rcClock_currentTimeDate.Month: this global variable is used for
*  comparison while setting and clearing month alarm status variable.
*
*  rcClock_alarmCfgTimeDate.Month: this global variable is modified
*  to store of the new month alarm.
*
*  rcClock_alarmCurStatus: this global variable could be changed if
*  month alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteAlarmMonth(uint8 month) 
{
    rcClock_alarmCfgTimeDate.Month = month;

    /* Check month alarm */
    if(rcClock_alarmCfgTimeDate.Month == rcClock_currentTimeDate.Month)
    {
        /* Set month alarm */
        rcClock_alarmCurStatus |= rcClock_ALARM_MONTH_MASK;
    }
    else /* no month alarm */
    {
        /* Clear month alarm */
        rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_MONTH_MASK);
    }
}


/*******************************************************************************
* Function Name:   rcClock_WriteAlarmYear
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
*  rcClock_currentTimeDate.Year: this global variable is used for
*  comparison while setting and clearing year alarm status variable.
*
*  rcClock_alarmCfgTimeDate.Year: this global variable is modified
*  to store of the new year alarm.
*
*  rcClock_alarmCurStatus: this global variable could be changed if
*  year alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteAlarmYear(uint16 year) 
{
   rcClock_alarmCfgTimeDate.Year = year;

    /* Check year alarm */
    if(rcClock_alarmCfgTimeDate.Year == rcClock_currentTimeDate.Year)
    {
        /* Set year alarm */
        rcClock_alarmCurStatus |= rcClock_ALARM_YEAR_MASK;
    }
    else /* no year alarm */
    {
        /* Set year alarm */
        rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_YEAR_MASK);
    }
}


/*******************************************************************************
* Function Name:   rcClock_WriteAlarmDayOfWeek
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
*  rcClock_currentTimeDate.DayOfWeek: this global variable is used for
*  comparison while setting and clearing day of week alarm status variable.
*
*  rcClock_alarmCfgTimeDate.DayOfWeek: this global variable is modified
*  to store of the new day of week alarm.
*
*  rcClock_alarmCurStatus: this global variable could be changed if
*  day of week alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteAlarmDayOfWeek(uint8 dayOfWeek) 
{
    rcClock_alarmCfgTimeDate.DayOfWeek = dayOfWeek;

    /* Check day of week alarm */
    if(rcClock_alarmCfgTimeDate.DayOfWeek == rcClock_currentTimeDate.DayOfWeek)
    {
        /* Set day of week alarm */
        rcClock_alarmCurStatus |= rcClock_ALARM_DAYOFWEEK_MASK;
    }
    else /* no day of week alarm */
    {
        /* Set day of week alarm */
        rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_DAYOFWEEK_MASK);
    }
}


/*******************************************************************************
* Function Name:   rcClock_WriteAlarmDayOfYear
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
*  rcClock_currentTimeDate.DayOfYear: this global variable is used for
*  comparison while setting and clearing day of year alarm status variable.
*
*  rcClock_alarmCfgTimeDate.DayOfYear: this global variable is modified
*  to store of the new day of year alarm.
*
*  rcClock_alarmCurStatus: this global variable could be changed if
*  day of year alarm will be raised.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteAlarmDayOfYear(uint16 dayOfYear) 
{
  rcClock_alarmCfgTimeDate.DayOfYear = dayOfYear;

    /* Check day of year alarm */
    if(rcClock_alarmCfgTimeDate.DayOfYear == rcClock_currentTimeDate.DayOfYear)
    {
        /* Set day of year alarm */
        rcClock_alarmCurStatus |= rcClock_ALARM_DAYOFYEAR_MASK;
    }
    else /* no day of year alarm */
    {
        /* Set day of year alarm */
        rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_DAYOFYEAR_MASK);
    }
}


/*******************************************************************************
* Function Name:   rcClock_ReadSecond
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
*  rcClock_currentTimeDate.Sec: the current second's value is used.
*
*******************************************************************************/
uint8 rcClock_ReadSecond(void) 
{
    /* Return current second */
    return (rcClock_currentTimeDate.Sec);
}


/*******************************************************************************
* Function Name:   rcClock_ReadMinute
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
*  rcClock_currentTimeDate.Min: the current field's value is used.
*
*******************************************************************************/
uint8 rcClock_ReadMinute(void) 
{
    /* Return current minute */
    return (rcClock_currentTimeDate.Min);
}


/*******************************************************************************
* Function Name:   rcClock_ReadHour
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
*  rcClock_currentTimeDate.Hour: the current field's value is used.
*
*******************************************************************************/
uint8 rcClock_ReadHour(void) 
{
    /* Return current hour */
    return (rcClock_currentTimeDate.Hour);
}


/*******************************************************************************
* Function Name:   rcClock_ReadDayOfMonth
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
*  rcClock_currentTimeDate.DayOfMonth: the current day of month's
*  value is used.
*
*******************************************************************************/
uint8 rcClock_ReadDayOfMonth(void) 
{
    /* Return current day of the month */
    return (rcClock_currentTimeDate.DayOfMonth);
}


/*******************************************************************************
* Function Name:   rcClock_ReadMonth
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
*  rcClock_currentTimeDate.Month: the current month's value is used.
*
*******************************************************************************/
uint8 rcClock_ReadMonth(void) 
{
    /* Return current month */
    return (rcClock_currentTimeDate.Month);
}


/*******************************************************************************
* Function Name:   rcClock_ReadYear
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
*  rcClock_currentTimeDate.Year: the current year's value is used.
*
*******************************************************************************/
uint16 rcClock_ReadYear(void) 
{
    /* Return current year */
    return (rcClock_currentTimeDate.Year);
}


/*******************************************************************************
* Function Name:   rcClock_ReadAlarmSecond
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
*  rcClock_alarmCfgTimeDate.Sec: the current second alarm value is
*  used.
*
********************************************************************************/
uint8 rcClock_ReadAlarmSecond(void) 
{
    /* Return current alarm second */
    return (rcClock_alarmCfgTimeDate.Sec);
}


/*******************************************************************************
* Function Name:   rcClock_ReadAlarmMinute
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
*  rcClock_alarmCfgTimeDate.Min: the current minute alarm is used.
*
*******************************************************************************/
uint8 rcClock_ReadAlarmMinute(void) 
{
    /* Return current alarm minute */
    return (rcClock_alarmCfgTimeDate.Min);
}


/*******************************************************************************
* Function Name:   rcClock_ReadAlarmHour
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
*  rcClock_alarmCfgTimeDate.Hour: the current hour alarm value is used.
*
*******************************************************************************/
uint8 rcClock_ReadAlarmHour(void) 
{
    /* Return current alarm hour */
    return (rcClock_alarmCfgTimeDate.Hour);
}


/*******************************************************************************
* Function Name:   rcClock_ReadAlarmDayOfMonth
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
*  rcClock_alarmCfgTimeDate.DayOfMonth: the current day of month alarm
*  value is used.
*
*******************************************************************************/
uint8 rcClock_ReadAlarmDayOfMonth(void) 
{
    /* Return current alarm day of month */
    return (rcClock_alarmCfgTimeDate.DayOfMonth);
}


/*******************************************************************************
* Function Name:   rcClock_ReadAlarmMonth
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
*  rcClock_alarmCfgTimeDate.Month: the current month alarm value is
*  used.
*
*******************************************************************************/
uint8 rcClock_ReadAlarmMonth(void) 
{
    /* Return current alarm month */
    return (rcClock_alarmCfgTimeDate.Month);
}


/*******************************************************************************
* Function Name:   rcClock_ReadAlarmYear
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
*  rcClock_alarmCfgTimeDate.Year: the current year alarm value is used.
*
*******************************************************************************/
uint16 rcClock_ReadAlarmYear(void) 
{
    /* Return current alarm year */
    return (rcClock_alarmCfgTimeDate.Year);
}


/*******************************************************************************
* Function Name:   rcClock_ReadAlarmDayOfWeek
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
*  rcClock_alarmCfgTimeDate.DayOfWeek: the current day of week alarm
*  value is used.
*
*******************************************************************************/
uint8 rcClock_ReadAlarmDayOfWeek(void) 
{
    /* Return current alarm day of the week */
    return (rcClock_alarmCfgTimeDate.DayOfWeek);
}


/*******************************************************************************
* Function Name:   rcClock_ReadAlarmDayOfYear
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
*  rcClock_alarmCfgTimeDate.DayOfYear: the current day of year alarm
*  value is used.
*
*******************************************************************************/
uint16 rcClock_ReadAlarmDayOfYear(void) 
{
    /* Return current alarm day of the year */
    return  (rcClock_alarmCfgTimeDate.DayOfYear);
}


/*******************************************************************************
* Function Name:   rcClock_WriteAlarmMask
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
*  rcClock_alarmCfgMask: global variable which stores masks for
*  time/date alarm configuration is modified.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteAlarmMask(uint8 mask) 
{
    rcClock_alarmCfgMask = mask;
}


/*******************************************************************************
* Function Name:   rcClock_WriteIntervalMask
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
*  rcClock_intervalCfgMask: this global variable is modified - the new
*  value of interval mask is stored here.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void rcClock_WriteIntervalMask(uint8 mask) 
{
    rcClock_intervalCfgMask = mask;
}


/*******************************************************************************
* Function Name:   rcClock_ReadStatus
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
*  rcClock_statusDateTime: global variable is modified - active alarm
*  status bit is cleared.
*
* Reentrant:
*  No.
*
* Side Effects:
*  Alarm active(AA) flag clear after read.
*
*******************************************************************************/
uint8 rcClock_ReadStatus(void) 
{
    uint8 status;

    /* Save status */
    status = (uint8)rcClock_statusDateTime;

    /* Clean AA flag after read of Status Register */
    rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_AA);

    return (status);
}


/*******************************************************************************
* Function Name:   rcClock_DayOfWeek
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
static uint8 rcClock_DayOfWeek(uint8 dayOfMonth, uint8 month, uint16 year)

{
    /* Calculated sequence ((31 * month) / 12) mod 7 from the Zeller's congruence */
    static const uint8 CYCODE rcClock_monthTemplate[rcClock_MONTHS_IN_YEAR] =
                                                            {0u, 3u, 2u, 5u, 0u, 3u, 5u, 1u, 4u, 6u, 2u, 4u};

    /* It is simpler to handle the modified year, which is year - 1 during
    * January and February
    */
    if(month < rcClock_MARCH)
    {
        year = year - 1u;
    }

    /* For Gregorian calendar: d = (day + y + y/4 - y/100 + y/400 + (31*m)/12) mod 7 */
    return ((uint8)(((year + (((year/4u) - (year/100u)) + (year/400u))) +
    (((uint16)rcClock_monthTemplate[month - 1u]) + ((uint16) dayOfMonth))) % rcClock_DAYS_IN_WEEK));
}


/*******************************************************************************
* Function Name:   rcClock_SetInitValues
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
*  rcClock_currentTimeDate, rcClock_dstTimeDateStart,
*  rcClock_dstTimeDateStop, rcClock_dstTimeDateStart,
*  rcClock_alarmCfgTimeDate, rcClock_statusDateTime,
*  rcClock_dstStartStatus, rcClock_dstStartStatus,
*  rcClock_dstStopStatus, rcClock_alarmCurStatus:
*  global variables are used while the initial calculation.
*
* rcClock_dstTimeDateStart, rcClock_currentTimeDate,
*  rcClock_statusDateTime, rcClock_dstStartStatus,
*  rcClock_dstStartStatus, rcClock_dstStopStatus,
*  rcClock_alarmCurStatus: global variables are modified with the
*  initial calculated data.
*
* Reentrant:
*  No.
*
*******************************************************************************/
static void rcClock_SetInitValues(void) 
{
    uint8 i;
    uint8 rcClock_alarmCfgMaskTemp;

    /* Clears day of month counter */
    rcClock_currentTimeDate.DayOfYear = 0u;

    /* Increments day of year value with day in current month */
    rcClock_currentTimeDate.DayOfYear += rcClock_currentTimeDate.DayOfMonth;

    /* Check leap year */
    if(1u == rcClock_LEAP_YEAR(rcClock_currentTimeDate.Year))
    {
        /* Set LP Year flag */
        rcClock_statusDateTime |= rcClock_STATUS_LY;
    }   /* leap year flag was set */
    else
    {
        /* Clear LP Year flag */
        rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_LY);
    }   /* leap year flag was cleared */

    /* Day of Year */
    for(i = 0u; i < (rcClock_currentTimeDate.Month - 1u); i++)
    {
        /* Increment on days in passed months */
        rcClock_currentTimeDate.DayOfYear += rcClock_daysInMonths[i];
    }   /* day of year is calculated */

    /* Leap year check */
    if(0u != rcClock_IS_BIT_SET(rcClock_statusDateTime, rcClock_STATUS_LY))
    {
        /* Leap day check */
        if(rcClock_currentTimeDate.Month > rcClock_FEBRUARY)
        {
            /* Add leap day */
            rcClock_currentTimeDate.DayOfYear++;
        }   /* Do nothing for non leap day */
    }   /* Do nothing for not leap year */

    /* DayOfWeek */
    rcClock_currentTimeDate.DayOfWeek = rcClock_DayOfWeek(
                                                                        rcClock_currentTimeDate.DayOfMonth,
                                                                        rcClock_currentTimeDate.Month,
                                                                        rcClock_currentTimeDate.Year) + 1u;

    if(rcClock_currentTimeDate.DayOfWeek > rcClock_START_OF_WEEK)
    {
        rcClock_currentTimeDate.DayOfWeek -= rcClock_START_OF_WEEK;
    }
    else
    {
        rcClock_currentTimeDate.DayOfWeek = rcClock_DAYS_IN_WEEK -
                                        (rcClock_START_OF_WEEK - rcClock_currentTimeDate.DayOfWeek);
    }

    #if (1u == rcClock_DST_FUNC_ENABLE)

        /* If DST values is given in a relative manner, converts to the absolute values */
        if(0u != rcClock_IS_BIT_SET(rcClock_dstModeType, rcClock_DST_RELDATE))
        {
            rcClock_DSTDateConversion();
        }

        /* Sets DST status respect to the DST start date and time */
        if(rcClock_currentTimeDate.Month > rcClock_dstTimeDateStart.Month)
        {
            rcClock_statusDateTime |= rcClock_STATUS_DST;
        }
        else if(rcClock_currentTimeDate.Month == rcClock_dstTimeDateStart.Month)
        {
            if(rcClock_currentTimeDate.DayOfMonth > rcClock_dstTimeDateStart.DayOfMonth)
            {
                rcClock_statusDateTime |= rcClock_STATUS_DST;
            }
            else if(rcClock_currentTimeDate.DayOfMonth == rcClock_dstTimeDateStart.DayOfMonth)
            {
                if(rcClock_currentTimeDate.Hour > rcClock_dstTimeDateStart.Hour)
                {
                    rcClock_statusDateTime |= rcClock_STATUS_DST;
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
        if(rcClock_currentTimeDate.Month > rcClock_dstTimeDateStop.Month)
        {
            rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_DST);
        }
        else if(rcClock_currentTimeDate.Month == rcClock_dstTimeDateStop.Month)
        {
            if(rcClock_currentTimeDate.DayOfMonth > rcClock_dstTimeDateStop.DayOfMonth)
            {
                rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_DST);
            }
            else if(rcClock_currentTimeDate.DayOfMonth == rcClock_dstTimeDateStop.DayOfMonth)
            {
                if(rcClock_currentTimeDate.Hour > rcClock_dstTimeDateStop.Hour)
                {
                    rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_DST);
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
        rcClock_dstStartStatus = 0u;
        rcClock_dstStopStatus = 0u;

        /* Sets DST stop status month flag if DST stop month is equal to the
        * current month, otherwise clears that flag.
        */
        if(rcClock_dstTimeDateStop.Month == rcClock_currentTimeDate.Month)
        {
            rcClock_dstStopStatus |= rcClock_DST_MONTH;
        }
        else
        {
            rcClock_dstStopStatus &= (uint8)(~rcClock_DST_MONTH);
        }

        /* Sets DST start status month flag if DST start month is equal to the
        * current month, otherwise clears that flag.
        */
        if(rcClock_dstTimeDateStart.Month == rcClock_currentTimeDate.Month)
        {
            rcClock_dstStartStatus |= rcClock_DST_MONTH;
        }
        else
        {
            rcClock_dstStartStatus &= (uint8)(~rcClock_DST_MONTH);
        }

        /* Sets DST stop status day of month flag if DST stop day of month is
        * equal to the current day of month, otherwise clears that flag.
        */
        if(rcClock_dstTimeDateStop.DayOfMonth == rcClock_currentTimeDate.DayOfMonth)
        {
            rcClock_dstStopStatus |= rcClock_DST_DAYOFMONTH;
        }
        else
        {
            rcClock_dstStopStatus &= (uint8)(~rcClock_DST_DAYOFMONTH);
        }

        /* Sets DST start status day of month flag if DST start day of month is
        * equal to the current day of month, otherwise clears that flag.
        */
        if(rcClock_dstTimeDateStart.DayOfMonth == rcClock_currentTimeDate.DayOfMonth)
        {
            rcClock_dstStartStatus |= rcClock_DST_DAYOFMONTH;
        }
        else
        {
            rcClock_dstStartStatus &= (uint8)(~rcClock_DST_DAYOFMONTH);
        }

        /* Sets DST stop status hour flag if DST stop hour is equal to the
        * current hour, otherwise clears that flag.
        */
        if(rcClock_dstTimeDateStop.Hour == rcClock_currentTimeDate.Hour)
        {
            rcClock_dstStopStatus |= rcClock_DST_HOUR;
        }
        else
        {
            rcClock_dstStopStatus &= (uint8)(~rcClock_DST_HOUR);
        }

        /* Sets DST start status hour flag if DST start hour is equal to the
        * current hour, otherwise clears that flag.
        */
        if(rcClock_dstTimeDateStart.Hour == rcClock_currentTimeDate.Hour)
        {
            rcClock_dstStartStatus |= rcClock_DST_HOUR;
        }
        else
        {
            rcClock_dstStartStatus &= (uint8)(~rcClock_DST_HOUR);
        }

        /* DST Enable ? */
        if(0u != rcClock_IS_BIT_SET(rcClock_dstModeType, rcClock_DST_ENABLE))
        {
            if(0u != rcClock_IS_BIT_SET(rcClock_statusDateTime, rcClock_STATUS_DST))
            {
                if(0u != rcClock_IS_BIT_SET(rcClock_dstStartStatus,
                        (rcClock_DST_HOUR | rcClock_DST_DAYOFMONTH | rcClock_DST_MONTH)))
                {
                    /* Subtract current minutes value with minutes value, what
                    *  are out of full hour in DST offset.
                    */
                    rcClock_currentTimeDate.Min -= rcClock_dstOffsetMin %
                                                            (rcClock_HOUR_ELAPSED + 1u);

                    /* If current minutes value is greater than number of
                    * minutes in hour - could be only if hour's value is negative
                    */
                    if(rcClock_currentTimeDate.Min > rcClock_HOUR_ELAPSED)
                    {
                        /* Adjust current minutes value. Convert to the positive. */
                        rcClock_currentTimeDate.Min = rcClock_HOUR_ELAPSED -
                                                               ((uint8)(~rcClock_currentTimeDate.Min));

                        /* Decrement current hours value. */
                        rcClock_currentTimeDate.Hour--;
                    }

                    /* Subtract current hours value with hours value, what
                    *  are full part of hours in DST offset.
                    */
                    rcClock_currentTimeDate.Hour -= rcClock_dstOffsetMin /
                                                             (rcClock_HOUR_ELAPSED + 1u);

                    /* Check if current hour's value is negative */
                    if(rcClock_currentTimeDate.Hour > rcClock_DAY_ELAPSED)
                    {
                        /* Adjust hour */
                        rcClock_currentTimeDate.Hour = rcClock_DAY_ELAPSED -
                                                                ((uint8)(~rcClock_currentTimeDate.Hour));

                        /* Decrement day of month, year and week */
                        rcClock_currentTimeDate.DayOfMonth--;
                        rcClock_currentTimeDate.DayOfYear--;
                        rcClock_currentTimeDate.DayOfWeek--;

                        if(0u == rcClock_currentTimeDate.DayOfWeek)
                        {
                            rcClock_currentTimeDate.DayOfWeek = rcClock_DAYS_IN_WEEK;
                        }

                        if(0u == rcClock_currentTimeDate.DayOfMonth)
                        {
                            /* Decrement months value */
                            rcClock_currentTimeDate.Month--;

                            /* The current month is month before 1st one. */
                            if(0u == rcClock_currentTimeDate.Month)
                            {
                                /* December is the month before January */
                                rcClock_currentTimeDate.Month = rcClock_DECEMBER;
                                rcClock_currentTimeDate.DayOfMonth =
                                            rcClock_daysInMonths[rcClock_currentTimeDate.Month - 1u];

                                /* Decrement years value */
                                rcClock_currentTimeDate.Year--;
                                if(1u == rcClock_LEAP_YEAR(rcClock_currentTimeDate.Year))
                                {
                                    /* Set leap year status flag */
                                    rcClock_statusDateTime |= rcClock_STATUS_LY;
                                    rcClock_currentTimeDate.DayOfYear = rcClock_DAYS_IN_LEAP_YEAR;
                                }
                                else
                                {
                                    /* Clear leap year status flag */
                                    rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_LY);
                                    rcClock_currentTimeDate.DayOfYear = rcClock_DAYS_IN_YEAR;
                                }
                            }   /* 0u == rcClock_currentTimeDate.Month */
                            else
                            {
                                rcClock_currentTimeDate.DayOfMonth =
                                            rcClock_daysInMonths[rcClock_currentTimeDate.Month - 1u];
                            }   /* 0u != End of rcClock_currentTimeDate.Month */
                        }   /* 0u == End of rcClock_currentTimeDate.DayOfMonth */
                    }   /* End of rcClock_currentTimeDate.Hour > rcClock_DAY_ELAPSED */

                    /* Clear DST status flag */
                    rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_DST);
                    /* Clear DST stop status */
                    rcClock_dstStopStatus = 0u;
                }
            }
            else    /* Current time and date DO NOT match DST time and date */
            {
                if(0u != rcClock_IS_BIT_SET(rcClock_dstStartStatus, rcClock_DST_HOUR |
                                                     rcClock_DST_DAYOFMONTH | rcClock_DST_MONTH))
                {
                    /* Add Hour and Min */
                    rcClock_currentTimeDate.Min +=
                                                rcClock_dstOffsetMin % (rcClock_HOUR_ELAPSED + 1u);

                    if(rcClock_currentTimeDate.Min > rcClock_HOUR_ELAPSED)
                    {
                        /* Adjust Min */
                        rcClock_currentTimeDate.Min -= (rcClock_HOUR_ELAPSED + 1u);
                        rcClock_currentTimeDate.Hour++;
                    }

                    rcClock_currentTimeDate.Hour +=
                                                rcClock_dstOffsetMin / (rcClock_HOUR_ELAPSED + 1u);
                    if(rcClock_currentTimeDate.Hour > rcClock_DAY_ELAPSED)
                    {
                        /* Adjust hour, add day */
                        rcClock_currentTimeDate.Hour -= (rcClock_DAY_ELAPSED + 1u);
                        rcClock_currentTimeDate.DayOfMonth++;
                        rcClock_currentTimeDate.DayOfYear++;
                        rcClock_currentTimeDate.DayOfWeek++;

                        if(rcClock_currentTimeDate.DayOfWeek > rcClock_WEEK_ELAPSED)
                        {
                            rcClock_currentTimeDate.DayOfWeek = 1u;
                        }

                        if(rcClock_currentTimeDate.DayOfMonth >
                                            rcClock_daysInMonths[rcClock_currentTimeDate.Month - 1u])
                        {
                            rcClock_currentTimeDate.Month++;
                            rcClock_currentTimeDate.DayOfMonth = 1u;

                            /* Has new year come? */
                            if(rcClock_currentTimeDate.Month > rcClock_YEAR_ELAPSED)
                            {
                                /* Set first month of the year */
                                rcClock_currentTimeDate.Month = rcClock_JANUARY;

                                /* Increment year */
                                rcClock_currentTimeDate.Year++;

                                /* Update leap year status */
                                if(1u == rcClock_LEAP_YEAR(rcClock_currentTimeDate.Year))
                                {
                                    /* LP - true, else - false */
                                    rcClock_statusDateTime |= rcClock_STATUS_LY;
                                }
                                else
                                {
                                    rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_LY);
                                }

                                /* Set day of year to the first one */
                                rcClock_currentTimeDate.DayOfYear = 1u;
                            }
                        }
                    }
                    rcClock_statusDateTime |= rcClock_STATUS_DST;
                    rcClock_dstStartStatus = 0u;
                }
            }
        }
    #endif /* 1u == rcClock_DST_FUNC_ENABLE */

    /* Set AM/PM flag */
    if(rcClock_currentTimeDate.Hour < rcClock_HALF_OF_DAY_ELAPSED)
    {
        /* AM Hour 00:00-11:59, flag zero */
        rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_AM_PM);
    }
    else
    {
        /* PM Hour 12:00 - 23:59, flag set */
        rcClock_statusDateTime |= rcClock_STATUS_AM_PM;
    }

    /* Alarm calculation */

    /* Alarm SEC */
    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask, rcClock_ALARM_SEC_MASK))
    {
        if(rcClock_alarmCfgTimeDate.Sec == rcClock_currentTimeDate.Sec)
        {
            /* Set second alarm */
            rcClock_alarmCurStatus |= rcClock_ALARM_SEC_MASK;
        }
        else
        {
            /* Clear second alarm */
            rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_SEC_MASK);
        }
    }

    /* Alarm MIN */
    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask, rcClock_ALARM_MIN_MASK))
    {
        if(rcClock_alarmCfgTimeDate.Min == rcClock_currentTimeDate.Min)
        {
            /* Set minute alarm */
            rcClock_alarmCurStatus |= rcClock_ALARM_MIN_MASK;
        }
        else
        {
            /* Clear minute alarm */
            rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_MIN_MASK);
        }
    }

    /* Alarm HOUR */
    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask, rcClock_ALARM_HOUR_MASK))
    {
        if(rcClock_alarmCfgTimeDate.Hour == rcClock_currentTimeDate.Hour)
        {
            /* Set hour alarm */
            rcClock_alarmCurStatus |= rcClock_ALARM_HOUR_MASK;
        }
        else
        {
            /* Clear hour alarm */
            rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_HOUR_MASK);
        }
    }

    /* Alarm DAYOFWEEK */
    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask, rcClock_ALARM_DAYOFWEEK_MASK))
    {
        if(rcClock_alarmCfgTimeDate.DayOfWeek == rcClock_currentTimeDate.DayOfWeek)
        {
            /* Set day of week alarm */
            rcClock_alarmCurStatus |= rcClock_ALARM_DAYOFWEEK_MASK;
        }
        else
        {
            /* Clear day of week alarm */
            rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_DAYOFWEEK_MASK);
        }
    }

    /* Alarm DAYOFYEAR */
    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask, rcClock_ALARM_DAYOFYEAR_MASK))
    {
        if(rcClock_alarmCfgTimeDate.DayOfYear == rcClock_currentTimeDate.DayOfYear)
        {
            /* Set day of year alarm */
            rcClock_alarmCurStatus |= rcClock_ALARM_DAYOFYEAR_MASK;
        }
        else
        {
            /* Clear day of year alarm */
            rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_DAYOFYEAR_MASK);
        }
    }

    /* Alarm DAYOFMONTH */
    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask, rcClock_ALARM_DAYOFMONTH_MASK))
    {
        if(rcClock_alarmCfgTimeDate.DayOfMonth == rcClock_currentTimeDate.DayOfMonth)
        {
            /* Set day of month alarm */
            rcClock_alarmCurStatus |= rcClock_ALARM_DAYOFMONTH_MASK;
        }
           else
        {
            /* Clear day of month alarm */
            rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_DAYOFMONTH_MASK);
        }
    }

    /* Alarm MONTH */
    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask, rcClock_ALARM_MONTH_MASK))
    {
        if(rcClock_alarmCfgTimeDate.Month == rcClock_currentTimeDate.Month)
        {
            /* Set month alarm */
            rcClock_alarmCurStatus |= rcClock_ALARM_MONTH_MASK;
        }
        else
        {
            /* Clear month alarm */
            rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_MONTH_MASK);
        }
    }

    /* Alarm YEAR */
    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask, rcClock_ALARM_YEAR_MASK))
    {
        if(rcClock_alarmCfgTimeDate.Year == rcClock_currentTimeDate.Year)
        {
            /* Set year alarm */
            rcClock_alarmCurStatus |= rcClock_ALARM_YEAR_MASK;
        }
        else
        {
            /* Clear year alarm */
            rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_YEAR_MASK);
        }
    }

    rcClock_alarmCfgMaskTemp = rcClock_alarmCfgMask;
    /* Set Alarm flag event */
    rcClock_SET_ALARM(rcClock_alarmCfgMaskTemp,
                               rcClock_alarmCurStatus,
                               rcClock_statusDateTime);
}


#if (1u == rcClock_DST_FUNC_ENABLE)
    /*******************************************************************************
    * Function Name:   rcClock_WriteDSTMode
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
    *  rcClock_dstModeType: global variable is modified with the new
    *  DST mode type: relative or fixed.
    *
    *  rcClock_dstTimeDateStart.Month,
    *  rcClock_dstTimeDateStart.DayOfWeek,
    *  rcClock_dstTimeDateStart.Week:
    *  rcClock_dstTimeDateStop.Month,
    *  rcClock_dstTimeDateStop.DayOfWeek,
    *  rcClock_dstTimeDateStop.Week,
    *  rcClock_currentTimeDate.Year: for the day of week correction,
    *   they are used by rcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rcClock_dstTimeDateStart.DayOfMonth,
    *  rcClock_dstTimeDateStop.DayOfMonth: updated after convertion by
    *  the rcClock_DSTDateConversion() function if DST mode is
    *  configured to be relative.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rcClock_WriteDSTMode(uint8 mode) 
    {
        /* Set DST mode */
        rcClock_dstModeType = mode;

        if(0u != rcClock_IS_BIT_SET(mode, rcClock_DST_RELDATE))
        {
            /* Convert DST date */
            rcClock_DSTDateConversion();
        }
    }


    /*******************************************************************************
    * Function Name:   rcClock_WriteDSTStartHour
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
    *  rcClock_dstTimeDateStart.Hour: global variable is modified with
    *  the new value.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rcClock_WriteDSTStartHour(uint8 hour) 
    {
        /* Set DST Start Hour */
        rcClock_dstTimeDateStart.Hour = hour;
    }


    /*******************************************************************************
    * Function Name:   rcClock_WriteDSTStartOfMonth
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
    *  rcClock_dstTimeDateStart.DayOfMonth: global variable is modified
    *  with the new value.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rcClock_WriteDSTStartDayOfMonth(uint8 dayOfMonth)
         
    {
        /* Set DST Start day of month */
        rcClock_dstTimeDateStart.DayOfMonth = dayOfMonth;
    }


    /*******************************************************************************
    * Function Name:   rcClock_WriteDSTStartMonth
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
    *  rcClock_dstTimeDateStart.Month: global variable is modified
    *  with the new value.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rcClock_WriteDSTStartMonth(uint8 month) 
    {
        /* Set DST Start month */
        rcClock_dstTimeDateStart.Month = month;
    }


    /*******************************************************************************
    * Function Name:   rcClock_WriteDSTStartDayOfWeek
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
    *  rcClock_dstModeType: global variable, where DST mode type:
    *  relative or fixed is stored.
    *
    *  rcClock_dstTimeDateStart.Month,
    *  rcClock_dstTimeDateStart.DayOfWeek,
    *  rcClock_dstTimeDateStart.Week,
    *  rcClock_dstTimeDateStop.Month,
    *  rcClock_dstTimeDateStop.DayOfWeek,
    *  rcClock_dstTimeDateStop.Week: for the day of week correction,
    *   they are used by rcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rcClock_currentTimeDate.Year: for the day of week calculation,
    *   it is used by rcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rcClock_dstTimeDateStart.DayOfWeek: global variable is modified
    *  with the new day of week value.
    *
    *  rcClock_dstTimeDateStart.DayOfMonth and
    *  rcClock_dstTimeDateStop.DayOfMonth are modified by
    *  the rcClock_DSTDateConversion() function if DST mode is
    *  configured to be relative.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rcClock_WriteDSTStartDayOfWeek(uint8 dayOfWeek)
         
    {
        /* Set DST Start day of week */
        rcClock_dstTimeDateStart.DayOfWeek = dayOfWeek;

        if(0u != rcClock_IS_BIT_SET(rcClock_dstModeType, rcClock_DST_RELDATE))
        {
            /* Convert DST date */
            rcClock_DSTDateConversion();
        }
    }


    /*******************************************************************************
    * Function Name:   rcClock_WriteDSTStartWeek
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
    *  rcClock_dstTimeDateStart.Week: global variable is modified with
    *   the new week's value of the DST start time/date.
    *
    *  rcClock_dstTimeDateStart.DayOfMonth,
    *  rcClock_dstTimeDateStop.DayOfMonth: is modified after convertion
    *  by the rcClock_DSTDateConversion() function if DST mode is
    *  configured to be relative.
    *
    *  rcClock_dstModeType: global variable is used for theDST mode
    *   type: relative or fixed store.
    *
    *  rcClock_dstTimeDateStart.Month,
    *  rcClock_dstTimeDateStart.DayOfWeek,
    *  rcClock_dstTimeDateStart.Week: for the day of week correction,
    *   they are used by rcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rcClock_dstTimeDateStop.Month,
    *  rcClock_dstTimeDateStop.DayOfWeek,
    *  rcClock_dstTimeDateStop.Week: for the day of week correction,
    *   they are used by rcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rcClock_currentTimeDate.Year: for the day of week calculation,
    *   it is used by rcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rcClock_WriteDSTStartWeek(uint8 week) 
    {
        /* Set DST Start week */
        rcClock_dstTimeDateStart.Week = week;

        if(0u != rcClock_IS_BIT_SET(rcClock_dstModeType, rcClock_DST_RELDATE))
        {
            /* Convert DST date */
            rcClock_DSTDateConversion();
        }
    }


    /*******************************************************************************
    * Function Name:   rcClock_WriteDSTStopHour
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
    void rcClock_WriteDSTStopHour(uint8 hour) 
    {
        /* Set DST Stop hour */
        rcClock_dstTimeDateStop.Hour = hour;
    }


    /*******************************************************************************
    * Function Name:   rcClock_WriteDSTStopDayOfMonth
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
    *  rcClock_dstTimeDateStop.DayOfMonth: global variable is modified
    *  where new day of month's value of the DST stop time/date.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rcClock_WriteDSTStopDayOfMonth(uint8 dayOfMonth)
         
    {
        /* Set DST Start day of month */
        rcClock_dstTimeDateStop.DayOfMonth = dayOfMonth;
    }


    /*******************************************************************************
    * Function Name:   rcClock_WriteDSTStopMonth
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
    *  rcClock_dstTimeDateStop.Month: global variable is modified with
    *   the new month of the DST stop time/date.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rcClock_WriteDSTStopMonth(uint8 month) 
    {
        /* Set DST Stop month */
        rcClock_dstTimeDateStop.Month = month;
    }


    /*******************************************************************************
    * Function Name:   rcClock_WriteDSTStopDayOfWeek
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
    *  rcClock_dstTimeDateStop.DayOfWeek: global variable is modified
    *   with the day of week of the DST stop time/date.
    *
    *  rcClock_dstModeType: global variable is used to store DST mode
    *   type: relative or fixed.
    *
    *  rcClock_dstTimeDateStart.Month,
    *  rcClock_dstTimeDateStart.DayOfWeek,
    *  rcClock_dstTimeDateStart.Week,
    *  rcClock_dstTimeDateStop.Month,
    *  rcClock_dstTimeDateStop.DayOfWeek,
    *  rcClock_dstTimeDateStop.Weekfor the day of week correction,
    *   they are used by rcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rcClock_currentTimeDate.Year: for the day of week calculation,
    *   it is used by rcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rcClock_dstTimeDateStop.DayOfWeek: global variable is modified
    *  with the new day of week's value.
    *
    *  rcClock_dstTimeDateStart.DayOfMonth and
    *  rcClock_dstTimeDateStop.DayOfMonth are modified by
    *  the rcClock_DSTDateConversion() function if DST mode is
    *  configured to be relative.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rcClock_WriteDSTStopDayOfWeek(uint8 dayOfWeek)
         
    {
        /* Set DST Stop day of week */
        rcClock_dstTimeDateStop.DayOfWeek = dayOfWeek;

        if(0u != rcClock_IS_BIT_SET(rcClock_dstModeType, rcClock_DST_RELDATE))
        {
            /* Convert DST date */
            rcClock_DSTDateConversion();
        }
    }


    /*******************************************************************************
    * Function Name:   rcClock_WriteDSTStopWeek
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
    *  rcClock_dstTimeDateStop.Week: global variable used to store the
    *  DST stop time/date is stored.
    *
    *  rcClock_dstModeType: global variable is used to store DST mode
    *   type: relative or fixed.
    *
    *  rcClock_dstTimeDateStart.Month,
    *  rcClock_dstTimeDateStart.DayOfWeek,
    *  rcClock_dstTimeDateStart.Week,
    *  rcClock_dstTimeDateStop.Month,
    *  rcClock_dstTimeDateStop.DayOfWeek,
    *  rcClock_dstTimeDateStop.Week: used for the day of week correction,
    *   they are used by rcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rcClock_currentTimeDate.Year: for the day of week calculation,
    *   it is used by rcClock_DSTDateConversion() function if DST
    *   mode is configured to be relative.
    *
    *  rcClock_dstTimeDateStop.Week: global variable is modified with
    *  the new value.
    *
    *  rcClock_dstTimeDateStart.DayOfMonth and
    *  rcClock_dstTimeDateStop.DayOfMonth are modified by
    *  the rcClock_DSTDateConversion() function if DST mode is
    *  configured to be relative.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rcClock_WriteDSTStopWeek(uint8 week) 
    {
        /* Set DST Stop week */
        rcClock_dstTimeDateStop.Week = week;

        if(0u != rcClock_IS_BIT_SET(rcClock_dstModeType, rcClock_DST_RELDATE))
        {
            /* Convert DST date */
            rcClock_DSTDateConversion();
        }
    }


    /*******************************************************************************
    * Function Name:   rcClock_WriteDSTOffset
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
    *  rcClock_dstOffsetMin: global variable is modified with the new
    *  DST offset value (in minutes).
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void rcClock_WriteDSTOffset(uint8 offset) 
    {
        /* Set DST offset */
        rcClock_dstOffsetMin = offset;
    }

#endif /* 1u == rcClock_DST_FUNC_ENABLE */


/* [] END OF FILE */
