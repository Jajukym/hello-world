/*******************************************************************************
* File Name: PWMBacklight_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
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

static PWMBacklight_BACKUP_STRUCT PWMBacklight_backup;


/*******************************************************************************
* Function Name: PWMBacklight_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: PWMBacklight_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_Sleep(void)
{
    if(0u != (PWMBacklight_BLOCK_CONTROL_REG & PWMBacklight_MASK))
    {
        PWMBacklight_backup.enableState = 1u;
    }
    else
    {
        PWMBacklight_backup.enableState = 0u;
    }

    PWMBacklight_Stop();
    PWMBacklight_SaveConfig();
}


/*******************************************************************************
* Function Name: PWMBacklight_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: PWMBacklight_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWMBacklight_Wakeup(void)
{
    PWMBacklight_RestoreConfig();

    if(0u != PWMBacklight_backup.enableState)
    {
        PWMBacklight_Enable();
    }
}


/* [] END OF FILE */
