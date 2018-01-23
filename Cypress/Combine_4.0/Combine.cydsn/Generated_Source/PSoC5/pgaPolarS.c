/*******************************************************************************
* File Name: pgaPolarS.c  
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

#include "pgaPolarS.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (CY_PSOC5A)
    static pgaPolarS_BACKUP_STRUCT  pgaPolarS_P5backup;
#endif /* (CY_ PSOC5A) */

uint8 pgaPolarS_initVar = 0u;


/*******************************************************************************   
* Function Name: pgaPolarS_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  pgaPolarS_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void pgaPolarS_Init(void) 
{
    /* Set PGA mode */
    pgaPolarS_CR0_REG = pgaPolarS_MODE_PGA;      
    /* Set non-inverting PGA mode and reference mode */
    pgaPolarS_CR1_REG |= pgaPolarS_PGA_NINV;  
    /* Set default gain and ref mode */
    pgaPolarS_CR2_REG = pgaPolarS_VREF_MODE;
    /* Set gain and compensation */
    pgaPolarS_SetGain(pgaPolarS_DEFAULT_GAIN);
    /* Set power */
    pgaPolarS_SetPower(pgaPolarS_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: pgaPolarS_Enable
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
void pgaPolarS_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(pgaPolarS_P5backup.enableState == 1u)
        {
            pgaPolarS_CR1_REG = pgaPolarS_P5backup.scCR1Reg;
            pgaPolarS_CR2_REG = pgaPolarS_P5backup.scCR2Reg;
            pgaPolarS_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */   

    /* Enable power to the Amp in Active mode*/
    pgaPolarS_PM_ACT_CFG_REG |= pgaPolarS_ACT_PWR_EN;

    /* Enable power to the Amp in Alternative Active mode*/
    pgaPolarS_PM_STBY_CFG_REG |= pgaPolarS_STBY_PWR_EN;
    
    pgaPolarS_PUMP_CR1_REG |= pgaPolarS_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                pgaPolarS_BSTCLK_REG &= (uint8)(~pgaPolarS_BST_CLK_INDEX_MASK);
                pgaPolarS_BSTCLK_REG |= pgaPolarS_BST_CLK_EN | CyScBoostClk__INDEX;
                pgaPolarS_SC_MISC_REG |= pgaPolarS_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                pgaPolarS_BSTCLK_REG &= (uint8)(~pgaPolarS_BST_CLK_EN);
                pgaPolarS_SC_MISC_REG &= (uint8)(~pgaPolarS_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: pgaPolarS_Start
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
void pgaPolarS_Start(void) 
{

    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modification in stop() API */

    if(pgaPolarS_initVar == 0u)
    {
        pgaPolarS_Init();
        pgaPolarS_initVar = 1u;
    }

    pgaPolarS_Enable();
}


/*******************************************************************************
* Function Name: pgaPolarS_Stop
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
void pgaPolarS_Stop(void) 
{ 
    /* Disble power to the Amp in Active mode template */
    pgaPolarS_PM_ACT_CFG_REG &= (uint8)(~pgaPolarS_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    pgaPolarS_PM_STBY_CFG_REG &= (uint8)(~pgaPolarS_STBY_PWR_EN);

    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            pgaPolarS_BSTCLK_REG &= (uint8)(~pgaPolarS_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((pgaPolarS_PM_ACT_CFG_REG & pgaPolarS_PM_ACT_CFG_MASK) == 0u)
            {
                pgaPolarS_SC_MISC_REG &= (uint8)(~pgaPolarS_PUMP_FORCE);
                pgaPolarS_PUMP_CR1_REG &= (uint8)(~pgaPolarS_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /* This sets PGA in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        pgaPolarS_P5backup.scCR1Reg = pgaPolarS_CR1_REG;
        pgaPolarS_P5backup.scCR2Reg = pgaPolarS_CR2_REG;
        pgaPolarS_CR1_REG = 0x00u;
        pgaPolarS_CR2_REG = 0x00u;
        pgaPolarS_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: pgaPolarS_SetPower
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
void pgaPolarS_SetPower(uint8 power) 
{
    uint8 tmpCR;

    tmpCR = pgaPolarS_CR1_REG & (uint8)(~pgaPolarS_DRIVE_MASK);
    tmpCR |= (power & pgaPolarS_DRIVE_MASK);
    pgaPolarS_CR1_REG = tmpCR;  
}


/*******************************************************************************
* Function Name: pgaPolarS_SetGain
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
void pgaPolarS_SetGain(uint8 gain) 
{
    /* Constant array for gain settings */
    const uint8 pgaPolarS_GainArray[9] = { 
        (pgaPolarS_RVAL_0K   | pgaPolarS_R20_40B_40K | pgaPolarS_BIAS_LOW), /* G=1  */
        (pgaPolarS_RVAL_40K  | pgaPolarS_R20_40B_40K | pgaPolarS_BIAS_LOW), /* G=2  */
        (pgaPolarS_RVAL_120K | pgaPolarS_R20_40B_40K | pgaPolarS_BIAS_LOW), /* G=4  */
        (pgaPolarS_RVAL_280K | pgaPolarS_R20_40B_40K | pgaPolarS_BIAS_LOW), /* G=8  */
        (pgaPolarS_RVAL_600K | pgaPolarS_R20_40B_40K | pgaPolarS_BIAS_LOW), /* G=16 */
        (pgaPolarS_RVAL_460K | pgaPolarS_R20_40B_40K | pgaPolarS_BIAS_LOW), /* G=24, Sets Rin as 20k */
        (pgaPolarS_RVAL_620K | pgaPolarS_R20_40B_20K | pgaPolarS_BIAS_LOW), /* G=32 */
        (pgaPolarS_RVAL_470K | pgaPolarS_R20_40B_20K | pgaPolarS_BIAS_LOW), /* G=48, Sets Rin as 10k */
        (pgaPolarS_RVAL_490K | pgaPolarS_R20_40B_20K | pgaPolarS_BIAS_LOW)  /* G=50, Sets Rin as 10k */
    };
    
    /* Constant array for gain compenstion settings */
    const uint8 pgaPolarS_GainComp[9] = { 
        ( pgaPolarS_COMP_4P35PF  | (uint8)( pgaPolarS_REDC_00 >> 2 )), /* G=1  */
        ( pgaPolarS_COMP_4P35PF  | (uint8)( pgaPolarS_REDC_01 >> 2 )), /* G=2  */
        ( pgaPolarS_COMP_3P0PF   | (uint8)( pgaPolarS_REDC_01 >> 2 )), /* G=4  */
        ( pgaPolarS_COMP_3P0PF   | (uint8)( pgaPolarS_REDC_01 >> 2 )), /* G=8  */
        ( pgaPolarS_COMP_3P6PF   | (uint8)( pgaPolarS_REDC_01 >> 2 )), /* G=16 */
        ( pgaPolarS_COMP_3P6PF   | (uint8)( pgaPolarS_REDC_11 >> 2 )), /* G=24 */
        ( pgaPolarS_COMP_3P6PF   | (uint8)( pgaPolarS_REDC_11 >> 2 )), /* G=32 */
        ( pgaPolarS_COMP_3P6PF   | (uint8)( pgaPolarS_REDC_00 >> 2 )), /* G=48 */
        ( pgaPolarS_COMP_3P6PF   | (uint8)( pgaPolarS_REDC_00 >> 2 ))  /* G=50 */
    };
    
    /* Only set new gain if it is a valid gain */
    if( gain <= pgaPolarS_GAIN_MAX)
    {
        /* Clear resistors, redc, and bias */
        pgaPolarS_CR2_REG &= (uint8)(~(pgaPolarS_RVAL_MASK | pgaPolarS_R20_40B_MASK | 
                                pgaPolarS_REDC_MASK | pgaPolarS_BIAS_MASK ));

        /* Set gain value resistors, redc comp, and bias */
        pgaPolarS_CR2_REG |= (pgaPolarS_GainArray[gain] |
                                ((uint8)(pgaPolarS_GainComp[gain] << 2 ) & pgaPolarS_REDC_MASK));

        /* Clear sc_comp  */
        pgaPolarS_CR1_REG &= (uint8)(~pgaPolarS_COMP_MASK);
        /* Set sc_comp  */
        pgaPolarS_CR1_REG |= ( pgaPolarS_GainComp[gain] | pgaPolarS_COMP_MASK );
    }
}


/* [] END OF FILE */
