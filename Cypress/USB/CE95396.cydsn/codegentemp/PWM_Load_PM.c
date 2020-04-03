/*******************************************************************************
* File Name: PWM_Load_PM.c
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

#include "PWM_Load.h"

static PWM_Load_backupStruct PWM_Load_backup;


/*******************************************************************************
* Function Name: PWM_Load_SaveConfig
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
*  PWM_Load_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Load_SaveConfig(void) 
{

    #if(!PWM_Load_UsingFixedFunction)
        #if(!PWM_Load_PWMModeIsCenterAligned)
            PWM_Load_backup.PWMPeriod = PWM_Load_ReadPeriod();
        #endif /* (!PWM_Load_PWMModeIsCenterAligned) */
        PWM_Load_backup.PWMUdb = PWM_Load_ReadCounter();
        #if (PWM_Load_UseStatus)
            PWM_Load_backup.InterruptMaskValue = PWM_Load_STATUS_MASK;
        #endif /* (PWM_Load_UseStatus) */

        #if(PWM_Load_DeadBandMode == PWM_Load__B_PWM__DBM_256_CLOCKS || \
            PWM_Load_DeadBandMode == PWM_Load__B_PWM__DBM_2_4_CLOCKS)
            PWM_Load_backup.PWMdeadBandValue = PWM_Load_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Load_KillModeMinTime)
             PWM_Load_backup.PWMKillCounterPeriod = PWM_Load_ReadKillTime();
        #endif /* (PWM_Load_KillModeMinTime) */

        #if(PWM_Load_UseControl)
            PWM_Load_backup.PWMControlRegister = PWM_Load_ReadControlRegister();
        #endif /* (PWM_Load_UseControl) */
    #endif  /* (!PWM_Load_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Load_RestoreConfig
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
*  PWM_Load_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Load_RestoreConfig(void) 
{
        #if(!PWM_Load_UsingFixedFunction)
            #if(!PWM_Load_PWMModeIsCenterAligned)
                PWM_Load_WritePeriod(PWM_Load_backup.PWMPeriod);
            #endif /* (!PWM_Load_PWMModeIsCenterAligned) */

            PWM_Load_WriteCounter(PWM_Load_backup.PWMUdb);

            #if (PWM_Load_UseStatus)
                PWM_Load_STATUS_MASK = PWM_Load_backup.InterruptMaskValue;
            #endif /* (PWM_Load_UseStatus) */

            #if(PWM_Load_DeadBandMode == PWM_Load__B_PWM__DBM_256_CLOCKS || \
                PWM_Load_DeadBandMode == PWM_Load__B_PWM__DBM_2_4_CLOCKS)
                PWM_Load_WriteDeadTime(PWM_Load_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Load_KillModeMinTime)
                PWM_Load_WriteKillTime(PWM_Load_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Load_KillModeMinTime) */

            #if(PWM_Load_UseControl)
                PWM_Load_WriteControlRegister(PWM_Load_backup.PWMControlRegister);
            #endif /* (PWM_Load_UseControl) */
        #endif  /* (!PWM_Load_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Load_Sleep
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
*  PWM_Load_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Load_Sleep(void) 
{
    #if(PWM_Load_UseControl)
        if(PWM_Load_CTRL_ENABLE == (PWM_Load_CONTROL & PWM_Load_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Load_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Load_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Load_UseControl) */

    /* Stop component */
    PWM_Load_Stop();

    /* Save registers configuration */
    PWM_Load_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Load_Wakeup
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
*  PWM_Load_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Load_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Load_RestoreConfig();

    if(PWM_Load_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Load_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
