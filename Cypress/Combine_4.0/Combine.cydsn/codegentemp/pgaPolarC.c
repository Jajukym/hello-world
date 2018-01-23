/*******************************************************************************
* File Name: pgaPolarC.c  
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

#include "pgaPolarC.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (CY_PSOC5A)
    static pgaPolarC_BACKUP_STRUCT  pgaPolarC_P5backup;
#endif /* (CY_ PSOC5A) */

uint8 pgaPolarC_initVar = 0u;


/*******************************************************************************   
* Function Name: pgaPolarC_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  pgaPolarC_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void pgaPolarC_Init(void) 
{
    /* Set PGA mode */
    pgaPolarC_CR0_REG = pgaPolarC_MODE_PGA;      
    /* Set non-inverting PGA mode and reference mode */
    pgaPolarC_CR1_REG |= pgaPolarC_PGA_NINV;  
    /* Set default gain and ref mode */
    pgaPolarC_CR2_REG = pgaPolarC_VREF_MODE;
    /* Set gain and compensation */
    pgaPolarC_SetGain(pgaPolarC_DEFAULT_GAIN);
    /* Set power */
    pgaPolarC_SetPower(pgaPolarC_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: pgaPolarC_Enable
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
void pgaPolarC_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(pgaPolarC_P5backup.enableState == 1u)
        {
            pgaPolarC_CR1_REG = pgaPolarC_P5backup.scCR1Reg;
            pgaPolarC_CR2_REG = pgaPolarC_P5backup.scCR2Reg;
            pgaPolarC_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */   

    /* Enable power to the Amp in Active mode*/
    pgaPolarC_PM_ACT_CFG_REG |= pgaPolarC_ACT_PWR_EN;

    /* Enable power to the Amp in Alternative Active mode*/
    pgaPolarC_PM_STBY_CFG_REG |= pgaPolarC_STBY_PWR_EN;
    
    pgaPolarC_PUMP_CR1_REG |= pgaPolarC_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                pgaPolarC_BSTCLK_REG &= (uint8)(~pgaPolarC_BST_CLK_INDEX_MASK);
                pgaPolarC_BSTCLK_REG |= pgaPolarC_BST_CLK_EN | CyScBoostClk__INDEX;
                pgaPolarC_SC_MISC_REG |= pgaPolarC_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                pgaPolarC_BSTCLK_REG &= (uint8)(~pgaPolarC_BST_CLK_EN);
                pgaPolarC_SC_MISC_REG &= (uint8)(~pgaPolarC_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: pgaPolarC_Start
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
void pgaPolarC_Start(void) 
{

    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modification in stop() API */

    if(pgaPolarC_initVar == 0u)
    {
        pgaPolarC_Init();
        pgaPolarC_initVar = 1u;
    }

    pgaPolarC_Enable();
}


/*******************************************************************************
* Function Name: pgaPolarC_Stop
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
void pgaPolarC_Stop(void) 
{ 
    /* Disble power to the Amp in Active mode template */
    pgaPolarC_PM_ACT_CFG_REG &= (uint8)(~pgaPolarC_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    pgaPolarC_PM_STBY_CFG_REG &= (uint8)(~pgaPolarC_STBY_PWR_EN);

    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            pgaPolarC_BSTCLK_REG &= (uint8)(~pgaPolarC_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((pgaPolarC_PM_ACT_CFG_REG & pgaPolarC_PM_ACT_CFG_MASK) == 0u)
            {
                pgaPolarC_SC_MISC_REG &= (uint8)(~pgaPolarC_PUMP_FORCE);
                pgaPolarC_PUMP_CR1_REG &= (uint8)(~pgaPolarC_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /* This sets PGA in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        pgaPolarC_P5backup.scCR1Reg = pgaPolarC_CR1_REG;
        pgaPolarC_P5backup.scCR2Reg = pgaPolarC_CR2_REG;
        pgaPolarC_CR1_REG = 0x00u;
        pgaPolarC_CR2_REG = 0x00u;
        pgaPolarC_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: pgaPolarC_SetPower
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
void pgaPolarC_SetPower(uint8 power) 
{
    uint8 tmpCR;

    tmpCR = pgaPolarC_CR1_REG & (uint8)(~pgaPolarC_DRIVE_MASK);
    tmpCR |= (power & pgaPolarC_DRIVE_MASK);
    pgaPolarC_CR1_REG = tmpCR;  
}


/*******************************************************************************
* Function Name: pgaPolarC_SetGain
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
void pgaPolarC_SetGain(uint8 gain) 
{
    /* Constant array for gain settings */
    const uint8 pgaPolarC_GainArray[9] = { 
        (pgaPolarC_RVAL_0K   | pgaPolarC_R20_40B_40K | pgaPolarC_BIAS_LOW), /* G=1  */
        (pgaPolarC_RVAL_40K  | pgaPolarC_R20_40B_40K | pgaPolarC_BIAS_LOW), /* G=2  */
        (pgaPolarC_RVAL_120K | pgaPolarC_R20_40B_40K | pgaPolarC_BIAS_LOW), /* G=4  */
        (pgaPolarC_RVAL_280K | pgaPolarC_R20_40B_40K | pgaPolarC_BIAS_LOW), /* G=8  */
        (pgaPolarC_RVAL_600K | pgaPolarC_R20_40B_40K | pgaPolarC_BIAS_LOW), /* G=16 */
        (pgaPolarC_RVAL_460K | pgaPolarC_R20_40B_40K | pgaPolarC_BIAS_LOW), /* G=24, Sets Rin as 20k */
        (pgaPolarC_RVAL_620K | pgaPolarC_R20_40B_20K | pgaPolarC_BIAS_LOW), /* G=32 */
        (pgaPolarC_RVAL_470K | pgaPolarC_R20_40B_20K | pgaPolarC_BIAS_LOW), /* G=48, Sets Rin as 10k */
        (pgaPolarC_RVAL_490K | pgaPolarC_R20_40B_20K | pgaPolarC_BIAS_LOW)  /* G=50, Sets Rin as 10k */
    };
    
    /* Constant array for gain compenstion settings */
    const uint8 pgaPolarC_GainComp[9] = { 
        ( pgaPolarC_COMP_4P35PF  | (uint8)( pgaPolarC_REDC_00 >> 2 )), /* G=1  */
        ( pgaPolarC_COMP_4P35PF  | (uint8)( pgaPolarC_REDC_01 >> 2 )), /* G=2  */
        ( pgaPolarC_COMP_3P0PF   | (uint8)( pgaPolarC_REDC_01 >> 2 )), /* G=4  */
        ( pgaPolarC_COMP_3P0PF   | (uint8)( pgaPolarC_REDC_01 >> 2 )), /* G=8  */
        ( pgaPolarC_COMP_3P6PF   | (uint8)( pgaPolarC_REDC_01 >> 2 )), /* G=16 */
        ( pgaPolarC_COMP_3P6PF   | (uint8)( pgaPolarC_REDC_11 >> 2 )), /* G=24 */
        ( pgaPolarC_COMP_3P6PF   | (uint8)( pgaPolarC_REDC_11 >> 2 )), /* G=32 */
        ( pgaPolarC_COMP_3P6PF   | (uint8)( pgaPolarC_REDC_00 >> 2 )), /* G=48 */
        ( pgaPolarC_COMP_3P6PF   | (uint8)( pgaPolarC_REDC_00 >> 2 ))  /* G=50 */
    };
    
    /* Only set new gain if it is a valid gain */
    if( gain <= pgaPolarC_GAIN_MAX)
    {
        /* Clear resistors, redc, and bias */
        pgaPolarC_CR2_REG &= (uint8)(~(pgaPolarC_RVAL_MASK | pgaPolarC_R20_40B_MASK | 
                                pgaPolarC_REDC_MASK | pgaPolarC_BIAS_MASK ));

        /* Set gain value resistors, redc comp, and bias */
        pgaPolarC_CR2_REG |= (pgaPolarC_GainArray[gain] |
                                ((uint8)(pgaPolarC_GainComp[gain] << 2 ) & pgaPolarC_REDC_MASK));

        /* Clear sc_comp  */
        pgaPolarC_CR1_REG &= (uint8)(~pgaPolarC_COMP_MASK);
        /* Set sc_comp  */
        pgaPolarC_CR1_REG |= ( pgaPolarC_GainComp[gain] | pgaPolarC_COMP_MASK );
    }
}


/* [] END OF FILE */
