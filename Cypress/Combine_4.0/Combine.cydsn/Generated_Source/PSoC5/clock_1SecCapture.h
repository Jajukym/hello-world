/*******************************************************************************
* File Name: clock_1SecCapture.h
* Version 2.0
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

#if !defined(CY_CLOCK_clock_1SecCapture_H)
#define CY_CLOCK_clock_1SecCapture_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void clock_1SecCapture_Start(void) ;
void clock_1SecCapture_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void clock_1SecCapture_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void clock_1SecCapture_StandbyPower(uint8 state) ;
void clock_1SecCapture_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 clock_1SecCapture_GetDividerRegister(void) ;
void clock_1SecCapture_SetModeRegister(uint8 modeBitMask) ;
void clock_1SecCapture_ClearModeRegister(uint8 modeBitMask) ;
uint8 clock_1SecCapture_GetModeRegister(void) ;
void clock_1SecCapture_SetSourceRegister(uint8 clkSource) ;
uint8 clock_1SecCapture_GetSourceRegister(void) ;
#if defined(clock_1SecCapture__CFG3)
void clock_1SecCapture_SetPhaseRegister(uint8 clkPhase) ;
uint8 clock_1SecCapture_GetPhaseRegister(void) ;
#endif /* defined(clock_1SecCapture__CFG3) */

#define clock_1SecCapture_Enable()                       clock_1SecCapture_Start()
#define clock_1SecCapture_Disable()                      clock_1SecCapture_Stop()
#define clock_1SecCapture_SetDivider(clkDivider)         clock_1SecCapture_SetDividerRegister(clkDivider, 1)
#define clock_1SecCapture_SetDividerValue(clkDivider)    clock_1SecCapture_SetDividerRegister((clkDivider) - 1, 1)
#define clock_1SecCapture_SetMode(clkMode)               clock_1SecCapture_SetModeRegister(clkMode)
#define clock_1SecCapture_SetSource(clkSource)           clock_1SecCapture_SetSourceRegister(clkSource)
#if defined(clock_1SecCapture__CFG3)
#define clock_1SecCapture_SetPhase(clkPhase)             clock_1SecCapture_SetPhaseRegister(clkPhase)
#define clock_1SecCapture_SetPhaseValue(clkPhase)        clock_1SecCapture_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(clock_1SecCapture__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define clock_1SecCapture_CLKEN              (* (reg8 *) clock_1SecCapture__PM_ACT_CFG)
#define clock_1SecCapture_CLKEN_PTR          ((reg8 *) clock_1SecCapture__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define clock_1SecCapture_CLKSTBY            (* (reg8 *) clock_1SecCapture__PM_STBY_CFG)
#define clock_1SecCapture_CLKSTBY_PTR        ((reg8 *) clock_1SecCapture__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define clock_1SecCapture_DIV_LSB            (* (reg8 *) clock_1SecCapture__CFG0)
#define clock_1SecCapture_DIV_LSB_PTR        ((reg8 *) clock_1SecCapture__CFG0)
#define clock_1SecCapture_DIV_PTR            ((reg16 *) clock_1SecCapture__CFG0)

/* Clock MSB divider configuration register. */
#define clock_1SecCapture_DIV_MSB            (* (reg8 *) clock_1SecCapture__CFG1)
#define clock_1SecCapture_DIV_MSB_PTR        ((reg8 *) clock_1SecCapture__CFG1)

/* Mode and source configuration register */
#define clock_1SecCapture_MOD_SRC            (* (reg8 *) clock_1SecCapture__CFG2)
#define clock_1SecCapture_MOD_SRC_PTR        ((reg8 *) clock_1SecCapture__CFG2)

#if defined(clock_1SecCapture__CFG3)
/* Analog clock phase configuration register */
#define clock_1SecCapture_PHASE              (* (reg8 *) clock_1SecCapture__CFG3)
#define clock_1SecCapture_PHASE_PTR          ((reg8 *) clock_1SecCapture__CFG3)
#endif /* defined(clock_1SecCapture__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define clock_1SecCapture_CLKEN_MASK         clock_1SecCapture__PM_ACT_MSK
#define clock_1SecCapture_CLKSTBY_MASK       clock_1SecCapture__PM_STBY_MSK

/* CFG2 field masks */
#define clock_1SecCapture_SRC_SEL_MSK        clock_1SecCapture__CFG2_SRC_SEL_MASK
#define clock_1SecCapture_MODE_MASK          (~(clock_1SecCapture_SRC_SEL_MSK))

#if defined(clock_1SecCapture__CFG3)
/* CFG3 phase mask */
#define clock_1SecCapture_PHASE_MASK         clock_1SecCapture__CFG3_PHASE_DLY_MASK
#endif /* defined(clock_1SecCapture__CFG3) */

#endif /* CY_CLOCK_clock_1SecCapture_H */


/* [] END OF FILE */
