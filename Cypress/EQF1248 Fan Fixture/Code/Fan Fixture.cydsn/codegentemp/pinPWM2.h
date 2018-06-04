/*******************************************************************************
* File Name: pinPWM2.h  
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

#if !defined(CY_PINS_pinPWM2_H) /* Pins pinPWM2_H */
#define CY_PINS_pinPWM2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinPWM2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinPWM2_Write(uint8 value) ;
void    pinPWM2_SetDriveMode(uint8 mode) ;
uint8   pinPWM2_ReadDataReg(void) ;
uint8   pinPWM2_Read(void) ;
void    pinPWM2_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   pinPWM2_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinPWM2_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define pinPWM2_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define pinPWM2_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define pinPWM2_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define pinPWM2_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define pinPWM2_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define pinPWM2_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define pinPWM2_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define pinPWM2_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinPWM2_MASK               pinPWM2__MASK
#define pinPWM2_SHIFT              pinPWM2__SHIFT
#define pinPWM2_WIDTH              1u

/* Interrupt constants */
#if defined(pinPWM2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinPWM2_SetInterruptMode() function.
     *  @{
     */
        #define pinPWM2_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define pinPWM2_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define pinPWM2_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define pinPWM2_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define pinPWM2_INTR_MASK      (0x01u)
#endif /* (pinPWM2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinPWM2_PS                     (* (reg8 *) pinPWM2__PS)
/* Data Register */
#define pinPWM2_DR                     (* (reg8 *) pinPWM2__DR)
/* Port Number */
#define pinPWM2_PRT_NUM                (* (reg8 *) pinPWM2__PRT) 
/* Connect to Analog Globals */                                                  
#define pinPWM2_AG                     (* (reg8 *) pinPWM2__AG)                       
/* Analog MUX bux enable */
#define pinPWM2_AMUX                   (* (reg8 *) pinPWM2__AMUX) 
/* Bidirectional Enable */                                                        
#define pinPWM2_BIE                    (* (reg8 *) pinPWM2__BIE)
/* Bit-mask for Aliased Register Access */
#define pinPWM2_BIT_MASK               (* (reg8 *) pinPWM2__BIT_MASK)
/* Bypass Enable */
#define pinPWM2_BYP                    (* (reg8 *) pinPWM2__BYP)
/* Port wide control signals */                                                   
#define pinPWM2_CTL                    (* (reg8 *) pinPWM2__CTL)
/* Drive Modes */
#define pinPWM2_DM0                    (* (reg8 *) pinPWM2__DM0) 
#define pinPWM2_DM1                    (* (reg8 *) pinPWM2__DM1)
#define pinPWM2_DM2                    (* (reg8 *) pinPWM2__DM2) 
/* Input Buffer Disable Override */
#define pinPWM2_INP_DIS                (* (reg8 *) pinPWM2__INP_DIS)
/* LCD Common or Segment Drive */
#define pinPWM2_LCD_COM_SEG            (* (reg8 *) pinPWM2__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinPWM2_LCD_EN                 (* (reg8 *) pinPWM2__LCD_EN)
/* Slew Rate Control */
#define pinPWM2_SLW                    (* (reg8 *) pinPWM2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinPWM2_PRTDSI__CAPS_SEL       (* (reg8 *) pinPWM2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinPWM2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinPWM2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinPWM2_PRTDSI__OE_SEL0        (* (reg8 *) pinPWM2__PRTDSI__OE_SEL0) 
#define pinPWM2_PRTDSI__OE_SEL1        (* (reg8 *) pinPWM2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinPWM2_PRTDSI__OUT_SEL0       (* (reg8 *) pinPWM2__PRTDSI__OUT_SEL0) 
#define pinPWM2_PRTDSI__OUT_SEL1       (* (reg8 *) pinPWM2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinPWM2_PRTDSI__SYNC_OUT       (* (reg8 *) pinPWM2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinPWM2__SIO_CFG)
    #define pinPWM2_SIO_HYST_EN        (* (reg8 *) pinPWM2__SIO_HYST_EN)
    #define pinPWM2_SIO_REG_HIFREQ     (* (reg8 *) pinPWM2__SIO_REG_HIFREQ)
    #define pinPWM2_SIO_CFG            (* (reg8 *) pinPWM2__SIO_CFG)
    #define pinPWM2_SIO_DIFF           (* (reg8 *) pinPWM2__SIO_DIFF)
#endif /* (pinPWM2__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinPWM2__INTSTAT)
    #define pinPWM2_INTSTAT             (* (reg8 *) pinPWM2__INTSTAT)
    #define pinPWM2_SNAP                (* (reg8 *) pinPWM2__SNAP)
    
	#define pinPWM2_0_INTTYPE_REG 		(* (reg8 *) pinPWM2__0__INTTYPE)
#endif /* (pinPWM2__INTSTAT) */

#endif /* End Pins pinPWM2_H */


/* [] END OF FILE */
