/*******************************************************************************
* File Name: LED_CONTROL_1_PM.c
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

#include "LED_CONTROL_1.h"

static LED_CONTROL_1_BACKUP_STRUCT LED_CONTROL_1_backup;


/*******************************************************************************
* Function Name: LED_CONTROL_1_SaveConfig
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
void LED_CONTROL_1_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: LED_CONTROL_1_Sleep
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
void LED_CONTROL_1_Sleep(void)
{
    if(0u != (LED_CONTROL_1_BLOCK_CONTROL_REG & LED_CONTROL_1_MASK))
    {
        LED_CONTROL_1_backup.enableState = 1u;
    }
    else
    {
        LED_CONTROL_1_backup.enableState = 0u;
    }

    LED_CONTROL_1_Stop();
    LED_CONTROL_1_SaveConfig();
}


/*******************************************************************************
* Function Name: LED_CONTROL_1_RestoreConfig
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
void LED_CONTROL_1_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: LED_CONTROL_1_Wakeup
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
void LED_CONTROL_1_Wakeup(void)
{
    LED_CONTROL_1_RestoreConfig();

    if(0u != LED_CONTROL_1_backup.enableState)
    {
        LED_CONTROL_1_Enable();
    }
}


/* [] END OF FILE */
