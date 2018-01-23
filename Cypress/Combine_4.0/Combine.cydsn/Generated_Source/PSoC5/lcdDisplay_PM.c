/*******************************************************************************
* File Name: lcdDisplay_PM.c
* Version 2.20
*
* Description:
*  This file provides the API source code for the Static Segment LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "lcdDisplay.h"


static lcdDisplay_BACKUP_STRUCT lcdDisplay_backup;


/*******************************************************************************
* Function Name: lcdDisplay_SaveConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void lcdDisplay_SaveConfig(void) 
{
}


/*******************************************************************************
* Function Name: lcdDisplay_RestoreConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void lcdDisplay_RestoreConfig(void) 
{
}


/*******************************************************************************
* Function Name: lcdDisplay_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void lcdDisplay_Sleep(void) 
{
    lcdDisplay_backup.enableState = lcdDisplay_enableState;
    lcdDisplay_SaveConfig();
    lcdDisplay_Stop();
}


/*******************************************************************************
* Function Name: lcdDisplay_Wakeup
********************************************************************************
*
* Summary:
*  Wakes the component from sleep mode. Configures DMA and enables the component
*  for normal operation.
*
* Parameters:
*  lcdDisplay_enableState - Global variable.
*
* Return:
*  Status one of standard status for PSoC3 Component
*       CYRET_SUCCESS - Function completed successfully.
*       CYRET_LOCKED - The object was locked, already in use. Some of TDs or
*                      a channel already in use.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void lcdDisplay_Wakeup(void) 
{
    lcdDisplay_RestoreConfig();

    if(lcdDisplay_backup.enableState == 1u)
    {
        lcdDisplay_Enable();
    }
}


/* [] END OF FILE */
