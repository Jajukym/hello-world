/*******************************************************************************
* File Name: Sender_PM.c
* Version 2.10
*
* Description:
*  This file provides the API source code for sleep mode support for Shift 
*  Register component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Sender.h"


static Sender_BACKUP_STRUCT Sender_backup = \
{
    /* enable state - disabled */
    0u
};


/*******************************************************************************
* Function Name: Sender_SaveConfig
********************************************************************************
*
* Summary:
*  Saves Shift Register configuration.
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
void Sender_SaveConfig(void) 
{
    /* Store A0, A1 and Status Mask registers */
    #if (CY_UDB_V0)
       Sender_backup.saveSrA0Reg   = CY_GET_REG8(Sender_SHIFT_REG_LSB_PTR);
       Sender_backup.saveSrA1Reg   = CY_GET_REG8(Sender_SHIFT_REG_VALUE_LSB_PTR);
       Sender_backup.saveSrIntMask = Sender_SR_STATUS_MASK;

    #else
    /* Store A0, A1 only (not need to save Status Mask register  in ES3 silicon) */
       Sender_backup.saveSrA0Reg   = CY_GET_REG8(Sender_SHIFT_REG_LSB_PTR);
       Sender_backup.saveSrA1Reg   = CY_GET_REG8(Sender_SHIFT_REG_VALUE_LSB_PTR);

    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: Sender_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Sender_RestoreConfig(void) 
{
    /* Restore tha data, saved by SaveConfig()function */
    #if (CY_UDB_V0)
        CY_SET_REG8(Sender_SHIFT_REG_LSB_PTR, Sender_backup.saveSrA0Reg);
            CY_SET_REG8(Sender_SHIFT_REG_VALUE_LSB_PTR, Sender_backup.saveSrA1Reg);
            Sender_SR_STATUS_MASK = Sender_backup.saveSrIntMask;
    #else
            CY_SET_REG8(Sender_SHIFT_REG_LSB_PTR, Sender_backup.saveSrA0Reg);
            CY_SET_REG8(Sender_SHIFT_REG_VALUE_LSB_PTR, Sender_backup.saveSrA1Reg);

    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: Sender_Sleep
********************************************************************************
*
* Summary:
*  Prepare the component to enter a Sleep mode.
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
void Sender_Sleep(void) 
{
    if((Sender_SR_CONTROL & Sender_CLK_EN) == Sender_CLK_EN)
    {
        Sender_backup.enableState = 1u;
    }
    else
    {
        Sender_backup.enableState = 0u;
    }
    
    Sender_Stop();
    Sender_SaveConfig();
}


/*******************************************************************************
* Function Name: Sender_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Sender_Wakeup(void) 
{
    Sender_RestoreConfig();
    
    if(Sender_backup.enableState == 1u)
    {
        Sender_Enable();   
    }
}

/* [] END OF FILE */
