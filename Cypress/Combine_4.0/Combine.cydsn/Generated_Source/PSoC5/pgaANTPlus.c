/*******************************************************************************
* File Name: pgaANTPlus.c  
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the PGA 
*  User Module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "pgaANTPlus.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (CY_PSOC5A)
    static pgaANTPlus_BACKUP_STRUCT  pgaANTPlus_P5backup;
#endif /* (CY_ PSOC5A) */

uint8 pgaANTPlus_initVar = 0u;


/*******************************************************************************   
* Function Name: pgaANTPlus_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  pgaANTPlus_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void pgaANTPlus_Init(void) 
{
    /* Set PGA mode */
    pgaANTPlus_CR0_REG = pgaANTPlus_MODE_PGA;      
    /* Set non-inverting PGA mode and reference mode */
    pgaANTPlus_CR1_REG |= pgaANTPlus_PGA_NINV;  
    /* Set default gain and ref mode */
    pgaANTPlus_CR2_REG = pgaANTPlus_VREF_MODE;
    /* Set gain and compensation */
    pgaANTPlus_SetGain(pgaANTPlus_DEFAULT_GAIN);
    /* Set power */
    pgaANTPlus_SetPower(pgaANTPlus_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: pgaANTPlus_Enable
********************************************************************************
*
* Summary:
*  Enables the PGA block operation.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void pgaANTPlus_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(pgaANTPlus_P5backup.enableState == 1u)
        {
            pgaANTPlus_CR1_REG = pgaANTPlus_P5backup.scCR1Reg;
            pgaANTPlus_CR2_REG = pgaANTPlus_P5backup.scCR2Reg;
            pgaANTPlus_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */   

    /* Enable power to the Amp in Active mode*/
    pgaANTPlus_PM_ACT_CFG_REG |= pgaANTPlus_ACT_PWR_EN;

    /* Enable power to the Amp in Alternative Active mode*/
    pgaANTPlus_PM_STBY_CFG_REG |= pgaANTPlus_STBY_PWR_EN;
    
    pgaANTPlus_PUMP_CR1_REG |= pgaANTPlus_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                pgaANTPlus_BSTCLK_REG &= (uint8)(~pgaANTPlus_BST_CLK_INDEX_MASK);
                pgaANTPlus_BSTCLK_REG |= pgaANTPlus_BST_CLK_EN | CyScBoostClk__INDEX;
                pgaANTPlus_SC_MISC_REG |= pgaANTPlus_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                pgaANTPlus_BSTCLK_REG &= (uint8)(~pgaANTPlus_BST_CLK_EN);
                pgaANTPlus_SC_MISC_REG &= (uint8)(~pgaANTPlus_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: pgaANTPlus_Start
********************************************************************************
*
* Summary:
*  The start function initializes the PGA with the default values and sets
*  the power to the given level. A power level of 0, is same as executing
*  the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void pgaANTPlus_Start(void) 
{

    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modification in stop() API */

    if(pgaANTPlus_initVar == 0u)
    {
        pgaANTPlus_Init();
        pgaANTPlus_initVar = 1u;
    }

    pgaANTPlus_Enable();
}


/*******************************************************************************
* Function Name: pgaANTPlus_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void pgaANTPlus_Stop(void) 
{ 
    /* Disble power to the Amp in Active mode template */
    pgaANTPlus_PM_ACT_CFG_REG &= (uint8)(~pgaANTPlus_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    pgaANTPlus_PM_STBY_CFG_REG &= (uint8)(~pgaANTPlus_STBY_PWR_EN);

    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            pgaANTPlus_BSTCLK_REG &= (uint8)(~pgaANTPlus_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((pgaANTPlus_PM_ACT_CFG_REG & pgaANTPlus_PM_ACT_CFG_MASK) == 0u)
            {
                pgaANTPlus_SC_MISC_REG &= (uint8)(~pgaANTPlus_PUMP_FORCE);
                pgaANTPlus_PUMP_CR1_REG &= (uint8)(~pgaANTPlus_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /* This sets PGA in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        pgaANTPlus_P5backup.scCR1Reg = pgaANTPlus_CR1_REG;
        pgaANTPlus_P5backup.scCR2Reg = pgaANTPlus_CR2_REG;
        pgaANTPlus_CR1_REG = 0x00u;
        pgaANTPlus_CR2_REG = 0x00u;
        pgaANTPlus_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: pgaANTPlus_SetPower
********************************************************************************
*
* Summary:
*  Set the power of the PGA.
*
* Parameters:
*  power: Sets power level between (0) and (3) high power
*
* Return:
*  void
*
*******************************************************************************/
void pgaANTPlus_SetPower(uint8 power) 
{
    uint8 tmpCR;

    tmpCR = pgaANTPlus_CR1_REG & (uint8)(~pgaANTPlus_DRIVE_MASK);
    tmpCR |= (power & pgaANTPlus_DRIVE_MASK);
    pgaANTPlus_CR1_REG = tmpCR;  
}


/*******************************************************************************
* Function Name: pgaANTPlus_SetGain
********************************************************************************
*
* Summary:
*  This function sets values of the input and feedback resistors to set a 
*  specific gain of the amplifier.
*
* Parameters:
*  gain: Gain value of PGA (See header file for gain values.)
*
* Return:
*  void 
*
*******************************************************************************/
void pgaANTPlus_SetGain(uint8 gain) 
{
    /* Constant array for gain settings */
    const uint8 pgaANTPlus_GainArray[9] = { 
        (pgaANTPlus_RVAL_0K   | pgaANTPlus_R20_40B_40K | pgaANTPlus_BIAS_LOW), /* G=1  */
        (pgaANTPlus_RVAL_40K  | pgaANTPlus_R20_40B_40K | pgaANTPlus_BIAS_LOW), /* G=2  */
        (pgaANTPlus_RVAL_120K | pgaANTPlus_R20_40B_40K | pgaANTPlus_BIAS_LOW), /* G=4  */
        (pgaANTPlus_RVAL_280K | pgaANTPlus_R20_40B_40K | pgaANTPlus_BIAS_LOW), /* G=8  */
        (pgaANTPlus_RVAL_600K | pgaANTPlus_R20_40B_40K | pgaANTPlus_BIAS_LOW), /* G=16 */
        (pgaANTPlus_RVAL_460K | pgaANTPlus_R20_40B_40K | pgaANTPlus_BIAS_LOW), /* G=24, Sets Rin as 20k */
        (pgaANTPlus_RVAL_620K | pgaANTPlus_R20_40B_20K | pgaANTPlus_BIAS_LOW), /* G=32 */
        (pgaANTPlus_RVAL_470K | pgaANTPlus_R20_40B_20K | pgaANTPlus_BIAS_LOW), /* G=48, Sets Rin as 10k */
        (pgaANTPlus_RVAL_490K | pgaANTPlus_R20_40B_20K | pgaANTPlus_BIAS_LOW)  /* G=50, Sets Rin as 10k */
    };
    
    /* Constant array for gain compenstion settings */
    const uint8 pgaANTPlus_GainComp[9] = { 
        ( pgaANTPlus_COMP_4P35PF  | (uint8)( pgaANTPlus_REDC_00 >> 2 )), /* G=1  */
        ( pgaANTPlus_COMP_4P35PF  | (uint8)( pgaANTPlus_REDC_01 >> 2 )), /* G=2  */
        ( pgaANTPlus_COMP_3P0PF   | (uint8)( pgaANTPlus_REDC_01 >> 2 )), /* G=4  */
        ( pgaANTPlus_COMP_3P0PF   | (uint8)( pgaANTPlus_REDC_01 >> 2 )), /* G=8  */
        ( pgaANTPlus_COMP_3P6PF   | (uint8)( pgaANTPlus_REDC_01 >> 2 )), /* G=16 */
        ( pgaANTPlus_COMP_3P6PF   | (uint8)( pgaANTPlus_REDC_11 >> 2 )), /* G=24 */
        ( pgaANTPlus_COMP_3P6PF   | (uint8)( pgaANTPlus_REDC_11 >> 2 )), /* G=32 */
        ( pgaANTPlus_COMP_3P6PF   | (uint8)( pgaANTPlus_REDC_00 >> 2 )), /* G=48 */
        ( pgaANTPlus_COMP_3P6PF   | (uint8)( pgaANTPlus_REDC_00 >> 2 ))  /* G=50 */
    };
    
    /* Only set new gain if it is a valid gain */
    if( gain <= pgaANTPlus_GAIN_MAX)
    {
        /* Clear resistors, redc, and bias */
        pgaANTPlus_CR2_REG &= (uint8)(~(pgaANTPlus_RVAL_MASK | pgaANTPlus_R20_40B_MASK | 
                                pgaANTPlus_REDC_MASK | pgaANTPlus_BIAS_MASK ));

        /* Set gain value resistors, redc comp, and bias */
        pgaANTPlus_CR2_REG |= (pgaANTPlus_GainArray[gain] |
                                ((uint8)(pgaANTPlus_GainComp[gain] << 2 ) & pgaANTPlus_REDC_MASK));

        /* Clear sc_comp  */
        pgaANTPlus_CR1_REG &= (uint8)(~pgaANTPlus_COMP_MASK);
        /* Set sc_comp  */
        pgaANTPlus_CR1_REG |= ( pgaANTPlus_GainComp[gain] | pgaANTPlus_COMP_MASK );
    }
}


/* [] END OF FILE */
