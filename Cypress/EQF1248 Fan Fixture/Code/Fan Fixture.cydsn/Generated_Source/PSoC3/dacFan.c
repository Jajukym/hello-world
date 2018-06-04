/*******************************************************************************
* File Name: dacFan.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "dacFan.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 dacFan_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 dacFan_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static dacFan_backupStruct dacFan_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: dacFan_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void dacFan_Init(void) 
{
    dacFan_CR0 = (dacFan_MODE_V );

    /* Set default data source */
    #if(dacFan_DEFAULT_DATA_SRC != 0 )
        dacFan_CR1 = (dacFan_DEFAULT_CNTL | dacFan_DACBUS_ENABLE) ;
    #else
        dacFan_CR1 = (dacFan_DEFAULT_CNTL | dacFan_DACBUS_DISABLE) ;
    #endif /* (dacFan_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(dacFan_DEFAULT_STRB != 0)
        dacFan_Strobe |= dacFan_STRB_EN ;
    #endif/* (dacFan_DEFAULT_STRB != 0) */

    /* Set default range */
    dacFan_SetRange(dacFan_DEFAULT_RANGE); 

    /* Set default speed */
    dacFan_SetSpeed(dacFan_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: dacFan_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void dacFan_Enable(void) 
{
    dacFan_PWRMGR |= dacFan_ACT_PWR_EN;
    dacFan_STBY_PWRMGR |= dacFan_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(dacFan_restoreVal == 1u) 
        {
             dacFan_CR0 = dacFan_backup.data_value;
             dacFan_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: dacFan_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  dacFan_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void dacFan_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(dacFan_initVar == 0u)
    { 
        dacFan_Init();
        dacFan_initVar = 1u;
    }

    /* Enable power to DAC */
    dacFan_Enable();

    /* Set default value */
    dacFan_SetValue(dacFan_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: dacFan_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void dacFan_Stop(void) 
{
    /* Disble power to DAC */
    dacFan_PWRMGR &= (uint8)(~dacFan_ACT_PWR_EN);
    dacFan_STBY_PWRMGR &= (uint8)(~dacFan_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        dacFan_backup.data_value = dacFan_CR0;
        dacFan_CR0 = dacFan_CUR_MODE_OUT_OFF;
        dacFan_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: dacFan_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void dacFan_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    dacFan_CR0 &= (uint8)(~dacFan_HS_MASK);
    dacFan_CR0 |=  (speed & dacFan_HS_MASK);
}


/*******************************************************************************
* Function Name: dacFan_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void dacFan_SetRange(uint8 range) 
{
    dacFan_CR0 &= (uint8)(~dacFan_RANGE_MASK);      /* Clear existing mode */
    dacFan_CR0 |= (range & dacFan_RANGE_MASK);      /*  Set Range  */
    dacFan_DacTrim();
}


/*******************************************************************************
* Function Name: dacFan_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void dacFan_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 dacFan_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    dacFan_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        dacFan_Data = value;
        CyExitCriticalSection(dacFan_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: dacFan_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void dacFan_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((dacFan_CR0 & dacFan_RANGE_MASK) >> 2) + dacFan_TRIM_M7_1V_RNG_OFFSET;
    dacFan_TR = CY_GET_XTND_REG8((uint8 *)(dacFan_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
