/*******************************************************************************
* File Name: dacFan_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "dacFan.h"

static dacFan_backupStruct dacFan_backup;


/*******************************************************************************
* Function Name: dacFan_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void dacFan_SaveConfig(void) 
{
    if (!((dacFan_CR1 & dacFan_SRC_MASK) == dacFan_SRC_UDB))
    {
        dacFan_backup.data_value = dacFan_Data;
    }
}


/*******************************************************************************
* Function Name: dacFan_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void dacFan_RestoreConfig(void) 
{
    if (!((dacFan_CR1 & dacFan_SRC_MASK) == dacFan_SRC_UDB))
    {
        if((dacFan_Strobe & dacFan_STRB_MASK) == dacFan_STRB_EN)
        {
            dacFan_Strobe &= (uint8)(~dacFan_STRB_MASK);
            dacFan_Data = dacFan_backup.data_value;
            dacFan_Strobe |= dacFan_STRB_EN;
        }
        else
        {
            dacFan_Data = dacFan_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: dacFan_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  dacFan_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void dacFan_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(dacFan_ACT_PWR_EN == (dacFan_PWRMGR & dacFan_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        dacFan_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        dacFan_backup.enableState = 0u;
    }
    
    dacFan_Stop();
    dacFan_SaveConfig();
}


/*******************************************************************************
* Function Name: dacFan_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  dacFan_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void dacFan_Wakeup(void) 
{
    dacFan_RestoreConfig();
    
    if(dacFan_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        dacFan_Enable();

        /* Restore the data register */
        dacFan_SetValue(dacFan_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
