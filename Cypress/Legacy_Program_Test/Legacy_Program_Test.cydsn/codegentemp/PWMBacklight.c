/*******************************************************************************
* File Name: PWMBacklight.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the PWMBacklight
*  component
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

#include "PWMBacklight.h"

uint8 PWMBacklight_initVar = 0u;


/*******************************************************************************
* Function Name: PWMBacklight_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default PWMBacklight configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (PWMBacklight__QUAD == PWMBacklight_CONFIG)
        PWMBacklight_CONTROL_REG = PWMBacklight_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        PWMBacklight_TRIG_CONTROL1_REG  = PWMBacklight_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        PWMBacklight_SetInterruptMode(PWMBacklight_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        PWMBacklight_SetCounterMode(PWMBacklight_COUNT_DOWN);
        PWMBacklight_WritePeriod(PWMBacklight_QUAD_PERIOD_INIT_VALUE);
        PWMBacklight_WriteCounter(PWMBacklight_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (PWMBacklight__QUAD == PWMBacklight_CONFIG) */

    #if (PWMBacklight__TIMER == PWMBacklight_CONFIG)
        PWMBacklight_CONTROL_REG = PWMBacklight_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        PWMBacklight_TRIG_CONTROL1_REG  = PWMBacklight_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        PWMBacklight_SetInterruptMode(PWMBacklight_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        PWMBacklight_WritePeriod(PWMBacklight_TC_PERIOD_VALUE );

        #if (PWMBacklight__COMPARE == PWMBacklight_TC_COMP_CAP_MODE)
            PWMBacklight_WriteCompare(PWMBacklight_TC_COMPARE_VALUE);

            #if (1u == PWMBacklight_TC_COMPARE_SWAP)
                PWMBacklight_SetCompareSwap(1u);
                PWMBacklight_WriteCompareBuf(PWMBacklight_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == PWMBacklight_TC_COMPARE_SWAP) */
        #endif  /* (PWMBacklight__COMPARE == PWMBacklight_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (PWMBacklight_CY_TCPWM_V2 && PWMBacklight_TIMER_UPDOWN_CNT_USED && !PWMBacklight_CY_TCPWM_4000)
            PWMBacklight_WriteCounter(1u);
        #elif(PWMBacklight__COUNT_DOWN == PWMBacklight_TC_COUNTER_MODE)
            PWMBacklight_WriteCounter(PWMBacklight_TC_PERIOD_VALUE);
        #else
            PWMBacklight_WriteCounter(0u);
        #endif /* (PWMBacklight_CY_TCPWM_V2 && PWMBacklight_TIMER_UPDOWN_CNT_USED && !PWMBacklight_CY_TCPWM_4000) */
    #endif  /* (PWMBacklight__TIMER == PWMBacklight_CONFIG) */

    #if (PWMBacklight__PWM_SEL == PWMBacklight_CONFIG)
        PWMBacklight_CONTROL_REG = PWMBacklight_CTRL_PWM_BASE_CONFIG;

        #if (PWMBacklight__PWM_PR == PWMBacklight_PWM_MODE)
            PWMBacklight_CONTROL_REG |= PWMBacklight_CTRL_PWM_RUN_MODE;
            PWMBacklight_WriteCounter(PWMBacklight_PWM_PR_INIT_VALUE);
        #else
            PWMBacklight_CONTROL_REG |= PWMBacklight_CTRL_PWM_ALIGN | PWMBacklight_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (PWMBacklight_CY_TCPWM_V2 && PWMBacklight_PWM_UPDOWN_CNT_USED && !PWMBacklight_CY_TCPWM_4000)
                PWMBacklight_WriteCounter(1u);
            #elif (PWMBacklight__RIGHT == PWMBacklight_PWM_ALIGN)
                PWMBacklight_WriteCounter(PWMBacklight_PWM_PERIOD_VALUE);
            #else 
                PWMBacklight_WriteCounter(0u);
            #endif  /* (PWMBacklight_CY_TCPWM_V2 && PWMBacklight_PWM_UPDOWN_CNT_USED && !PWMBacklight_CY_TCPWM_4000) */
        #endif  /* (PWMBacklight__PWM_PR == PWMBacklight_PWM_MODE) */

        #if (PWMBacklight__PWM_DT == PWMBacklight_PWM_MODE)
            PWMBacklight_CONTROL_REG |= PWMBacklight_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (PWMBacklight__PWM_DT == PWMBacklight_PWM_MODE) */

        #if (PWMBacklight__PWM == PWMBacklight_PWM_MODE)
            PWMBacklight_CONTROL_REG |= PWMBacklight_CTRL_PWM_PRESCALER;
        #endif  /* (PWMBacklight__PWM == PWMBacklight_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        PWMBacklight_TRIG_CONTROL1_REG  = PWMBacklight_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        PWMBacklight_SetInterruptMode(PWMBacklight_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (PWMBacklight__PWM_PR == PWMBacklight_PWM_MODE)
            PWMBacklight_TRIG_CONTROL2_REG =
                    (PWMBacklight_CC_MATCH_NO_CHANGE    |
                    PWMBacklight_OVERLOW_NO_CHANGE      |
                    PWMBacklight_UNDERFLOW_NO_CHANGE);
        #else
            #if (PWMBacklight__LEFT == PWMBacklight_PWM_ALIGN)
                PWMBacklight_TRIG_CONTROL2_REG = PWMBacklight_PWM_MODE_LEFT;
            #endif  /* ( PWMBacklight_PWM_LEFT == PWMBacklight_PWM_ALIGN) */

            #if (PWMBacklight__RIGHT == PWMBacklight_PWM_ALIGN)
                PWMBacklight_TRIG_CONTROL2_REG = PWMBacklight_PWM_MODE_RIGHT;
            #endif  /* ( PWMBacklight_PWM_RIGHT == PWMBacklight_PWM_ALIGN) */

            #if (PWMBacklight__CENTER == PWMBacklight_PWM_ALIGN)
                PWMBacklight_TRIG_CONTROL2_REG = PWMBacklight_PWM_MODE_CENTER;
            #endif  /* ( PWMBacklight_PWM_CENTER == PWMBacklight_PWM_ALIGN) */

            #if (PWMBacklight__ASYMMETRIC == PWMBacklight_PWM_ALIGN)
                PWMBacklight_TRIG_CONTROL2_REG = PWMBacklight_PWM_MODE_ASYM;
            #endif  /* (PWMBacklight__ASYMMETRIC == PWMBacklight_PWM_ALIGN) */
        #endif  /* (PWMBacklight__PWM_PR == PWMBacklight_PWM_MODE) */

        /* Set other values from customizer */
        PWMBacklight_WritePeriod(PWMBacklight_PWM_PERIOD_VALUE );
        PWMBacklight_WriteCompare(PWMBacklight_PWM_COMPARE_VALUE);

        #if (1u == PWMBacklight_PWM_COMPARE_SWAP)
            PWMBacklight_SetCompareSwap(1u);
            PWMBacklight_WriteCompareBuf(PWMBacklight_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == PWMBacklight_PWM_COMPARE_SWAP) */

        #if (1u == PWMBacklight_PWM_PERIOD_SWAP)
            PWMBacklight_SetPeriodSwap(1u);
            PWMBacklight_WritePeriodBuf(PWMBacklight_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == PWMBacklight_PWM_PERIOD_SWAP) */
    #endif  /* (PWMBacklight__PWM_SEL == PWMBacklight_CONFIG) */
    
}


/*******************************************************************************
* Function Name: PWMBacklight_Enable
********************************************************************************
*
* Summary:
*  Enables the PWMBacklight.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    PWMBacklight_BLOCK_CONTROL_REG |= PWMBacklight_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (PWMBacklight__PWM_SEL == PWMBacklight_CONFIG)
        #if (0u == PWMBacklight_PWM_START_SIGNAL_PRESENT)
            PWMBacklight_TriggerCommand(PWMBacklight_MASK, PWMBacklight_CMD_START);
        #endif /* (0u == PWMBacklight_PWM_START_SIGNAL_PRESENT) */
    #endif /* (PWMBacklight__PWM_SEL == PWMBacklight_CONFIG) */

    #if (PWMBacklight__TIMER == PWMBacklight_CONFIG)
        #if (0u == PWMBacklight_TC_START_SIGNAL_PRESENT)
            PWMBacklight_TriggerCommand(PWMBacklight_MASK, PWMBacklight_CMD_START);
        #endif /* (0u == PWMBacklight_TC_START_SIGNAL_PRESENT) */
    #endif /* (PWMBacklight__TIMER == PWMBacklight_CONFIG) */
    
    #if (PWMBacklight__QUAD == PWMBacklight_CONFIG)
        #if (0u != PWMBacklight_QUAD_AUTO_START)
            PWMBacklight_TriggerCommand(PWMBacklight_MASK, PWMBacklight_CMD_RELOAD);
        #endif /* (0u != PWMBacklight_QUAD_AUTO_START) */
    #endif  /* (PWMBacklight__QUAD == PWMBacklight_CONFIG) */
}


/*******************************************************************************
* Function Name: PWMBacklight_Start
********************************************************************************
*
* Summary:
*  Initializes the PWMBacklight with default customizer
*  values when called the first time and enables the PWMBacklight.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMBacklight_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time PWMBacklight_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the PWMBacklight_Start() routine.
*
*******************************************************************************/
void PWMBacklight_Start(void)
{
    if (0u == PWMBacklight_initVar)
    {
        PWMBacklight_Init();
        PWMBacklight_initVar = 1u;
    }

    PWMBacklight_Enable();
}


/*******************************************************************************
* Function Name: PWMBacklight_Stop
********************************************************************************
*
* Summary:
*  Disables the PWMBacklight.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_BLOCK_CONTROL_REG &= (uint32)~PWMBacklight_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the PWMBacklight. This function is used when
*  configured as a generic PWMBacklight and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the PWMBacklight to operate in
*   Values:
*   - PWMBacklight_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - PWMBacklight_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - PWMBacklight_MODE_QUAD - Quadrature decoder
*         - PWMBacklight_MODE_PWM - PWM
*         - PWMBacklight_MODE_PWM_DT - PWM with dead time
*         - PWMBacklight_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_CONTROL_REG &= (uint32)~PWMBacklight_MODE_MASK;
    PWMBacklight_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - PWMBacklight_MODE_X1 - Counts on phi 1 rising
*         - PWMBacklight_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - PWMBacklight_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_CONTROL_REG &= (uint32)~PWMBacklight_QUAD_MODE_MASK;
    PWMBacklight_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - PWMBacklight_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - PWMBacklight_PRESCALE_DIVBY2    - Divide by 2
*         - PWMBacklight_PRESCALE_DIVBY4    - Divide by 4
*         - PWMBacklight_PRESCALE_DIVBY8    - Divide by 8
*         - PWMBacklight_PRESCALE_DIVBY16   - Divide by 16
*         - PWMBacklight_PRESCALE_DIVBY32   - Divide by 32
*         - PWMBacklight_PRESCALE_DIVBY64   - Divide by 64
*         - PWMBacklight_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_CONTROL_REG &= (uint32)~PWMBacklight_PRESCALER_MASK;
    PWMBacklight_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWMBacklight runs
*  continuously or stops when terminal count is reached.  By default the
*  PWMBacklight operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_CONTROL_REG &= (uint32)~PWMBacklight_ONESHOT_MASK;
    PWMBacklight_CONTROL_REG |= ((uint32)((oneShotEnable & PWMBacklight_1BIT_MASK) <<
                                                               PWMBacklight_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetPWMMode(uint32 modeMask)
{
    PWMBacklight_TRIG_CONTROL2_REG = (modeMask & PWMBacklight_6BIT_MASK);
}



/*******************************************************************************
* Function Name: PWMBacklight_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_CONTROL_REG &= (uint32)~PWMBacklight_PWM_SYNC_KILL_MASK;
    PWMBacklight_CONTROL_REG |= ((uint32)((syncKillEnable & PWMBacklight_1BIT_MASK)  <<
                                               PWMBacklight_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_CONTROL_REG &= (uint32)~PWMBacklight_PWM_STOP_KILL_MASK;
    PWMBacklight_CONTROL_REG |= ((uint32)((stopOnKillEnable & PWMBacklight_1BIT_MASK)  <<
                                                         PWMBacklight_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_CONTROL_REG &= (uint32)~PWMBacklight_PRESCALER_MASK;
    PWMBacklight_CONTROL_REG |= ((uint32)((deadTime & PWMBacklight_8BIT_MASK) <<
                                                          PWMBacklight_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - PWMBacklight_INVERT_LINE   - Inverts the line output
*         - PWMBacklight_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_CONTROL_REG &= (uint32)~PWMBacklight_INV_OUT_MASK;
    PWMBacklight_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: PWMBacklight_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_WriteCounter(uint32 count)
{
    PWMBacklight_COUNTER_REG = (count & PWMBacklight_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMBacklight_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 PWMBacklight_ReadCounter(void)
{
    return (PWMBacklight_COUNTER_REG & PWMBacklight_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - PWMBacklight_COUNT_UP       - Counts up
*     - PWMBacklight_COUNT_DOWN     - Counts down
*     - PWMBacklight_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - PWMBacklight_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_CONTROL_REG &= (uint32)~PWMBacklight_UPDOWN_MASK;
    PWMBacklight_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_WritePeriod(uint32 period)
{
    PWMBacklight_PERIOD_REG = (period & PWMBacklight_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMBacklight_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 PWMBacklight_ReadPeriod(void)
{
    return (PWMBacklight_PERIOD_REG & PWMBacklight_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_CONTROL_REG &= (uint32)~PWMBacklight_RELOAD_CC_MASK;
    PWMBacklight_CONTROL_REG |= (swapEnable & PWMBacklight_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_WritePeriodBuf(uint32 periodBuf)
{
    PWMBacklight_PERIOD_BUF_REG = (periodBuf & PWMBacklight_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMBacklight_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 PWMBacklight_ReadPeriodBuf(void)
{
    return (PWMBacklight_PERIOD_BUF_REG & PWMBacklight_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_CONTROL_REG &= (uint32)~PWMBacklight_RELOAD_PERIOD_MASK;
    PWMBacklight_CONTROL_REG |= ((uint32)((swapEnable & PWMBacklight_1BIT_MASK) <<
                                                            PWMBacklight_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void PWMBacklight_WriteCompare(uint32 compare)
{
    #if (PWMBacklight_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (PWMBacklight_CY_TCPWM_4000) */

    #if (PWMBacklight_CY_TCPWM_4000)
        currentMode = ((PWMBacklight_CONTROL_REG & PWMBacklight_UPDOWN_MASK) >> PWMBacklight_UPDOWN_SHIFT);

        if (((uint32)PWMBacklight__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)PWMBacklight__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (PWMBacklight_CY_TCPWM_4000) */
    
    PWMBacklight_COMP_CAP_REG = (compare & PWMBacklight_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMBacklight_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 PWMBacklight_ReadCompare(void)
{
    #if (PWMBacklight_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (PWMBacklight_CY_TCPWM_4000) */

    #if (PWMBacklight_CY_TCPWM_4000)
        currentMode = ((PWMBacklight_CONTROL_REG & PWMBacklight_UPDOWN_MASK) >> PWMBacklight_UPDOWN_SHIFT);
        
        regVal = PWMBacklight_COMP_CAP_REG;
        
        if (((uint32)PWMBacklight__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)PWMBacklight__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & PWMBacklight_16BIT_MASK);
    #else
        return (PWMBacklight_COMP_CAP_REG & PWMBacklight_16BIT_MASK);
    #endif /* (PWMBacklight_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: PWMBacklight_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void PWMBacklight_WriteCompareBuf(uint32 compareBuf)
{
    #if (PWMBacklight_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (PWMBacklight_CY_TCPWM_4000) */

    #if (PWMBacklight_CY_TCPWM_4000)
        currentMode = ((PWMBacklight_CONTROL_REG & PWMBacklight_UPDOWN_MASK) >> PWMBacklight_UPDOWN_SHIFT);

        if (((uint32)PWMBacklight__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)PWMBacklight__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (PWMBacklight_CY_TCPWM_4000) */
    
    PWMBacklight_COMP_CAP_BUF_REG = (compareBuf & PWMBacklight_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMBacklight_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 PWMBacklight_ReadCompareBuf(void)
{
    #if (PWMBacklight_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (PWMBacklight_CY_TCPWM_4000) */

    #if (PWMBacklight_CY_TCPWM_4000)
        currentMode = ((PWMBacklight_CONTROL_REG & PWMBacklight_UPDOWN_MASK) >> PWMBacklight_UPDOWN_SHIFT);

        regVal = PWMBacklight_COMP_CAP_BUF_REG;
        
        if (((uint32)PWMBacklight__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)PWMBacklight__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & PWMBacklight_16BIT_MASK);
    #else
        return (PWMBacklight_COMP_CAP_BUF_REG & PWMBacklight_16BIT_MASK);
    #endif /* (PWMBacklight_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: PWMBacklight_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 PWMBacklight_ReadCapture(void)
{
    return (PWMBacklight_COMP_CAP_REG & PWMBacklight_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMBacklight_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 PWMBacklight_ReadCaptureBuf(void)
{
    return (PWMBacklight_COMP_CAP_BUF_REG & PWMBacklight_16BIT_MASK);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWMBacklight_TRIG_LEVEL     - Level
*     - PWMBacklight_TRIG_RISING    - Rising edge
*     - PWMBacklight_TRIG_FALLING   - Falling edge
*     - PWMBacklight_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_TRIG_CONTROL1_REG &= (uint32)~PWMBacklight_CAPTURE_MASK;
    PWMBacklight_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWMBacklight_TRIG_LEVEL     - Level
*     - PWMBacklight_TRIG_RISING    - Rising edge
*     - PWMBacklight_TRIG_FALLING   - Falling edge
*     - PWMBacklight_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_TRIG_CONTROL1_REG &= (uint32)~PWMBacklight_RELOAD_MASK;
    PWMBacklight_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWMBacklight_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWMBacklight_TRIG_LEVEL     - Level
*     - PWMBacklight_TRIG_RISING    - Rising edge
*     - PWMBacklight_TRIG_FALLING   - Falling edge
*     - PWMBacklight_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_TRIG_CONTROL1_REG &= (uint32)~PWMBacklight_START_MASK;
    PWMBacklight_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWMBacklight_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWMBacklight_TRIG_LEVEL     - Level
*     - PWMBacklight_TRIG_RISING    - Rising edge
*     - PWMBacklight_TRIG_FALLING   - Falling edge
*     - PWMBacklight_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_TRIG_CONTROL1_REG &= (uint32)~PWMBacklight_STOP_MASK;
    PWMBacklight_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWMBacklight_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - PWMBacklight_TRIG_LEVEL     - Level
*     - PWMBacklight_TRIG_RISING    - Rising edge
*     - PWMBacklight_TRIG_FALLING   - Falling edge
*     - PWMBacklight_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_TRIG_CONTROL1_REG &= (uint32)~PWMBacklight_COUNT_MASK;
    PWMBacklight_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << PWMBacklight_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - PWMBacklight_CMD_CAPTURE    - Trigger Capture/Switch command
*     - PWMBacklight_CMD_RELOAD     - Trigger Reload/Index command
*     - PWMBacklight_CMD_STOP       - Trigger Stop/Kill command
*     - PWMBacklight_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    PWMBacklight_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: PWMBacklight_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the PWMBacklight.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - PWMBacklight_STATUS_DOWN    - Set if counting down
*     - PWMBacklight_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 PWMBacklight_ReadStatus(void)
{
    return ((PWMBacklight_STATUS_REG >> PWMBacklight_RUNNING_STATUS_SHIFT) |
            (PWMBacklight_STATUS_REG & PWMBacklight_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: PWMBacklight_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - PWMBacklight_INTR_MASK_TC       - Terminal count mask
*     - PWMBacklight_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetInterruptMode(uint32 interruptMask)
{
    PWMBacklight_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: PWMBacklight_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - PWMBacklight_INTR_MASK_TC       - Terminal count mask
*     - PWMBacklight_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 PWMBacklight_GetInterruptSourceMasked(void)
{
    return (PWMBacklight_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: PWMBacklight_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - PWMBacklight_INTR_MASK_TC       - Terminal count mask
*     - PWMBacklight_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 PWMBacklight_GetInterruptSource(void)
{
    return (PWMBacklight_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: PWMBacklight_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - PWMBacklight_INTR_MASK_TC       - Terminal count mask
*     - PWMBacklight_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_ClearInterrupt(uint32 interruptMask)
{
    PWMBacklight_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: PWMBacklight_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - PWMBacklight_INTR_MASK_TC       - Terminal count mask
*     - PWMBacklight_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SetInterrupt(uint32 interruptMask)
{
    PWMBacklight_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
