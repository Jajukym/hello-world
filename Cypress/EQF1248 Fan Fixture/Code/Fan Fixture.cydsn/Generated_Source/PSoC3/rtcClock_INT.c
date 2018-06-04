/*******************************************************************************
* File Name: rtcClock_INT.c
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

#include "rtcClock.h"
#include "CyLib.h"


/* Function Prototypes */
static void rtcClock_EverySecondHandler(void);
static void rtcClock_EveryMinuteHandler(void);
static void rtcClock_EveryHourHandler(void);
static void rtcClock_EveryDayHandler(void);
static void rtcClock_EveryWeekHandler(void);
static void rtcClock_EveryMonthHandler(void);
static void rtcClock_EveryYearHandler(void);


/*******************************************************************************
*  Place your includes, defines and code here
*******************************************************************************/
/* `#START RTC_ISR_DEFINITION` */

/* `#END` */


/*******************************************************************************
* Function Name:   rtcClock_EverySecondHandler
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
static void rtcClock_EverySecondHandler(void)
{
    /*  Place your every second handler code here. */
    /* `#START EVERY_SECOND_HANDLER_CODE` */

    /* `#END` */
    
    #ifdef rtcClock_EVERY_SECOND_HANDLER_CALLBACK
        rtcClock_EverySecondHandler_Callback();
    #endif /* rtcClock_EVERY_SECOND_HANDLER_CALLBACK */
}


/*******************************************************************************
* Function Name:   rtcClock_EveryMinuteHandler
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
static void rtcClock_EveryMinuteHandler(void)
{
    /*  Place your every minute handler code here. */
    /* `#START EVERY_MINUTE_HANDLER_CODE` */

    /* `#END` */

    #ifdef rtcClock_EVERY_MINUTE_HANDLER_CALLBACK
        rtcClock_EveryMinuteHandler_Callback();
    #endif /* rtcClock_EVERY_MINUTE_HANDLER_CALLBACK */    
}


/*******************************************************************************
* Function Name:   rtcClock_EveryHourHandler
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
static void rtcClock_EveryHourHandler(void)
{
    /*  Place your every hour handler code here. */
    /* `#START EVERY_HOUR_HANDLER_CODE` */

    /* `#END` */
    
    #ifdef rtcClock_EVERY_HOUR_HANDLER_CALLBACK
        rtcClock_EveryHourHandler_Callback();
    #endif /* rtcClock_EVERY_HOUR_HANDLER_CALLBACK */
}


/*******************************************************************************
* Function Name:   rtcClock_EveryDayHandler
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
static void rtcClock_EveryDayHandler(void)
{
    /*  Place your everyday handler code here. */
    /* `#START EVERY_DAY_HANDLER_CODE` */

    /* `#END` */
    
    #ifdef rtcClock_EVERY_DAY_HANDLER_CALLBACK
        rtcClock_EveryDayHandler_Callback();
    #endif /* rtcClock_EVERY_DAY_HANDLER_CALLBACK */
}


/*******************************************************************************
* Function Name:   rtcClock_EveryWeekHandler
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
static void rtcClock_EveryWeekHandler(void)
{
    /*  Place your every week handler code here. */
    /* `#START EVERY_WEEK_HANDLER_CODE` */

    /* `#END` */

    #ifdef rtcClock_EVERY_WEEK_HANDLER_CALLBACK
        rtcClock_EveryWeekHandler_Callback();
    #endif /* rtcClock_EVERY_WEEK_HANDLER_CALLBACK */
}


/*******************************************************************************
* Function Name:   rtcClock_EveryMonthHandler
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
static void rtcClock_EveryMonthHandler(void)
{
    /*  Place your every month handler code here. */
    /* `#START EVERY_MONTH_HANDLER_CODE` */

    /* `#END` */
    
    #ifdef rtcClock_EVERY_MONTH_HANDLER_CALLBACK
        rtcClock_EveryMonthHandler_Callback();
    #endif /* rtcClock_EVERY_MONTH_HANDLER_CALLBACK */
}


/*******************************************************************************
* Function Name:   rtcClock_EveryYearHandler
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
static void rtcClock_EveryYearHandler(void)
{
    /*  Place your every year handler code here. */
    /* `#START EVERY_YEAR_HANDLER_CODE` */

    /* `#END` */

    #ifdef rtcClock_EVERY_YEAR_HANDLER_CALLBACK
        rtcClock_EveryYearHandler_Callback();
    #endif /* rtcClock_EVERY_YEAR_HANDLER_CALLBACK */    
}


/*******************************************************************************
* Function Name: rtcClock_ISR
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
* rtcClock_currentTimeDate, rtcClock_dstTimeDateStart,
*  rtcClock_dstTimeDateStop, rtcClock_dstTimeDateStart,
*  rtcClock_alarmCfgTimeDate, rtcClock_statusDateTime,
*  rtcClock_dstStartStatus, rtcClock_dstStartStatus,
*  rtcClock_dstStopStatus, rtcClock_alarmCurStatus: global
*  variables are used for the time/date, DST and alarm update procedure.
*
*  rtcClock_dstTimeDateStart and rtcClock_currentTimeDate:
*  are modified with the updated values.
*
*  rtcClock_statusDateTime, rtcClock_dstStartStatus,
*  rtcClock_dstStartStatus, rtcClock_dstStopStatus,
*  rtcClock_alarmCurStatus: global variables could be modified while
*  current time/date is updated.
*
* Side Effects:
*  Clears all interrupt status bits (react_int, limact_int, onepps_int, ctw_int,
*  and  ftw_int) in Power Manager Interrupt Status Register. If an interrupt
*  gets generated at the same time as a clear, the bit will remain set (which
*  causes another interrupt).
*
*******************************************************************************/
CY_ISR(rtcClock_ISR)
{
    uint8 rtcClock_tmp;

    #ifdef rtcClock_ISR_ENTRY_CALLBACK
        rtcClock_ISR_EntryCallback();
    #endif /* rtcClock_ISR_ENTRY_CALLBACK */
    
    /* Clear OPPS interrupt status flag */
    (void) CyPmReadStatus(CY_PM_ONEPPS_INT);

    /* Increment seconds counter */
    rtcClock_currentTimeDate.Sec++;

    /* Check if minute elapsed */
    if(rtcClock_currentTimeDate.Sec > rtcClock_MINUTE_ELAPSED)
    {
        /* Inc Min */
        rtcClock_currentTimeDate.Min++;

        /* Clear Sec */
        rtcClock_currentTimeDate.Sec = 0u;

        if(rtcClock_currentTimeDate.Min > rtcClock_HOUR_ELAPSED)
        {
            /* Inc HOUR */
            rtcClock_currentTimeDate.Hour++;

            /* Clear Min */
            rtcClock_currentTimeDate.Min = 0u;

            /* Day roll over */
            if(rtcClock_currentTimeDate.Hour > rtcClock_DAY_ELAPSED)
            {
                /* Inc DayOfMonth */
                rtcClock_currentTimeDate.DayOfMonth++;

                /* Clear Hour */
                rtcClock_currentTimeDate.Hour = 0u;

                /* Inc DayOfYear */
                rtcClock_currentTimeDate.DayOfYear++;

                /* Inc DayOfWeek */
                rtcClock_currentTimeDate.DayOfWeek++;

                /* Check DayOfWeek */
                if(rtcClock_currentTimeDate.DayOfWeek > rtcClock_WEEK_ELAPSED)
                {
                    /* start new week */
                    rtcClock_currentTimeDate.DayOfWeek = 1u;
                }

                /* Day of month roll over.
                * Check if day of month greater than 29 in February of leap year or
                * if day of month greater than 28 NOT in February of NON leap year or
                * if day of month greater than it should be in every month in non leap year
                */
                if(((0u != (rtcClock_statusDateTime & rtcClock_STATUS_LY)) &&
                    (rtcClock_currentTimeDate.Month == rtcClock_FEBRUARY)  &&
                    (rtcClock_currentTimeDate.DayOfMonth >
                             (rtcClock_daysInMonths[rtcClock_currentTimeDate.Month - 1u] + 1u))) ||
                   ((0u != (rtcClock_statusDateTime & rtcClock_STATUS_LY))  &&
                    (rtcClock_currentTimeDate.Month != rtcClock_FEBRUARY) &&
                    (rtcClock_currentTimeDate.DayOfMonth >
                                    rtcClock_daysInMonths[rtcClock_currentTimeDate.Month - 1u])) ||
                   ((0u == (rtcClock_statusDateTime & rtcClock_STATUS_LY))  &&
                    (rtcClock_currentTimeDate.DayOfMonth >
                                    rtcClock_daysInMonths[rtcClock_currentTimeDate.Month - 1u])))
                {
                    /* Inc Month */
                    rtcClock_currentTimeDate.Month++;

                    /* Set first day of month */
                    rtcClock_currentTimeDate.DayOfMonth = 1u;

                    /* Year roll over */
                    if(rtcClock_currentTimeDate.Month > rtcClock_YEAR_ELAPSED)
                    {
                        /* Inc Year */
                        rtcClock_currentTimeDate.Year++;

                        /* Set first month of year */
                        rtcClock_currentTimeDate.Month = 1u;

                        /* Set first day of year */
                        rtcClock_currentTimeDate.DayOfYear = 1u;

                        /* Is this year leap */
                        if(1u == rtcClock_LEAP_YEAR(rtcClock_currentTimeDate.Year))
                        {
                            /* Set leap year flag */
                            rtcClock_statusDateTime |= rtcClock_STATUS_LY;
                        }
                        else    /* not leap year */
                        {
                            /* Clear leap year */
                            rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_LY);
                        }

                        /* Alarm YEAR */
                        if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask,
                                                             rtcClock_ALARM_YEAR_MASK))
                        {
                            /* Years match */
                            if(rtcClock_alarmCfgTimeDate.Year == rtcClock_currentTimeDate.Year)
                            {
                                /* Rise year alarm */
                                rtcClock_alarmCurStatus |= rtcClock_ALARM_YEAR_MASK;
                            }
                            else    /* Years do not match */
                            {
                                /* Clear year alarm */
                                rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_YEAR_MASK);
                            }
                        } /* do not alarm year */

                        /* Set Alarm flag event */
                        rtcClock_tmp = rtcClock_alarmCfgMask;
                        rtcClock_SET_ALARM(rtcClock_tmp,
                                                   rtcClock_alarmCurStatus,
                                                   rtcClock_statusDateTime);

                        /* Every Year */
                        if(0u != rtcClock_IS_BIT_SET(rtcClock_intervalCfgMask,
                                                             rtcClock_INTERVAL_YEAR_MASK))
                        {
                            rtcClock_EveryYearHandler();
                        }

                    } /* Month > 12 */

                    /* Alarm MONTH */
                    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask,
                                                         rtcClock_ALARM_MONTH_MASK))
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
                    }   /* Month alarm is masked */

                    #if (1u == rtcClock_DST_FUNC_ENABLE)
                        if(rtcClock_dstTimeDateStop.Month == rtcClock_currentTimeDate.Month)
                        {
                            rtcClock_dstStopStatus |= rtcClock_DST_MONTH;
                        }
                        else
                        {
                            rtcClock_dstStopStatus &= (uint8)(~rtcClock_DST_MONTH);
                        }

                        if(rtcClock_dstTimeDateStart.Month == rtcClock_currentTimeDate.Month)
                        {
                            rtcClock_dstStartStatus |= rtcClock_DST_MONTH;
                        }
                        else
                        {
                            rtcClock_dstStartStatus &= (uint8)(~rtcClock_DST_MONTH);
                        }
                    #endif /* 1u == rtcClock_DST_FUNC_ENABLE */

                    /* Set Alarm flag event */
                    rtcClock_tmp = rtcClock_alarmCfgMask;
                    rtcClock_SET_ALARM(rtcClock_tmp,
                                               rtcClock_alarmCurStatus,
                                               rtcClock_statusDateTime);

                    /* Every Month */
                    if(0u != rtcClock_IS_BIT_SET(rtcClock_intervalCfgMask,
                                                         rtcClock_INTERVAL_MONTH_MASK))
                    {
                        rtcClock_EveryMonthHandler();
                    }
                }   /* Day roll over */

                /* Alarm DAYOFWEEK */
                if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask,
                                                     rtcClock_ALARM_DAYOFWEEK_MASK))
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
                }   /* Day of week alarm is masked */

                /* Alarm DAYOFYEAR */
                if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask,
                                                     rtcClock_ALARM_DAYOFYEAR_MASK))
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
                }   /* Day of year alarm is masked */

                /* Alarm DAYOFMONTH */
                if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask,
                         rtcClock_ALARM_DAYOFMONTH_MASK))
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
                }   /* Day of month alarm is masked */

                #if (1u == rtcClock_DST_FUNC_ENABLE)
                    if(rtcClock_dstTimeDateStop.DayOfMonth == rtcClock_currentTimeDate.DayOfMonth)
                    {
                        rtcClock_dstStopStatus |= rtcClock_DST_DAYOFMONTH;
                    }
                    else
                    {
                        rtcClock_dstStopStatus &= (uint8)(~rtcClock_DST_DAYOFMONTH);
                    }

                    if(rtcClock_dstTimeDateStart.DayOfMonth == rtcClock_currentTimeDate.DayOfMonth)
                    {
                        rtcClock_dstStartStatus |= rtcClock_DST_DAYOFMONTH;
                    }
                    else
                    {
                        rtcClock_dstStartStatus &= (uint8)(~rtcClock_DST_DAYOFMONTH);
                    }
                #endif /* 1u == rtcClock_DST_FUNC_ENABLE */

                /* Set Alarm flag event */
                rtcClock_tmp = rtcClock_alarmCfgMask;
                rtcClock_SET_ALARM(rtcClock_tmp,
                                           rtcClock_alarmCurStatus,
                                           rtcClock_statusDateTime);

                /* Every Day */
                if(0u != rtcClock_IS_BIT_SET(rtcClock_intervalCfgMask,
                         rtcClock_INTERVAL_DAY_MASK))
                {
                    rtcClock_EveryDayHandler();
                }

                if(1u == rtcClock_currentTimeDate.DayOfWeek)
                {
                    /* Every Week */
                    if(0u != rtcClock_IS_BIT_SET(rtcClock_intervalCfgMask,
                                                         rtcClock_INTERVAL_WEEK_MASK))
                    {
                       rtcClock_EveryWeekHandler();
                    }
                }

            } /* End of day roll over */

            /* Status set PM/AM flag */
            if(rtcClock_currentTimeDate.Hour < rtcClock_HALF_OF_DAY_ELAPSED)
            {
                /* AM Hour 00:00-11:59, flag zero */
                rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_AM_PM);
            }
            else
            {
                /* PM Hour 12:00-23:59, flag set */
                rtcClock_statusDateTime |= rtcClock_STATUS_AM_PM;
            }

            #if (1u == rtcClock_DST_FUNC_ENABLE)
                if(rtcClock_dstTimeDateStop.Hour == rtcClock_currentTimeDate.Hour)
                {
                    rtcClock_dstStopStatus |= rtcClock_DST_HOUR;
                }
                else
                {
                    rtcClock_dstStopStatus &= (uint8)(~rtcClock_DST_HOUR);
                }

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
                        if(0u != rtcClock_IS_BIT_SET(rtcClock_dstStopStatus, rtcClock_DST_HOUR |
                                                       rtcClock_DST_DAYOFMONTH | rtcClock_DST_MONTH))
                        {
                            /* Substruct from current value of minutes, number of minutes
                            * in DST offset which is out of complete hour
                            */
                            rtcClock_currentTimeDate.Min -=
                                                rtcClock_dstOffsetMin % (rtcClock_HOUR_ELAPSED + 1u);

                            /* Is minute value negative? */
                            if(rtcClock_currentTimeDate.Min > rtcClock_HOUR_ELAPSED)
                            {
                                /* Convert to the positive.
                                * HOUR_ELAPSED -     (~currentTimeDate.Min    ) ==
                                * HOUR_ELAPSED + 1 - (~currentTimeDate.Min + 1)
                                */
                                rtcClock_currentTimeDate.Min = rtcClock_HOUR_ELAPSED -
                                                             ((uint8)(~rtcClock_currentTimeDate.Min));

                                rtcClock_currentTimeDate.Hour--;
                            }

                            rtcClock_currentTimeDate.Hour -= rtcClock_dstOffsetMin /
                                                                     (rtcClock_HOUR_ELAPSED + 1u);

                            /* Day roll over
                            * Is hour value negative? */
                            if(rtcClock_currentTimeDate.Hour > rtcClock_DAY_ELAPSED)
                            {
                                /* Convert to the positive.
                                * DAY_ELAPSED - (~currentTimeDate.Hour) ==
                                * DAY_ELAPSED + 1 - (~currentTimeDate.Hour + 1)
                                */
                                rtcClock_currentTimeDate.Hour = rtcClock_DAY_ELAPSED -
                                                              ((uint8)(~rtcClock_currentTimeDate.Hour));

                                /* Status set PM/AM flag */
                                if(rtcClock_currentTimeDate.Hour < rtcClock_HALF_OF_DAY_ELAPSED)
                                {
                                    /* AM Hour 00:00-11:59, flag zero */
                                    rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_AM_PM);
                                }
                                else
                                {
                                    /* PM Hour 12:00-23:59, flag set */
                                    rtcClock_statusDateTime |= rtcClock_STATUS_AM_PM;
                                }

                                rtcClock_currentTimeDate.DayOfMonth--;
                                rtcClock_currentTimeDate.DayOfYear--;
                                rtcClock_currentTimeDate.DayOfWeek--;

                                if(0u == rtcClock_currentTimeDate.DayOfWeek)
                                {
                                    rtcClock_currentTimeDate.DayOfWeek = rtcClock_DAYS_IN_WEEK;
                                }

                                if(0u == rtcClock_currentTimeDate.DayOfMonth)
                                {
                                    rtcClock_currentTimeDate.Month--;
                                    if(0u == rtcClock_currentTimeDate.Month)
                                    {
                                        rtcClock_currentTimeDate.Month = rtcClock_DECEMBER;

                                        rtcClock_currentTimeDate.DayOfMonth =
                                            rtcClock_daysInMonths[rtcClock_currentTimeDate.Month - 1u];

                                        rtcClock_currentTimeDate.Year--;

                                        if(1u == rtcClock_LEAP_YEAR(rtcClock_currentTimeDate.Year))
                                        {
                                            /* LP - true, else - false */
                                            rtcClock_statusDateTime |= rtcClock_STATUS_LY;
                                            rtcClock_currentTimeDate.DayOfYear =
                                                                                    rtcClock_DAYS_IN_LEAP_YEAR;
                                        }
                                        else
                                        {
                                            rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_LY);
                                            rtcClock_currentTimeDate.DayOfYear = rtcClock_DAYS_IN_YEAR;
                                        }
                                        rtcClock_EveryYearHandler();
                                    }
                                    else
                                    {
                                        /* Day of month roll over.
                                        * Check if day of month February 29 of leap year
                                        */
                                        if((0u != (rtcClock_statusDateTime & rtcClock_STATUS_LY)) &&
                                            (rtcClock_currentTimeDate.Month == rtcClock_FEBRUARY))
                                        {
                                            rtcClock_currentTimeDate.DayOfMonth =
                                            rtcClock_daysInMonths[rtcClock_currentTimeDate.Month - 1u]
                                            + 1u;
                                        }
                                        else
                                        {
                                            rtcClock_currentTimeDate.DayOfMonth =
                                            rtcClock_daysInMonths[rtcClock_currentTimeDate.Month - 1u];
                                        }
                                    }
                                    rtcClock_EveryMonthHandler();
                                }
                                rtcClock_EveryDayHandler();
                            }
                            rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_DST);
                            rtcClock_dstStopStatus = 0u;
                        }
                    }
                    else
                    {
                        if(0u != rtcClock_IS_BIT_SET(rtcClock_dstStartStatus,
                                                      (rtcClock_DST_HOUR | rtcClock_DST_DAYOFMONTH |
                                                       rtcClock_DST_MONTH)))
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

                            rtcClock_currentTimeDate.Hour += rtcClock_dstOffsetMin /
                                                                     (rtcClock_HOUR_ELAPSED + 1u);

                            if(rtcClock_currentTimeDate.Hour > rtcClock_DAY_ELAPSED)
                            {
                                /* Adjust hour, add day */
                                rtcClock_currentTimeDate.Hour -= (rtcClock_DAY_ELAPSED + 1u);

                                /* Status set PM/AM flag */
                                if(rtcClock_currentTimeDate.Hour < rtcClock_HALF_OF_DAY_ELAPSED)
                                {
                                    /* AM Hour 00:00-11:59, flag zero */
                                    rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_AM_PM);
                                }
                                else
                                {
                                    /* PM Hour 12:00-23:59, flag set */
                                    rtcClock_statusDateTime |= rtcClock_STATUS_AM_PM;
                                }

                                rtcClock_currentTimeDate.DayOfMonth++;
                                rtcClock_currentTimeDate.DayOfYear++;
                                rtcClock_currentTimeDate.DayOfWeek++;

                                if(rtcClock_currentTimeDate.DayOfWeek > rtcClock_WEEK_ELAPSED)
                                {
                                    rtcClock_currentTimeDate.DayOfWeek = 1u;
                                }

                                /* Day of month roll over.
                                * Check if day of month greater than 29 in February of leap year or
                                * if day of month greater than 28 NOT in February of NON leap year or
                                * if day of month greater than it should be in every month in non leap year
                                */
                                if(((0u != (rtcClock_statusDateTime & rtcClock_STATUS_LY)) &&
                                    (rtcClock_currentTimeDate.Month == rtcClock_FEBRUARY)  &&
                                    (rtcClock_currentTimeDate.DayOfMonth >
                                  (rtcClock_daysInMonths[rtcClock_currentTimeDate.Month - 1u] + 1u))) ||
                                   ((0u != (rtcClock_statusDateTime & rtcClock_STATUS_LY)) &&
                                    (rtcClock_currentTimeDate.Month != rtcClock_FEBRUARY)  &&
                                    (rtcClock_currentTimeDate.DayOfMonth >
                                     rtcClock_daysInMonths[rtcClock_currentTimeDate.Month - 1u])) ||
                                   ((0u == (rtcClock_statusDateTime & rtcClock_STATUS_LY)) &&
                                    (rtcClock_currentTimeDate.DayOfMonth >
                                     rtcClock_daysInMonths[rtcClock_currentTimeDate.Month - 1u])))
                                {
                                    rtcClock_currentTimeDate.Month++;
                                    rtcClock_currentTimeDate.DayOfMonth = 1u;
                                    if(rtcClock_currentTimeDate.Month > rtcClock_YEAR_ELAPSED)
                                    {
                                        rtcClock_currentTimeDate.Month = rtcClock_JANUARY;
                                        rtcClock_currentTimeDate.Year++;

                                        if(1u == rtcClock_LEAP_YEAR(rtcClock_currentTimeDate.Year))
                                        {
                                            /* LP - true, else - false */
                                            rtcClock_statusDateTime |= rtcClock_STATUS_LY;
                                        }
                                        else
                                        {
                                            rtcClock_statusDateTime &= (uint8)(~rtcClock_STATUS_LY);
                                        }
                                        rtcClock_currentTimeDate.DayOfYear = 1u;

                                        rtcClock_EveryYearHandler();
                                    }
                                    rtcClock_EveryMonthHandler();
                                }
                                rtcClock_EveryDayHandler();
                            }
                            rtcClock_statusDateTime |= rtcClock_STATUS_DST;
                            rtcClock_dstStartStatus = 0u;

                            /* Month */
                            if(rtcClock_dstTimeDateStop.Month == rtcClock_currentTimeDate.Month)
                            {
                                rtcClock_dstStopStatus |= rtcClock_DST_MONTH;
                            }
                            else
                            {
                                rtcClock_dstStopStatus &= (uint8)(~rtcClock_DST_MONTH);
                            }

                            /* DayOfMonth */
                            if(rtcClock_dstTimeDateStop.DayOfMonth ==
                                                                            rtcClock_currentTimeDate.DayOfMonth)
                            {
                                rtcClock_dstStopStatus |= rtcClock_DST_DAYOFMONTH;
                            }
                            else
                            {
                                rtcClock_dstStopStatus &= (uint8)(~rtcClock_DST_DAYOFMONTH);
                            }
                        }
                    }

                    /* Alarm DAYOFWEEK */
                    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask,
                                                         rtcClock_ALARM_DAYOFWEEK_MASK))
                    {
                        if(rtcClock_alarmCfgTimeDate.DayOfWeek == rtcClock_currentTimeDate.DayOfWeek)
                        {
                            rtcClock_alarmCurStatus |= rtcClock_ALARM_DAYOFWEEK_MASK;
                        }
                        else
                        {
                            rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_DAYOFWEEK_MASK);
                        }
                    }

                    /* Alarm DAYOFYEAR */
                    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask,
                                                         rtcClock_ALARM_DAYOFYEAR_MASK))
                    {
                        if(rtcClock_alarmCfgTimeDate.DayOfYear == rtcClock_currentTimeDate.DayOfYear)
                        {
                            rtcClock_alarmCurStatus |= rtcClock_ALARM_DAYOFYEAR_MASK;
                        }
                        else
                        {
                            rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_DAYOFYEAR_MASK);
                        }
                    }

                    /* Alarm DAYOFMONTH */
                    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask,
                                                         rtcClock_ALARM_DAYOFMONTH_MASK))
                    {
                        if(rtcClock_alarmCfgTimeDate.DayOfMonth == rtcClock_currentTimeDate.DayOfMonth)
                        {
                            rtcClock_alarmCurStatus |= rtcClock_ALARM_DAYOFMONTH_MASK;
                        }
                        else
                        {
                            rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_DAYOFMONTH_MASK);
                        }
                    }

                    /* Alarm MONTH */
                    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask,
                                                         rtcClock_ALARM_MONTH_MASK))
                    {
                        if(rtcClock_alarmCfgTimeDate.Month == rtcClock_currentTimeDate.Month)
                        {
                            rtcClock_alarmCurStatus |= rtcClock_ALARM_MONTH_MASK;
                        }
                        else
                        {
                            rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_MONTH_MASK);
                        }
                    }

                    /* Alarm YEAR */
                    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask,
                                                         rtcClock_ALARM_YEAR_MASK))
                    {
                        if(rtcClock_alarmCfgTimeDate.Year == rtcClock_currentTimeDate.Year)
                        {
                            rtcClock_alarmCurStatus |= rtcClock_ALARM_YEAR_MASK;
                        }
                        else
                        {
                            rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_YEAR_MASK);
                        }
                    }

                    /* Set Alarm flag event */
                    rtcClock_tmp = rtcClock_alarmCfgMask;
                    rtcClock_SET_ALARM(rtcClock_tmp,
                                               rtcClock_alarmCurStatus,
                                               rtcClock_statusDateTime);
                }
            #endif /* 1u == rtcClock_DST_FUNC_ENABLE */

            /* Alarm HOUR */
            if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask, rtcClock_ALARM_HOUR_MASK))
            {
                if(rtcClock_alarmCfgTimeDate.Hour == rtcClock_currentTimeDate.Hour)
                {
                    rtcClock_alarmCurStatus |= rtcClock_ALARM_HOUR_MASK;
                }
                else
                {
                    rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_HOUR_MASK);
                }
            }

            /* Set Alarm flag event */
            rtcClock_tmp = rtcClock_alarmCfgMask;
            rtcClock_SET_ALARM(rtcClock_tmp,
                                       rtcClock_alarmCurStatus,
                                       rtcClock_statusDateTime);

            /* Every Hour */
            if(0u != rtcClock_IS_BIT_SET(rtcClock_intervalCfgMask, rtcClock_INTERVAL_HOUR_MASK))
            {
                rtcClock_EveryHourHandler();
            }
        } /* Min > 59 = Hour */

        /* Alarm MIN */
        if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask, rtcClock_ALARM_MIN_MASK))
        {
            if(rtcClock_alarmCfgTimeDate.Min == rtcClock_currentTimeDate.Min)
            {
                rtcClock_alarmCurStatus |= rtcClock_ALARM_MIN_MASK;
            }
            else
            {
                rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_MIN_MASK);
            }
        }

        /* Set Alarm flag event */
        rtcClock_tmp = rtcClock_alarmCfgMask;
        rtcClock_SET_ALARM(rtcClock_tmp,
                                   rtcClock_alarmCurStatus,
                                   rtcClock_statusDateTime);

        /* Every Min */
        if(0u != rtcClock_IS_BIT_SET(rtcClock_intervalCfgMask, rtcClock_INTERVAL_MIN_MASK))
        {
            rtcClock_EveryMinuteHandler();
        }
    } /* Sec */

    /* Alarm SEC */
    if(0u != rtcClock_IS_BIT_SET(rtcClock_alarmCfgMask, rtcClock_ALARM_SEC_MASK))
    {
        if(rtcClock_alarmCfgTimeDate.Sec == rtcClock_currentTimeDate.Sec)
        {
            rtcClock_alarmCurStatus |= rtcClock_ALARM_SEC_MASK;
        }
        else
        {
            rtcClock_alarmCurStatus &= (uint8)(~rtcClock_ALARM_SEC_MASK);
        }
    }

    /* Set Alarm flag event */
    rtcClock_tmp = rtcClock_alarmCfgMask;
    rtcClock_SET_ALARM(rtcClock_tmp, rtcClock_alarmCurStatus, rtcClock_statusDateTime);

    /* Execute every second handler if needed */
    if(0u != rtcClock_IS_BIT_SET(rtcClock_intervalCfgMask, rtcClock_INTERVAL_SEC_MASK))
    {
        rtcClock_EverySecondHandler();
    }
    
    #ifdef rtcClock_ISR_EXIT_CALLBACK
        rtcClock_ISR_ExitCallback();
    #endif /* rtcClock_ISR_EXIT_CALLBACK */
}


/* [] END OF FILE */
