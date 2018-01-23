/*******************************************************************************
* File Name: ShiftCounter_PM.c  
* Version 2.20
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "ShiftCounter.h"

static ShiftCounter_backupStruct ShiftCounter_backup;


/*******************************************************************************
* Function Name: ShiftCounter_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ShiftCounter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void ShiftCounter_SaveConfig(void) 
{
    #if (!ShiftCounter_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            ShiftCounter_backup.CounterUdb = ShiftCounter_ReadCounter();
            ShiftCounter_backup.CounterPeriod = ShiftCounter_ReadPeriod();
            ShiftCounter_backup.CompareValue = ShiftCounter_ReadCompare();
            ShiftCounter_backup.InterruptMaskValue = ShiftCounter_STATUS_MASK;
        #endif /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            ShiftCounter_backup.CounterUdb = ShiftCounter_ReadCounter();
            ShiftCounter_backup.InterruptMaskValue = ShiftCounter_STATUS_MASK;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!ShiftCounter_ControlRegRemoved)
            ShiftCounter_backup.CounterControlRegister = ShiftCounter_ReadControlRegister();
        #endif /* (!ShiftCounter_ControlRegRemoved) */
    #endif /* (!ShiftCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ShiftCounter_RestoreConfig
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
* Global variables:
*  ShiftCounter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ShiftCounter_RestoreConfig(void) 
{      
    #if (!ShiftCounter_UsingFixedFunction)     
        /* Restore the UDB non-rentention registers for PSoC5A */
        #if (CY_PSOC5A)
            /* Interrupt State Backup for Critical Region*/
            uint8 ShiftCounter_interruptState;
        
            ShiftCounter_WriteCounter(ShiftCounter_backup.CounterUdb);
            ShiftCounter_WritePeriod(ShiftCounter_backup.CounterPeriod);
            ShiftCounter_WriteCompare(ShiftCounter_backup.CompareValue);
            /* Enter Critical Region*/
            ShiftCounter_interruptState = CyEnterCriticalSection();
        
            ShiftCounter_STATUS_AUX_CTRL |= ShiftCounter_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(ShiftCounter_interruptState);
            ShiftCounter_STATUS_MASK = ShiftCounter_backup.InterruptMaskValue;
        #endif  /* (CY_PSOC5A) */
        
        #if (CY_PSOC3 || CY_PSOC5LP)
            ShiftCounter_WriteCounter(ShiftCounter_backup.CounterUdb);
            ShiftCounter_STATUS_MASK = ShiftCounter_backup.InterruptMaskValue;
        #endif /* (CY_PSOC3 || CY_PSOC5LP) */
        
        #if(!ShiftCounter_ControlRegRemoved)
            ShiftCounter_WriteControlRegister(ShiftCounter_backup.CounterControlRegister);
        #endif /* (!ShiftCounter_ControlRegRemoved) */
    #endif /* (!ShiftCounter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: ShiftCounter_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ShiftCounter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void ShiftCounter_Sleep(void) 
{
    #if(!ShiftCounter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(ShiftCounter_CTRL_ENABLE == (ShiftCounter_CONTROL & ShiftCounter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            ShiftCounter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            ShiftCounter_backup.CounterEnableState = 0u;
        }
    #endif /* (!ShiftCounter_ControlRegRemoved) */
    ShiftCounter_Stop();
    ShiftCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: ShiftCounter_Wakeup
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
*  ShiftCounter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ShiftCounter_Wakeup(void) 
{
    ShiftCounter_RestoreConfig();
    #if(!ShiftCounter_ControlRegRemoved)
        if(ShiftCounter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            ShiftCounter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!ShiftCounter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
