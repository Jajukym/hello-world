/*******************************************************************************
* File Name: pwmFan2_PM.c
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

#include "pwmFan2.h"

static pwmFan2_backupStruct pwmFan2_backup;


/*******************************************************************************
* Function Name: pwmFan2_SaveConfig
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
*  pwmFan2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void pwmFan2_SaveConfig(void) 
{

    #if(!pwmFan2_UsingFixedFunction)
        #if(!pwmFan2_PWMModeIsCenterAligned)
            pwmFan2_backup.PWMPeriod = pwmFan2_ReadPeriod();
        #endif /* (!pwmFan2_PWMModeIsCenterAligned) */
        pwmFan2_backup.PWMUdb = pwmFan2_ReadCounter();
        #if (pwmFan2_UseStatus)
            pwmFan2_backup.InterruptMaskValue = pwmFan2_STATUS_MASK;
        #endif /* (pwmFan2_UseStatus) */

        #if(pwmFan2_DeadBandMode == pwmFan2__B_PWM__DBM_256_CLOCKS || \
            pwmFan2_DeadBandMode == pwmFan2__B_PWM__DBM_2_4_CLOCKS)
            pwmFan2_backup.PWMdeadBandValue = pwmFan2_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(pwmFan2_KillModeMinTime)
             pwmFan2_backup.PWMKillCounterPeriod = pwmFan2_ReadKillTime();
        #endif /* (pwmFan2_KillModeMinTime) */

        #if(pwmFan2_UseControl)
            pwmFan2_backup.PWMControlRegister = pwmFan2_ReadControlRegister();
        #endif /* (pwmFan2_UseControl) */
    #endif  /* (!pwmFan2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pwmFan2_RestoreConfig
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
*  pwmFan2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void pwmFan2_RestoreConfig(void) 
{
        #if(!pwmFan2_UsingFixedFunction)
            #if(!pwmFan2_PWMModeIsCenterAligned)
                pwmFan2_WritePeriod(pwmFan2_backup.PWMPeriod);
            #endif /* (!pwmFan2_PWMModeIsCenterAligned) */

            pwmFan2_WriteCounter(pwmFan2_backup.PWMUdb);

            #if (pwmFan2_UseStatus)
                pwmFan2_STATUS_MASK = pwmFan2_backup.InterruptMaskValue;
            #endif /* (pwmFan2_UseStatus) */

            #if(pwmFan2_DeadBandMode == pwmFan2__B_PWM__DBM_256_CLOCKS || \
                pwmFan2_DeadBandMode == pwmFan2__B_PWM__DBM_2_4_CLOCKS)
                pwmFan2_WriteDeadTime(pwmFan2_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(pwmFan2_KillModeMinTime)
                pwmFan2_WriteKillTime(pwmFan2_backup.PWMKillCounterPeriod);
            #endif /* (pwmFan2_KillModeMinTime) */

            #if(pwmFan2_UseControl)
                pwmFan2_WriteControlRegister(pwmFan2_backup.PWMControlRegister);
            #endif /* (pwmFan2_UseControl) */
        #endif  /* (!pwmFan2_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: pwmFan2_Sleep
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
*  pwmFan2_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void pwmFan2_Sleep(void) 
{
    #if(pwmFan2_UseControl)
        if(pwmFan2_CTRL_ENABLE == (pwmFan2_CONTROL & pwmFan2_CTRL_ENABLE))
        {
            /*Component is enabled */
            pwmFan2_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            pwmFan2_backup.PWMEnableState = 0u;
        }
    #endif /* (pwmFan2_UseControl) */

    /* Stop component */
    pwmFan2_Stop();

    /* Save registers configuration */
    pwmFan2_SaveConfig();
}


/*******************************************************************************
* Function Name: pwmFan2_Wakeup
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
*  pwmFan2_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void pwmFan2_Wakeup(void) 
{
     /* Restore registers values */
    pwmFan2_RestoreConfig();

    if(pwmFan2_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        pwmFan2_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
