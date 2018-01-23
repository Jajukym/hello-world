/*******************************************************************************
* File Name: lcdDisplay_LCDPort.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_lcdDisplay_LCDPort_H) /* Pins lcdDisplay_LCDPort_H */
#define CY_PINS_lcdDisplay_LCDPort_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "lcdDisplay_LCDPort_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 lcdDisplay_LCDPort__PORT == 15 && ((lcdDisplay_LCDPort__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    lcdDisplay_LCDPort_Write(uint8 value);
void    lcdDisplay_LCDPort_SetDriveMode(uint8 mode);
uint8   lcdDisplay_LCDPort_ReadDataReg(void);
uint8   lcdDisplay_LCDPort_Read(void);
void    lcdDisplay_LCDPort_SetInterruptMode(uint16 position, uint16 mode);
uint8   lcdDisplay_LCDPort_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the lcdDisplay_LCDPort_SetDriveMode() function.
     *  @{
     */
        #define lcdDisplay_LCDPort_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define lcdDisplay_LCDPort_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define lcdDisplay_LCDPort_DM_RES_UP          PIN_DM_RES_UP
        #define lcdDisplay_LCDPort_DM_RES_DWN         PIN_DM_RES_DWN
        #define lcdDisplay_LCDPort_DM_OD_LO           PIN_DM_OD_LO
        #define lcdDisplay_LCDPort_DM_OD_HI           PIN_DM_OD_HI
        #define lcdDisplay_LCDPort_DM_STRONG          PIN_DM_STRONG
        #define lcdDisplay_LCDPort_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define lcdDisplay_LCDPort_MASK               lcdDisplay_LCDPort__MASK
#define lcdDisplay_LCDPort_SHIFT              lcdDisplay_LCDPort__SHIFT
#define lcdDisplay_LCDPort_WIDTH              7u

/* Interrupt constants */
#if defined(lcdDisplay_LCDPort__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in lcdDisplay_LCDPort_SetInterruptMode() function.
     *  @{
     */
        #define lcdDisplay_LCDPort_INTR_NONE      (uint16)(0x0000u)
        #define lcdDisplay_LCDPort_INTR_RISING    (uint16)(0x0001u)
        #define lcdDisplay_LCDPort_INTR_FALLING   (uint16)(0x0002u)
        #define lcdDisplay_LCDPort_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define lcdDisplay_LCDPort_INTR_MASK      (0x01u) 
#endif /* (lcdDisplay_LCDPort__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define lcdDisplay_LCDPort_PS                     (* (reg8 *) lcdDisplay_LCDPort__PS)
/* Data Register */
#define lcdDisplay_LCDPort_DR                     (* (reg8 *) lcdDisplay_LCDPort__DR)
/* Port Number */
#define lcdDisplay_LCDPort_PRT_NUM                (* (reg8 *) lcdDisplay_LCDPort__PRT) 
/* Connect to Analog Globals */                                                  
#define lcdDisplay_LCDPort_AG                     (* (reg8 *) lcdDisplay_LCDPort__AG)                       
/* Analog MUX bux enable */
#define lcdDisplay_LCDPort_AMUX                   (* (reg8 *) lcdDisplay_LCDPort__AMUX) 
/* Bidirectional Enable */                                                        
#define lcdDisplay_LCDPort_BIE                    (* (reg8 *) lcdDisplay_LCDPort__BIE)
/* Bit-mask for Aliased Register Access */
#define lcdDisplay_LCDPort_BIT_MASK               (* (reg8 *) lcdDisplay_LCDPort__BIT_MASK)
/* Bypass Enable */
#define lcdDisplay_LCDPort_BYP                    (* (reg8 *) lcdDisplay_LCDPort__BYP)
/* Port wide control signals */                                                   
#define lcdDisplay_LCDPort_CTL                    (* (reg8 *) lcdDisplay_LCDPort__CTL)
/* Drive Modes */
#define lcdDisplay_LCDPort_DM0                    (* (reg8 *) lcdDisplay_LCDPort__DM0) 
#define lcdDisplay_LCDPort_DM1                    (* (reg8 *) lcdDisplay_LCDPort__DM1)
#define lcdDisplay_LCDPort_DM2                    (* (reg8 *) lcdDisplay_LCDPort__DM2) 
/* Input Buffer Disable Override */
#define lcdDisplay_LCDPort_INP_DIS                (* (reg8 *) lcdDisplay_LCDPort__INP_DIS)
/* LCD Common or Segment Drive */
#define lcdDisplay_LCDPort_LCD_COM_SEG            (* (reg8 *) lcdDisplay_LCDPort__LCD_COM_SEG)
/* Enable Segment LCD */
#define lcdDisplay_LCDPort_LCD_EN                 (* (reg8 *) lcdDisplay_LCDPort__LCD_EN)
/* Slew Rate Control */
#define lcdDisplay_LCDPort_SLW                    (* (reg8 *) lcdDisplay_LCDPort__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define lcdDisplay_LCDPort_PRTDSI__CAPS_SEL       (* (reg8 *) lcdDisplay_LCDPort__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define lcdDisplay_LCDPort_PRTDSI__DBL_SYNC_IN    (* (reg8 *) lcdDisplay_LCDPort__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define lcdDisplay_LCDPort_PRTDSI__OE_SEL0        (* (reg8 *) lcdDisplay_LCDPort__PRTDSI__OE_SEL0) 
#define lcdDisplay_LCDPort_PRTDSI__OE_SEL1        (* (reg8 *) lcdDisplay_LCDPort__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define lcdDisplay_LCDPort_PRTDSI__OUT_SEL0       (* (reg8 *) lcdDisplay_LCDPort__PRTDSI__OUT_SEL0) 
#define lcdDisplay_LCDPort_PRTDSI__OUT_SEL1       (* (reg8 *) lcdDisplay_LCDPort__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define lcdDisplay_LCDPort_PRTDSI__SYNC_OUT       (* (reg8 *) lcdDisplay_LCDPort__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(lcdDisplay_LCDPort__SIO_CFG)
    #define lcdDisplay_LCDPort_SIO_HYST_EN        (* (reg8 *) lcdDisplay_LCDPort__SIO_HYST_EN)
    #define lcdDisplay_LCDPort_SIO_REG_HIFREQ     (* (reg8 *) lcdDisplay_LCDPort__SIO_REG_HIFREQ)
    #define lcdDisplay_LCDPort_SIO_CFG            (* (reg8 *) lcdDisplay_LCDPort__SIO_CFG)
    #define lcdDisplay_LCDPort_SIO_DIFF           (* (reg8 *) lcdDisplay_LCDPort__SIO_DIFF)
#endif /* (lcdDisplay_LCDPort__SIO_CFG) */

/* Interrupt Registers */
#if defined(lcdDisplay_LCDPort__INTSTAT)
    #define lcdDisplay_LCDPort_INTSTAT            (* (reg8 *) lcdDisplay_LCDPort__INTSTAT)
    #define lcdDisplay_LCDPort_SNAP               (* (reg8 *) lcdDisplay_LCDPort__SNAP)
    
	#define lcdDisplay_LCDPort_0_INTTYPE_REG 		(* (reg8 *) lcdDisplay_LCDPort__0__INTTYPE)
	#define lcdDisplay_LCDPort_1_INTTYPE_REG 		(* (reg8 *) lcdDisplay_LCDPort__1__INTTYPE)
	#define lcdDisplay_LCDPort_2_INTTYPE_REG 		(* (reg8 *) lcdDisplay_LCDPort__2__INTTYPE)
	#define lcdDisplay_LCDPort_3_INTTYPE_REG 		(* (reg8 *) lcdDisplay_LCDPort__3__INTTYPE)
	#define lcdDisplay_LCDPort_4_INTTYPE_REG 		(* (reg8 *) lcdDisplay_LCDPort__4__INTTYPE)
	#define lcdDisplay_LCDPort_5_INTTYPE_REG 		(* (reg8 *) lcdDisplay_LCDPort__5__INTTYPE)
	#define lcdDisplay_LCDPort_6_INTTYPE_REG 		(* (reg8 *) lcdDisplay_LCDPort__6__INTTYPE)
#endif /* (lcdDisplay_LCDPort__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_lcdDisplay_LCDPort_H */


/* [] END OF FILE */
