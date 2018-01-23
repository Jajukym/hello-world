/*******************************************************************************
* File Name: clockButtonRead.h
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

#if !defined(CY_CLOCK_clockButtonRead_H)
#define CY_CLOCK_clockButtonRead_H

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

void clockButtonRead_Start(void) ;
void clockButtonRead_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clockButtonRead_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clockButtonRead_StandbyPower(uint8 state) ;
void clockButtonRead_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clockButtonRead_GetDividerRegister(void) ;
void clockButtonRead_SetModeRegister(uint8 modeBitMask) ;
void clockButtonRead_ClearModeRegister(uint8 modeBitMask) ;
uint8 clockButtonRead_GetModeRegister(void) ;
void clockButtonRead_SetSourceRegister(uint8 clkSource) ;
uint8 clockButtonRead_GetSourceRegister(void) ;
#if defined(clockButtonRead__CFG3)
void clockButtonRead_SetPhaseRegister(uint8 clkPhase) ;
uint8 clockButtonRead_GetPhaseRegister(void) ;
#endif /* defined(clockButtonRead__CFG3) */

#define clockButtonRead_Enable()                       clockButtonRead_Start()
#define clockButtonRead_Disable()                      clockButtonRead_Stop()
#define clockButtonRead_SetDivider(clkDivider)         clockButtonRead_SetDividerRegister(clkDivider, 1u)
#define clockButtonRead_SetDividerValue(clkDivider)    clockButtonRead_SetDividerRegister((clkDivider) - 1u, 1u)
#define clockButtonRead_SetMode(clkMode)               clockButtonRead_SetModeRegister(clkMode)
#define clockButtonRead_SetSource(clkSource)           clockButtonRead_SetSourceRegister(clkSource)
#if defined(clockButtonRead__CFG3)
#define clockButtonRead_SetPhase(clkPhase)             clockButtonRead_SetPhaseRegister(clkPhase)
#define clockButtonRead_SetPhaseValue(clkPhase)        clockButtonRead_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(clockButtonRead__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clockButtonRead_CLKEN              (* (reg8 *) clockButtonRead__PM_ACT_CFG)
#define clockButtonRead_CLKEN_PTR          ((reg8 *) clockButtonRead__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clockButtonRead_CLKSTBY            (* (reg8 *) clockButtonRead__PM_STBY_CFG)
#define clockButtonRead_CLKSTBY_PTR        ((reg8 *) clockButtonRead__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clockButtonRead_DIV_LSB            (* (reg8 *) clockButtonRead__CFG0)
#define clockButtonRead_DIV_LSB_PTR        ((reg8 *) clockButtonRead__CFG0)
#define clockButtonRead_DIV_PTR            ((reg16 *) clockButtonRead__CFG0)

/* Clock MSB divider configuration register. */
#define clockButtonRead_DIV_MSB            (* (reg8 *) clockButtonRead__CFG1)
#define clockButtonRead_DIV_MSB_PTR        ((reg8 *) clockButtonRead__CFG1)

/* Mode and source configuration register */
#define clockButtonRead_MOD_SRC            (* (reg8 *) clockButtonRead__CFG2)
#define clockButtonRead_MOD_SRC_PTR        ((reg8 *) clockButtonRead__CFG2)

#if defined(clockButtonRead__CFG3)
/* Analog clock phase configuration register */
#define clockButtonRead_PHASE              (* (reg8 *) clockButtonRead__CFG3)
#define clockButtonRead_PHASE_PTR          ((reg8 *) clockButtonRead__CFG3)
#endif /* defined(clockButtonRead__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clockButtonRead_CLKEN_MASK         clockButtonRead__PM_ACT_MSK
#define clockButtonRead_CLKSTBY_MASK       clockButtonRead__PM_STBY_MSK

/* CFG2 field masks */
#define clockButtonRead_SRC_SEL_MSK        clockButtonRead__CFG2_SRC_SEL_MASK
#define clockButtonRead_MODE_MASK          (~(clockButtonRead_SRC_SEL_MSK))

#if defined(clockButtonRead__CFG3)
/* CFG3 phase mask */
#define clockButtonRead_PHASE_MASK         clockButtonRead__CFG3_PHASE_DLY_MASK
#endif /* defined(clockButtonRead__CFG3) */

#endif /* CY_CLOCK_clockButtonRead_H */


/* [] END OF FILE */
