/*******************************************************************************
* File Name: Receiver_PM.c
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

#include "Receiver.h"


static Receiver_BACKUP_STRUCT Receiver_backup = \
{
    /* enable state - disabled */
    0u
};


/*******************************************************************************
* Function Name: Receiver_SaveConfig
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
void Receiver_SaveConfig(void) 
{
    /* Store A0, A1 and Status Mask registers */
    #if (CY_UDB_V0)
       Receiver_backup.saveSrA0Reg   = CY_GET_REG8(Receiver_SHIFT_REG_LSB_PTR);
       Receiver_backup.saveSrA1Reg   = CY_GET_REG8(Receiver_SHIFT_REG_VALUE_LSB_PTR);
       Receiver_backup.saveSrIntMask = Receiver_SR_STATUS_MASK;

    #else
    /* Store A0, A1 only (not need to save Status Mask register  in ES3 silicon) */
       Receiver_backup.saveSrA0Reg   = CY_GET_REG8(Receiver_SHIFT_REG_LSB_PTR);
       Receiver_backup.saveSrA1Reg   = CY_GET_REG8(Receiver_SHIFT_REG_VALUE_LSB_PTR);

    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: Receiver_RestoreConfig
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
void Receiver_RestoreConfig(void) 
{
    /* Restore tha data, saved by SaveConfig()function */
    #if (CY_UDB_V0)
        CY_SET_REG8(Receiver_SHIFT_REG_LSB_PTR, Receiver_backup.saveSrA0Reg);
            CY_SET_REG8(Receiver_SHIFT_REG_VALUE_LSB_PTR, Receiver_backup.saveSrA1Reg);
            Receiver_SR_STATUS_MASK = Receiver_backup.saveSrIntMask;
    #else
            CY_SET_REG8(Receiver_SHIFT_REG_LSB_PTR, Receiver_backup.saveSrA0Reg);
            CY_SET_REG8(Receiver_SHIFT_REG_VALUE_LSB_PTR, Receiver_backup.saveSrA1Reg);

    #endif /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: Receiver_Sleep
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
void Receiver_Sleep(void) 
{
    if((Receiver_SR_CONTROL & Receiver_CLK_EN) == Receiver_CLK_EN)
    {
        Receiver_backup.enableState = 1u;
    }
    else
    {
        Receiver_backup.enableState = 0u;
    }
    
    Receiver_Stop();
    Receiver_SaveConfig();
}


/*******************************************************************************
* Function Name: Receiver_Wakeup
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
void Receiver_Wakeup(void) 
{
    Receiver_RestoreConfig();
    
    if(Receiver_backup.enableState == 1u)
    {
        Receiver_Enable();   
    }
}

/* [] END OF FILE */
