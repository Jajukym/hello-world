/*******************************************************************************
* File Name: clockPulseCount.h
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

#if !defined(CY_CLOCK_clockPulseCount_H)
#define CY_CLOCK_clockPulseCount_H

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

void clockPulseCount_Start(void) ;
void clockPulseCount_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clockPulseCount_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clockPulseCount_StandbyPower(uint8 state) ;
void clockPulseCount_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clockPulseCount_GetDividerRegister(void) ;
void clockPulseCount_SetModeRegister(uint8 modeBitMask) ;
void clockPulseCount_ClearModeRegister(uint8 modeBitMask) ;
uint8 clockPulseCount_GetModeRegister(void) ;
void clockPulseCount_SetSourceRegister(uint8 clkSource) ;
uint8 clockPulseCount_GetSourceRegister(void) ;
#if defined(clockPulseCount__CFG3)
void clockPulseCount_SetPhaseRegister(uint8 clkPhase) ;
uint8 clockPulseCount_GetPhaseRegister(void) ;
#endif /* defined(clockPulseCount__CFG3) */

#define clockPulseCount_Enable()                       clockPulseCount_Start()
#define clockPulseCount_Disable()                      clockPulseCount_Stop()
#define clockPulseCount_SetDivider(clkDivider)         clockPulseCount_SetDividerRegister(clkDivider, 1u)
#define clockPulseCount_SetDividerValue(clkDivider)    clockPulseCount_SetDividerRegister((clkDivider) - 1u, 1u)
#define clockPulseCount_SetMode(clkMode)               clockPulseCount_SetModeRegister(clkMode)
#define clockPulseCount_SetSource(clkSource)           clockPulseCount_SetSourceRegister(clkSource)
#if defined(clockPulseCount__CFG3)
#define clockPulseCount_SetPhase(clkPhase)             clockPulseCount_SetPhaseRegister(clkPhase)
#define clockPulseCount_SetPhaseValue(clkPhase)        clockPulseCount_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clockPulseCount__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clockPulseCount_CLKEN              (* (reg8 *) clockPulseCount__PM_ACT_CFG)
#define clockPulseCount_CLKEN_PTR          ((reg8 *) clockPulseCount__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clockPulseCount_CLKSTBY            (* (reg8 *) clockPulseCount__PM_STBY_CFG)
#define clockPulseCount_CLKSTBY_PTR        ((reg8 *) clockPulseCount__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clockPulseCount_DIV_LSB            (* (reg8 *) clockPulseCount__CFG0)
#define clockPulseCount_DIV_LSB_PTR        ((reg8 *) clockPulseCount__CFG0)
#define clockPulseCount_DIV_PTR            ((reg16 *) clockPulseCount__CFG0)

/* Clock MSB divider configuration register. */
#define clockPulseCount_DIV_MSB            (* (reg8 *) clockPulseCount__CFG1)
#define clockPulseCount_DIV_MSB_PTR        ((reg8 *) clockPulseCount__CFG1)

/* Mode and source configuration register */
#define clockPulseCount_MOD_SRC            (* (reg8 *) clockPulseCount__CFG2)
#define clockPulseCount_MOD_SRC_PTR        ((reg8 *) clockPulseCount__CFG2)

#if defined(clockPulseCount__CFG3)
/* Analog clock phase configuration register */
#define clockPulseCount_PHASE              (* (reg8 *) clockPulseCount__CFG3)
#define clockPulseCount_PHASE_PTR          ((reg8 *) clockPulseCount__CFG3)
#endif /* defined(clockPulseCount__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clockPulseCount_CLKEN_MASK         clockPulseCount__PM_ACT_MSK
#define clockPulseCount_CLKSTBY_MASK       clockPulseCount__PM_STBY_MSK

/* CFG2 field masks */
#define clockPulseCount_SRC_SEL_MSK        clockPulseCount__CFG2_SRC_SEL_MASK
#define clockPulseCount_MODE_MASK          (~(clockPulseCount_SRC_SEL_MSK))

#if defined(clockPulseCount__CFG3)
/* CFG3 phase mask */
#define clockPulseCount_PHASE_MASK         clockPulseCount__CFG3_PHASE_DLY_MASK
#endif /* defined(clockPulseCount__CFG3) */

#endif /* CY_CLOCK_clockPulseCount_H */


/* [] END OF FILE */
