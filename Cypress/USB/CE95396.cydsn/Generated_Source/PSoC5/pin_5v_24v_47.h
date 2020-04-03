/*******************************************************************************
* File Name: pin_5v_24v_47.h  
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

#if !defined(CY_PINS_pin_5v_24v_47_H) /* Pins pin_5v_24v_47_H */
#define CY_PINS_pin_5v_24v_47_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pin_5v_24v_47_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pin_5v_24v_47__PORT == 15 && ((pin_5v_24v_47__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pin_5v_24v_47_Write(uint8 value);
void    pin_5v_24v_47_SetDriveMode(uint8 mode);
uint8   pin_5v_24v_47_ReadDataReg(void);
uint8   pin_5v_24v_47_Read(void);
void    pin_5v_24v_47_SetInterruptMode(uint16 position, uint16 mode);
uint8   pin_5v_24v_47_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pin_5v_24v_47_SetDriveMode() function.
     *  @{
     */
        #define pin_5v_24v_47_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pin_5v_24v_47_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pin_5v_24v_47_DM_RES_UP          PIN_DM_RES_UP
        #define pin_5v_24v_47_DM_RES_DWN         PIN_DM_RES_DWN
        #define pin_5v_24v_47_DM_OD_LO           PIN_DM_OD_LO
        #define pin_5v_24v_47_DM_OD_HI           PIN_DM_OD_HI
        #define pin_5v_24v_47_DM_STRONG          PIN_DM_STRONG
        #define pin_5v_24v_47_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pin_5v_24v_47_MASK               pin_5v_24v_47__MASK
#define pin_5v_24v_47_SHIFT              pin_5v_24v_47__SHIFT
#define pin_5v_24v_47_WIDTH              1u

/* Interrupt constants */
#if defined(pin_5v_24v_47__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pin_5v_24v_47_SetInterruptMode() function.
     *  @{
     */
        #define pin_5v_24v_47_INTR_NONE      (uint16)(0x0000u)
        #define pin_5v_24v_47_INTR_RISING    (uint16)(0x0001u)
        #define pin_5v_24v_47_INTR_FALLING   (uint16)(0x0002u)
        #define pin_5v_24v_47_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pin_5v_24v_47_INTR_MASK      (0x01u) 
#endif /* (pin_5v_24v_47__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pin_5v_24v_47_PS                     (* (reg8 *) pin_5v_24v_47__PS)
/* Data Register */
#define pin_5v_24v_47_DR                     (* (reg8 *) pin_5v_24v_47__DR)
/* Port Number */
#define pin_5v_24v_47_PRT_NUM                (* (reg8 *) pin_5v_24v_47__PRT) 
/* Connect to Analog Globals */                                                  
#define pin_5v_24v_47_AG                     (* (reg8 *) pin_5v_24v_47__AG)                       
/* Analog MUX bux enable */
#define pin_5v_24v_47_AMUX                   (* (reg8 *) pin_5v_24v_47__AMUX) 
/* Bidirectional Enable */                                                        
#define pin_5v_24v_47_BIE                    (* (reg8 *) pin_5v_24v_47__BIE)
/* Bit-mask for Aliased Register Access */
#define pin_5v_24v_47_BIT_MASK               (* (reg8 *) pin_5v_24v_47__BIT_MASK)
/* Bypass Enable */
#define pin_5v_24v_47_BYP                    (* (reg8 *) pin_5v_24v_47__BYP)
/* Port wide control signals */                                                   
#define pin_5v_24v_47_CTL                    (* (reg8 *) pin_5v_24v_47__CTL)
/* Drive Modes */
#define pin_5v_24v_47_DM0                    (* (reg8 *) pin_5v_24v_47__DM0) 
#define pin_5v_24v_47_DM1                    (* (reg8 *) pin_5v_24v_47__DM1)
#define pin_5v_24v_47_DM2                    (* (reg8 *) pin_5v_24v_47__DM2) 
/* Input Buffer Disable Override */
#define pin_5v_24v_47_INP_DIS                (* (reg8 *) pin_5v_24v_47__INP_DIS)
/* LCD Common or Segment Drive */
#define pin_5v_24v_47_LCD_COM_SEG            (* (reg8 *) pin_5v_24v_47__LCD_COM_SEG)
/* Enable Segment LCD */
#define pin_5v_24v_47_LCD_EN                 (* (reg8 *) pin_5v_24v_47__LCD_EN)
/* Slew Rate Control */
#define pin_5v_24v_47_SLW                    (* (reg8 *) pin_5v_24v_47__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pin_5v_24v_47_PRTDSI__CAPS_SEL       (* (reg8 *) pin_5v_24v_47__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pin_5v_24v_47_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pin_5v_24v_47__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pin_5v_24v_47_PRTDSI__OE_SEL0        (* (reg8 *) pin_5v_24v_47__PRTDSI__OE_SEL0) 
#define pin_5v_24v_47_PRTDSI__OE_SEL1        (* (reg8 *) pin_5v_24v_47__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pin_5v_24v_47_PRTDSI__OUT_SEL0       (* (reg8 *) pin_5v_24v_47__PRTDSI__OUT_SEL0) 
#define pin_5v_24v_47_PRTDSI__OUT_SEL1       (* (reg8 *) pin_5v_24v_47__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pin_5v_24v_47_PRTDSI__SYNC_OUT       (* (reg8 *) pin_5v_24v_47__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pin_5v_24v_47__SIO_CFG)
    #define pin_5v_24v_47_SIO_HYST_EN        (* (reg8 *) pin_5v_24v_47__SIO_HYST_EN)
    #define pin_5v_24v_47_SIO_REG_HIFREQ     (* (reg8 *) pin_5v_24v_47__SIO_REG_HIFREQ)
    #define pin_5v_24v_47_SIO_CFG            (* (reg8 *) pin_5v_24v_47__SIO_CFG)
    #define pin_5v_24v_47_SIO_DIFF           (* (reg8 *) pin_5v_24v_47__SIO_DIFF)
#endif /* (pin_5v_24v_47__SIO_CFG) */

/* Interrupt Registers */
#if defined(pin_5v_24v_47__INTSTAT)
    #define pin_5v_24v_47_INTSTAT            (* (reg8 *) pin_5v_24v_47__INTSTAT)
    #define pin_5v_24v_47_SNAP               (* (reg8 *) pin_5v_24v_47__SNAP)
    
	#define pin_5v_24v_47_0_INTTYPE_REG 		(* (reg8 *) pin_5v_24v_47__0__INTTYPE)
#endif /* (pin_5v_24v_47__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pin_5v_24v_47_H */


/* [] END OF FILE */
