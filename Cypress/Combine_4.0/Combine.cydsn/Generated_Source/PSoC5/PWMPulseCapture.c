/*******************************************************************************
* File Name: PWMPulseCapture.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "PWMPulseCapture.h"

/* Error message for removed <resource> through optimization */
#ifdef PWMPulseCapture_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* PWMPulseCapture_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 PWMPulseCapture_initVar = 0u;


/*******************************************************************************
* Function Name: PWMPulseCapture_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMPulseCapture_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void PWMPulseCapture_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(PWMPulseCapture_initVar == 0u)
    {
        PWMPulseCapture_Init();
        PWMPulseCapture_initVar = 1u;
    }
    PWMPulseCapture_Enable();

}


/*******************************************************************************
* Function Name: PWMPulseCapture_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  PWMPulseCapture_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMPulseCapture_Init(void) 
{
    #if (PWMPulseCapture_UsingFixedFunction || PWMPulseCapture_UseControl)
        uint8 ctrl;
    #endif /* (PWMPulseCapture_UsingFixedFunction || PWMPulseCapture_UseControl) */

    #if(!PWMPulseCapture_UsingFixedFunction)
        #if(PWMPulseCapture_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 PWMPulseCapture_interruptState;
        #endif /* (PWMPulseCapture_UseStatus) */
    #endif /* (!PWMPulseCapture_UsingFixedFunction) */

    #if (PWMPulseCapture_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        PWMPulseCapture_CONTROL |= PWMPulseCapture_CFG0_MODE;
        #if (PWMPulseCapture_DeadBand2_4)
            PWMPulseCapture_CONTROL |= PWMPulseCapture_CFG0_DB;
        #endif /* (PWMPulseCapture_DeadBand2_4) */

        ctrl = PWMPulseCapture_CONTROL3 & ((uint8 )(~PWMPulseCapture_CTRL_CMPMODE1_MASK));
        PWMPulseCapture_CONTROL3 = ctrl | PWMPulseCapture_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        PWMPulseCapture_RT1 &= ((uint8)(~PWMPulseCapture_RT1_MASK));
        PWMPulseCapture_RT1 |= PWMPulseCapture_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        PWMPulseCapture_RT1 &= ((uint8)(~PWMPulseCapture_SYNCDSI_MASK));
        PWMPulseCapture_RT1 |= PWMPulseCapture_SYNCDSI_EN;

    #elif (PWMPulseCapture_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = PWMPulseCapture_CONTROL & ((uint8)(~PWMPulseCapture_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~PWMPulseCapture_CTRL_CMPMODE1_MASK));
        PWMPulseCapture_CONTROL = ctrl | PWMPulseCapture_DEFAULT_COMPARE2_MODE |
                                   PWMPulseCapture_DEFAULT_COMPARE1_MODE;
    #endif /* (PWMPulseCapture_UsingFixedFunction) */

    #if (!PWMPulseCapture_UsingFixedFunction)
        #if (PWMPulseCapture_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            PWMPulseCapture_AUX_CONTROLDP0 |= (PWMPulseCapture_AUX_CTRL_FIFO0_CLR);
        #else /* (PWMPulseCapture_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            PWMPulseCapture_AUX_CONTROLDP0 |= (PWMPulseCapture_AUX_CTRL_FIFO0_CLR);
            PWMPulseCapture_AUX_CONTROLDP1 |= (PWMPulseCapture_AUX_CTRL_FIFO0_CLR);
        #endif /* (PWMPulseCapture_Resolution == 8) */

        PWMPulseCapture_WriteCounter(PWMPulseCapture_INIT_PERIOD_VALUE);
    #endif /* (!PWMPulseCapture_UsingFixedFunction) */

    PWMPulseCapture_WritePeriod(PWMPulseCapture_INIT_PERIOD_VALUE);

        #if (PWMPulseCapture_UseOneCompareMode)
            PWMPulseCapture_WriteCompare(PWMPulseCapture_INIT_COMPARE_VALUE1);
        #else
            PWMPulseCapture_WriteCompare1(PWMPulseCapture_INIT_COMPARE_VALUE1);
            PWMPulseCapture_WriteCompare2(PWMPulseCapture_INIT_COMPARE_VALUE2);
        #endif /* (PWMPulseCapture_UseOneCompareMode) */

        #if (PWMPulseCapture_KillModeMinTime)
            PWMPulseCapture_WriteKillTime(PWMPulseCapture_MinimumKillTime);
        #endif /* (PWMPulseCapture_KillModeMinTime) */

        #if (PWMPulseCapture_DeadBandUsed)
            PWMPulseCapture_WriteDeadTime(PWMPulseCapture_INIT_DEAD_TIME);
        #endif /* (PWMPulseCapture_DeadBandUsed) */

    #if (PWMPulseCapture_UseStatus || PWMPulseCapture_UsingFixedFunction)
        PWMPulseCapture_SetInterruptMode(PWMPulseCapture_INIT_INTERRUPTS_MODE);
    #endif /* (PWMPulseCapture_UseStatus || PWMPulseCapture_UsingFixedFunction) */

    #if (PWMPulseCapture_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        PWMPulseCapture_GLOBAL_ENABLE |= PWMPulseCapture_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        PWMPulseCapture_CONTROL2 |= PWMPulseCapture_CTRL2_IRQ_SEL;
    #else
        #if(PWMPulseCapture_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            PWMPulseCapture_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            PWMPulseCapture_STATUS_AUX_CTRL |= PWMPulseCapture_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(PWMPulseCapture_interruptState);

            /* Clear the FIFO to enable the PWMPulseCapture_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            PWMPulseCapture_ClearFIFO();
        #endif /* (PWMPulseCapture_UseStatus) */
    #endif /* (PWMPulseCapture_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWMPulseCapture_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void PWMPulseCapture_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (PWMPulseCapture_UsingFixedFunction)
        PWMPulseCapture_GLOBAL_ENABLE |= PWMPulseCapture_BLOCK_EN_MASK;
        PWMPulseCapture_GLOBAL_STBY_ENABLE |= PWMPulseCapture_BLOCK_STBY_EN_MASK;
    #endif /* (PWMPulseCapture_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (PWMPulseCapture_UseControl || PWMPulseCapture_UsingFixedFunction)
        PWMPulseCapture_CONTROL |= PWMPulseCapture_CTRL_ENABLE;
    #endif /* (PWMPulseCapture_UseControl || PWMPulseCapture_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWMPulseCapture_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void PWMPulseCapture_Stop(void) 
{
    #if (PWMPulseCapture_UseControl || PWMPulseCapture_UsingFixedFunction)
        PWMPulseCapture_CONTROL &= ((uint8)(~PWMPulseCapture_CTRL_ENABLE));
    #endif /* (PWMPulseCapture_UseControl || PWMPulseCapture_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (PWMPulseCapture_UsingFixedFunction)
        PWMPulseCapture_GLOBAL_ENABLE &= ((uint8)(~PWMPulseCapture_BLOCK_EN_MASK));
        PWMPulseCapture_GLOBAL_STBY_ENABLE &= ((uint8)(~PWMPulseCapture_BLOCK_STBY_EN_MASK));
    #endif /* (PWMPulseCapture_UsingFixedFunction) */
}

#if (PWMPulseCapture_UseOneCompareMode)
    #if (PWMPulseCapture_CompareMode1SW)


        /*******************************************************************************
        * Function Name: PWMPulseCapture_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PWMPulseCapture_SetCompareMode(uint8 comparemode) 
        {
            #if(PWMPulseCapture_UsingFixedFunction)

                #if(0 != PWMPulseCapture_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWMPulseCapture_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != PWMPulseCapture_CTRL_CMPMODE1_SHIFT) */

                PWMPulseCapture_CONTROL3 &= ((uint8)(~PWMPulseCapture_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                PWMPulseCapture_CONTROL3 |= comparemodemasked;

            #elif (PWMPulseCapture_UseControl)

                #if(0 != PWMPulseCapture_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << PWMPulseCapture_CTRL_CMPMODE1_SHIFT)) &
                                                PWMPulseCapture_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & PWMPulseCapture_CTRL_CMPMODE1_MASK;
                #endif /* (0 != PWMPulseCapture_CTRL_CMPMODE1_SHIFT) */

                #if(0 != PWMPulseCapture_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << PWMPulseCapture_CTRL_CMPMODE2_SHIFT)) &
                                               PWMPulseCapture_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & PWMPulseCapture_CTRL_CMPMODE2_MASK;
                #endif /* (0 != PWMPulseCapture_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                PWMPulseCapture_CONTROL &= ((uint8)(~(PWMPulseCapture_CTRL_CMPMODE1_MASK |
                                            PWMPulseCapture_CTRL_CMPMODE2_MASK)));
                PWMPulseCapture_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (PWMPulseCapture_UsingFixedFunction) */
        }
    #endif /* PWMPulseCapture_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (PWMPulseCapture_CompareMode1SW)


        /*******************************************************************************
        * Function Name: PWMPulseCapture_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PWMPulseCapture_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != PWMPulseCapture_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWMPulseCapture_CTRL_CMPMODE1_SHIFT)) &
                                           PWMPulseCapture_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & PWMPulseCapture_CTRL_CMPMODE1_MASK;
            #endif /* (0 != PWMPulseCapture_CTRL_CMPMODE1_SHIFT) */

            #if (PWMPulseCapture_UseControl)
                PWMPulseCapture_CONTROL &= ((uint8)(~PWMPulseCapture_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                PWMPulseCapture_CONTROL |= comparemodemasked;
            #endif /* (PWMPulseCapture_UseControl) */
        }
    #endif /* PWMPulseCapture_CompareMode1SW */

#if (PWMPulseCapture_CompareMode2SW)


    /*******************************************************************************
    * Function Name: PWMPulseCapture_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWMPulseCapture_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != PWMPulseCapture_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << PWMPulseCapture_CTRL_CMPMODE2_SHIFT)) &
                                                 PWMPulseCapture_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & PWMPulseCapture_CTRL_CMPMODE2_MASK;
        #endif /* (0 != PWMPulseCapture_CTRL_CMPMODE2_SHIFT) */

        #if (PWMPulseCapture_UseControl)
            PWMPulseCapture_CONTROL &= ((uint8)(~PWMPulseCapture_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            PWMPulseCapture_CONTROL |= comparemodemasked;
        #endif /* (PWMPulseCapture_UseControl) */
    }
    #endif /*PWMPulseCapture_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!PWMPulseCapture_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWMPulseCapture_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void PWMPulseCapture_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(PWMPulseCapture_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: PWMPulseCapture_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 PWMPulseCapture_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(PWMPulseCapture_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(PWMPulseCapture_CAPTURE_LSB_PTR));
    }

    #if (PWMPulseCapture_UseStatus)


        /*******************************************************************************
        * Function Name: PWMPulseCapture_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void PWMPulseCapture_ClearFIFO(void) 
        {
            while(0u != (PWMPulseCapture_ReadStatusRegister() & PWMPulseCapture_STATUS_FIFONEMPTY))
            {
                (void)PWMPulseCapture_ReadCapture();
            }
        }

    #endif /* PWMPulseCapture_UseStatus */

#endif /* !PWMPulseCapture_UsingFixedFunction */


/*******************************************************************************
* Function Name: PWMPulseCapture_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void PWMPulseCapture_WritePeriod(uint16 period) 
{
    #if(PWMPulseCapture_UsingFixedFunction)
        CY_SET_REG16(PWMPulseCapture_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(PWMPulseCapture_PERIOD_LSB_PTR, period);
    #endif /* (PWMPulseCapture_UsingFixedFunction) */
}

#if (PWMPulseCapture_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: PWMPulseCapture_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void PWMPulseCapture_WriteCompare(uint16 compare) \
                                       
    {
        #if(PWMPulseCapture_UsingFixedFunction)
            CY_SET_REG16(PWMPulseCapture_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(PWMPulseCapture_COMPARE1_LSB_PTR, compare);
        #endif /* (PWMPulseCapture_UsingFixedFunction) */

        #if (PWMPulseCapture_PWMMode == PWMPulseCapture__B_PWM__DITHER)
            #if(PWMPulseCapture_UsingFixedFunction)
                CY_SET_REG16(PWMPulseCapture_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(PWMPulseCapture_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (PWMPulseCapture_UsingFixedFunction) */
        #endif /* (PWMPulseCapture_PWMMode == PWMPulseCapture__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: PWMPulseCapture_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWMPulseCapture_WriteCompare1(uint16 compare) \
                                        
    {
        #if(PWMPulseCapture_UsingFixedFunction)
            CY_SET_REG16(PWMPulseCapture_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(PWMPulseCapture_COMPARE1_LSB_PTR, compare);
        #endif /* (PWMPulseCapture_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: PWMPulseCapture_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWMPulseCapture_WriteCompare2(uint16 compare) \
                                        
    {
        #if(PWMPulseCapture_UsingFixedFunction)
            CY_SET_REG16(PWMPulseCapture_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(PWMPulseCapture_COMPARE2_LSB_PTR, compare);
        #endif /* (PWMPulseCapture_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (PWMPulseCapture_DeadBandUsed)


    /*******************************************************************************
    * Function Name: PWMPulseCapture_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWMPulseCapture_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!PWMPulseCapture_DeadBand2_4)
            CY_SET_REG8(PWMPulseCapture_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            PWMPulseCapture_DEADBAND_COUNT &= ((uint8)(~PWMPulseCapture_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(PWMPulseCapture_DEADBAND_COUNT_SHIFT)
                PWMPulseCapture_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << PWMPulseCapture_DEADBAND_COUNT_SHIFT)) &
                                                    PWMPulseCapture_DEADBAND_COUNT_MASK;
            #else
                PWMPulseCapture_DEADBAND_COUNT |= deadtime & PWMPulseCapture_DEADBAND_COUNT_MASK;
            #endif /* (PWMPulseCapture_DEADBAND_COUNT_SHIFT) */

        #endif /* (!PWMPulseCapture_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: PWMPulseCapture_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 PWMPulseCapture_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!PWMPulseCapture_DeadBand2_4)
            return (CY_GET_REG8(PWMPulseCapture_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(PWMPulseCapture_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(PWMPulseCapture_DEADBAND_COUNT & PWMPulseCapture_DEADBAND_COUNT_MASK)) >>
                                                                           PWMPulseCapture_DEADBAND_COUNT_SHIFT));
            #else
                return (PWMPulseCapture_DEADBAND_COUNT & PWMPulseCapture_DEADBAND_COUNT_MASK);
            #endif /* (PWMPulseCapture_DEADBAND_COUNT_SHIFT) */
        #endif /* (!PWMPulseCapture_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (PWMPulseCapture_UseStatus || PWMPulseCapture_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWMPulseCapture_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWMPulseCapture_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(PWMPulseCapture_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: PWMPulseCapture_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 PWMPulseCapture_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(PWMPulseCapture_STATUS_PTR));
    }

#endif /* (PWMPulseCapture_UseStatus || PWMPulseCapture_UsingFixedFunction) */


#if (PWMPulseCapture_UseControl)


    /*******************************************************************************
    * Function Name: PWMPulseCapture_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 PWMPulseCapture_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(PWMPulseCapture_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: PWMPulseCapture_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWMPulseCapture_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(PWMPulseCapture_CONTROL_PTR, control);
    }

#endif /* (PWMPulseCapture_UseControl) */


#if (!PWMPulseCapture_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: PWMPulseCapture_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 PWMPulseCapture_ReadCapture(void) 
    {
        return (CY_GET_REG16(PWMPulseCapture_CAPTURE_LSB_PTR));
    }

#endif /* (!PWMPulseCapture_UsingFixedFunction) */


#if (PWMPulseCapture_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: PWMPulseCapture_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 PWMPulseCapture_ReadCompare(void) 
    {
        #if(PWMPulseCapture_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(PWMPulseCapture_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(PWMPulseCapture_COMPARE1_LSB_PTR));
        #endif /* (PWMPulseCapture_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: PWMPulseCapture_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 PWMPulseCapture_ReadCompare1(void) 
    {
        return (CY_GET_REG16(PWMPulseCapture_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: PWMPulseCapture_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 PWMPulseCapture_ReadCompare2(void) 
    {
        return (CY_GET_REG16(PWMPulseCapture_COMPARE2_LSB_PTR));
    }

#endif /* (PWMPulseCapture_UseOneCompareMode) */


/*******************************************************************************
* Function Name: PWMPulseCapture_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 PWMPulseCapture_ReadPeriod(void) 
{
    #if(PWMPulseCapture_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(PWMPulseCapture_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(PWMPulseCapture_PERIOD_LSB_PTR));
    #endif /* (PWMPulseCapture_UsingFixedFunction) */
}

#if ( PWMPulseCapture_KillModeMinTime)


    /*******************************************************************************
    * Function Name: PWMPulseCapture_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void PWMPulseCapture_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(PWMPulseCapture_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: PWMPulseCapture_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 PWMPulseCapture_ReadKillTime(void) 
    {
        return (CY_GET_REG8(PWMPulseCapture_KILLMODEMINTIME_PTR));
    }

#endif /* ( PWMPulseCapture_KillModeMinTime) */

/* [] END OF FILE */
