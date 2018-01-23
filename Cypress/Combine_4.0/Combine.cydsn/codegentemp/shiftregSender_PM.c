/*******************************************************************************
* File Name: shiftregSender_PM.c
* Version 2.30
*
* Description:
*  This file provides the API source code for sleep mode support for Shift
*  Register component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "shiftregSender.h"

static shiftregSender_BACKUP_STRUCT shiftregSender_backup =
{
    shiftregSender_DISABLED,

    ((uint8) shiftregSender_DEFAULT_A0),
    ((uint8) shiftregSender_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint8) shiftregSender_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: shiftregSender_SaveConfig
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
void shiftregSender_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    shiftregSender_backup.saveSrA0Reg   = CY_GET_REG8(shiftregSender_SHIFT_REG_LSB_PTR);
    shiftregSender_backup.saveSrA1Reg   = CY_GET_REG8(shiftregSender_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        shiftregSender_backup.saveSrIntMask = shiftregSender_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: shiftregSender_RestoreConfig
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
void shiftregSender_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG8(shiftregSender_SHIFT_REG_LSB_PTR, shiftregSender_backup.saveSrA0Reg);
    CY_SET_REG8(shiftregSender_SHIFT_REG_VALUE_LSB_PTR, shiftregSender_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        shiftregSender_SR_STATUS_MASK = ((uint8) shiftregSender_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: shiftregSender_Sleep
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
void shiftregSender_Sleep(void) 
{
    shiftregSender_backup.enableState = ((uint8) shiftregSender_IS_ENABLED);

    shiftregSender_Stop();
    shiftregSender_SaveConfig();
}


/*******************************************************************************
* Function Name: shiftregSender_Wakeup
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
void shiftregSender_Wakeup(void) 
{
    shiftregSender_RestoreConfig();

    if(0u != shiftregSender_backup.enableState)
    {
        shiftregSender_Enable();
    }
}


/* [] END OF FILE */
