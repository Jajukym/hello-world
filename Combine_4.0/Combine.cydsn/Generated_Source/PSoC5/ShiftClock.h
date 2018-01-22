/*******************************************************************************
* File Name: ShiftClock.h
* Version 1.70
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_CLOCK_ShiftClock_H)
#define CY_CLOCK_ShiftClock_H

#include <cytypes.h>
#include <cyfitter.h>

/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v1_70 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

/***************************************
*        Function Prototypes
***************************************/

void ShiftClock_Start(void) ;
void ShiftClock_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void ShiftClock_StopBlock(void) ;
#endif

void ShiftClock_StandbyPower(uint8 state) ;
void ShiftClock_SetDividerRegister(uint16 clkDivider, uint8 reset) ;
uint16 ShiftClock_GetDividerRegister(void) ;
void ShiftClock_SetModeRegister(uint8 modeBitMask) ;
void ShiftClock_ClearModeRegister(uint8 modeBitMask) ;
uint8 ShiftClock_GetModeRegister(void) ;
void ShiftClock_SetSourceRegister(uint8 clkSource) ;
uint8 ShiftClock_GetSourceRegister(void) ;
#if defined(ShiftClock__CFG3)
void ShiftClock_SetPhaseRegister(uint8 clkPhase) ;
uint8 ShiftClock_GetPhaseRegister(void) ;
#endif

#define ShiftClock_Enable()                       ShiftClock_Start()
#define ShiftClock_Disable()                      ShiftClock_Stop()
#define ShiftClock_SetDivider(clkDivider)         ShiftClock_SetDividerRegister(clkDivider, 1)
#define ShiftClock_SetDividerValue(clkDivider)    ShiftClock_SetDividerRegister((clkDivider) - 1, 1)
#define ShiftClock_SetMode(clkMode)               ShiftClock_SetModeRegister(clkMode)
#define ShiftClock_SetSource(clkSource)           ShiftClock_SetSourceRegister(clkSource)
#if defined(ShiftClock__CFG3)
#define ShiftClock_SetPhase(clkPhase)             ShiftClock_SetPhaseRegister(clkPhase)
#define ShiftClock_SetPhaseValue(clkPhase)        ShiftClock_SetPhaseRegister((clkPhase) + 1)
#endif


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define ShiftClock_CLKEN              (* (reg8 *) ShiftClock__PM_ACT_CFG)
#define ShiftClock_CLKEN_PTR          ((reg8 *) ShiftClock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define ShiftClock_CLKSTBY            (* (reg8 *) ShiftClock__PM_STBY_CFG)
#define ShiftClock_CLKSTBY_PTR        ((reg8 *) ShiftClock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define ShiftClock_DIV_LSB            (* (reg8 *) ShiftClock__CFG0)
#define ShiftClock_DIV_LSB_PTR        ((reg8 *) ShiftClock__CFG0)
#define ShiftClock_DIV_PTR            ((reg16 *) ShiftClock__CFG0)

/* Clock MSB divider configuration register. */
#define ShiftClock_DIV_MSB            (* (reg8 *) ShiftClock__CFG1)
#define ShiftClock_DIV_MSB_PTR        ((reg8 *) ShiftClock__CFG1)

/* Mode and source configuration register */
#define ShiftClock_MOD_SRC            (* (reg8 *) ShiftClock__CFG2)
#define ShiftClock_MOD_SRC_PTR        ((reg8 *) ShiftClock__CFG2)

#if defined(ShiftClock__CFG3)
/* Analog clock phase configuration register */
#define ShiftClock_PHASE              (* (reg8 *) ShiftClock__CFG3)
#define ShiftClock_PHASE_PTR          ((reg8 *) ShiftClock__CFG3)
#endif


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define ShiftClock_CLKEN_MASK         ShiftClock__PM_ACT_MSK
#define ShiftClock_CLKSTBY_MASK       ShiftClock__PM_STBY_MSK

/* CFG2 field masks */
#define ShiftClock_SRC_SEL_MSK        ShiftClock__CFG2_SRC_SEL_MASK
#define ShiftClock_MODE_MASK          (~(ShiftClock_SRC_SEL_MSK))

#if defined(ShiftClock__CFG3)
/* CFG3 phase mask */
#define ShiftClock_PHASE_MASK         ShiftClock__CFG3_PHASE_DLY_MASK
#endif

#endif /* CY_CLOCK_ShiftClock_H */


/* [] END OF FILE */
