/*******************************************************************************
* File Name: rcClock_INT.c
* Version 2.0
*
* Description:
*  This file contains the Interrupt Service Routine (ISR) for the RTC component.
*  This interrupt routine has entry pointes to overflow on time or date.
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
static void rcClock_EverySecondHandler(void);
static void rcClock_EveryMinuteHandler(void);
static void rcClock_EveryHourHandler(void);
static void rcClock_EveryDayHandler(void);
static void rcClock_EveryWeekHandler(void);
static void rcClock_EveryMonthHandler(void);
static void rcClock_EveryYearHandler(void);


/*******************************************************************************
*  Place your includes, defines and code here
*******************************************************************************/
/* `#START RTC_ISR_DEFINITION` */

/* `#END` */


/*******************************************************************************
* Function Name:   rcClock_EverySecondHandler
********************************************************************************
*
* Summary:
*  This function is called every second.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
static void rcClock_EverySecondHandler(void)
{
    /*  Place your every second handler code here. */
    /* `#START EVERY_SECOND_HANDLER_CODE` */

    /* `#END` */
    
    #ifdef rcClock_EVERY_SECOND_HANDLER_CALLBACK
        rcClock_EverySecondHandler_Callback();
    #endif /* rcClock_EVERY_SECOND_HANDLER_CALLBACK */
}


/*******************************************************************************
* Function Name:   rcClock_EveryMinuteHandler
********************************************************************************
*
* Summary:
*  This function is called every minute.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
static void rcClock_EveryMinuteHandler(void)
{
    /*  Place your every minute handler code here. */
    /* `#START EVERY_MINUTE_HANDLER_CODE` */

    /* `#END` */

    #ifdef rcClock_EVERY_MINUTE_HANDLER_CALLBACK
        rcClock_EveryMinuteHandler_Callback();
    #endif /* rcClock_EVERY_MINUTE_HANDLER_CALLBACK */    
}


/*******************************************************************************
* Function Name:   rcClock_EveryHourHandler
********************************************************************************
*
* Summary:
*  This function is called every hour.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
static void rcClock_EveryHourHandler(void)
{
    /*  Place your every hour handler code here. */
    /* `#START EVERY_HOUR_HANDLER_CODE` */

    /* `#END` */
    
    #ifdef rcClock_EVERY_HOUR_HANDLER_CALLBACK
        rcClock_EveryHourHandler_Callback();
    #endif /* rcClock_EVERY_HOUR_HANDLER_CALLBACK */
}


/*******************************************************************************
* Function Name:   rcClock_EveryDayHandler
********************************************************************************
*
* Summary:
*  This function is called every day.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
static void rcClock_EveryDayHandler(void)
{
    /*  Place your everyday handler code here. */
    /* `#START EVERY_DAY_HANDLER_CODE` */

    /* `#END` */
    
    #ifdef rcClock_EVERY_DAY_HANDLER_CALLBACK
        rcClock_EveryDayHandler_Callback();
    #endif /* rcClock_EVERY_DAY_HANDLER_CALLBACK */
}


/*******************************************************************************
* Function Name:   rcClock_EveryWeekHandler
********************************************************************************
*
* Summary:
*  This function is called every week.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
static void rcClock_EveryWeekHandler(void)
{
    /*  Place your every week handler code here. */
    /* `#START EVERY_WEEK_HANDLER_CODE` */

    /* `#END` */

    #ifdef rcClock_EVERY_WEEK_HANDLER_CALLBACK
        rcClock_EveryWeekHandler_Callback();
    #endif /* rcClock_EVERY_WEEK_HANDLER_CALLBACK */
}


/*******************************************************************************
* Function Name:   rcClock_EveryMonthHandler
********************************************************************************
*
* Summary:
*  This function is called every month.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
static void rcClock_EveryMonthHandler(void)
{
    /*  Place your every month handler code here. */
    /* `#START EVERY_MONTH_HANDLER_CODE` */

    /* `#END` */
    
    #ifdef rcClock_EVERY_MONTH_HANDLER_CALLBACK
        rcClock_EveryMonthHandler_Callback();
    #endif /* rcClock_EVERY_MONTH_HANDLER_CALLBACK */
}


/*******************************************************************************
* Function Name:   rcClock_EveryYearHandler
********************************************************************************
*
* Summary:
*  This function is called every year.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
static void rcClock_EveryYearHandler(void)
{
    /*  Place your every year handler code here. */
    /* `#START EVERY_YEAR_HANDLER_CODE` */

    /* `#END` */

    #ifdef rcClock_EVERY_YEAR_HANDLER_CALLBACK
        rcClock_EveryYearHandler_Callback();
    #endif /* rcClock_EVERY_YEAR_HANDLER_CALLBACK */    
}


/*******************************************************************************
* Function Name: rcClock_ISR
********************************************************************************
*
* Summary:
*  This ISR is executed on 1PPS (one pulse per second) event.
*  Global interrupt must be enabled to invoke this ISR.
*  This interrupt trigs every second.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
* rcClock_currentTimeDate, rcClock_dstTimeDateStart,
*  rcClock_dstTimeDateStop, rcClock_dstTimeDateStart,
*  rcClock_alarmCfgTimeDate, rcClock_statusDateTime,
*  rcClock_dstStartStatus, rcClock_dstStartStatus,
*  rcClock_dstStopStatus, rcClock_alarmCurStatus: global
*  variables are used for the time/date, DST and alarm update procedure.
*
*  rcClock_dstTimeDateStart and rcClock_currentTimeDate:
*  are modified with the updated values.
*
*  rcClock_statusDateTime, rcClock_dstStartStatus,
*  rcClock_dstStartStatus, rcClock_dstStopStatus,
*  rcClock_alarmCurStatus: global variables could be modified while
*  current time/date is updated.
*
* Side Effects:
*  Clears all interrupt status bits (react_int, limact_int, onepps_int, ctw_int,
*  and  ftw_int) in Power Manager Interrupt Status Register. If an interrupt
*  gets generated at the same time as a clear, the bit will remain set (which
*  causes another interrupt).
*
*******************************************************************************/
CY_ISR(rcClock_ISR)
{
    uint8 rcClock_tmp;

    #ifdef rcClock_ISR_ENTRY_CALLBACK
        rcClock_ISR_EntryCallback();
    #endif /* rcClock_ISR_ENTRY_CALLBACK */
    
    /* Clear OPPS interrupt status flag */
    (void) CyPmReadStatus(CY_PM_ONEPPS_INT);

    /* Increment seconds counter */
    rcClock_currentTimeDate.Sec++;

    /* Check if minute elapsed */
    if(rcClock_currentTimeDate.Sec > rcClock_MINUTE_ELAPSED)
    {
        /* Inc Min */
        rcClock_currentTimeDate.Min++;

        /* Clear Sec */
        rcClock_currentTimeDate.Sec = 0u;

        if(rcClock_currentTimeDate.Min > rcClock_HOUR_ELAPSED)
        {
            /* Inc HOUR */
            rcClock_currentTimeDate.Hour++;

            /* Clear Min */
            rcClock_currentTimeDate.Min = 0u;

            /* Day roll over */
            if(rcClock_currentTimeDate.Hour > rcClock_DAY_ELAPSED)
            {
                /* Inc DayOfMonth */
                rcClock_currentTimeDate.DayOfMonth++;

                /* Clear Hour */
                rcClock_currentTimeDate.Hour = 0u;

                /* Inc DayOfYear */
                rcClock_currentTimeDate.DayOfYear++;

                /* Inc DayOfWeek */
                rcClock_currentTimeDate.DayOfWeek++;

                /* Check DayOfWeek */
                if(rcClock_currentTimeDate.DayOfWeek > rcClock_WEEK_ELAPSED)
                {
                    /* start new week */
                    rcClock_currentTimeDate.DayOfWeek = 1u;
                }

                /* Day of month roll over.
                * Check if day of month greater than 29 in February of leap year or
                * if day of month greater than 28 NOT in February of NON leap year or
                * if day of month greater than it should be in every month in non leap year
                */
                if(((0u != (rcClock_statusDateTime & rcClock_STATUS_LY)) &&
                    (rcClock_currentTimeDate.Month == rcClock_FEBRUARY)  &&
                    (rcClock_currentTimeDate.DayOfMonth >
                             (rcClock_daysInMonths[rcClock_currentTimeDate.Month - 1u] + 1u))) ||
                   ((0u != (rcClock_statusDateTime & rcClock_STATUS_LY))  &&
                    (rcClock_currentTimeDate.Month != rcClock_FEBRUARY) &&
                    (rcClock_currentTimeDate.DayOfMonth >
                                    rcClock_daysInMonths[rcClock_currentTimeDate.Month - 1u])) ||
                   ((0u == (rcClock_statusDateTime & rcClock_STATUS_LY))  &&
                    (rcClock_currentTimeDate.DayOfMonth >
                                    rcClock_daysInMonths[rcClock_currentTimeDate.Month - 1u])))
                {
                    /* Inc Month */
                    rcClock_currentTimeDate.Month++;

                    /* Set first day of month */
                    rcClock_currentTimeDate.DayOfMonth = 1u;

                    /* Year roll over */
                    if(rcClock_currentTimeDate.Month > rcClock_YEAR_ELAPSED)
                    {
                        /* Inc Year */
                        rcClock_currentTimeDate.Year++;

                        /* Set first month of year */
                        rcClock_currentTimeDate.Month = 1u;

                        /* Set first day of year */
                        rcClock_currentTimeDate.DayOfYear = 1u;

                        /* Is this year leap */
                        if(1u == rcClock_LEAP_YEAR(rcClock_currentTimeDate.Year))
                        {
                            /* Set leap year flag */
                            rcClock_statusDateTime |= rcClock_STATUS_LY;
                        }
                        else    /* not leap year */
                        {
                            /* Clear leap year */
                            rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_LY);
                        }

                        /* Alarm YEAR */
                        if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask,
                                                             rcClock_ALARM_YEAR_MASK))
                        {
                            /* Years match */
                            if(rcClock_alarmCfgTimeDate.Year == rcClock_currentTimeDate.Year)
                            {
                                /* Rise year alarm */
                                rcClock_alarmCurStatus |= rcClock_ALARM_YEAR_MASK;
                            }
                            else    /* Years do not match */
                            {
                                /* Clear year alarm */
                                rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_YEAR_MASK);
                            }
                        } /* do not alarm year */

                        /* Set Alarm flag event */
                        rcClock_tmp = rcClock_alarmCfgMask;
                        rcClock_SET_ALARM(rcClock_tmp,
                                                   rcClock_alarmCurStatus,
                                                   rcClock_statusDateTime);

                        /* Every Year */
                        if(0u != rcClock_IS_BIT_SET(rcClock_intervalCfgMask,
                                                             rcClock_INTERVAL_YEAR_MASK))
                        {
                            rcClock_EveryYearHandler();
                        }

                    } /* Month > 12 */

                    /* Alarm MONTH */
                    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask,
                                                         rcClock_ALARM_MONTH_MASK))
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
                    }   /* Month alarm is masked */

                    #if (1u == rcClock_DST_FUNC_ENABLE)
                        if(rcClock_dstTimeDateStop.Month == rcClock_currentTimeDate.Month)
                        {
                            rcClock_dstStopStatus |= rcClock_DST_MONTH;
                        }
                        else
                        {
                            rcClock_dstStopStatus &= (uint8)(~rcClock_DST_MONTH);
                        }

                        if(rcClock_dstTimeDateStart.Month == rcClock_currentTimeDate.Month)
                        {
                            rcClock_dstStartStatus |= rcClock_DST_MONTH;
                        }
                        else
                        {
                            rcClock_dstStartStatus &= (uint8)(~rcClock_DST_MONTH);
                        }
                    #endif /* 1u == rcClock_DST_FUNC_ENABLE */

                    /* Set Alarm flag event */
                    rcClock_tmp = rcClock_alarmCfgMask;
                    rcClock_SET_ALARM(rcClock_tmp,
                                               rcClock_alarmCurStatus,
                                               rcClock_statusDateTime);

                    /* Every Month */
                    if(0u != rcClock_IS_BIT_SET(rcClock_intervalCfgMask,
                                                         rcClock_INTERVAL_MONTH_MASK))
                    {
                        rcClock_EveryMonthHandler();
                    }
                }   /* Day roll over */

                /* Alarm DAYOFWEEK */
                if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask,
                                                     rcClock_ALARM_DAYOFWEEK_MASK))
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
                }   /* Day of week alarm is masked */

                /* Alarm DAYOFYEAR */
                if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask,
                                                     rcClock_ALARM_DAYOFYEAR_MASK))
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
                }   /* Day of year alarm is masked */

                /* Alarm DAYOFMONTH */
                if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask,
                         rcClock_ALARM_DAYOFMONTH_MASK))
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
                }   /* Day of month alarm is masked */

                #if (1u == rcClock_DST_FUNC_ENABLE)
                    if(rcClock_dstTimeDateStop.DayOfMonth == rcClock_currentTimeDate.DayOfMonth)
                    {
                        rcClock_dstStopStatus |= rcClock_DST_DAYOFMONTH;
                    }
                    else
                    {
                        rcClock_dstStopStatus &= (uint8)(~rcClock_DST_DAYOFMONTH);
                    }

                    if(rcClock_dstTimeDateStart.DayOfMonth == rcClock_currentTimeDate.DayOfMonth)
                    {
                        rcClock_dstStartStatus |= rcClock_DST_DAYOFMONTH;
                    }
                    else
                    {
                        rcClock_dstStartStatus &= (uint8)(~rcClock_DST_DAYOFMONTH);
                    }
                #endif /* 1u == rcClock_DST_FUNC_ENABLE */

                /* Set Alarm flag event */
                rcClock_tmp = rcClock_alarmCfgMask;
                rcClock_SET_ALARM(rcClock_tmp,
                                           rcClock_alarmCurStatus,
                                           rcClock_statusDateTime);

                /* Every Day */
                if(0u != rcClock_IS_BIT_SET(rcClock_intervalCfgMask,
                         rcClock_INTERVAL_DAY_MASK))
                {
                    rcClock_EveryDayHandler();
                }

                if(1u == rcClock_currentTimeDate.DayOfWeek)
                {
                    /* Every Week */
                    if(0u != rcClock_IS_BIT_SET(rcClock_intervalCfgMask,
                                                         rcClock_INTERVAL_WEEK_MASK))
                    {
                       rcClock_EveryWeekHandler();
                    }
                }

            } /* End of day roll over */

            /* Status set PM/AM flag */
            if(rcClock_currentTimeDate.Hour < rcClock_HALF_OF_DAY_ELAPSED)
            {
                /* AM Hour 00:00-11:59, flag zero */
                rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_AM_PM);
            }
            else
            {
                /* PM Hour 12:00-23:59, flag set */
                rcClock_statusDateTime |= rcClock_STATUS_AM_PM;
            }

            #if (1u == rcClock_DST_FUNC_ENABLE)
                if(rcClock_dstTimeDateStop.Hour == rcClock_currentTimeDate.Hour)
                {
                    rcClock_dstStopStatus |= rcClock_DST_HOUR;
                }
                else
                {
                    rcClock_dstStopStatus &= (uint8)(~rcClock_DST_HOUR);
                }

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
                        if(0u != rcClock_IS_BIT_SET(rcClock_dstStopStatus, rcClock_DST_HOUR |
                                                       rcClock_DST_DAYOFMONTH | rcClock_DST_MONTH))
                        {
                            /* Substruct from current value of minutes, number of minutes
                            * in DST offset which is out of complete hour
                            */
                            rcClock_currentTimeDate.Min -=
                                                rcClock_dstOffsetMin % (rcClock_HOUR_ELAPSED + 1u);

                            /* Is minute value negative? */
                            if(rcClock_currentTimeDate.Min > rcClock_HOUR_ELAPSED)
                            {
                                /* Convert to the positive.
                                * HOUR_ELAPSED -     (~currentTimeDate.Min    ) ==
                                * HOUR_ELAPSED + 1 - (~currentTimeDate.Min + 1)
                                */
                                rcClock_currentTimeDate.Min = rcClock_HOUR_ELAPSED -
                                                             ((uint8)(~rcClock_currentTimeDate.Min));

                                rcClock_currentTimeDate.Hour--;
                            }

                            rcClock_currentTimeDate.Hour -= rcClock_dstOffsetMin /
                                                                     (rcClock_HOUR_ELAPSED + 1u);

                            /* Day roll over
                            * Is hour value negative? */
                            if(rcClock_currentTimeDate.Hour > rcClock_DAY_ELAPSED)
                            {
                                /* Convert to the positive.
                                * DAY_ELAPSED - (~currentTimeDate.Hour) ==
                                * DAY_ELAPSED + 1 - (~currentTimeDate.Hour + 1)
                                */
                                rcClock_currentTimeDate.Hour = rcClock_DAY_ELAPSED -
                                                              ((uint8)(~rcClock_currentTimeDate.Hour));

                                /* Status set PM/AM flag */
                                if(rcClock_currentTimeDate.Hour < rcClock_HALF_OF_DAY_ELAPSED)
                                {
                                    /* AM Hour 00:00-11:59, flag zero */
                                    rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_AM_PM);
                                }
                                else
                                {
                                    /* PM Hour 12:00-23:59, flag set */
                                    rcClock_statusDateTime |= rcClock_STATUS_AM_PM;
                                }

                                rcClock_currentTimeDate.DayOfMonth--;
                                rcClock_currentTimeDate.DayOfYear--;
                                rcClock_currentTimeDate.DayOfWeek--;

                                if(0u == rcClock_currentTimeDate.DayOfWeek)
                                {
                                    rcClock_currentTimeDate.DayOfWeek = rcClock_DAYS_IN_WEEK;
                                }

                                if(0u == rcClock_currentTimeDate.DayOfMonth)
                                {
                                    rcClock_currentTimeDate.Month--;
                                    if(0u == rcClock_currentTimeDate.Month)
                                    {
                                        rcClock_currentTimeDate.Month = rcClock_DECEMBER;

                                        rcClock_currentTimeDate.DayOfMonth =
                                            rcClock_daysInMonths[rcClock_currentTimeDate.Month - 1u];

                                        rcClock_currentTimeDate.Year--;

                                        if(1u == rcClock_LEAP_YEAR(rcClock_currentTimeDate.Year))
                                        {
                                            /* LP - true, else - false */
                                            rcClock_statusDateTime |= rcClock_STATUS_LY;
                                            rcClock_currentTimeDate.DayOfYear =
                                                                                    rcClock_DAYS_IN_LEAP_YEAR;
                                        }
                                        else
                                        {
                                            rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_LY);
                                            rcClock_currentTimeDate.DayOfYear = rcClock_DAYS_IN_YEAR;
                                        }
                                        rcClock_EveryYearHandler();
                                    }
                                    else
                                    {
                                        /* Day of month roll over.
                                        * Check if day of month February 29 of leap year
                                        */
                                        if((0u != (rcClock_statusDateTime & rcClock_STATUS_LY)) &&
                                            (rcClock_currentTimeDate.Month == rcClock_FEBRUARY))
                                        {
                                            rcClock_currentTimeDate.DayOfMonth =
                                            rcClock_daysInMonths[rcClock_currentTimeDate.Month - 1u]
                                            + 1u;
                                        }
                                        else
                                        {
                                            rcClock_currentTimeDate.DayOfMonth =
                                            rcClock_daysInMonths[rcClock_currentTimeDate.Month - 1u];
                                        }
                                    }
                                    rcClock_EveryMonthHandler();
                                }
                                rcClock_EveryDayHandler();
                            }
                            rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_DST);
                            rcClock_dstStopStatus = 0u;
                        }
                    }
                    else
                    {
                        if(0u != rcClock_IS_BIT_SET(rcClock_dstStartStatus,
                                                      (rcClock_DST_HOUR | rcClock_DST_DAYOFMONTH |
                                                       rcClock_DST_MONTH)))
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

                            rcClock_currentTimeDate.Hour += rcClock_dstOffsetMin /
                                                                     (rcClock_HOUR_ELAPSED + 1u);

                            if(rcClock_currentTimeDate.Hour > rcClock_DAY_ELAPSED)
                            {
                                /* Adjust hour, add day */
                                rcClock_currentTimeDate.Hour -= (rcClock_DAY_ELAPSED + 1u);

                                /* Status set PM/AM flag */
                                if(rcClock_currentTimeDate.Hour < rcClock_HALF_OF_DAY_ELAPSED)
                                {
                                    /* AM Hour 00:00-11:59, flag zero */
                                    rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_AM_PM);
                                }
                                else
                                {
                                    /* PM Hour 12:00-23:59, flag set */
                                    rcClock_statusDateTime |= rcClock_STATUS_AM_PM;
                                }

                                rcClock_currentTimeDate.DayOfMonth++;
                                rcClock_currentTimeDate.DayOfYear++;
                                rcClock_currentTimeDate.DayOfWeek++;

                                if(rcClock_currentTimeDate.DayOfWeek > rcClock_WEEK_ELAPSED)
                                {
                                    rcClock_currentTimeDate.DayOfWeek = 1u;
                                }

                                /* Day of month roll over.
                                * Check if day of month greater than 29 in February of leap year or
                                * if day of month greater than 28 NOT in February of NON leap year or
                                * if day of month greater than it should be in every month in non leap year
                                */
                                if(((0u != (rcClock_statusDateTime & rcClock_STATUS_LY)) &&
                                    (rcClock_currentTimeDate.Month == rcClock_FEBRUARY)  &&
                                    (rcClock_currentTimeDate.DayOfMonth >
                                  (rcClock_daysInMonths[rcClock_currentTimeDate.Month - 1u] + 1u))) ||
                                   ((0u != (rcClock_statusDateTime & rcClock_STATUS_LY)) &&
                                    (rcClock_currentTimeDate.Month != rcClock_FEBRUARY)  &&
                                    (rcClock_currentTimeDate.DayOfMonth >
                                     rcClock_daysInMonths[rcClock_currentTimeDate.Month - 1u])) ||
                                   ((0u == (rcClock_statusDateTime & rcClock_STATUS_LY)) &&
                                    (rcClock_currentTimeDate.DayOfMonth >
                                     rcClock_daysInMonths[rcClock_currentTimeDate.Month - 1u])))
                                {
                                    rcClock_currentTimeDate.Month++;
                                    rcClock_currentTimeDate.DayOfMonth = 1u;
                                    if(rcClock_currentTimeDate.Month > rcClock_YEAR_ELAPSED)
                                    {
                                        rcClock_currentTimeDate.Month = rcClock_JANUARY;
                                        rcClock_currentTimeDate.Year++;

                                        if(1u == rcClock_LEAP_YEAR(rcClock_currentTimeDate.Year))
                                        {
                                            /* LP - true, else - false */
                                            rcClock_statusDateTime |= rcClock_STATUS_LY;
                                        }
                                        else
                                        {
                                            rcClock_statusDateTime &= (uint8)(~rcClock_STATUS_LY);
                                        }
                                        rcClock_currentTimeDate.DayOfYear = 1u;

                                        rcClock_EveryYearHandler();
                                    }
                                    rcClock_EveryMonthHandler();
                                }
                                rcClock_EveryDayHandler();
                            }
                            rcClock_statusDateTime |= rcClock_STATUS_DST;
                            rcClock_dstStartStatus = 0u;

                            /* Month */
                            if(rcClock_dstTimeDateStop.Month == rcClock_currentTimeDate.Month)
                            {
                                rcClock_dstStopStatus |= rcClock_DST_MONTH;
                            }
                            else
                            {
                                rcClock_dstStopStatus &= (uint8)(~rcClock_DST_MONTH);
                            }

                            /* DayOfMonth */
                            if(rcClock_dstTimeDateStop.DayOfMonth ==
                                                                            rcClock_currentTimeDate.DayOfMonth)
                            {
                                rcClock_dstStopStatus |= rcClock_DST_DAYOFMONTH;
                            }
                            else
                            {
                                rcClock_dstStopStatus &= (uint8)(~rcClock_DST_DAYOFMONTH);
                            }
                        }
                    }

                    /* Alarm DAYOFWEEK */
                    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask,
                                                         rcClock_ALARM_DAYOFWEEK_MASK))
                    {
                        if(rcClock_alarmCfgTimeDate.DayOfWeek == rcClock_currentTimeDate.DayOfWeek)
                        {
                            rcClock_alarmCurStatus |= rcClock_ALARM_DAYOFWEEK_MASK;
                        }
                        else
                        {
                            rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_DAYOFWEEK_MASK);
                        }
                    }

                    /* Alarm DAYOFYEAR */
                    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask,
                                                         rcClock_ALARM_DAYOFYEAR_MASK))
                    {
                        if(rcClock_alarmCfgTimeDate.DayOfYear == rcClock_currentTimeDate.DayOfYear)
                        {
                            rcClock_alarmCurStatus |= rcClock_ALARM_DAYOFYEAR_MASK;
                        }
                        else
                        {
                            rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_DAYOFYEAR_MASK);
                        }
                    }

                    /* Alarm DAYOFMONTH */
                    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask,
                                                         rcClock_ALARM_DAYOFMONTH_MASK))
                    {
                        if(rcClock_alarmCfgTimeDate.DayOfMonth == rcClock_currentTimeDate.DayOfMonth)
                        {
                            rcClock_alarmCurStatus |= rcClock_ALARM_DAYOFMONTH_MASK;
                        }
                        else
                        {
                            rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_DAYOFMONTH_MASK);
                        }
                    }

                    /* Alarm MONTH */
                    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask,
                                                         rcClock_ALARM_MONTH_MASK))
                    {
                        if(rcClock_alarmCfgTimeDate.Month == rcClock_currentTimeDate.Month)
                        {
                            rcClock_alarmCurStatus |= rcClock_ALARM_MONTH_MASK;
                        }
                        else
                        {
                            rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_MONTH_MASK);
                        }
                    }

                    /* Alarm YEAR */
                    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask,
                                                         rcClock_ALARM_YEAR_MASK))
                    {
                        if(rcClock_alarmCfgTimeDate.Year == rcClock_currentTimeDate.Year)
                        {
                            rcClock_alarmCurStatus |= rcClock_ALARM_YEAR_MASK;
                        }
                        else
                        {
                            rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_YEAR_MASK);
                        }
                    }

                    /* Set Alarm flag event */
                    rcClock_tmp = rcClock_alarmCfgMask;
                    rcClock_SET_ALARM(rcClock_tmp,
                                               rcClock_alarmCurStatus,
                                               rcClock_statusDateTime);
                }
            #endif /* 1u == rcClock_DST_FUNC_ENABLE */

            /* Alarm HOUR */
            if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask, rcClock_ALARM_HOUR_MASK))
            {
                if(rcClock_alarmCfgTimeDate.Hour == rcClock_currentTimeDate.Hour)
                {
                    rcClock_alarmCurStatus |= rcClock_ALARM_HOUR_MASK;
                }
                else
                {
                    rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_HOUR_MASK);
                }
            }

            /* Set Alarm flag event */
            rcClock_tmp = rcClock_alarmCfgMask;
            rcClock_SET_ALARM(rcClock_tmp,
                                       rcClock_alarmCurStatus,
                                       rcClock_statusDateTime);

            /* Every Hour */
            if(0u != rcClock_IS_BIT_SET(rcClock_intervalCfgMask, rcClock_INTERVAL_HOUR_MASK))
            {
                rcClock_EveryHourHandler();
            }
        } /* Min > 59 = Hour */

        /* Alarm MIN */
        if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask, rcClock_ALARM_MIN_MASK))
        {
            if(rcClock_alarmCfgTimeDate.Min == rcClock_currentTimeDate.Min)
            {
                rcClock_alarmCurStatus |= rcClock_ALARM_MIN_MASK;
            }
            else
            {
                rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_MIN_MASK);
            }
        }

        /* Set Alarm flag event */
        rcClock_tmp = rcClock_alarmCfgMask;
        rcClock_SET_ALARM(rcClock_tmp,
                                   rcClock_alarmCurStatus,
                                   rcClock_statusDateTime);

        /* Every Min */
        if(0u != rcClock_IS_BIT_SET(rcClock_intervalCfgMask, rcClock_INTERVAL_MIN_MASK))
        {
            rcClock_EveryMinuteHandler();
        }
    } /* Sec */

    /* Alarm SEC */
    if(0u != rcClock_IS_BIT_SET(rcClock_alarmCfgMask, rcClock_ALARM_SEC_MASK))
    {
        if(rcClock_alarmCfgTimeDate.Sec == rcClock_currentTimeDate.Sec)
        {
            rcClock_alarmCurStatus |= rcClock_ALARM_SEC_MASK;
        }
        else
        {
            rcClock_alarmCurStatus &= (uint8)(~rcClock_ALARM_SEC_MASK);
        }
    }

    /* Set Alarm flag event */
    rcClock_tmp = rcClock_alarmCfgMask;
    rcClock_SET_ALARM(rcClock_tmp, rcClock_alarmCurStatus, rcClock_statusDateTime);

    /* Execute every second handler if needed */
    if(0u != rcClock_IS_BIT_SET(rcClock_intervalCfgMask, rcClock_INTERVAL_SEC_MASK))
    {
        rcClock_EverySecondHandler();
    }
    
    #ifdef rcClock_ISR_EXIT_CALLBACK
        rcClock_ISR_ExitCallback();
    #endif /* rcClock_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */
