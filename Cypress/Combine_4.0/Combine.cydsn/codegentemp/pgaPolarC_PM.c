/*******************************************************************************
* File Name: pgaPolarC_PM.c  
* Version 2.0
*
* Description:
*  This file provides the power manager source code to the API for PGA 
*  Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "pgaPolarC.h"

static pgaPolarC_BACKUP_STRUCT  pgaPolarC_backup;


/*******************************************************************************
* Function Name: pgaPolarC_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user register configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void pgaPolarC_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: pgaPolarC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void pgaPolarC_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: pgaPolarC_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  pgaPolarC_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void pgaPolarC_Sleep(void) 
{
    /* Save PGA enable state */
    if((pgaPolarC_PM_ACT_CFG_REG & pgaPolarC_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        pgaPolarC_backup.enableState = 1u;
        /* Stop the configuration */
        pgaPolarC_Stop();
    }
    else
    {
        /* Component is disabled */
        pgaPolarC_backup.enableState = 0u;
    }
    /* Save the configuration */
    pgaPolarC_SaveConfig();
}


/*******************************************************************************
* Function Name: pgaPolarC_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  void
*
* Global variables:
*  pgaPolarC_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
* 
*******************************************************************************/
void pgaPolarC_Wakeup(void) 
{
    /* Restore the configurations */
    pgaPolarC_RestoreConfig();
     /* Enables the component operation */
    if(pgaPolarC_backup.enableState == 1u)
    {
        pgaPolarC_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
