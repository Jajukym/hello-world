/*******************************************************************************
* File Name: pin_12v_enable.h  
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

#if !defined(CY_PINS_pin_12v_enable_H) /* Pins pin_12v_enable_H */
#define CY_PINS_pin_12v_enable_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pin_12v_enable_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pin_12v_enable__PORT == 15 && ((pin_12v_enable__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pin_12v_enable_Write(uint8 value);
void    pin_12v_enable_SetDriveMode(uint8 mode);
uint8   pin_12v_enable_ReadDataReg(void);
uint8   pin_12v_enable_Read(void);
void    pin_12v_enable_SetInterruptMode(uint16 position, uint16 mode);
uint8   pin_12v_enable_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pin_12v_enable_SetDriveMode() function.
     *  @{
     */
        #define pin_12v_enable_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pin_12v_enable_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pin_12v_enable_DM_RES_UP          PIN_DM_RES_UP
        #define pin_12v_enable_DM_RES_DWN         PIN_DM_RES_DWN
        #define pin_12v_enable_DM_OD_LO           PIN_DM_OD_LO
        #define pin_12v_enable_DM_OD_HI           PIN_DM_OD_HI
        #define pin_12v_enable_DM_STRONG          PIN_DM_STRONG
        #define pin_12v_enable_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pin_12v_enable_MASK               pin_12v_enable__MASK
#define pin_12v_enable_SHIFT              pin_12v_enable__SHIFT
#define pin_12v_enable_WIDTH              1u

/* Interrupt constants */
#if defined(pin_12v_enable__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pin_12v_enable_SetInterruptMode() function.
     *  @{
     */
        #define pin_12v_enable_INTR_NONE      (uint16)(0x0000u)
        #define pin_12v_enable_INTR_RISING    (uint16)(0x0001u)
        #define pin_12v_enable_INTR_FALLING   (uint16)(0x0002u)
        #define pin_12v_enable_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pin_12v_enable_INTR_MASK      (0x01u) 
#endif /* (pin_12v_enable__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pin_12v_enable_PS                     (* (reg8 *) pin_12v_enable__PS)
/* Data Register */
#define pin_12v_enable_DR                     (* (reg8 *) pin_12v_enable__DR)
/* Port Number */
#define pin_12v_enable_PRT_NUM                (* (reg8 *) pin_12v_enable__PRT) 
/* Connect to Analog Globals */                                                  
#define pin_12v_enable_AG                     (* (reg8 *) pin_12v_enable__AG)                       
/* Analog MUX bux enable */
#define pin_12v_enable_AMUX                   (* (reg8 *) pin_12v_enable__AMUX) 
/* Bidirectional Enable */                                                        
#define pin_12v_enable_BIE                    (* (reg8 *) pin_12v_enable__BIE)
/* Bit-mask for Aliased Register Access */
#define pin_12v_enable_BIT_MASK               (* (reg8 *) pin_12v_enable__BIT_MASK)
/* Bypass Enable */
#define pin_12v_enable_BYP                    (* (reg8 *) pin_12v_enable__BYP)
/* Port wide control signals */                                                   
#define pin_12v_enable_CTL                    (* (reg8 *) pin_12v_enable__CTL)
/* Drive Modes */
#define pin_12v_enable_DM0                    (* (reg8 *) pin_12v_enable__DM0) 
#define pin_12v_enable_DM1                    (* (reg8 *) pin_12v_enable__DM1)
#define pin_12v_enable_DM2                    (* (reg8 *) pin_12v_enable__DM2) 
/* Input Buffer Disable Override */
#define pin_12v_enable_INP_DIS                (* (reg8 *) pin_12v_enable__INP_DIS)
/* LCD Common or Segment Drive */
#define pin_12v_enable_LCD_COM_SEG            (* (reg8 *) pin_12v_enable__LCD_COM_SEG)
/* Enable Segment LCD */
#define pin_12v_enable_LCD_EN                 (* (reg8 *) pin_12v_enable__LCD_EN)
/* Slew Rate Control */
#define pin_12v_enable_SLW                    (* (reg8 *) pin_12v_enable__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pin_12v_enable_PRTDSI__CAPS_SEL       (* (reg8 *) pin_12v_enable__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pin_12v_enable_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pin_12v_enable__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pin_12v_enable_PRTDSI__OE_SEL0        (* (reg8 *) pin_12v_enable__PRTDSI__OE_SEL0) 
#define pin_12v_enable_PRTDSI__OE_SEL1        (* (reg8 *) pin_12v_enable__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pin_12v_enable_PRTDSI__OUT_SEL0       (* (reg8 *) pin_12v_enable__PRTDSI__OUT_SEL0) 
#define pin_12v_enable_PRTDSI__OUT_SEL1       (* (reg8 *) pin_12v_enable__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pin_12v_enable_PRTDSI__SYNC_OUT       (* (reg8 *) pin_12v_enable__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pin_12v_enable__SIO_CFG)
    #define pin_12v_enable_SIO_HYST_EN        (* (reg8 *) pin_12v_enable__SIO_HYST_EN)
    #define pin_12v_enable_SIO_REG_HIFREQ     (* (reg8 *) pin_12v_enable__SIO_REG_HIFREQ)
    #define pin_12v_enable_SIO_CFG            (* (reg8 *) pin_12v_enable__SIO_CFG)
    #define pin_12v_enable_SIO_DIFF           (* (reg8 *) pin_12v_enable__SIO_DIFF)
#endif /* (pin_12v_enable__SIO_CFG) */

/* Interrupt Registers */
#if defined(pin_12v_enable__INTSTAT)
    #define pin_12v_enable_INTSTAT            (* (reg8 *) pin_12v_enable__INTSTAT)
    #define pin_12v_enable_SNAP               (* (reg8 *) pin_12v_enable__SNAP)
    
	#define pin_12v_enable_0_INTTYPE_REG 		(* (reg8 *) pin_12v_enable__0__INTTYPE)
#endif /* (pin_12v_enable__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pin_12v_enable_H */


/* [] END OF FILE */
