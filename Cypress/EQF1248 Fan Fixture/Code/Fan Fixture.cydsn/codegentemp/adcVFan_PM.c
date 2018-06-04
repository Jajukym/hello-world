/*******************************************************************************
* File Name: adcVFan_PM.c
* Version 3.30
*
* Description:
*  This file provides the power manager source code to the API for the
*  Delta-Sigma ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "adcVFan.h"

static adcVFan_BACKUP_STRUCT adcVFan_backup =
{
    adcVFan_DISABLED,
    adcVFan_CFG1_DEC_CR
};


/*******************************************************************************
* Function Name: adcVFan_SaveConfig
********************************************************************************
*
* Summary:
*  Save the register configuration which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  adcVFan_backup:  This global structure variable is used to store
*  configuration registers which are non retention whenever user wants to go
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void adcVFan_SaveConfig(void) 
{
    adcVFan_backup.deccr = adcVFan_DEC_CR_REG;
}


/*******************************************************************************
* Function Name: adcVFan_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  adcVFan_backup:  This global structure variable is used to restore
*  configuration registers which are non retention whenever user wants to switch
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void adcVFan_RestoreConfig(void) 
{
    adcVFan_DEC_CR_REG = adcVFan_backup.deccr;
}


/*******************************************************************************
* Function Name: adcVFan_Sleep
********************************************************************************
*
* Summary:
*  Stops the operation of the block and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  adcVFan_backup:  The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void adcVFan_Sleep(void) 
{
    /* Save ADC enable state */
    if((adcVFan_ACT_PWR_DEC_EN == (adcVFan_PWRMGR_DEC_REG & adcVFan_ACT_PWR_DEC_EN)) &&
       (adcVFan_ACT_PWR_DSM_EN == (adcVFan_PWRMGR_DSM_REG & adcVFan_ACT_PWR_DSM_EN)))
    {
        /* Component is enabled */
        adcVFan_backup.enableState = adcVFan_ENABLED;
        if((adcVFan_DEC_CR_REG & adcVFan_DEC_START_CONV) != 0u)
        {   
            /* Conversion is started */
            adcVFan_backup.enableState |= adcVFan_STARTED;
        }
		
        /* Stop the configuration */
        adcVFan_Stop();
    }
    else
    {
        /* Component is disabled */
        adcVFan_backup.enableState = adcVFan_DISABLED;
    }

    /* Save the user configuration */
    adcVFan_SaveConfig();
}


/*******************************************************************************
* Function Name: adcVFan_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and enables the power to the block.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  adcVFan_backup:  The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void adcVFan_Wakeup(void) 
{
    /* Restore the configuration */
    adcVFan_RestoreConfig();

    /* Enables the component operation */
    if(adcVFan_backup.enableState != adcVFan_DISABLED)
    {
        adcVFan_Enable();
        if((adcVFan_backup.enableState & adcVFan_STARTED) != 0u)
        {
            adcVFan_StartConvert();
        }
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
