/*******************************************************************************
* File Name: counterPolarS_PM.c  
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

#include "counterPolarS.h"

static counterPolarS_backupStruct counterPolarS_backup;


/*******************************************************************************
* Function Name: counterPolarS_SaveConfig
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
*  counterPolarS_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void counterPolarS_SaveConfig(void) 
{
    #if (!counterPolarS_UsingFixedFunction)

        counterPolarS_backup.CounterUdb = counterPolarS_ReadCounter();

        #if(!counterPolarS_ControlRegRemoved)
            counterPolarS_backup.CounterControlRegister = counterPolarS_ReadControlRegister();
        #endif /* (!counterPolarS_ControlRegRemoved) */

    #endif /* (!counterPolarS_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarS_RestoreConfig
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
*  counterPolarS_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void counterPolarS_RestoreConfig(void) 
{      
    #if (!counterPolarS_UsingFixedFunction)

       counterPolarS_WriteCounter(counterPolarS_backup.CounterUdb);

        #if(!counterPolarS_ControlRegRemoved)
            counterPolarS_WriteControlRegister(counterPolarS_backup.CounterControlRegister);
        #endif /* (!counterPolarS_ControlRegRemoved) */

    #endif /* (!counterPolarS_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterPolarS_Sleep
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
*  counterPolarS_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void counterPolarS_Sleep(void) 
{
    #if(!counterPolarS_ControlRegRemoved)
        /* Save Counter's enable state */
        if(counterPolarS_CTRL_ENABLE == (counterPolarS_CONTROL & counterPolarS_CTRL_ENABLE))
        {
            /* Counter is enabled */
            counterPolarS_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            counterPolarS_backup.CounterEnableState = 0u;
        }
    #else
        counterPolarS_backup.CounterEnableState = 1u;
        if(counterPolarS_backup.CounterEnableState != 0u)
        {
            counterPolarS_backup.CounterEnableState = 0u;
        }
    #endif /* (!counterPolarS_ControlRegRemoved) */
    
    counterPolarS_Stop();
    counterPolarS_SaveConfig();
}


/*******************************************************************************
* Function Name: counterPolarS_Wakeup
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
*  counterPolarS_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void counterPolarS_Wakeup(void) 
{
    counterPolarS_RestoreConfig();
    #if(!counterPolarS_ControlRegRemoved)
        if(counterPolarS_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            counterPolarS_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!counterPolarS_ControlRegRemoved) */
    
}


/* [] END OF FILE */
