/*******************************************************************************
* File Name: PWM_PulseCapture_PM.c
* Version 2.40
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cytypes.h"
#include "PWM_PulseCapture.h"

static PWM_PulseCapture_backupStruct PWM_PulseCapture_backup;


/*******************************************************************************
* Function Name: PWM_PulseCapture_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_PulseCapture_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PWM_PulseCapture_SaveConfig(void) 
{
    
    #if(!PWM_PulseCapture_UsingFixedFunction)
        #if (CY_UDB_V0)
            PWM_PulseCapture_backup.PWMUdb = PWM_PulseCapture_ReadCounter();
            PWM_PulseCapture_backup.PWMPeriod = PWM_PulseCapture_ReadPeriod();
            #if (PWM_PulseCapture_UseStatus)
                PWM_PulseCapture_backup.InterruptMaskValue = PWM_PulseCapture_STATUS_MASK;
            #endif /* (PWM_PulseCapture_UseStatus) */
            
            #if(PWM_PulseCapture_UseOneCompareMode)
                PWM_PulseCapture_backup.PWMCompareValue = PWM_PulseCapture_ReadCompare();
            #else
                PWM_PulseCapture_backup.PWMCompareValue1 = PWM_PulseCapture_ReadCompare1();
                PWM_PulseCapture_backup.PWMCompareValue2 = PWM_PulseCapture_ReadCompare2();
            #endif /* (PWM_PulseCapture_UseOneCompareMode) */
            
           #if(PWM_PulseCapture_DeadBandUsed)
                PWM_PulseCapture_backup.PWMdeadBandValue = PWM_PulseCapture_ReadDeadTime();
            #endif /* (PWM_PulseCapture_DeadBandUsed) */
          
            #if ( PWM_PulseCapture_KillModeMinTime)
                PWM_PulseCapture_backup.PWMKillCounterPeriod = PWM_PulseCapture_ReadKillTime();
            #endif /* ( PWM_PulseCapture_KillModeMinTime) */
        #endif /* (CY_UDB_V0) */
        
        #if (CY_UDB_V1)
            #if(!PWM_PulseCapture_PWMModeIsCenterAligned)
                PWM_PulseCapture_backup.PWMPeriod = PWM_PulseCapture_ReadPeriod();
            #endif /* (!PWM_PulseCapture_PWMModeIsCenterAligned) */
            PWM_PulseCapture_backup.PWMUdb = PWM_PulseCapture_ReadCounter();
            #if (PWM_PulseCapture_UseStatus)
                PWM_PulseCapture_backup.InterruptMaskValue = PWM_PulseCapture_STATUS_MASK;
            #endif /* (PWM_PulseCapture_UseStatus) */
            
            #if(PWM_PulseCapture_DeadBandMode == PWM_PulseCapture__B_PWM__DBM_256_CLOCKS || \
                PWM_PulseCapture_DeadBandMode == PWM_PulseCapture__B_PWM__DBM_2_4_CLOCKS)
                PWM_PulseCapture_backup.PWMdeadBandValue = PWM_PulseCapture_ReadDeadTime();
            #endif /*  deadband count is either 2-4 clocks or 256 clocks */
            
            #if(PWM_PulseCapture_KillModeMinTime)
                 PWM_PulseCapture_backup.PWMKillCounterPeriod = PWM_PulseCapture_ReadKillTime();
            #endif /* (PWM_PulseCapture_KillModeMinTime) */
        #endif /* (CY_UDB_V1) */
        
        #if(PWM_PulseCapture_UseControl)
            PWM_PulseCapture_backup.PWMControlRegister = PWM_PulseCapture_ReadControlRegister();
        #endif /* (PWM_PulseCapture_UseControl) */
    #endif  /* (!PWM_PulseCapture_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_PulseCapture_RestoreConfig
********************************************************************************
* 
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_PulseCapture_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_PulseCapture_RestoreConfig(void) 
{
        #if(!PWM_PulseCapture_UsingFixedFunction)
            #if (CY_UDB_V0)
                /* Interrupt State Backup for Critical Region*/
                uint8 PWM_PulseCapture_interruptState;
                /* Enter Critical Region*/
                PWM_PulseCapture_interruptState = CyEnterCriticalSection();
                #if (PWM_PulseCapture_UseStatus)
                    /* Use the interrupt output of the status register for IRQ output */
                    PWM_PulseCapture_STATUS_AUX_CTRL |= PWM_PulseCapture_STATUS_ACTL_INT_EN_MASK;
                    
                    PWM_PulseCapture_STATUS_MASK = PWM_PulseCapture_backup.InterruptMaskValue;
                #endif /* (PWM_PulseCapture_UseStatus) */
                
                #if (PWM_PulseCapture_Resolution == 8)
                    /* Set FIFO 0 to 1 byte register for period*/
                    PWM_PulseCapture_AUX_CONTROLDP0 |= (PWM_PulseCapture_AUX_CTRL_FIFO0_CLR);
                #else /* (PWM_PulseCapture_Resolution == 16)*/
                    /* Set FIFO 0 to 1 byte register for period */
                    PWM_PulseCapture_AUX_CONTROLDP0 |= (PWM_PulseCapture_AUX_CTRL_FIFO0_CLR);
                    PWM_PulseCapture_AUX_CONTROLDP1 |= (PWM_PulseCapture_AUX_CTRL_FIFO0_CLR);
                #endif /* (PWM_PulseCapture_Resolution == 8) */
                /* Exit Critical Region*/
                CyExitCriticalSection(PWM_PulseCapture_interruptState);
                
                PWM_PulseCapture_WriteCounter(PWM_PulseCapture_backup.PWMUdb);
                PWM_PulseCapture_WritePeriod(PWM_PulseCapture_backup.PWMPeriod);
                
                #if(PWM_PulseCapture_UseOneCompareMode)
                    PWM_PulseCapture_WriteCompare(PWM_PulseCapture_backup.PWMCompareValue);
                #else
                    PWM_PulseCapture_WriteCompare1(PWM_PulseCapture_backup.PWMCompareValue1);
                    PWM_PulseCapture_WriteCompare2(PWM_PulseCapture_backup.PWMCompareValue2);
                #endif /* (PWM_PulseCapture_UseOneCompareMode) */
                
               #if(PWM_PulseCapture_DeadBandMode == PWM_PulseCapture__B_PWM__DBM_256_CLOCKS || \
                   PWM_PulseCapture_DeadBandMode == PWM_PulseCapture__B_PWM__DBM_2_4_CLOCKS)
                    PWM_PulseCapture_WriteDeadTime(PWM_PulseCapture_backup.PWMdeadBandValue);
                #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
                #if ( PWM_PulseCapture_KillModeMinTime)
                    PWM_PulseCapture_WriteKillTime(PWM_PulseCapture_backup.PWMKillCounterPeriod);
                #endif /* ( PWM_PulseCapture_KillModeMinTime) */
            #endif /* (CY_UDB_V0) */
            
            #if (CY_UDB_V1)
                #if(!PWM_PulseCapture_PWMModeIsCenterAligned)
                    PWM_PulseCapture_WritePeriod(PWM_PulseCapture_backup.PWMPeriod);
                #endif /* (!PWM_PulseCapture_PWMModeIsCenterAligned) */
                PWM_PulseCapture_WriteCounter(PWM_PulseCapture_backup.PWMUdb);
                #if (PWM_PulseCapture_UseStatus)
                    PWM_PulseCapture_STATUS_MASK = PWM_PulseCapture_backup.InterruptMaskValue;
                #endif /* (PWM_PulseCapture_UseStatus) */
                
                #if(PWM_PulseCapture_DeadBandMode == PWM_PulseCapture__B_PWM__DBM_256_CLOCKS || \
                    PWM_PulseCapture_DeadBandMode == PWM_PulseCapture__B_PWM__DBM_2_4_CLOCKS)
                    PWM_PulseCapture_WriteDeadTime(PWM_PulseCapture_backup.PWMdeadBandValue);
                #endif /* deadband count is either 2-4 clocks or 256 clocks */
                
                #if(PWM_PulseCapture_KillModeMinTime)
                    PWM_PulseCapture_WriteKillTime(PWM_PulseCapture_backup.PWMKillCounterPeriod);
                #endif /* (PWM_PulseCapture_KillModeMinTime) */
            #endif /* (CY_UDB_V1) */
            
            #if(PWM_PulseCapture_UseControl)
                PWM_PulseCapture_WriteControlRegister(PWM_PulseCapture_backup.PWMControlRegister); 
            #endif /* (PWM_PulseCapture_UseControl) */
        #endif  /* (!PWM_PulseCapture_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_PulseCapture_Sleep
********************************************************************************
* 
* Summary:
*  Disables block's operation and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_PulseCapture_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_PulseCapture_Sleep(void) 
{
    #if(PWM_PulseCapture_UseControl)
        if(PWM_PulseCapture_CTRL_ENABLE == (PWM_PulseCapture_CONTROL & PWM_PulseCapture_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_PulseCapture_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_PulseCapture_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_PulseCapture_UseControl) */

    /* Stop component */
    PWM_PulseCapture_Stop();
    
    /* Save registers configuration */
    PWM_PulseCapture_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_PulseCapture_Wakeup
********************************************************************************
* 
* Summary:
*  Restores and enables the user configuration. Should be called just after 
*  awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_PulseCapture_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_PulseCapture_Wakeup(void) 
{
     /* Restore registers values */
    PWM_PulseCapture_RestoreConfig();
    
    if(PWM_PulseCapture_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_PulseCapture_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
