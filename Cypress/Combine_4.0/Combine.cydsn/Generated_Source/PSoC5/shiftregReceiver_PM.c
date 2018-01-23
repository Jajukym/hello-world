/*******************************************************************************
* File Name: shiftregReceiver_PM.c
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

#include "shiftregReceiver.h"

static shiftregReceiver_BACKUP_STRUCT shiftregReceiver_backup =
{
    shiftregReceiver_DISABLED,

    ((uint8) shiftregReceiver_DEFAULT_A0),
    ((uint8) shiftregReceiver_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint8) shiftregReceiver_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: shiftregReceiver_SaveConfig
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
void shiftregReceiver_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    shiftregReceiver_backup.saveSrA0Reg   = CY_GET_REG8(shiftregReceiver_SHIFT_REG_LSB_PTR);
    shiftregReceiver_backup.saveSrA1Reg   = CY_GET_REG8(shiftregReceiver_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        shiftregReceiver_backup.saveSrIntMask = shiftregReceiver_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: shiftregReceiver_RestoreConfig
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
void shiftregReceiver_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG8(shiftregReceiver_SHIFT_REG_LSB_PTR, shiftregReceiver_backup.saveSrA0Reg);
    CY_SET_REG8(shiftregReceiver_SHIFT_REG_VALUE_LSB_PTR, shiftregReceiver_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        shiftregReceiver_SR_STATUS_MASK = ((uint8) shiftregReceiver_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: shiftregReceiver_Sleep
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
void shiftregReceiver_Sleep(void) 
{
    shiftregReceiver_backup.enableState = ((uint8) shiftregReceiver_IS_ENABLED);

    shiftregReceiver_Stop();
    shiftregReceiver_SaveConfig();
}


/*******************************************************************************
* Function Name: shiftregReceiver_Wakeup
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
void shiftregReceiver_Wakeup(void) 
{
    shiftregReceiver_RestoreConfig();

    if(0u != shiftregReceiver_backup.enableState)
    {
        shiftregReceiver_Enable();
    }
}


/* [] END OF FILE */
