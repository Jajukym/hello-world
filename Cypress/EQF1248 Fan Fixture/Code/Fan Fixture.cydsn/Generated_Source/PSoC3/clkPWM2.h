/*******************************************************************************
* File Name: clkPWM2.h
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

#if !defined(CY_CLOCK_clkPWM2_H)
#define CY_CLOCK_clkPWM2_H

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

void clkPWM2_Start(void) ;
void clkPWM2_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clkPWM2_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clkPWM2_StandbyPower(uint8 state) ;
void clkPWM2_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clkPWM2_GetDividerRegister(void) ;
void clkPWM2_SetModeRegister(uint8 modeBitMask) ;
void clkPWM2_ClearModeRegister(uint8 modeBitMask) ;
uint8 clkPWM2_GetModeRegister(void) ;
void clkPWM2_SetSourceRegister(uint8 clkSource) ;
uint8 clkPWM2_GetSourceRegister(void) ;
#if defined(clkPWM2__CFG3)
void clkPWM2_SetPhaseRegister(uint8 clkPhase) ;
uint8 clkPWM2_GetPhaseRegister(void) ;
#endif /* defined(clkPWM2__CFG3) */

#define clkPWM2_Enable()                       clkPWM2_Start()
#define clkPWM2_Disable()                      clkPWM2_Stop()
#define clkPWM2_SetDivider(clkDivider)         clkPWM2_SetDividerRegister(clkDivider, 1u)
#define clkPWM2_SetDividerValue(clkDivider)    clkPWM2_SetDividerRegister((clkDivider) - 1u, 1u)
#define clkPWM2_SetMode(clkMode)               clkPWM2_SetModeRegister(clkMode)
#define clkPWM2_SetSource(clkSource)           clkPWM2_SetSourceRegister(clkSource)
#if defined(clkPWM2__CFG3)
#define clkPWM2_SetPhase(clkPhase)             clkPWM2_SetPhaseRegister(clkPhase)
#define clkPWM2_SetPhaseValue(clkPhase)        clkPWM2_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clkPWM2__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clkPWM2_CLKEN              (* (reg8 *) clkPWM2__PM_ACT_CFG)
#define clkPWM2_CLKEN_PTR          ((reg8 *) clkPWM2__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clkPWM2_CLKSTBY            (* (reg8 *) clkPWM2__PM_STBY_CFG)
#define clkPWM2_CLKSTBY_PTR        ((reg8 *) clkPWM2__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clkPWM2_DIV_LSB            (* (reg8 *) clkPWM2__CFG0)
#define clkPWM2_DIV_LSB_PTR        ((reg8 *) clkPWM2__CFG0)
#define clkPWM2_DIV_PTR            ((reg16 *) clkPWM2__CFG0)

/* Clock MSB divider configuration register. */
#define clkPWM2_DIV_MSB            (* (reg8 *) clkPWM2__CFG1)
#define clkPWM2_DIV_MSB_PTR        ((reg8 *) clkPWM2__CFG1)

/* Mode and source configuration register */
#define clkPWM2_MOD_SRC            (* (reg8 *) clkPWM2__CFG2)
#define clkPWM2_MOD_SRC_PTR        ((reg8 *) clkPWM2__CFG2)

#if defined(clkPWM2__CFG3)
/* Analog clock phase configuration register */
#define clkPWM2_PHASE              (* (reg8 *) clkPWM2__CFG3)
#define clkPWM2_PHASE_PTR          ((reg8 *) clkPWM2__CFG3)
#endif /* defined(clkPWM2__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clkPWM2_CLKEN_MASK         clkPWM2__PM_ACT_MSK
#define clkPWM2_CLKSTBY_MASK       clkPWM2__PM_STBY_MSK

/* CFG2 field masks */
#define clkPWM2_SRC_SEL_MSK        clkPWM2__CFG2_SRC_SEL_MASK
#define clkPWM2_MODE_MASK          (~(clkPWM2_SRC_SEL_MSK))

#if defined(clkPWM2__CFG3)
/* CFG3 phase mask */
#define clkPWM2_PHASE_MASK         clkPWM2__CFG3_PHASE_DLY_MASK
#endif /* defined(clkPWM2__CFG3) */

#endif /* CY_CLOCK_clkPWM2_H */


/* [] END OF FILE */
