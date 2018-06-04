/*******************************************************************************
* File Name: rcClock.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the RTC Component.
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_RTC_rcClock_H)
#define CY_RTC_rcClock_H

#include "cyfitter.h"
#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component RTC_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

/***************************************
*           Global Variables
***************************************/
extern uint8 rcClock_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

/* what day of the week is start of week */
#define rcClock_START_OF_WEEK          (0u)

/* Daylight saving time */
#define rcClock_DST_FUNC_ENABLE        (0u)


/***************************************
*    Data Struct Definitions
***************************************/

typedef struct
{
    uint8  Sec;
    uint8  Min;
    uint8  Hour;
    uint8  DayOfWeek;
    uint8  DayOfMonth;
    uint16 DayOfYear;
    uint8  Month;
    uint16 Year;
} volatile rcClock_TIME_DATE;

typedef struct
{
    uint8 Hour;
    uint8 DayOfWeek;
    uint8 Week;
    uint8 DayOfMonth;
    uint8 Month;
} volatile rcClock_DSTIME;


/***************************************
*    Function Prototypes
***************************************/

CY_ISR_PROTO(rcClock_ISR);

void rcClock_Start(void)                            ;
void rcClock_Stop(void)                             ;
void rcClock_EnableInt(void)                        ;
void rcClock_DisableInt(void)                       ;
void rcClock_Init(void)                             ;
void rcClock_Enable(void)                           ;

rcClock_TIME_DATE * rcClock_ReadTime(void) ;
void rcClock_WriteTime(const rcClock_TIME_DATE * timeDate)
                                                             ;

/* RTC write functions to set Start Values */
void rcClock_WriteSecond(uint8 second)              ;
void rcClock_WriteMinute(uint8 minute)              ;
void rcClock_WriteHour(uint8 hour)                  ;
void rcClock_WriteDayOfMonth(uint8 dayOfMonth)      ;
void rcClock_WriteMonth(uint8 month)                ;
void rcClock_WriteYear(uint16 year)                 ;

/* RTC Alarm write settings */
void rcClock_WriteAlarmSecond(uint8 second)         ;
void rcClock_WriteAlarmMinute(uint8 minute)         ;
void rcClock_WriteAlarmHour(uint8 hour)             ;
void rcClock_WriteAlarmDayOfMonth(uint8 dayOfMonth) ;
void rcClock_WriteAlarmMonth(uint8 month)           ;
void rcClock_WriteAlarmYear(uint16 year)            ;
void rcClock_WriteAlarmDayOfWeek(uint8 dayOfWeek)   ;
void rcClock_WriteAlarmDayOfYear(uint16 dayOfYear)  ;

/* RTC read settings to set start values */
uint8  rcClock_ReadSecond(void)                     ;
uint8  rcClock_ReadMinute(void)                     ;
uint8  rcClock_ReadHour(void)                       ;
uint8  rcClock_ReadDayOfMonth(void)                 ;
uint8  rcClock_ReadMonth(void)                      ;
uint16 rcClock_ReadYear(void)                       ;

/* Alarm read settings */
uint8  rcClock_ReadAlarmSecond(void)                ;
uint8  rcClock_ReadAlarmMinute(void)                ;
uint8  rcClock_ReadAlarmHour(void)                  ;
uint8  rcClock_ReadAlarmDayOfMonth(void)            ;
uint8  rcClock_ReadAlarmMonth(void)                 ;
uint16 rcClock_ReadAlarmYear(void)                  ;
uint8  rcClock_ReadAlarmDayOfWeek(void)             ;
uint16 rcClock_ReadAlarmDayOfYear(void)             ;

/* Set mask interrupt registers */
void rcClock_WriteAlarmMask(uint8 mask)             ;
void rcClock_WriteIntervalMask(uint8 mask)          ;

/* Read status register */
uint8 rcClock_ReadStatus(void)                      ;

#if (1u == rcClock_DST_FUNC_ENABLE)

    /* DST write settings */
    void rcClock_WriteDSTMode(uint8 mode)           ;
    void rcClock_WriteDSTStartHour(uint8 hour)      ;
    void rcClock_WriteDSTStartDayOfMonth(uint8 dayOfMonth)
                                                          ;
    void rcClock_WriteDSTStartMonth(uint8 month)    ;
    void rcClock_WriteDSTStartDayOfWeek(uint8 dayOfWeek)
                                                          ;
    void rcClock_WriteDSTStartWeek(uint8 week)      ;

    void rcClock_WriteDSTStopHour(uint8 hour)       ;
    void rcClock_WriteDSTStopDayOfMonth(uint8 dayOfMonth)
                                                          ;
    void rcClock_WriteDSTStopMonth(uint8 month)     ;
    void rcClock_WriteDSTStopDayOfWeek(uint8 dayOfWeek)
                                                          ;
    void rcClock_WriteDSTStopWeek(uint8 week)       ;
    void rcClock_WriteDSTOffset(uint8 offset)       ;

#endif /* 1u == rcClock_DST_FUNC_ENABLE */


/***************************************
*        API Constants
***************************************/

/* Number of the rcClock_isr interrupt */
#define rcClock_ISR_NUMBER             ((uint8) rcClock_isr__INTC_NUMBER)

/* Priority of the rcClock_isr interrupt */
#define rcClock_ISR_PRIORITY           ((uint8) rcClock_isr__INTC_PRIOR_NUM)

/* Time elapse constants */
#define rcClock_MINUTE_ELAPSED         (59u)
#define rcClock_HOUR_ELAPSED           (59u)
#define rcClock_HALF_OF_DAY_ELAPSED    (12u)
#define rcClock_DAY_ELAPSED            (23u)
#define rcClock_WEEK_ELAPSED           (7u)
#define rcClock_YEAR_ELAPSED           (12u)
#define rcClock_DAYS_IN_WEEK           (7u)

/* Interval software register bit location */
#define rcClock_INTERVAL_SEC_MASK      (0x01u)       /* SEC */
#define rcClock_INTERVAL_MIN_MASK      (0x02u)       /* MIN */
#define rcClock_INTERVAL_HOUR_MASK     (0x04u)       /* HOUR*/
#define rcClock_INTERVAL_DAY_MASK      (0x08u)       /* DOM */
#define rcClock_INTERVAL_WEEK_MASK     (0x10u)       /* DOM */
#define rcClock_INTERVAL_MONTH_MASK    (0x20u)       /* MONTH */
#define rcClock_INTERVAL_YEAR_MASK     (0x40u)       /* YEAR */

/* Alarm software register bit location */
#define rcClock_ALARM_SEC_MASK         (0x01u)       /* SEC */
#define rcClock_ALARM_MIN_MASK         (0x02u)       /* MIN */
#define rcClock_ALARM_HOUR_MASK        (0x04u)       /* HOUR*/
#define rcClock_ALARM_DAYOFWEEK_MASK   (0x08u)       /* DOW */
#define rcClock_ALARM_DAYOFMONTH_MASK  (0x10u)       /* DOM */
#define rcClock_ALARM_DAYOFYEAR_MASK   (0x20u)       /* DOY */
#define rcClock_ALARM_MONTH_MASK       (0x40u)       /* MONTH */
#define rcClock_ALARM_YEAR_MASK        (0x80u)       /* YEAR */

/* Status software register bit location */

/* DST status bit */
#define rcClock_STATUS_DST             (0x01u)

/* Leap Year status bit */
#define rcClock_STATUS_LY              (0x02u)

/* AM/PM status bit */
#define rcClock_STATUS_AM_PM           (0x04u)

/* Alarm Active status bit */
#define rcClock_STATUS_AA              (0x08u)

/* Days Of Week definition */
#define rcClock_SUNDAY                       (1u)
#define rcClock_MONDAY                       (2u)
#define rcClock_TUESDAY                      (3u)
#define rcClock_WEDNESDAY                    (4u)
#define rcClock_THURDAY                      (5u)
#define rcClock_FRIDAY                       (6u)
#define rcClock_SATURDAY                     (7u)


/* Month definition */
#define rcClock_JANUARY                (1u)
#define rcClock_DAYS_IN_JANUARY        (31u)
#define rcClock_FEBRUARY               (2u)
#define rcClock_DAYS_IN_FEBRUARY       (28u)
#define rcClock_MARCH                  (3u)
#define rcClock_DAYS_IN_MARCH          (31u)
#define rcClock_APRIL                  (4u)
#define rcClock_DAYS_IN_APRIL          (30u)
#define rcClock_MAY                    (5u)
#define rcClock_DAYS_IN_MAY            (31u)
#define rcClock_JUNE                   (6u)
#define rcClock_DAYS_IN_JUNE           (30u)
#define rcClock_JULY                   (7u)
#define rcClock_DAYS_IN_JULY           (31u)
#define rcClock_AUGUST                 (8u)
#define rcClock_DAYS_IN_AUGUST         (31u)
#define rcClock_SEPTEMBER              (9u)
#define rcClock_DAYS_IN_SEPTEMBER      (30u)
#define rcClock_OCTOBER                (10u)
#define rcClock_DAYS_IN_OCTOBER        (31u)
#define rcClock_NOVEMBER               (11u)
#define rcClock_DAYS_IN_NOVEMBER       (30u)
#define rcClock_DECEMBER               (12u)
#define rcClock_DAYS_IN_DECEMBER       (31u)

/* DTS software registers bit location */

/* DST Enable */
#define rcClock_DST_ENABLE             (0x01u)

/* Fixed data selected */
#define rcClock_DST_FIXDATE            (0x00u)

/* Relative data selected */
#define rcClock_DST_RELDATE            (0x02u)

/* DST hour match flag */
#define rcClock_DST_HOUR               (0x01u)

/* DST day of month match flag */
#define rcClock_DST_DAYOFMONTH         (0x02u)

/* DST month match flag */
#define rcClock_DST_MONTH              (0x04u)

#define rcClock_MONTHS_IN_YEAR         (12u)
#define rcClock_DAYS_IN_YEAR           (365u)
#define rcClock_DAYS_IN_LEAP_YEAR      (366u)

/* Returns 1 if leap year, otherwise 0 */
#define rcClock_LEAP_YEAR(year) \
                    (((((year) % 400u) == 0u) || ((((year) % 4u) == 0u) && (((year) % 100u) != 0u))) ? 0x01u : 0x00u)

/* Returns 1 if corresponding bit is set, otherwise 0 */
#define rcClock_IS_BIT_SET(value, mask) (((mask) == ((value) & (mask))) ? 0x01u : 0x00u)

/* Set alarm if needed */
#define rcClock_SET_ALARM(alarmCfg, alarmCur, status) \
    do { \
        if(((alarmCfg) != 0u) && ((rcClock_IS_BIT_SET((alarmCur), (alarmCfg))) != 0u)) \
        { \
            (status) |= rcClock_STATUS_AA; \
            (alarmCur) = 0u; \
        } \
    } while (0)


/***************************************
*    Registers
***************************************/

/* Time wheel Configuration Register 2 */
#define rcClock_OPPS_CFG_REG           (* (reg8 *) CYREG_PM_TW_CFG2)
#define rcClock_OPPS_CFG_PTR           (  (reg8 *) CYREG_PM_TW_CFG2)

/* Power Manager Interrupt Status Register */
#define rcClock_OPPS_INT_SR_REG        (* (reg8 *) CYREG_PM_INT_SR)
#define rcClock_OPPS_INT_SR_PTR        (  (reg8 *) CYREG_PM_INT_SR)


/***************************************
*    External Software Registers
***************************************/

extern rcClock_TIME_DATE   rcClock_alarmCfgTimeDate;
extern rcClock_TIME_DATE   rcClock_currentTimeDate;

#if (1u == rcClock_DST_FUNC_ENABLE)
    extern volatile uint8           rcClock_dstModeType;
    extern rcClock_DSTIME  rcClock_dstTimeDateStart;
    extern rcClock_DSTIME  rcClock_dstTimeDateStop;
    extern volatile uint8           rcClock_dstOffsetMin;
    extern volatile uint8           rcClock_dstStartStatus;
    extern volatile uint8           rcClock_dstStopStatus;
#endif /* 1u == rcClock_DST_FUNC_ENABLE */

extern volatile uint8               rcClock_alarmCfgMask;
extern volatile uint8               rcClock_alarmCurStatus;
extern volatile uint8               rcClock_intervalCfgMask;
extern volatile uint8               rcClock_statusDateTime;

extern const uint8 CYCODE           rcClock_daysInMonths[rcClock_MONTHS_IN_YEAR];


/***************************************
*        Register Constants
****************************************/

#define rcClock_OPPS_EN_MASK           (0x10u)
#define rcClock_OPPSIE_EN_MASK         (0x20u)

/* Enable wakeup from the Sleep low power mode */
#define rcClock_PM_WAKEUP_CTW_1PPS     (0x80u)

#endif /* CY_RTC_rcClock_H */


/* [] END OF FILE */
