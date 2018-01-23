/*******************************************************************************
* File Name: counterANTPlus_PM.c  
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

#include "counterANTPlus.h"

static counterANTPlus_backupStruct counterANTPlus_backup;


/*******************************************************************************
* Function Name: counterANTPlus_SaveConfig
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
*  counterANTPlus_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void counterANTPlus_SaveConfig(void) 
{
    #if (!counterANTPlus_UsingFixedFunction)

        counterANTPlus_backup.CounterUdb = counterANTPlus_ReadCounter();

        #if(!counterANTPlus_ControlRegRemoved)
            counterANTPlus_backup.CounterControlRegister = counterANTPlus_ReadControlRegister();
        #endif /* (!counterANTPlus_ControlRegRemoved) */

    #endif /* (!counterANTPlus_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterANTPlus_RestoreConfig
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
*  counterANTPlus_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void counterANTPlus_RestoreConfig(void) 
{      
    #if (!counterANTPlus_UsingFixedFunction)

       counterANTPlus_WriteCounter(counterANTPlus_backup.CounterUdb);

        #if(!counterANTPlus_ControlRegRemoved)
            counterANTPlus_WriteControlRegister(counterANTPlus_backup.CounterControlRegister);
        #endif /* (!counterANTPlus_ControlRegRemoved) */

    #endif /* (!counterANTPlus_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: counterANTPlus_Sleep
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
*  counterANTPlus_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void counterANTPlus_Sleep(void) 
{
    #if(!counterANTPlus_ControlRegRemoved)
        /* Save Counter's enable state */
        if(counterANTPlus_CTRL_ENABLE == (counterANTPlus_CONTROL & counterANTPlus_CTRL_ENABLE))
        {
            /* Counter is enabled */
            counterANTPlus_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            counterANTPlus_backup.CounterEnableState = 0u;
        }
    #else
        counterANTPlus_backup.CounterEnableState = 1u;
        if(counterANTPlus_backup.CounterEnableState != 0u)
        {
            counterANTPlus_backup.CounterEnableState = 0u;
        }
    #endif /* (!counterANTPlus_ControlRegRemoved) */
    
    counterANTPlus_Stop();
    counterANTPlus_SaveConfig();
}


/*******************************************************************************
* Function Name: counterANTPlus_Wakeup
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
*  counterANTPlus_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void counterANTPlus_Wakeup(void) 
{
    counterANTPlus_RestoreConfig();
    #if(!counterANTPlus_ControlRegRemoved)
        if(counterANTPlus_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            counterANTPlus_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!counterANTPlus_ControlRegRemoved) */
    
}


/* [] END OF FILE */
