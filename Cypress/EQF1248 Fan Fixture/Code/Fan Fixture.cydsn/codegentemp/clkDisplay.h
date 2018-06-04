/*******************************************************************************
* File Name: clkDisplay.h
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

#if !defined(CY_CLOCK_clkDisplay_H)
#define CY_CLOCK_clkDisplay_H

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

void clkDisplay_Start(void) ;
void clkDisplay_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clkDisplay_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clkDisplay_StandbyPower(uint8 state) ;
void clkDisplay_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clkDisplay_GetDividerRegister(void) ;
void clkDisplay_SetModeRegister(uint8 modeBitMask) ;
void clkDisplay_ClearModeRegister(uint8 modeBitMask) ;
uint8 clkDisplay_GetModeRegister(void) ;
void clkDisplay_SetSourceRegister(uint8 clkSource) ;
uint8 clkDisplay_GetSourceRegister(void) ;
#if defined(clkDisplay__CFG3)
void clkDisplay_SetPhaseRegister(uint8 clkPhase) ;
uint8 clkDisplay_GetPhaseRegister(void) ;
#endif /* defined(clkDisplay__CFG3) */

#define clkDisplay_Enable()                       clkDisplay_Start()
#define clkDisplay_Disable()                      clkDisplay_Stop()
#define clkDisplay_SetDivider(clkDivider)         clkDisplay_SetDividerRegister(clkDivider, 1u)
#define clkDisplay_SetDividerValue(clkDivider)    clkDisplay_SetDividerRegister((clkDivider) - 1u, 1u)
#define clkDisplay_SetMode(clkMode)               clkDisplay_SetModeRegister(clkMode)
#define clkDisplay_SetSource(clkSource)           clkDisplay_SetSourceRegister(clkSource)
#if defined(clkDisplay__CFG3)
#define clkDisplay_SetPhase(clkPhase)             clkDisplay_SetPhaseRegister(clkPhase)
#define clkDisplay_SetPhaseValue(clkPhase)        clkDisplay_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clkDisplay__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clkDisplay_CLKEN              (* (reg8 *) clkDisplay__PM_ACT_CFG)
#define clkDisplay_CLKEN_PTR          ((reg8 *) clkDisplay__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clkDisplay_CLKSTBY            (* (reg8 *) clkDisplay__PM_STBY_CFG)
#define clkDisplay_CLKSTBY_PTR        ((reg8 *) clkDisplay__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clkDisplay_DIV_LSB            (* (reg8 *) clkDisplay__CFG0)
#define clkDisplay_DIV_LSB_PTR        ((reg8 *) clkDisplay__CFG0)
#define clkDisplay_DIV_PTR            ((reg16 *) clkDisplay__CFG0)

/* Clock MSB divider configuration register. */
#define clkDisplay_DIV_MSB            (* (reg8 *) clkDisplay__CFG1)
#define clkDisplay_DIV_MSB_PTR        ((reg8 *) clkDisplay__CFG1)

/* Mode and source configuration register */
#define clkDisplay_MOD_SRC            (* (reg8 *) clkDisplay__CFG2)
#define clkDisplay_MOD_SRC_PTR        ((reg8 *) clkDisplay__CFG2)

#if defined(clkDisplay__CFG3)
/* Analog clock phase configuration register */
#define clkDisplay_PHASE              (* (reg8 *) clkDisplay__CFG3)
#define clkDisplay_PHASE_PTR          ((reg8 *) clkDisplay__CFG3)
#endif /* defined(clkDisplay__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clkDisplay_CLKEN_MASK         clkDisplay__PM_ACT_MSK
#define clkDisplay_CLKSTBY_MASK       clkDisplay__PM_STBY_MSK

/* CFG2 field masks */
#define clkDisplay_SRC_SEL_MSK        clkDisplay__CFG2_SRC_SEL_MASK
#define clkDisplay_MODE_MASK          (~(clkDisplay_SRC_SEL_MSK))

#if defined(clkDisplay__CFG3)
/* CFG3 phase mask */
#define clkDisplay_PHASE_MASK         clkDisplay__CFG3_PHASE_DLY_MASK
#endif /* defined(clkDisplay__CFG3) */

#endif /* CY_CLOCK_clkDisplay_H */


/* [] END OF FILE */
