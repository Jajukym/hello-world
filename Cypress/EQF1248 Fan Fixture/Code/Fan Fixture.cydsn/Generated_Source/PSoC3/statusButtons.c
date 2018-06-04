/*******************************************************************************
* File Name: statusButtons.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "statusButtons.h"

#if !defined(statusButtons_sts_intr_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: statusButtons_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 statusButtons_Read(void) 
{ 
    return statusButtons_Status;
}


/*******************************************************************************
* Function Name: statusButtons_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void statusButtons_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    statusButtons_Status_Aux_Ctrl |= statusButtons_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: statusButtons_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void statusButtons_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    statusButtons_Status_Aux_Ctrl &= (uint8)(~statusButtons_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: statusButtons_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void statusButtons_WriteMask(uint8 mask) 
{
    #if(statusButtons_INPUTS < 8u)
    	mask &= ((uint8)(1u << statusButtons_INPUTS) - 1u);
	#endif /* End statusButtons_INPUTS < 8u */
    statusButtons_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: statusButtons_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 statusButtons_ReadMask(void) 
{
    return statusButtons_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
