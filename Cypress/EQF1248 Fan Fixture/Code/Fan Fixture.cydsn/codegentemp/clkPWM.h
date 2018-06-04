/*******************************************************************************
* File Name: clkPWM.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_clkPWM_H)
#define CY_CLOCK_clkPWM_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void clkPWM_Start(void) ;
void clkPWM_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clkPWM_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clkPWM_StandbyPower(uint8 state) ;
void clkPWM_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clkPWM_GetDividerRegister(void) ;
void clkPWM_SetModeRegister(uint8 modeBitMask) ;
void clkPWM_ClearModeRegister(uint8 modeBitMask) ;
uint8 clkPWM_GetModeRegister(void) ;
void clkPWM_SetSourceRegister(uint8 clkSource) ;
uint8 clkPWM_GetSourceRegister(void) ;
#if defined(clkPWM__CFG3)
void clkPWM_SetPhaseRegister(uint8 clkPhase) ;
uint8 clkPWM_GetPhaseRegister(void) ;
#endif /* defined(clkPWM__CFG3) */

#define clkPWM_Enable()                       clkPWM_Start()
#define clkPWM_Disable()                      clkPWM_Stop()
#define clkPWM_SetDivider(clkDivider)         clkPWM_SetDividerRegister(clkDivider, 1u)
#define clkPWM_SetDividerValue(clkDivider)    clkPWM_SetDividerRegister((clkDivider) - 1u, 1u)
#define clkPWM_SetMode(clkMode)               clkPWM_SetModeRegister(clkMode)
#define clkPWM_SetSource(clkSource)           clkPWM_SetSourceRegister(clkSource)
#if defined(clkPWM__CFG3)
#define clkPWM_SetPhase(clkPhase)             clkPWM_SetPhaseRegister(clkPhase)
#define clkPWM_SetPhaseValue(clkPhase)        clkPWM_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clkPWM__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clkPWM_CLKEN              (* (reg8 *) clkPWM__PM_ACT_CFG)
#define clkPWM_CLKEN_PTR          ((reg8 *) clkPWM__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clkPWM_CLKSTBY            (* (reg8 *) clkPWM__PM_STBY_CFG)
#define clkPWM_CLKSTBY_PTR        ((reg8 *) clkPWM__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clkPWM_DIV_LSB            (* (reg8 *) clkPWM__CFG0)
#define clkPWM_DIV_LSB_PTR        ((reg8 *) clkPWM__CFG0)
#define clkPWM_DIV_PTR            ((reg16 *) clkPWM__CFG0)

/* Clock MSB divider configuration register. */
#define clkPWM_DIV_MSB            (* (reg8 *) clkPWM__CFG1)
#define clkPWM_DIV_MSB_PTR        ((reg8 *) clkPWM__CFG1)

/* Mode and source configuration register */
#define clkPWM_MOD_SRC            (* (reg8 *) clkPWM__CFG2)
#define clkPWM_MOD_SRC_PTR        ((reg8 *) clkPWM__CFG2)

#if defined(clkPWM__CFG3)
/* Analog clock phase configuration register */
#define clkPWM_PHASE              (* (reg8 *) clkPWM__CFG3)
#define clkPWM_PHASE_PTR          ((reg8 *) clkPWM__CFG3)
#endif /* defined(clkPWM__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clkPWM_CLKEN_MASK         clkPWM__PM_ACT_MSK
#define clkPWM_CLKSTBY_MASK       clkPWM__PM_STBY_MSK

/* CFG2 field masks */
#define clkPWM_SRC_SEL_MSK        clkPWM__CFG2_SRC_SEL_MASK
#define clkPWM_MODE_MASK          (~(clkPWM_SRC_SEL_MSK))

#if defined(clkPWM__CFG3)
/* CFG3 phase mask */
#define clkPWM_PHASE_MASK         clkPWM__CFG3_PHASE_DLY_MASK
#endif /* defined(clkPWM__CFG3) */

#endif /* CY_CLOCK_clkPWM_H */


/* [] END OF FILE */
