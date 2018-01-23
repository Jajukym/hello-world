/*******************************************************************************
* File Name: counterShift_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "counterShift.h"

static counterShift_backupStruct counterShift_backup;


/*******************************************************************************
* Function Name: counterShift_SaveConfig
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
*  counterShift_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void counterShift_SaveConfig(void) 
{
    #if (!counterShift_UsingFixedFunction)

        counterShift_backup.CounterUdb = counterShift_ReadCounter();

        #if(!counterShift_ControlRegRemoved)
            counterShift_backup.CounterControlRegister = counterShift_ReadControlRegister();
        #endif /* (!counterShift_ControlRegRemoved) */

    #endif /* (!counterShift_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterShift_RestoreConfig
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
*  counterShift_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void counterShift_RestoreConfig(void) 
{      
    #if (!counterShift_UsingFixedFunction)

       counterShift_WriteCounter(counterShift_backup.CounterUdb);

        #if(!counterShift_ControlRegRemoved)
            counterShift_WriteControlRegister(counterShift_backup.CounterControlRegister);
        #endif /* (!counterShift_ControlRegRemoved) */

    #endif /* (!counterShift_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterShift_Sleep
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
*  counterShift_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void counterShift_Sleep(void) 
{
    #if(!counterShift_ControlRegRemoved)
        /* Save Counter's enable state */
        if(counterShift_CTRL_ENABLE == (counterShift_CONTROL & counterShift_CTRL_ENABLE))
        {
            /* Counter is enabled */
            counterShift_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            counterShift_backup.CounterEnableState = 0u;
        }
    #else
        counterShift_backup.CounterEnableState = 1u;
        if(counterShift_backup.CounterEnableState != 0u)
        {
            counterShift_backup.CounterEnableState = 0u;
        }
    #endif /* (!counterShift_ControlRegRemoved) */
    
    counterShift_Stop();
    counterShift_SaveConfig();
}


/*******************************************************************************
* Function Name: counterShift_Wakeup
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
*  counterShift_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void counterShift_Wakeup(void) 
{
    counterShift_RestoreConfig();
    #if(!counterShift_ControlRegRemoved)
        if(counterShift_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            counterShift_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!counterShift_ControlRegRemoved) */
    
}


/* [] END OF FILE */
