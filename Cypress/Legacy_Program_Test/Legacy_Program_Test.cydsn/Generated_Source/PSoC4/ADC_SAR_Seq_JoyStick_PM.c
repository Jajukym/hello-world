/*******************************************************************************
* File Name: ADC_SAR_Seq_JoyStick_PM.c
* Version 2.40
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_SAR_Seq_JoyStick.h"


/***************************************
* Local data allocation
***************************************/

static ADC_SAR_Seq_JoyStick_BACKUP_STRUCT  ADC_SAR_Seq_JoyStick_backup =
{
    ADC_SAR_Seq_JoyStick_DISABLED
};


/*******************************************************************************
* Function Name: ADC_SAR_Seq_JoyStick_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_SAR_Seq_JoyStick_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_JoyStick_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_SAR_Seq_JoyStick_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_JoyStick_Sleep
********************************************************************************
*
* Summary:
*  Stops the ADC operation and saves the configuration registers and component
*  enable state. Should be called just prior to entering sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_SAR_Seq_JoyStick_backup - modified.
*
*******************************************************************************/
void ADC_SAR_Seq_JoyStick_Sleep(void)
{
    /* During deepsleep/ hibernate mode keep SARMUX active, i.e. do not open
    *   all switches (disconnect), to be used for ADFT
    */
    ADC_SAR_Seq_JoyStick_SAR_DFT_CTRL_REG |= ADC_SAR_Seq_JoyStick_ADFT_OVERRIDE;
    if((ADC_SAR_Seq_JoyStick_SAR_CTRL_REG  & ADC_SAR_Seq_JoyStick_ENABLE) != 0u)
    {
        if((ADC_SAR_Seq_JoyStick_SAR_SAMPLE_CTRL_REG & ADC_SAR_Seq_JoyStick_CONTINUOUS_EN) != 0u)
        {
            ADC_SAR_Seq_JoyStick_backup.enableState = ADC_SAR_Seq_JoyStick_ENABLED | ADC_SAR_Seq_JoyStick_STARTED;
        }
        else
        {
            ADC_SAR_Seq_JoyStick_backup.enableState = ADC_SAR_Seq_JoyStick_ENABLED;
        }
        ADC_SAR_Seq_JoyStick_StopConvert();
        ADC_SAR_Seq_JoyStick_Stop();
        
        /* Disable the SAR internal pump before entering the chip low power mode */
        if((ADC_SAR_Seq_JoyStick_SAR_CTRL_REG & ADC_SAR_Seq_JoyStick_BOOSTPUMP_EN) != 0u)
        {
            ADC_SAR_Seq_JoyStick_SAR_CTRL_REG &= (uint32)~ADC_SAR_Seq_JoyStick_BOOSTPUMP_EN;
            ADC_SAR_Seq_JoyStick_backup.enableState |= ADC_SAR_Seq_JoyStick_BOOSTPUMP_ENABLED;
        }
    }
    else
    {
        ADC_SAR_Seq_JoyStick_backup.enableState = ADC_SAR_Seq_JoyStick_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ADC_SAR_Seq_JoyStick_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component enable state and configuration registers.
*  This should be called just after awaking from sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_SAR_Seq_JoyStick_backup - used.
*
*******************************************************************************/
void ADC_SAR_Seq_JoyStick_Wakeup(void)
{
    ADC_SAR_Seq_JoyStick_SAR_DFT_CTRL_REG &= (uint32)~ADC_SAR_Seq_JoyStick_ADFT_OVERRIDE;
    if(ADC_SAR_Seq_JoyStick_backup.enableState != ADC_SAR_Seq_JoyStick_DISABLED)
    {
        /* Enable the SAR internal pump  */
        if((ADC_SAR_Seq_JoyStick_backup.enableState & ADC_SAR_Seq_JoyStick_BOOSTPUMP_ENABLED) != 0u)
        {
            ADC_SAR_Seq_JoyStick_SAR_CTRL_REG |= ADC_SAR_Seq_JoyStick_BOOSTPUMP_EN;
        }
        ADC_SAR_Seq_JoyStick_Enable();
        if((ADC_SAR_Seq_JoyStick_backup.enableState & ADC_SAR_Seq_JoyStick_STARTED) != 0u)
        {
            ADC_SAR_Seq_JoyStick_StartConvert();
        }
    }
}
/* [] END OF FILE */
