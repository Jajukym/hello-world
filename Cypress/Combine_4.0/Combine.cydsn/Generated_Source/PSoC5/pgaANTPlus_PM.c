/*******************************************************************************
* File Name: pgaANTPlus_PM.c  
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

#include "pgaANTPlus.h"

static pgaANTPlus_BACKUP_STRUCT  pgaANTPlus_backup;


/*******************************************************************************
* Function Name: pgaANTPlus_SaveConfig
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
void pgaANTPlus_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: pgaANTPlus_RestoreConfig
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
void pgaANTPlus_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: pgaANTPlus_Sleep
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
*  pgaANTPlus_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void pgaANTPlus_Sleep(void) 
{
    /* Save PGA enable state */
    if((pgaANTPlus_PM_ACT_CFG_REG & pgaANTPlus_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        pgaANTPlus_backup.enableState = 1u;
        /* Stop the configuration */
        pgaANTPlus_Stop();
    }
    else
    {
        /* Component is disabled */
        pgaANTPlus_backup.enableState = 0u;
    }
    /* Save the configuration */
    pgaANTPlus_SaveConfig();
}


/*******************************************************************************
* Function Name: pgaANTPlus_Wakeup
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
*  pgaANTPlus_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
* 
*******************************************************************************/
void pgaANTPlus_Wakeup(void) 
{
    /* Restore the configurations */
    pgaANTPlus_RestoreConfig();
     /* Enables the component operation */
    if(pgaANTPlus_backup.enableState == 1u)
    {
        pgaANTPlus_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
