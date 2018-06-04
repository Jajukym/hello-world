/*******************************************************************************
* File Name: clkDebounce.h
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

#if !defined(CY_CLOCK_clkDebounce_H)
#define CY_CLOCK_clkDebounce_H

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

void clkDebounce_Start(void) ;
void clkDebounce_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clkDebounce_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clkDebounce_StandbyPower(uint8 state) ;
void clkDebounce_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clkDebounce_GetDividerRegister(void) ;
void clkDebounce_SetModeRegister(uint8 modeBitMask) ;
void clkDebounce_ClearModeRegister(uint8 modeBitMask) ;
uint8 clkDebounce_GetModeRegister(void) ;
void clkDebounce_SetSourceRegister(uint8 clkSource) ;
uint8 clkDebounce_GetSourceRegister(void) ;
#if defined(clkDebounce__CFG3)
void clkDebounce_SetPhaseRegister(uint8 clkPhase) ;
uint8 clkDebounce_GetPhaseRegister(void) ;
#endif /* defined(clkDebounce__CFG3) */

#define clkDebounce_Enable()                       clkDebounce_Start()
#define clkDebounce_Disable()                      clkDebounce_Stop()
#define clkDebounce_SetDivider(clkDivider)         clkDebounce_SetDividerRegister(clkDivider, 1u)
#define clkDebounce_SetDividerValue(clkDivider)    clkDebounce_SetDividerRegister((clkDivider) - 1u, 1u)
#define clkDebounce_SetMode(clkMode)               clkDebounce_SetModeRegister(clkMode)
#define clkDebounce_SetSource(clkSource)           clkDebounce_SetSourceRegister(clkSource)
#if defined(clkDebounce__CFG3)
#define clkDebounce_SetPhase(clkPhase)             clkDebounce_SetPhaseRegister(clkPhase)
#define clkDebounce_SetPhaseValue(clkPhase)        clkDebounce_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clkDebounce__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clkDebounce_CLKEN              (* (reg8 *) clkDebounce__PM_ACT_CFG)
#define clkDebounce_CLKEN_PTR          ((reg8 *) clkDebounce__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clkDebounce_CLKSTBY            (* (reg8 *) clkDebounce__PM_STBY_CFG)
#define clkDebounce_CLKSTBY_PTR        ((reg8 *) clkDebounce__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clkDebounce_DIV_LSB            (* (reg8 *) clkDebounce__CFG0)
#define clkDebounce_DIV_LSB_PTR        ((reg8 *) clkDebounce__CFG0)
#define clkDebounce_DIV_PTR            ((reg16 *) clkDebounce__CFG0)

/* Clock MSB divider configuration register. */
#define clkDebounce_DIV_MSB            (* (reg8 *) clkDebounce__CFG1)
#define clkDebounce_DIV_MSB_PTR        ((reg8 *) clkDebounce__CFG1)

/* Mode and source configuration register */
#define clkDebounce_MOD_SRC            (* (reg8 *) clkDebounce__CFG2)
#define clkDebounce_MOD_SRC_PTR        ((reg8 *) clkDebounce__CFG2)

#if defined(clkDebounce__CFG3)
/* Analog clock phase configuration register */
#define clkDebounce_PHASE              (* (reg8 *) clkDebounce__CFG3)
#define clkDebounce_PHASE_PTR          ((reg8 *) clkDebounce__CFG3)
#endif /* defined(clkDebounce__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clkDebounce_CLKEN_MASK         clkDebounce__PM_ACT_MSK
#define clkDebounce_CLKSTBY_MASK       clkDebounce__PM_STBY_MSK

/* CFG2 field masks */
#define clkDebounce_SRC_SEL_MSK        clkDebounce__CFG2_SRC_SEL_MASK
#define clkDebounce_MODE_MASK          (~(clkDebounce_SRC_SEL_MSK))

#if defined(clkDebounce__CFG3)
/* CFG3 phase mask */
#define clkDebounce_PHASE_MASK         clkDebounce__CFG3_PHASE_DLY_MASK
#endif /* defined(clkDebounce__CFG3) */

#endif /* CY_CLOCK_clkDebounce_H */


/* [] END OF FILE */
