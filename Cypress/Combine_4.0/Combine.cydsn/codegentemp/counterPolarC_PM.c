/*******************************************************************************
* File Name: counterPolarC_PM.c  
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

#include "counterPolarC.h"

static counterPolarC_backupStruct counterPolarC_backup;


/*******************************************************************************
* Function Name: counterPolarC_SaveConfig
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
*  counterPolarC_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void counterPolarC_SaveConfig(void) 
{
    #if (!counterPolarC_UsingFixedFunction)

        counterPolarC_backup.CounterUdb = counterPolarC_ReadCounter();

        #if(!counterPolarC_ControlRegRemoved)
            counterPolarC_backup.CounterControlRegister = counterPolarC_ReadControlRegister();
        #endif /* (!counterPolarC_ControlRegRemoved) */

    #endif /* (!counterPolarC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarC_RestoreConfig
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
*  counterPolarC_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void counterPolarC_RestoreConfig(void) 
{      
    #if (!counterPolarC_UsingFixedFunction)

       counterPolarC_WriteCounter(counterPolarC_backup.CounterUdb);

        #if(!counterPolarC_ControlRegRemoved)
            counterPolarC_WriteControlRegister(counterPolarC_backup.CounterControlRegister);
        #endif /* (!counterPolarC_ControlRegRemoved) */

    #endif /* (!counterPolarC_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarC_Sleep
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
*  counterPolarC_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void counterPolarC_Sleep(void) 
{
    #if(!counterPolarC_ControlRegRemoved)
        /* Save Counter's enable state */
        if(counterPolarC_CTRL_ENABLE == (counterPolarC_CONTROL & counterPolarC_CTRL_ENABLE))
        {
            /* Counter is enabled */
            counterPolarC_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            counterPolarC_backup.CounterEnableState = 0u;
        }
    #else
        counterPolarC_backup.CounterEnableState = 1u;
        if(counterPolarC_backup.CounterEnableState != 0u)
        {
            counterPolarC_backup.CounterEnableState = 0u;
        }
    #endif /* (!counterPolarC_ControlRegRemoved) */
    
    counterPolarC_Stop();
    counterPolarC_SaveConfig();
}


/*******************************************************************************
* Function Name: counterPolarC_Wakeup
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
*  counterPolarC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void counterPolarC_Wakeup(void) 
{
    counterPolarC_RestoreConfig();
    #if(!counterPolarC_ControlRegRemoved)
        if(counterPolarC_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            counterPolarC_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!counterPolarC_ControlRegRemoved) */
    
}


/* [] END OF FILE */
