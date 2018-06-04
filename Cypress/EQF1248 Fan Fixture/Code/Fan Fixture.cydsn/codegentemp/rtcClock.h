/*******************************************************************************
* File Name: rtcClock.h
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

#if !defined(CY_RTC_rtcClock_H)
#define CY_RTC_rtcClock_H

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
extern uint8 rtcClock_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

/* what day of the week is start of week */
#define rtcClock_START_OF_WEEK          (0u)

/* Daylight saving time */
#define rtcClock_DST_FUNC_ENABLE        (1u)


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
} volatile rtcClock_TIME_DATE;

typedef struct
{
    uint8 Hour;
    uint8 DayOfWeek;
    uint8 Week;
    uint8 DayOfMonth;
    uint8 Month;
} volatile rtcClock_DSTIME;


/***************************************
*    Function Prototypes
***************************************/

CY_ISR_PROTO(rtcClock_ISR);

void rtcClock_Start(void)                            ;
void rtcClock_Stop(void)                             ;
void rtcClock_EnableInt(void)                        ;
void rtcClock_DisableInt(void)                       ;
void rtcClock_Init(void)                             ;
void rtcClock_Enable(void)                           ;

rtcClock_TIME_DATE * rtcClock_ReadTime(void) ;
void rtcClock_WriteTime(const rtcClock_TIME_DATE * timeDate)
                                                             ;

/* RTC write functions to set Start Values */
void rtcClock_WriteSecond(uint8 second)              ;
void rtcClock_WriteMinute(uint8 minute)              ;
void rtcClock_WriteHour(uint8 hour)                  ;
void rtcClock_WriteDayOfMonth(uint8 dayOfMonth)      ;
void rtcClock_WriteMonth(uint8 month)                ;
void rtcClock_WriteYear(uint16 year)                 ;

/* RTC Alarm write settings */
void rtcClock_WriteAlarmSecond(uint8 second)         ;
void rtcClock_WriteAlarmMinute(uint8 minute)         ;
void rtcClock_WriteAlarmHour(uint8 hour)             ;
void rtcClock_WriteAlarmDayOfMonth(uint8 dayOfMonth) ;
void rtcClock_WriteAlarmMonth(uint8 month)           ;
void rtcClock_WriteAlarmYear(uint16 year)            ;
void rtcClock_WriteAlarmDayOfWeek(uint8 dayOfWeek)   ;
void rtcClock_WriteAlarmDayOfYear(uint16 dayOfYear)  ;

/* RTC read settings to set start values */
uint8  rtcClock_ReadSecond(void)                     ;
uint8  rtcClock_ReadMinute(void)                     ;
uint8  rtcClock_ReadHour(void)                       ;
uint8  rtcClock_ReadDayOfMonth(void)                 ;
uint8  rtcClock_ReadMonth(void)                      ;
uint16 rtcClock_ReadYear(void)                       ;

/* Alarm read settings */
uint8  rtcClock_ReadAlarmSecond(void)                ;
uint8  rtcClock_ReadAlarmMinute(void)                ;
uint8  rtcClock_ReadAlarmHour(void)                  ;
uint8  rtcClock_ReadAlarmDayOfMonth(void)            ;
uint8  rtcClock_ReadAlarmMonth(void)                 ;
uint16 rtcClock_ReadAlarmYear(void)                  ;
uint8  rtcClock_ReadAlarmDayOfWeek(void)             ;
uint16 rtcClock_ReadAlarmDayOfYear(void)             ;

/* Set mask interrupt registers */
void rtcClock_WriteAlarmMask(uint8 mask)             ;
void rtcClock_WriteIntervalMask(uint8 mask)          ;

/* Read status register */
uint8 rtcClock_ReadStatus(void)                      ;

#if (1u == rtcClock_DST_FUNC_ENABLE)

    /* DST write settings */
    void rtcClock_WriteDSTMode(uint8 mode)           ;
    void rtcClock_WriteDSTStartHour(uint8 hour)      ;
    void rtcClock_WriteDSTStartDayOfMonth(uint8 dayOfMonth)
                                                          ;
    void rtcClock_WriteDSTStartMonth(uint8 month)    ;
    void rtcClock_WriteDSTStartDayOfWeek(uint8 dayOfWeek)
                                                          ;
    void rtcClock_WriteDSTStartWeek(uint8 week)      ;

    void rtcClock_WriteDSTStopHour(uint8 hour)       ;
    void rtcClock_WriteDSTStopDayOfMonth(uint8 dayOfMonth)
                                                          ;
    void rtcClock_WriteDSTStopMonth(uint8 month)     ;
    void rtcClock_WriteDSTStopDayOfWeek(uint8 dayOfWeek)
                                                          ;
    void rtcClock_WriteDSTStopWeek(uint8 week)       ;
    void rtcClock_WriteDSTOffset(uint8 offset)       ;

#endif /* 1u == rtcClock_DST_FUNC_ENABLE */


/***************************************
*        API Constants
***************************************/

/* Number of the rtcClock_isr interrupt */
#define rtcClock_ISR_NUMBER             ((uint8) rtcClock_isr__INTC_NUMBER)

/* Priority of the rtcClock_isr interrupt */
#define rtcClock_ISR_PRIORITY           ((uint8) rtcClock_isr__INTC_PRIOR_NUM)

/* Time elapse constants */
#define rtcClock_MINUTE_ELAPSED         (59u)
#define rtcClock_HOUR_ELAPSED           (59u)
#define rtcClock_HALF_OF_DAY_ELAPSED    (12u)
#define rtcClock_DAY_ELAPSED            (23u)
#define rtcClock_WEEK_ELAPSED           (7u)
#define rtcClock_YEAR_ELAPSED           (12u)
#define rtcClock_DAYS_IN_WEEK           (7u)

/* Interval software register bit location */
#define rtcClock_INTERVAL_SEC_MASK      (0x01u)       /* SEC */
#define rtcClock_INTERVAL_MIN_MASK      (0x02u)       /* MIN */
#define rtcClock_INTERVAL_HOUR_MASK     (0x04u)       /* HOUR*/
#define rtcClock_INTERVAL_DAY_MASK      (0x08u)       /* DOM */
#define rtcClock_INTERVAL_WEEK_MASK     (0x10u)       /* DOM */
#define rtcClock_INTERVAL_MONTH_MASK    (0x20u)       /* MONTH */
#define rtcClock_INTERVAL_YEAR_MASK     (0x40u)       /* YEAR */

/* Alarm software register bit location */
#define rtcClock_ALARM_SEC_MASK         (0x01u)       /* SEC */
#define rtcClock_ALARM_MIN_MASK         (0x02u)       /* MIN */
#define rtcClock_ALARM_HOUR_MASK        (0x04u)       /* HOUR*/
#define rtcClock_ALARM_DAYOFWEEK_MASK   (0x08u)       /* DOW */
#define rtcClock_ALARM_DAYOFMONTH_MASK  (0x10u)       /* DOM */
#define rtcClock_ALARM_DAYOFYEAR_MASK   (0x20u)       /* DOY */
#define rtcClock_ALARM_MONTH_MASK       (0x40u)       /* MONTH */
#define rtcClock_ALARM_YEAR_MASK        (0x80u)       /* YEAR */

/* Status software register bit location */

/* DST status bit */
#define rtcClock_STATUS_DST             (0x01u)

/* Leap Year status bit */
#define rtcClock_STATUS_LY              (0x02u)

/* AM/PM status bit */
#define rtcClock_STATUS_AM_PM           (0x04u)

/* Alarm Active status bit */
#define rtcClock_STATUS_AA              (0x08u)

/* Days Of Week definition */
#define rtcClock_SUNDAY                       (1u)
#define rtcClock_MONDAY                       (2u)
#define rtcClock_TUESDAY                      (3u)
#define rtcClock_WEDNESDAY                    (4u)
#define rtcClock_THURDAY                      (5u)
#define rtcClock_FRIDAY                       (6u)
#define rtcClock_SATURDAY                     (7u)


/* Month definition */
#define rtcClock_JANUARY                (1u)
#define rtcClock_DAYS_IN_JANUARY        (31u)
#define rtcClock_FEBRUARY               (2u)
#define rtcClock_DAYS_IN_FEBRUARY       (28u)
#define rtcClock_MARCH                  (3u)
#define rtcClock_DAYS_IN_MARCH          (31u)
#define rtcClock_APRIL                  (4u)
#define rtcClock_DAYS_IN_APRIL          (30u)
#define rtcClock_MAY                    (5u)
#define rtcClock_DAYS_IN_MAY            (31u)
#define rtcClock_JUNE                   (6u)
#define rtcClock_DAYS_IN_JUNE           (30u)
#define rtcClock_JULY                   (7u)
#define rtcClock_DAYS_IN_JULY           (31u)
#define rtcClock_AUGUST                 (8u)
#define rtcClock_DAYS_IN_AUGUST         (31u)
#define rtcClock_SEPTEMBER              (9u)
#define rtcClock_DAYS_IN_SEPTEMBER      (30u)
#define rtcClock_OCTOBER                (10u)
#define rtcClock_DAYS_IN_OCTOBER        (31u)
#define rtcClock_NOVEMBER               (11u)
#define rtcClock_DAYS_IN_NOVEMBER       (30u)
#define rtcClock_DECEMBER               (12u)
#define rtcClock_DAYS_IN_DECEMBER       (31u)

/* DTS software registers bit location */

/* DST Enable */
#define rtcClock_DST_ENABLE             (0x01u)

/* Fixed data selected */
#define rtcClock_DST_FIXDATE            (0x00u)

/* Relative data selected */
#define rtcClock_DST_RELDATE            (0x02u)

/* DST hour match flag */
#define rtcClock_DST_HOUR               (0x01u)

/* DST day of month match flag */
#define rtcClock_DST_DAYOFMONTH         (0x02u)

/* DST month match flag */
#define rtcClock_DST_MONTH              (0x04u)

#define rtcClock_MONTHS_IN_YEAR         (12u)
#define rtcClock_DAYS_IN_YEAR           (365u)
#define rtcClock_DAYS_IN_LEAP_YEAR      (366u)

/* Returns 1 if leap year, otherwise 0 */
#define rtcClock_LEAP_YEAR(year) \
                    (((((year) % 400u) == 0u) || ((((year) % 4u) == 0u) && (((year) % 100u) != 0u))) ? 0x01u : 0x00u)

/* Returns 1 if corresponding bit is set, otherwise 0 */
#define rtcClock_IS_BIT_SET(value, mask) (((mask) == ((value) & (mask))) ? 0x01u : 0x00u)

/* Set alarm if needed */
#define rtcClock_SET_ALARM(alarmCfg, alarmCur, status) \
    do { \
        if(((alarmCfg) != 0u) && ((rtcClock_IS_BIT_SET((alarmCur), (alarmCfg))) != 0u)) \
        { \
            (status) |= rtcClock_STATUS_AA; \
            (alarmCur) = 0u; \
        } \
    } while (0)


/***************************************
*    Registers
***************************************/

/* Time wheel Configuration Register 2 */
#define rtcClock_OPPS_CFG_REG           (* (reg8 *) CYREG_PM_TW_CFG2)
#define rtcClock_OPPS_CFG_PTR           (  (reg8 *) CYREG_PM_TW_CFG2)

/* Power Manager Interrupt Status Register */
#define rtcClock_OPPS_INT_SR_REG        (* (reg8 *) CYREG_PM_INT_SR)
#define rtcClock_OPPS_INT_SR_PTR        (  (reg8 *) CYREG_PM_INT_SR)


/***************************************
*    External Software Registers
***************************************/

extern rtcClock_TIME_DATE   rtcClock_alarmCfgTimeDate;
extern rtcClock_TIME_DATE   rtcClock_currentTimeDate;

#if (1u == rtcClock_DST_FUNC_ENABLE)
    extern volatile uint8           rtcClock_dstModeType;
    extern rtcClock_DSTIME  rtcClock_dstTimeDateStart;
    extern rtcClock_DSTIME  rtcClock_dstTimeDateStop;
    extern volatile uint8           rtcClock_dstOffsetMin;
    extern volatile uint8           rtcClock_dstStartStatus;
    extern volatile uint8           rtcClock_dstStopStatus;
#endif /* 1u == rtcClock_DST_FUNC_ENABLE */

extern volatile uint8               rtcClock_alarmCfgMask;
extern volatile uint8               rtcClock_alarmCurStatus;
extern volatile uint8               rtcClock_intervalCfgMask;
extern volatile uint8               rtcClock_statusDateTime;

extern const uint8 CYCODE           rtcClock_daysInMonths[rtcClock_MONTHS_IN_YEAR];


/***************************************
*        Register Constants
****************************************/

#define rtcClock_OPPS_EN_MASK           (0x10u)
#define rtcClock_OPPSIE_EN_MASK         (0x20u)

/* Enable wakeup from the Sleep low power mode */
#define rtcClock_PM_WAKEUP_CTW_1PPS     (0x80u)

#endif /* CY_RTC_rtcClock_H */


/* [] END OF FILE */
