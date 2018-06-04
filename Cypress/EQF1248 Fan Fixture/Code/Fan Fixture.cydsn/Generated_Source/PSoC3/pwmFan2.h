/*******************************************************************************
* File Name: pwmFan2.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_pwmFan2_H)
#define CY_PWM_pwmFan2_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 pwmFan2_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define pwmFan2_Resolution                     (8u)
#define pwmFan2_UsingFixedFunction             (0u)
#define pwmFan2_DeadBandMode                   (0u)
#define pwmFan2_KillModeMinTime                (0u)
#define pwmFan2_KillMode                       (0u)
#define pwmFan2_PWMMode                        (0u)
#define pwmFan2_PWMModeIsCenterAligned         (0u)
#define pwmFan2_DeadBandUsed                   (0u)
#define pwmFan2_DeadBand2_4                    (0u)

#if !defined(pwmFan2_PWMUDB_genblk8_stsreg__REMOVED)
    #define pwmFan2_UseStatus                  (1u)
#else
    #define pwmFan2_UseStatus                  (0u)
#endif /* !defined(pwmFan2_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(pwmFan2_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define pwmFan2_UseControl                 (1u)
#else
    #define pwmFan2_UseControl                 (0u)
#endif /* !defined(pwmFan2_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define pwmFan2_UseOneCompareMode              (1u)
#define pwmFan2_MinimumKillTime                (1u)
#define pwmFan2_EnableMode                     (0u)

#define pwmFan2_CompareMode1SW                 (0u)
#define pwmFan2_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define pwmFan2__B_PWM__DISABLED 0
#define pwmFan2__B_PWM__ASYNCHRONOUS 1
#define pwmFan2__B_PWM__SINGLECYCLE 2
#define pwmFan2__B_PWM__LATCHED 3
#define pwmFan2__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define pwmFan2__B_PWM__DBMDISABLED 0
#define pwmFan2__B_PWM__DBM_2_4_CLOCKS 1
#define pwmFan2__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define pwmFan2__B_PWM__ONE_OUTPUT 0
#define pwmFan2__B_PWM__TWO_OUTPUTS 1
#define pwmFan2__B_PWM__DUAL_EDGE 2
#define pwmFan2__B_PWM__CENTER_ALIGN 3
#define pwmFan2__B_PWM__DITHER 5
#define pwmFan2__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define pwmFan2__B_PWM__LESS_THAN 1
#define pwmFan2__B_PWM__LESS_THAN_OR_EQUAL 2
#define pwmFan2__B_PWM__GREATER_THAN 3
#define pwmFan2__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define pwmFan2__B_PWM__EQUAL 0
#define pwmFan2__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!pwmFan2_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!pwmFan2_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!pwmFan2_PWMModeIsCenterAligned) */
        #if (pwmFan2_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (pwmFan2_UseStatus) */

        /* Backup for Deadband parameters */
        #if(pwmFan2_DeadBandMode == pwmFan2__B_PWM__DBM_256_CLOCKS || \
            pwmFan2_DeadBandMode == pwmFan2__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(pwmFan2_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (pwmFan2_KillModeMinTime) */

        /* Backup control register */
        #if(pwmFan2_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (pwmFan2_UseControl) */

    #endif /* (!pwmFan2_UsingFixedFunction) */

}pwmFan2_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    pwmFan2_Start(void) ;
void    pwmFan2_Stop(void) ;

#if (pwmFan2_UseStatus || pwmFan2_UsingFixedFunction)
    void  pwmFan2_SetInterruptMode(uint8 interruptMode) ;
    uint8 pwmFan2_ReadStatusRegister(void) ;
#endif /* (pwmFan2_UseStatus || pwmFan2_UsingFixedFunction) */

#define pwmFan2_GetInterruptSource() pwmFan2_ReadStatusRegister()

#if (pwmFan2_UseControl)
    uint8 pwmFan2_ReadControlRegister(void) ;
    void  pwmFan2_WriteControlRegister(uint8 control)
          ;
#endif /* (pwmFan2_UseControl) */

#if (pwmFan2_UseOneCompareMode)
   #if (pwmFan2_CompareMode1SW)
       void    pwmFan2_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (pwmFan2_CompareMode1SW) */
#else
    #if (pwmFan2_CompareMode1SW)
        void    pwmFan2_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (pwmFan2_CompareMode1SW) */
    #if (pwmFan2_CompareMode2SW)
        void    pwmFan2_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (pwmFan2_CompareMode2SW) */
#endif /* (pwmFan2_UseOneCompareMode) */

#if (!pwmFan2_UsingFixedFunction)
    uint8   pwmFan2_ReadCounter(void) ;
    uint8 pwmFan2_ReadCapture(void) ;

    #if (pwmFan2_UseStatus)
            void pwmFan2_ClearFIFO(void) ;
    #endif /* (pwmFan2_UseStatus) */

    void    pwmFan2_WriteCounter(uint8 counter)
            ;
#endif /* (!pwmFan2_UsingFixedFunction) */

void    pwmFan2_WritePeriod(uint8 period)
        ;
uint8 pwmFan2_ReadPeriod(void) ;

#if (pwmFan2_UseOneCompareMode)
    void    pwmFan2_WriteCompare(uint8 compare)
            ;
    uint8 pwmFan2_ReadCompare(void) ;
#else
    void    pwmFan2_WriteCompare1(uint8 compare)
            ;
    uint8 pwmFan2_ReadCompare1(void) ;
    void    pwmFan2_WriteCompare2(uint8 compare)
            ;
    uint8 pwmFan2_ReadCompare2(void) ;
#endif /* (pwmFan2_UseOneCompareMode) */


#if (pwmFan2_DeadBandUsed)
    void    pwmFan2_WriteDeadTime(uint8 deadtime) ;
    uint8   pwmFan2_ReadDeadTime(void) ;
#endif /* (pwmFan2_DeadBandUsed) */

#if ( pwmFan2_KillModeMinTime)
    void pwmFan2_WriteKillTime(uint8 killtime) ;
    uint8 pwmFan2_ReadKillTime(void) ;
#endif /* ( pwmFan2_KillModeMinTime) */

void pwmFan2_Init(void) ;
void pwmFan2_Enable(void) ;
void pwmFan2_Sleep(void) ;
void pwmFan2_Wakeup(void) ;
void pwmFan2_SaveConfig(void) ;
void pwmFan2_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define pwmFan2_INIT_PERIOD_VALUE          (100u)
#define pwmFan2_INIT_COMPARE_VALUE1        (0u)
#define pwmFan2_INIT_COMPARE_VALUE2        (65u)
#define pwmFan2_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    pwmFan2_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    pwmFan2_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    pwmFan2_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    pwmFan2_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define pwmFan2_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  pwmFan2_CTRL_CMPMODE2_SHIFT)
#define pwmFan2_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  pwmFan2_CTRL_CMPMODE1_SHIFT)
#define pwmFan2_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (pwmFan2_UsingFixedFunction)
   #define pwmFan2_PERIOD_LSB              (*(reg16 *) pwmFan2_PWMHW__PER0)
   #define pwmFan2_PERIOD_LSB_PTR          ( (reg16 *) pwmFan2_PWMHW__PER0)
   #define pwmFan2_COMPARE1_LSB            (*(reg16 *) pwmFan2_PWMHW__CNT_CMP0)
   #define pwmFan2_COMPARE1_LSB_PTR        ( (reg16 *) pwmFan2_PWMHW__CNT_CMP0)
   #define pwmFan2_COMPARE2_LSB            (0x00u)
   #define pwmFan2_COMPARE2_LSB_PTR        (0x00u)
   #define pwmFan2_COUNTER_LSB             (*(reg16 *) pwmFan2_PWMHW__CNT_CMP0)
   #define pwmFan2_COUNTER_LSB_PTR         ( (reg16 *) pwmFan2_PWMHW__CNT_CMP0)
   #define pwmFan2_CAPTURE_LSB             (*(reg16 *) pwmFan2_PWMHW__CAP0)
   #define pwmFan2_CAPTURE_LSB_PTR         ( (reg16 *) pwmFan2_PWMHW__CAP0)
   #define pwmFan2_RT1                     (*(reg8 *)  pwmFan2_PWMHW__RT1)
   #define pwmFan2_RT1_PTR                 ( (reg8 *)  pwmFan2_PWMHW__RT1)

#else
   #if (pwmFan2_Resolution == 8u) /* 8bit - PWM */

       #if(pwmFan2_PWMModeIsCenterAligned)
           #define pwmFan2_PERIOD_LSB      (*(reg8 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__D1_REG)
           #define pwmFan2_PERIOD_LSB_PTR  ((reg8 *)   pwmFan2_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #else
           #define pwmFan2_PERIOD_LSB      (*(reg8 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__F0_REG)
           #define pwmFan2_PERIOD_LSB_PTR  ((reg8 *)   pwmFan2_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #endif /* (pwmFan2_PWMModeIsCenterAligned) */

       #define pwmFan2_COMPARE1_LSB        (*(reg8 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define pwmFan2_COMPARE1_LSB_PTR    ((reg8 *)   pwmFan2_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define pwmFan2_COMPARE2_LSB        (*(reg8 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define pwmFan2_COMPARE2_LSB_PTR    ((reg8 *)   pwmFan2_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define pwmFan2_COUNTERCAP_LSB      (*(reg8 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define pwmFan2_COUNTERCAP_LSB_PTR  ((reg8 *)   pwmFan2_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define pwmFan2_COUNTER_LSB         (*(reg8 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define pwmFan2_COUNTER_LSB_PTR     ((reg8 *)   pwmFan2_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define pwmFan2_CAPTURE_LSB         (*(reg8 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__F1_REG)
       #define pwmFan2_CAPTURE_LSB_PTR     ((reg8 *)   pwmFan2_PWMUDB_sP8_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(pwmFan2_PWMModeIsCenterAligned)
               #define pwmFan2_PERIOD_LSB      (*(reg16 *) pwmFan2_PWMUDB_sP8_pwmdp_u0__D1_REG)
               #define pwmFan2_PERIOD_LSB_PTR  ((reg16 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #else
               #define pwmFan2_PERIOD_LSB      (*(reg16 *) pwmFan2_PWMUDB_sP8_pwmdp_u0__F0_REG)
               #define pwmFan2_PERIOD_LSB_PTR  ((reg16 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__F0_REG)
            #endif /* (pwmFan2_PWMModeIsCenterAligned) */

            #define pwmFan2_COMPARE1_LSB       (*(reg16 *) pwmFan2_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define pwmFan2_COMPARE1_LSB_PTR   ((reg16 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define pwmFan2_COMPARE2_LSB       (*(reg16 *) pwmFan2_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define pwmFan2_COMPARE2_LSB_PTR   ((reg16 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define pwmFan2_COUNTERCAP_LSB     (*(reg16 *) pwmFan2_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define pwmFan2_COUNTERCAP_LSB_PTR ((reg16 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define pwmFan2_COUNTER_LSB        (*(reg16 *) pwmFan2_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define pwmFan2_COUNTER_LSB_PTR    ((reg16 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define pwmFan2_CAPTURE_LSB        (*(reg16 *) pwmFan2_PWMUDB_sP8_pwmdp_u0__F1_REG)
            #define pwmFan2_CAPTURE_LSB_PTR    ((reg16 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__F1_REG)
        #else
            #if(pwmFan2_PWMModeIsCenterAligned)
               #define pwmFan2_PERIOD_LSB      (*(reg16 *) pwmFan2_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
               #define pwmFan2_PERIOD_LSB_PTR  ((reg16 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #else
               #define pwmFan2_PERIOD_LSB      (*(reg16 *) pwmFan2_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
               #define pwmFan2_PERIOD_LSB_PTR  ((reg16 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
            #endif /* (pwmFan2_PWMModeIsCenterAligned) */

            #define pwmFan2_COMPARE1_LSB       (*(reg16 *) pwmFan2_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define pwmFan2_COMPARE1_LSB_PTR   ((reg16 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define pwmFan2_COMPARE2_LSB       (*(reg16 *) pwmFan2_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define pwmFan2_COMPARE2_LSB_PTR   ((reg16 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define pwmFan2_COUNTERCAP_LSB     (*(reg16 *) pwmFan2_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define pwmFan2_COUNTERCAP_LSB_PTR ((reg16 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define pwmFan2_COUNTER_LSB        (*(reg16 *) pwmFan2_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define pwmFan2_COUNTER_LSB_PTR    ((reg16 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define pwmFan2_CAPTURE_LSB        (*(reg16 *) pwmFan2_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
            #define pwmFan2_CAPTURE_LSB_PTR    ((reg16 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define pwmFan2_AUX_CONTROLDP1          (*(reg8 *)  pwmFan2_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define pwmFan2_AUX_CONTROLDP1_PTR      ((reg8 *)   pwmFan2_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (pwmFan2_Resolution == 8) */

   #define pwmFan2_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define pwmFan2_AUX_CONTROLDP0          (*(reg8 *)  pwmFan2_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define pwmFan2_AUX_CONTROLDP0_PTR      ((reg8 *)   pwmFan2_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (pwmFan2_UsingFixedFunction) */

#if(pwmFan2_KillModeMinTime )
    #define pwmFan2_KILLMODEMINTIME        (*(reg8 *)  pwmFan2_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define pwmFan2_KILLMODEMINTIME_PTR    ((reg8 *)   pwmFan2_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (pwmFan2_KillModeMinTime ) */

#if(pwmFan2_DeadBandMode == pwmFan2__B_PWM__DBM_256_CLOCKS)
    #define pwmFan2_DEADBAND_COUNT         (*(reg8 *)  pwmFan2_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define pwmFan2_DEADBAND_COUNT_PTR     ((reg8 *)   pwmFan2_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define pwmFan2_DEADBAND_LSB_PTR       ((reg8 *)   pwmFan2_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define pwmFan2_DEADBAND_LSB           (*(reg8 *)  pwmFan2_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(pwmFan2_DeadBandMode == pwmFan2__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (pwmFan2_UsingFixedFunction)
        #define pwmFan2_DEADBAND_COUNT         (*(reg8 *)  pwmFan2_PWMHW__CFG0)
        #define pwmFan2_DEADBAND_COUNT_PTR     ((reg8 *)   pwmFan2_PWMHW__CFG0)
        #define pwmFan2_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << pwmFan2_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define pwmFan2_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define pwmFan2_DEADBAND_COUNT         (*(reg8 *)  pwmFan2_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define pwmFan2_DEADBAND_COUNT_PTR     ((reg8 *)   pwmFan2_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define pwmFan2_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << pwmFan2_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define pwmFan2_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (pwmFan2_UsingFixedFunction) */
#endif /* (pwmFan2_DeadBandMode == pwmFan2__B_PWM__DBM_256_CLOCKS) */



#if (pwmFan2_UsingFixedFunction)
    #define pwmFan2_STATUS                 (*(reg8 *) pwmFan2_PWMHW__SR0)
    #define pwmFan2_STATUS_PTR             ((reg8 *) pwmFan2_PWMHW__SR0)
    #define pwmFan2_STATUS_MASK            (*(reg8 *) pwmFan2_PWMHW__SR0)
    #define pwmFan2_STATUS_MASK_PTR        ((reg8 *) pwmFan2_PWMHW__SR0)
    #define pwmFan2_CONTROL                (*(reg8 *) pwmFan2_PWMHW__CFG0)
    #define pwmFan2_CONTROL_PTR            ((reg8 *) pwmFan2_PWMHW__CFG0)
    #define pwmFan2_CONTROL2               (*(reg8 *) pwmFan2_PWMHW__CFG1)
    #define pwmFan2_CONTROL3               (*(reg8 *) pwmFan2_PWMHW__CFG2)
    #define pwmFan2_GLOBAL_ENABLE          (*(reg8 *) pwmFan2_PWMHW__PM_ACT_CFG)
    #define pwmFan2_GLOBAL_ENABLE_PTR      ( (reg8 *) pwmFan2_PWMHW__PM_ACT_CFG)
    #define pwmFan2_GLOBAL_STBY_ENABLE     (*(reg8 *) pwmFan2_PWMHW__PM_STBY_CFG)
    #define pwmFan2_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) pwmFan2_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define pwmFan2_BLOCK_EN_MASK          (pwmFan2_PWMHW__PM_ACT_MSK)
    #define pwmFan2_BLOCK_STBY_EN_MASK     (pwmFan2_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define pwmFan2_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define pwmFan2_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define pwmFan2_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define pwmFan2_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define pwmFan2_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define pwmFan2_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define pwmFan2_CTRL_ENABLE            (uint8)((uint8)0x01u << pwmFan2_CTRL_ENABLE_SHIFT)
    #define pwmFan2_CTRL_RESET             (uint8)((uint8)0x01u << pwmFan2_CTRL_RESET_SHIFT)
    #define pwmFan2_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << pwmFan2_CTRL_CMPMODE2_SHIFT)
    #define pwmFan2_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << pwmFan2_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define pwmFan2_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define pwmFan2_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << pwmFan2_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define pwmFan2_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define pwmFan2_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define pwmFan2_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define pwmFan2_STATUS_TC_INT_EN_MASK_SHIFT            (pwmFan2_STATUS_TC_SHIFT - 4u)
    #define pwmFan2_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define pwmFan2_STATUS_CMP1_INT_EN_MASK_SHIFT          (pwmFan2_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define pwmFan2_STATUS_TC              (uint8)((uint8)0x01u << pwmFan2_STATUS_TC_SHIFT)
    #define pwmFan2_STATUS_CMP1            (uint8)((uint8)0x01u << pwmFan2_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define pwmFan2_STATUS_TC_INT_EN_MASK              (uint8)((uint8)pwmFan2_STATUS_TC >> 4u)
    #define pwmFan2_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)pwmFan2_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define pwmFan2_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define pwmFan2_RT1_MASK              (uint8)((uint8)0x03u << pwmFan2_RT1_SHIFT)
    #define pwmFan2_SYNC                  (uint8)((uint8)0x03u << pwmFan2_RT1_SHIFT)
    #define pwmFan2_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define pwmFan2_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << pwmFan2_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define pwmFan2_SYNCDSI_EN            (uint8)((uint8)0x0Fu << pwmFan2_SYNCDSI_SHIFT)


#else
    #define pwmFan2_STATUS                (*(reg8 *)   pwmFan2_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define pwmFan2_STATUS_PTR            ((reg8 *)    pwmFan2_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define pwmFan2_STATUS_MASK           (*(reg8 *)   pwmFan2_PWMUDB_genblk8_stsreg__MASK_REG)
    #define pwmFan2_STATUS_MASK_PTR       ((reg8 *)    pwmFan2_PWMUDB_genblk8_stsreg__MASK_REG)
    #define pwmFan2_STATUS_AUX_CTRL       (*(reg8 *)   pwmFan2_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define pwmFan2_CONTROL               (*(reg8 *)   pwmFan2_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define pwmFan2_CONTROL_PTR           ((reg8 *)    pwmFan2_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define pwmFan2_CTRL_ENABLE_SHIFT      (0x07u)
    #define pwmFan2_CTRL_RESET_SHIFT       (0x06u)
    #define pwmFan2_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define pwmFan2_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define pwmFan2_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define pwmFan2_CTRL_ENABLE            (uint8)((uint8)0x01u << pwmFan2_CTRL_ENABLE_SHIFT)
    #define pwmFan2_CTRL_RESET             (uint8)((uint8)0x01u << pwmFan2_CTRL_RESET_SHIFT)
    #define pwmFan2_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << pwmFan2_CTRL_CMPMODE2_SHIFT)
    #define pwmFan2_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << pwmFan2_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define pwmFan2_STATUS_KILL_SHIFT          (0x05u)
    #define pwmFan2_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define pwmFan2_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define pwmFan2_STATUS_TC_SHIFT            (0x02u)
    #define pwmFan2_STATUS_CMP2_SHIFT          (0x01u)
    #define pwmFan2_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define pwmFan2_STATUS_KILL_INT_EN_MASK_SHIFT          (pwmFan2_STATUS_KILL_SHIFT)
    #define pwmFan2_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (pwmFan2_STATUS_FIFONEMPTY_SHIFT)
    #define pwmFan2_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (pwmFan2_STATUS_FIFOFULL_SHIFT)
    #define pwmFan2_STATUS_TC_INT_EN_MASK_SHIFT            (pwmFan2_STATUS_TC_SHIFT)
    #define pwmFan2_STATUS_CMP2_INT_EN_MASK_SHIFT          (pwmFan2_STATUS_CMP2_SHIFT)
    #define pwmFan2_STATUS_CMP1_INT_EN_MASK_SHIFT          (pwmFan2_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define pwmFan2_STATUS_KILL            (uint8)((uint8)0x00u << pwmFan2_STATUS_KILL_SHIFT )
    #define pwmFan2_STATUS_FIFOFULL        (uint8)((uint8)0x01u << pwmFan2_STATUS_FIFOFULL_SHIFT)
    #define pwmFan2_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << pwmFan2_STATUS_FIFONEMPTY_SHIFT)
    #define pwmFan2_STATUS_TC              (uint8)((uint8)0x01u << pwmFan2_STATUS_TC_SHIFT)
    #define pwmFan2_STATUS_CMP2            (uint8)((uint8)0x01u << pwmFan2_STATUS_CMP2_SHIFT)
    #define pwmFan2_STATUS_CMP1            (uint8)((uint8)0x01u << pwmFan2_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define pwmFan2_STATUS_KILL_INT_EN_MASK            (pwmFan2_STATUS_KILL)
    #define pwmFan2_STATUS_FIFOFULL_INT_EN_MASK        (pwmFan2_STATUS_FIFOFULL)
    #define pwmFan2_STATUS_FIFONEMPTY_INT_EN_MASK      (pwmFan2_STATUS_FIFONEMPTY)
    #define pwmFan2_STATUS_TC_INT_EN_MASK              (pwmFan2_STATUS_TC)
    #define pwmFan2_STATUS_CMP2_INT_EN_MASK            (pwmFan2_STATUS_CMP2)
    #define pwmFan2_STATUS_CMP1_INT_EN_MASK            (pwmFan2_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define pwmFan2_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define pwmFan2_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define pwmFan2_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define pwmFan2_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define pwmFan2_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* pwmFan2_UsingFixedFunction */

#endif  /* CY_PWM_pwmFan2_H */


/* [] END OF FILE */
