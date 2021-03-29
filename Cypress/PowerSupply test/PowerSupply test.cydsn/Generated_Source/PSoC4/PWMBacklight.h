/*******************************************************************************
* File Name: PWMBacklight.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the PWMBacklight
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_PWMBacklight_H)
#define CY_TCPWM_PWMBacklight_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} PWMBacklight_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  PWMBacklight_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define PWMBacklight_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define PWMBacklight_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define PWMBacklight_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define PWMBacklight_QUAD_ENCODING_MODES            (0lu)
#define PWMBacklight_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define PWMBacklight_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define PWMBacklight_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define PWMBacklight_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define PWMBacklight_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define PWMBacklight_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define PWMBacklight_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define PWMBacklight_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define PWMBacklight_TC_RUN_MODE                    (0lu)
#define PWMBacklight_TC_COUNTER_MODE                (0lu)
#define PWMBacklight_TC_COMP_CAP_MODE               (2lu)
#define PWMBacklight_TC_PRESCALER                   (0lu)

/* Signal modes */
#define PWMBacklight_TC_RELOAD_SIGNAL_MODE          (0lu)
#define PWMBacklight_TC_COUNT_SIGNAL_MODE           (3lu)
#define PWMBacklight_TC_START_SIGNAL_MODE           (0lu)
#define PWMBacklight_TC_STOP_SIGNAL_MODE            (0lu)
#define PWMBacklight_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWMBacklight_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define PWMBacklight_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define PWMBacklight_TC_START_SIGNAL_PRESENT        (0lu)
#define PWMBacklight_TC_STOP_SIGNAL_PRESENT         (0lu)
#define PWMBacklight_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWMBacklight_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define PWMBacklight_PWM_KILL_EVENT                 (0lu)
#define PWMBacklight_PWM_STOP_EVENT                 (0lu)
#define PWMBacklight_PWM_MODE                       (4lu)
#define PWMBacklight_PWM_OUT_N_INVERT               (0lu)
#define PWMBacklight_PWM_OUT_INVERT                 (0lu)
#define PWMBacklight_PWM_ALIGN                      (0lu)
#define PWMBacklight_PWM_RUN_MODE                   (0lu)
#define PWMBacklight_PWM_DEAD_TIME_CYCLE            (0lu)
#define PWMBacklight_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define PWMBacklight_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define PWMBacklight_PWM_COUNT_SIGNAL_MODE          (3lu)
#define PWMBacklight_PWM_START_SIGNAL_MODE          (0lu)
#define PWMBacklight_PWM_STOP_SIGNAL_MODE           (0lu)
#define PWMBacklight_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWMBacklight_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define PWMBacklight_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define PWMBacklight_PWM_START_SIGNAL_PRESENT       (0lu)
#define PWMBacklight_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define PWMBacklight_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWMBacklight_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define PWMBacklight_TC_PERIOD_VALUE                (65535lu)
#define PWMBacklight_TC_COMPARE_VALUE               (65535lu)
#define PWMBacklight_TC_COMPARE_BUF_VALUE           (65535lu)
#define PWMBacklight_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define PWMBacklight_PWM_PERIOD_VALUE               (256lu)
#define PWMBacklight_PWM_PERIOD_BUF_VALUE           (65535lu)
#define PWMBacklight_PWM_PERIOD_SWAP                (0lu)
#define PWMBacklight_PWM_COMPARE_VALUE              (16lu)
#define PWMBacklight_PWM_COMPARE_BUF_VALUE          (65535lu)
#define PWMBacklight_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define PWMBacklight__LEFT 0
#define PWMBacklight__RIGHT 1
#define PWMBacklight__CENTER 2
#define PWMBacklight__ASYMMETRIC 3

#define PWMBacklight__X1 0
#define PWMBacklight__X2 1
#define PWMBacklight__X4 2

#define PWMBacklight__PWM 4
#define PWMBacklight__PWM_DT 5
#define PWMBacklight__PWM_PR 6

#define PWMBacklight__INVERSE 1
#define PWMBacklight__DIRECT 0

#define PWMBacklight__CAPTURE 2
#define PWMBacklight__COMPARE 0

#define PWMBacklight__TRIG_LEVEL 3
#define PWMBacklight__TRIG_RISING 0
#define PWMBacklight__TRIG_FALLING 1
#define PWMBacklight__TRIG_BOTH 2

#define PWMBacklight__INTR_MASK_TC 1
#define PWMBacklight__INTR_MASK_CC_MATCH 2
#define PWMBacklight__INTR_MASK_NONE 0
#define PWMBacklight__INTR_MASK_TC_CC 3

#define PWMBacklight__UNCONFIG 8
#define PWMBacklight__TIMER 1
#define PWMBacklight__QUAD 3
#define PWMBacklight__PWM_SEL 7

#define PWMBacklight__COUNT_UP 0
#define PWMBacklight__COUNT_DOWN 1
#define PWMBacklight__COUNT_UPDOWN0 2
#define PWMBacklight__COUNT_UPDOWN1 3


/* Prescaler */
#define PWMBacklight_PRESCALE_DIVBY1                ((uint32)(0u << PWMBacklight_PRESCALER_SHIFT))
#define PWMBacklight_PRESCALE_DIVBY2                ((uint32)(1u << PWMBacklight_PRESCALER_SHIFT))
#define PWMBacklight_PRESCALE_DIVBY4                ((uint32)(2u << PWMBacklight_PRESCALER_SHIFT))
#define PWMBacklight_PRESCALE_DIVBY8                ((uint32)(3u << PWMBacklight_PRESCALER_SHIFT))
#define PWMBacklight_PRESCALE_DIVBY16               ((uint32)(4u << PWMBacklight_PRESCALER_SHIFT))
#define PWMBacklight_PRESCALE_DIVBY32               ((uint32)(5u << PWMBacklight_PRESCALER_SHIFT))
#define PWMBacklight_PRESCALE_DIVBY64               ((uint32)(6u << PWMBacklight_PRESCALER_SHIFT))
#define PWMBacklight_PRESCALE_DIVBY128              ((uint32)(7u << PWMBacklight_PRESCALER_SHIFT))

/* TCPWM set modes */
#define PWMBacklight_MODE_TIMER_COMPARE             ((uint32)(PWMBacklight__COMPARE         <<  \
                                                                  PWMBacklight_MODE_SHIFT))
#define PWMBacklight_MODE_TIMER_CAPTURE             ((uint32)(PWMBacklight__CAPTURE         <<  \
                                                                  PWMBacklight_MODE_SHIFT))
#define PWMBacklight_MODE_QUAD                      ((uint32)(PWMBacklight__QUAD            <<  \
                                                                  PWMBacklight_MODE_SHIFT))
#define PWMBacklight_MODE_PWM                       ((uint32)(PWMBacklight__PWM             <<  \
                                                                  PWMBacklight_MODE_SHIFT))
#define PWMBacklight_MODE_PWM_DT                    ((uint32)(PWMBacklight__PWM_DT          <<  \
                                                                  PWMBacklight_MODE_SHIFT))
#define PWMBacklight_MODE_PWM_PR                    ((uint32)(PWMBacklight__PWM_PR          <<  \
                                                                  PWMBacklight_MODE_SHIFT))

/* Quad Modes */
#define PWMBacklight_MODE_X1                        ((uint32)(PWMBacklight__X1              <<  \
                                                                  PWMBacklight_QUAD_MODE_SHIFT))
#define PWMBacklight_MODE_X2                        ((uint32)(PWMBacklight__X2              <<  \
                                                                  PWMBacklight_QUAD_MODE_SHIFT))
#define PWMBacklight_MODE_X4                        ((uint32)(PWMBacklight__X4              <<  \
                                                                  PWMBacklight_QUAD_MODE_SHIFT))

/* Counter modes */
#define PWMBacklight_COUNT_UP                       ((uint32)(PWMBacklight__COUNT_UP        <<  \
                                                                  PWMBacklight_UPDOWN_SHIFT))
#define PWMBacklight_COUNT_DOWN                     ((uint32)(PWMBacklight__COUNT_DOWN      <<  \
                                                                  PWMBacklight_UPDOWN_SHIFT))
#define PWMBacklight_COUNT_UPDOWN0                  ((uint32)(PWMBacklight__COUNT_UPDOWN0   <<  \
                                                                  PWMBacklight_UPDOWN_SHIFT))
#define PWMBacklight_COUNT_UPDOWN1                  ((uint32)(PWMBacklight__COUNT_UPDOWN1   <<  \
                                                                  PWMBacklight_UPDOWN_SHIFT))

/* PWM output invert */
#define PWMBacklight_INVERT_LINE                    ((uint32)(PWMBacklight__INVERSE         <<  \
                                                                  PWMBacklight_INV_OUT_SHIFT))
#define PWMBacklight_INVERT_LINE_N                  ((uint32)(PWMBacklight__INVERSE         <<  \
                                                                  PWMBacklight_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define PWMBacklight_TRIG_RISING                    ((uint32)PWMBacklight__TRIG_RISING)
#define PWMBacklight_TRIG_FALLING                   ((uint32)PWMBacklight__TRIG_FALLING)
#define PWMBacklight_TRIG_BOTH                      ((uint32)PWMBacklight__TRIG_BOTH)
#define PWMBacklight_TRIG_LEVEL                     ((uint32)PWMBacklight__TRIG_LEVEL)

/* Interrupt mask */
#define PWMBacklight_INTR_MASK_TC                   ((uint32)PWMBacklight__INTR_MASK_TC)
#define PWMBacklight_INTR_MASK_CC_MATCH             ((uint32)PWMBacklight__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define PWMBacklight_CC_MATCH_SET                   (0x00u)
#define PWMBacklight_CC_MATCH_CLEAR                 (0x01u)
#define PWMBacklight_CC_MATCH_INVERT                (0x02u)
#define PWMBacklight_CC_MATCH_NO_CHANGE             (0x03u)
#define PWMBacklight_OVERLOW_SET                    (0x00u)
#define PWMBacklight_OVERLOW_CLEAR                  (0x04u)
#define PWMBacklight_OVERLOW_INVERT                 (0x08u)
#define PWMBacklight_OVERLOW_NO_CHANGE              (0x0Cu)
#define PWMBacklight_UNDERFLOW_SET                  (0x00u)
#define PWMBacklight_UNDERFLOW_CLEAR                (0x10u)
#define PWMBacklight_UNDERFLOW_INVERT               (0x20u)
#define PWMBacklight_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define PWMBacklight_PWM_MODE_LEFT                  (PWMBacklight_CC_MATCH_CLEAR        |   \
                                                         PWMBacklight_OVERLOW_SET           |   \
                                                         PWMBacklight_UNDERFLOW_NO_CHANGE)
#define PWMBacklight_PWM_MODE_RIGHT                 (PWMBacklight_CC_MATCH_SET          |   \
                                                         PWMBacklight_OVERLOW_NO_CHANGE     |   \
                                                         PWMBacklight_UNDERFLOW_CLEAR)
#define PWMBacklight_PWM_MODE_ASYM                  (PWMBacklight_CC_MATCH_INVERT       |   \
                                                         PWMBacklight_OVERLOW_SET           |   \
                                                         PWMBacklight_UNDERFLOW_CLEAR)

#if (PWMBacklight_CY_TCPWM_V2)
    #if(PWMBacklight_CY_TCPWM_4000)
        #define PWMBacklight_PWM_MODE_CENTER                (PWMBacklight_CC_MATCH_INVERT       |   \
                                                                 PWMBacklight_OVERLOW_NO_CHANGE     |   \
                                                                 PWMBacklight_UNDERFLOW_CLEAR)
    #else
        #define PWMBacklight_PWM_MODE_CENTER                (PWMBacklight_CC_MATCH_INVERT       |   \
                                                                 PWMBacklight_OVERLOW_SET           |   \
                                                                 PWMBacklight_UNDERFLOW_CLEAR)
    #endif /* (PWMBacklight_CY_TCPWM_4000) */
#else
    #define PWMBacklight_PWM_MODE_CENTER                (PWMBacklight_CC_MATCH_INVERT       |   \
                                                             PWMBacklight_OVERLOW_NO_CHANGE     |   \
                                                             PWMBacklight_UNDERFLOW_CLEAR)
#endif /* (PWMBacklight_CY_TCPWM_NEW) */

/* Command operations without condition */
#define PWMBacklight_CMD_CAPTURE                    (0u)
#define PWMBacklight_CMD_RELOAD                     (8u)
#define PWMBacklight_CMD_STOP                       (16u)
#define PWMBacklight_CMD_START                      (24u)

/* Status */
#define PWMBacklight_STATUS_DOWN                    (1u)
#define PWMBacklight_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   PWMBacklight_Init(void);
void   PWMBacklight_Enable(void);
void   PWMBacklight_Start(void);
void   PWMBacklight_Stop(void);

void   PWMBacklight_SetMode(uint32 mode);
void   PWMBacklight_SetCounterMode(uint32 counterMode);
void   PWMBacklight_SetPWMMode(uint32 modeMask);
void   PWMBacklight_SetQDMode(uint32 qdMode);

void   PWMBacklight_SetPrescaler(uint32 prescaler);
void   PWMBacklight_TriggerCommand(uint32 mask, uint32 command);
void   PWMBacklight_SetOneShot(uint32 oneShotEnable);
uint32 PWMBacklight_ReadStatus(void);

void   PWMBacklight_SetPWMSyncKill(uint32 syncKillEnable);
void   PWMBacklight_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   PWMBacklight_SetPWMDeadTime(uint32 deadTime);
void   PWMBacklight_SetPWMInvert(uint32 mask);

void   PWMBacklight_SetInterruptMode(uint32 interruptMask);
uint32 PWMBacklight_GetInterruptSourceMasked(void);
uint32 PWMBacklight_GetInterruptSource(void);
void   PWMBacklight_ClearInterrupt(uint32 interruptMask);
void   PWMBacklight_SetInterrupt(uint32 interruptMask);

void   PWMBacklight_WriteCounter(uint32 count);
uint32 PWMBacklight_ReadCounter(void);

uint32 PWMBacklight_ReadCapture(void);
uint32 PWMBacklight_ReadCaptureBuf(void);

void   PWMBacklight_WritePeriod(uint32 period);
uint32 PWMBacklight_ReadPeriod(void);
void   PWMBacklight_WritePeriodBuf(uint32 periodBuf);
uint32 PWMBacklight_ReadPeriodBuf(void);

void   PWMBacklight_WriteCompare(uint32 compare);
uint32 PWMBacklight_ReadCompare(void);
void   PWMBacklight_WriteCompareBuf(uint32 compareBuf);
uint32 PWMBacklight_ReadCompareBuf(void);

void   PWMBacklight_SetPeriodSwap(uint32 swapEnable);
void   PWMBacklight_SetCompareSwap(uint32 swapEnable);

void   PWMBacklight_SetCaptureMode(uint32 triggerMode);
void   PWMBacklight_SetReloadMode(uint32 triggerMode);
void   PWMBacklight_SetStartMode(uint32 triggerMode);
void   PWMBacklight_SetStopMode(uint32 triggerMode);
void   PWMBacklight_SetCountMode(uint32 triggerMode);

void   PWMBacklight_SaveConfig(void);
void   PWMBacklight_RestoreConfig(void);
void   PWMBacklight_Sleep(void);
void   PWMBacklight_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define PWMBacklight_BLOCK_CONTROL_REG              (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWMBacklight_BLOCK_CONTROL_PTR              ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWMBacklight_COMMAND_REG                    (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWMBacklight_COMMAND_PTR                    ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWMBacklight_INTRRUPT_CAUSE_REG             (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWMBacklight_INTRRUPT_CAUSE_PTR             ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWMBacklight_CONTROL_REG                    (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__CTRL )
#define PWMBacklight_CONTROL_PTR                    ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__CTRL )
#define PWMBacklight_STATUS_REG                     (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__STATUS )
#define PWMBacklight_STATUS_PTR                     ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__STATUS )
#define PWMBacklight_COUNTER_REG                    (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__COUNTER )
#define PWMBacklight_COUNTER_PTR                    ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__COUNTER )
#define PWMBacklight_COMP_CAP_REG                   (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__CC )
#define PWMBacklight_COMP_CAP_PTR                   ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__CC )
#define PWMBacklight_COMP_CAP_BUF_REG               (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWMBacklight_COMP_CAP_BUF_PTR               ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWMBacklight_PERIOD_REG                     (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__PERIOD )
#define PWMBacklight_PERIOD_PTR                     ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__PERIOD )
#define PWMBacklight_PERIOD_BUF_REG                 (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWMBacklight_PERIOD_BUF_PTR                 ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWMBacklight_TRIG_CONTROL0_REG              (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWMBacklight_TRIG_CONTROL0_PTR              ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWMBacklight_TRIG_CONTROL1_REG              (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWMBacklight_TRIG_CONTROL1_PTR              ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWMBacklight_TRIG_CONTROL2_REG              (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWMBacklight_TRIG_CONTROL2_PTR              ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWMBacklight_INTERRUPT_REQ_REG              (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__INTR )
#define PWMBacklight_INTERRUPT_REQ_PTR              ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__INTR )
#define PWMBacklight_INTERRUPT_SET_REG              (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__INTR_SET )
#define PWMBacklight_INTERRUPT_SET_PTR              ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__INTR_SET )
#define PWMBacklight_INTERRUPT_MASK_REG             (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWMBacklight_INTERRUPT_MASK_PTR             ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWMBacklight_INTERRUPT_MASKED_REG           (*(reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__INTR_MASKED )
#define PWMBacklight_INTERRUPT_MASKED_PTR           ( (reg32 *) PWMBacklight_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define PWMBacklight_MASK                           ((uint32)PWMBacklight_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define PWMBacklight_RELOAD_CC_SHIFT                (0u)
#define PWMBacklight_RELOAD_PERIOD_SHIFT            (1u)
#define PWMBacklight_PWM_SYNC_KILL_SHIFT            (2u)
#define PWMBacklight_PWM_STOP_KILL_SHIFT            (3u)
#define PWMBacklight_PRESCALER_SHIFT                (8u)
#define PWMBacklight_UPDOWN_SHIFT                   (16u)
#define PWMBacklight_ONESHOT_SHIFT                  (18u)
#define PWMBacklight_QUAD_MODE_SHIFT                (20u)
#define PWMBacklight_INV_OUT_SHIFT                  (20u)
#define PWMBacklight_INV_COMPL_OUT_SHIFT            (21u)
#define PWMBacklight_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define PWMBacklight_RELOAD_CC_MASK                 ((uint32)(PWMBacklight_1BIT_MASK        <<  \
                                                                            PWMBacklight_RELOAD_CC_SHIFT))
#define PWMBacklight_RELOAD_PERIOD_MASK             ((uint32)(PWMBacklight_1BIT_MASK        <<  \
                                                                            PWMBacklight_RELOAD_PERIOD_SHIFT))
#define PWMBacklight_PWM_SYNC_KILL_MASK             ((uint32)(PWMBacklight_1BIT_MASK        <<  \
                                                                            PWMBacklight_PWM_SYNC_KILL_SHIFT))
#define PWMBacklight_PWM_STOP_KILL_MASK             ((uint32)(PWMBacklight_1BIT_MASK        <<  \
                                                                            PWMBacklight_PWM_STOP_KILL_SHIFT))
#define PWMBacklight_PRESCALER_MASK                 ((uint32)(PWMBacklight_8BIT_MASK        <<  \
                                                                            PWMBacklight_PRESCALER_SHIFT))
#define PWMBacklight_UPDOWN_MASK                    ((uint32)(PWMBacklight_2BIT_MASK        <<  \
                                                                            PWMBacklight_UPDOWN_SHIFT))
#define PWMBacklight_ONESHOT_MASK                   ((uint32)(PWMBacklight_1BIT_MASK        <<  \
                                                                            PWMBacklight_ONESHOT_SHIFT))
#define PWMBacklight_QUAD_MODE_MASK                 ((uint32)(PWMBacklight_3BIT_MASK        <<  \
                                                                            PWMBacklight_QUAD_MODE_SHIFT))
#define PWMBacklight_INV_OUT_MASK                   ((uint32)(PWMBacklight_2BIT_MASK        <<  \
                                                                            PWMBacklight_INV_OUT_SHIFT))
#define PWMBacklight_MODE_MASK                      ((uint32)(PWMBacklight_3BIT_MASK        <<  \
                                                                            PWMBacklight_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define PWMBacklight_CAPTURE_SHIFT                  (0u)
#define PWMBacklight_COUNT_SHIFT                    (2u)
#define PWMBacklight_RELOAD_SHIFT                   (4u)
#define PWMBacklight_STOP_SHIFT                     (6u)
#define PWMBacklight_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define PWMBacklight_CAPTURE_MASK                   ((uint32)(PWMBacklight_2BIT_MASK        <<  \
                                                                  PWMBacklight_CAPTURE_SHIFT))
#define PWMBacklight_COUNT_MASK                     ((uint32)(PWMBacklight_2BIT_MASK        <<  \
                                                                  PWMBacklight_COUNT_SHIFT))
#define PWMBacklight_RELOAD_MASK                    ((uint32)(PWMBacklight_2BIT_MASK        <<  \
                                                                  PWMBacklight_RELOAD_SHIFT))
#define PWMBacklight_STOP_MASK                      ((uint32)(PWMBacklight_2BIT_MASK        <<  \
                                                                  PWMBacklight_STOP_SHIFT))
#define PWMBacklight_START_MASK                     ((uint32)(PWMBacklight_2BIT_MASK        <<  \
                                                                  PWMBacklight_START_SHIFT))

/* MASK */
#define PWMBacklight_1BIT_MASK                      ((uint32)0x01u)
#define PWMBacklight_2BIT_MASK                      ((uint32)0x03u)
#define PWMBacklight_3BIT_MASK                      ((uint32)0x07u)
#define PWMBacklight_6BIT_MASK                      ((uint32)0x3Fu)
#define PWMBacklight_8BIT_MASK                      ((uint32)0xFFu)
#define PWMBacklight_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define PWMBacklight_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define PWMBacklight_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(PWMBacklight_QUAD_ENCODING_MODES     << PWMBacklight_QUAD_MODE_SHIFT))       |\
         ((uint32)(PWMBacklight_CONFIG                  << PWMBacklight_MODE_SHIFT)))

#define PWMBacklight_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(PWMBacklight_PWM_STOP_EVENT          << PWMBacklight_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(PWMBacklight_PWM_OUT_INVERT          << PWMBacklight_INV_OUT_SHIFT))         |\
         ((uint32)(PWMBacklight_PWM_OUT_N_INVERT        << PWMBacklight_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(PWMBacklight_PWM_MODE                << PWMBacklight_MODE_SHIFT)))

#define PWMBacklight_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(PWMBacklight_PWM_RUN_MODE         << PWMBacklight_ONESHOT_SHIFT))
            
#define PWMBacklight_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(PWMBacklight_PWM_ALIGN            << PWMBacklight_UPDOWN_SHIFT))

#define PWMBacklight_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(PWMBacklight_PWM_KILL_EVENT      << PWMBacklight_PWM_SYNC_KILL_SHIFT))

#define PWMBacklight_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(PWMBacklight_PWM_DEAD_TIME_CYCLE  << PWMBacklight_PRESCALER_SHIFT))

#define PWMBacklight_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(PWMBacklight_PWM_PRESCALER        << PWMBacklight_PRESCALER_SHIFT))

#define PWMBacklight_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(PWMBacklight_TC_PRESCALER            << PWMBacklight_PRESCALER_SHIFT))       |\
         ((uint32)(PWMBacklight_TC_COUNTER_MODE         << PWMBacklight_UPDOWN_SHIFT))          |\
         ((uint32)(PWMBacklight_TC_RUN_MODE             << PWMBacklight_ONESHOT_SHIFT))         |\
         ((uint32)(PWMBacklight_TC_COMP_CAP_MODE        << PWMBacklight_MODE_SHIFT)))
        
#define PWMBacklight_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(PWMBacklight_QUAD_PHIA_SIGNAL_MODE   << PWMBacklight_COUNT_SHIFT))           |\
         ((uint32)(PWMBacklight_QUAD_INDEX_SIGNAL_MODE  << PWMBacklight_RELOAD_SHIFT))          |\
         ((uint32)(PWMBacklight_QUAD_STOP_SIGNAL_MODE   << PWMBacklight_STOP_SHIFT))            |\
         ((uint32)(PWMBacklight_QUAD_PHIB_SIGNAL_MODE   << PWMBacklight_START_SHIFT)))

#define PWMBacklight_PWM_SIGNALS_MODES                                                              \
        (((uint32)(PWMBacklight_PWM_SWITCH_SIGNAL_MODE  << PWMBacklight_CAPTURE_SHIFT))         |\
         ((uint32)(PWMBacklight_PWM_COUNT_SIGNAL_MODE   << PWMBacklight_COUNT_SHIFT))           |\
         ((uint32)(PWMBacklight_PWM_RELOAD_SIGNAL_MODE  << PWMBacklight_RELOAD_SHIFT))          |\
         ((uint32)(PWMBacklight_PWM_STOP_SIGNAL_MODE    << PWMBacklight_STOP_SHIFT))            |\
         ((uint32)(PWMBacklight_PWM_START_SIGNAL_MODE   << PWMBacklight_START_SHIFT)))

#define PWMBacklight_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(PWMBacklight_TC_CAPTURE_SIGNAL_MODE  << PWMBacklight_CAPTURE_SHIFT))         |\
         ((uint32)(PWMBacklight_TC_COUNT_SIGNAL_MODE    << PWMBacklight_COUNT_SHIFT))           |\
         ((uint32)(PWMBacklight_TC_RELOAD_SIGNAL_MODE   << PWMBacklight_RELOAD_SHIFT))          |\
         ((uint32)(PWMBacklight_TC_STOP_SIGNAL_MODE     << PWMBacklight_STOP_SHIFT))            |\
         ((uint32)(PWMBacklight_TC_START_SIGNAL_MODE    << PWMBacklight_START_SHIFT)))
        
#define PWMBacklight_TIMER_UPDOWN_CNT_USED                                                          \
                ((PWMBacklight__COUNT_UPDOWN0 == PWMBacklight_TC_COUNTER_MODE)                  ||\
                 (PWMBacklight__COUNT_UPDOWN1 == PWMBacklight_TC_COUNTER_MODE))

#define PWMBacklight_PWM_UPDOWN_CNT_USED                                                            \
                ((PWMBacklight__CENTER == PWMBacklight_PWM_ALIGN)                               ||\
                 (PWMBacklight__ASYMMETRIC == PWMBacklight_PWM_ALIGN))               
        
#define PWMBacklight_PWM_PR_INIT_VALUE              (1u)
#define PWMBacklight_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_PWMBacklight_H */

/* [] END OF FILE */
