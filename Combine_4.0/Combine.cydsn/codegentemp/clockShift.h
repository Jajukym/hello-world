/*******************************************************************************
* File Name: clockShift.h
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

#if !defined(CY_CLOCK_clockShift_H)
#define CY_CLOCK_clockShift_H

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

void clockShift_Start(void) ;
void clockShift_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clockShift_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clockShift_StandbyPower(uint8 state) ;
void clockShift_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clockShift_GetDividerRegister(void) ;
void clockShift_SetModeRegister(uint8 modeBitMask) ;
void clockShift_ClearModeRegister(uint8 modeBitMask) ;
uint8 clockShift_GetModeRegister(void) ;
void clockShift_SetSourceRegister(uint8 clkSource) ;
uint8 clockShift_GetSourceRegister(void) ;
#if defined(clockShift__CFG3)
void clockShift_SetPhaseRegister(uint8 clkPhase) ;
uint8 clockShift_GetPhaseRegister(void) ;
#endif /* defined(clockShift__CFG3) */

#define clockShift_Enable()                       clockShift_Start()
#define clockShift_Disable()                      clockShift_Stop()
#define clockShift_SetDivider(clkDivider)         clockShift_SetDividerRegister(clkDivider, 1u)
#define clockShift_SetDividerValue(clkDivider)    clockShift_SetDividerRegister((clkDivider) - 1u, 1u)
#define clockShift_SetMode(clkMode)               clockShift_SetModeRegister(clkMode)
#define clockShift_SetSource(clkSource)           clockShift_SetSourceRegister(clkSource)
#if defined(clockShift__CFG3)
#define clockShift_SetPhase(clkPhase)             clockShift_SetPhaseRegister(clkPhase)
#define clockShift_SetPhaseValue(clkPhase)        clockShift_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clockShift__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clockShift_CLKEN              (* (reg8 *) clockShift__PM_ACT_CFG)
#define clockShift_CLKEN_PTR          ((reg8 *) clockShift__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clockShift_CLKSTBY            (* (reg8 *) clockShift__PM_STBY_CFG)
#define clockShift_CLKSTBY_PTR        ((reg8 *) clockShift__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clockShift_DIV_LSB            (* (reg8 *) clockShift__CFG0)
#define clockShift_DIV_LSB_PTR        ((reg8 *) clockShift__CFG0)
#define clockShift_DIV_PTR            ((reg16 *) clockShift__CFG0)

/* Clock MSB divider configuration register. */
#define clockShift_DIV_MSB            (* (reg8 *) clockShift__CFG1)
#define clockShift_DIV_MSB_PTR        ((reg8 *) clockShift__CFG1)

/* Mode and source configuration register */
#define clockShift_MOD_SRC            (* (reg8 *) clockShift__CFG2)
#define clockShift_MOD_SRC_PTR        ((reg8 *) clockShift__CFG2)

#if defined(clockShift__CFG3)
/* Analog clock phase configuration register */
#define clockShift_PHASE              (* (reg8 *) clockShift__CFG3)
#define clockShift_PHASE_PTR          ((reg8 *) clockShift__CFG3)
#endif /* defined(clockShift__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clockShift_CLKEN_MASK         clockShift__PM_ACT_MSK
#define clockShift_CLKSTBY_MASK       clockShift__PM_STBY_MSK

/* CFG2 field masks */
#define clockShift_SRC_SEL_MSK        clockShift__CFG2_SRC_SEL_MASK
#define clockShift_MODE_MASK          (~(clockShift_SRC_SEL_MSK))

#if defined(clockShift__CFG3)
/* CFG3 phase mask */
#define clockShift_PHASE_MASK         clockShift__CFG3_PHASE_DLY_MASK
#endif /* defined(clockShift__CFG3) */

#endif /* CY_CLOCK_clockShift_H */


/* [] END OF FILE */
