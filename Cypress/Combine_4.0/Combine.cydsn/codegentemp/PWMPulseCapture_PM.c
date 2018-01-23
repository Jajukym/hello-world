/*******************************************************************************
* File Name: PWMPulseCapture_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWMPulseCapture.h"

static PWMPulseCapture_backupStruct PWMPulseCapture_backup;


/*******************************************************************************
* Function Name: PWMPulseCapture_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMPulseCapture_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWMPulseCapture_SaveConfig(void) 
{

    #if(!PWMPulseCapture_UsingFixedFunction)
        #if(!PWMPulseCapture_PWMModeIsCenterAligned)
            PWMPulseCapture_backup.PWMPeriod = PWMPulseCapture_ReadPeriod();
        #endif /* (!PWMPulseCapture_PWMModeIsCenterAligned) */
        PWMPulseCapture_backup.PWMUdb = PWMPulseCapture_ReadCounter();
        #if (PWMPulseCapture_UseStatus)
            PWMPulseCapture_backup.InterruptMaskValue = PWMPulseCapture_STATUS_MASK;
        #endif /* (PWMPulseCapture_UseStatus) */

        #if(PWMPulseCapture_DeadBandMode == PWMPulseCapture__B_PWM__DBM_256_CLOCKS || \
            PWMPulseCapture_DeadBandMode == PWMPulseCapture__B_PWM__DBM_2_4_CLOCKS)
            PWMPulseCapture_backup.PWMdeadBandValue = PWMPulseCapture_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWMPulseCapture_KillModeMinTime)
             PWMPulseCapture_backup.PWMKillCounterPeriod = PWMPulseCapture_ReadKillTime();
        #endif /* (PWMPulseCapture_KillModeMinTime) */

        #if(PWMPulseCapture_UseControl)
            PWMPulseCapture_backup.PWMControlRegister = PWMPulseCapture_ReadControlRegister();
        #endif /* (PWMPulseCapture_UseControl) */
    #endif  /* (!PWMPulseCapture_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWMPulseCapture_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMPulseCapture_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWMPulseCapture_RestoreConfig(void) 
{
        #if(!PWMPulseCapture_UsingFixedFunction)
            #if(!PWMPulseCapture_PWMModeIsCenterAligned)
                PWMPulseCapture_WritePeriod(PWMPulseCapture_backup.PWMPeriod);
            #endif /* (!PWMPulseCapture_PWMModeIsCenterAligned) */

            PWMPulseCapture_WriteCounter(PWMPulseCapture_backup.PWMUdb);

            #if (PWMPulseCapture_UseStatus)
                PWMPulseCapture_STATUS_MASK = PWMPulseCapture_backup.InterruptMaskValue;
            #endif /* (PWMPulseCapture_UseStatus) */

            #if(PWMPulseCapture_DeadBandMode == PWMPulseCapture__B_PWM__DBM_256_CLOCKS || \
                PWMPulseCapture_DeadBandMode == PWMPulseCapture__B_PWM__DBM_2_4_CLOCKS)
                PWMPulseCapture_WriteDeadTime(PWMPulseCapture_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWMPulseCapture_KillModeMinTime)
                PWMPulseCapture_WriteKillTime(PWMPulseCapture_backup.PWMKillCounterPeriod);
            #endif /* (PWMPulseCapture_KillModeMinTime) */

            #if(PWMPulseCapture_UseControl)
                PWMPulseCapture_WriteControlRegister(PWMPulseCapture_backup.PWMControlRegister);
            #endif /* (PWMPulseCapture_UseControl) */
        #endif  /* (!PWMPulseCapture_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWMPulseCapture_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMPulseCapture_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWMPulseCapture_Sleep(void) 
{
    #if(PWMPulseCapture_UseControl)
        if(PWMPulseCapture_CTRL_ENABLE == (PWMPulseCapture_CONTROL & PWMPulseCapture_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWMPulseCapture_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWMPulseCapture_backup.PWMEnableState = 0u;
        }
    #endif /* (PWMPulseCapture_UseControl) */

    /* Stop component */
    PWMPulseCapture_Stop();

    /* Save registers configuration */
    PWMPulseCapture_SaveConfig();
}


/*******************************************************************************
* Function Name: PWMPulseCapture_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWMPulseCapture_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWMPulseCapture_Wakeup(void) 
{
     /* Restore registers values */
    PWMPulseCapture_RestoreConfig();

    if(PWMPulseCapture_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWMPulseCapture_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
