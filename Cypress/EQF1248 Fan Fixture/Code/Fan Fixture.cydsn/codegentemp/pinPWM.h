/*******************************************************************************
* File Name: pinPWM.h  
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

#if !defined(CY_PINS_pinPWM_H) /* Pins pinPWM_H */
#define CY_PINS_pinPWM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinPWM_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinPWM_Write(uint8 value) ;
void    pinPWM_SetDriveMode(uint8 mode) ;
uint8   pinPWM_ReadDataReg(void) ;
uint8   pinPWM_Read(void) ;
void    pinPWM_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   pinPWM_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinPWM_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define pinPWM_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define pinPWM_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define pinPWM_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define pinPWM_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define pinPWM_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define pinPWM_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define pinPWM_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define pinPWM_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinPWM_MASK               pinPWM__MASK
#define pinPWM_SHIFT              pinPWM__SHIFT
#define pinPWM_WIDTH              1u

/* Interrupt constants */
#if defined(pinPWM__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinPWM_SetInterruptMode() function.
     *  @{
     */
        #define pinPWM_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define pinPWM_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define pinPWM_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define pinPWM_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define pinPWM_INTR_MASK      (0x01u)
#endif /* (pinPWM__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinPWM_PS                     (* (reg8 *) pinPWM__PS)
/* Data Register */
#define pinPWM_DR                     (* (reg8 *) pinPWM__DR)
/* Port Number */
#define pinPWM_PRT_NUM                (* (reg8 *) pinPWM__PRT) 
/* Connect to Analog Globals */                                                  
#define pinPWM_AG                     (* (reg8 *) pinPWM__AG)                       
/* Analog MUX bux enable */
#define pinPWM_AMUX                   (* (reg8 *) pinPWM__AMUX) 
/* Bidirectional Enable */                                                        
#define pinPWM_BIE                    (* (reg8 *) pinPWM__BIE)
/* Bit-mask for Aliased Register Access */
#define pinPWM_BIT_MASK               (* (reg8 *) pinPWM__BIT_MASK)
/* Bypass Enable */
#define pinPWM_BYP                    (* (reg8 *) pinPWM__BYP)
/* Port wide control signals */                                                   
#define pinPWM_CTL                    (* (reg8 *) pinPWM__CTL)
/* Drive Modes */
#define pinPWM_DM0                    (* (reg8 *) pinPWM__DM0) 
#define pinPWM_DM1                    (* (reg8 *) pinPWM__DM1)
#define pinPWM_DM2                    (* (reg8 *) pinPWM__DM2) 
/* Input Buffer Disable Override */
#define pinPWM_INP_DIS                (* (reg8 *) pinPWM__INP_DIS)
/* LCD Common or Segment Drive */
#define pinPWM_LCD_COM_SEG            (* (reg8 *) pinPWM__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinPWM_LCD_EN                 (* (reg8 *) pinPWM__LCD_EN)
/* Slew Rate Control */
#define pinPWM_SLW                    (* (reg8 *) pinPWM__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinPWM_PRTDSI__CAPS_SEL       (* (reg8 *) pinPWM__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinPWM_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinPWM__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinPWM_PRTDSI__OE_SEL0        (* (reg8 *) pinPWM__PRTDSI__OE_SEL0) 
#define pinPWM_PRTDSI__OE_SEL1        (* (reg8 *) pinPWM__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinPWM_PRTDSI__OUT_SEL0       (* (reg8 *) pinPWM__PRTDSI__OUT_SEL0) 
#define pinPWM_PRTDSI__OUT_SEL1       (* (reg8 *) pinPWM__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinPWM_PRTDSI__SYNC_OUT       (* (reg8 *) pinPWM__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinPWM__SIO_CFG)
    #define pinPWM_SIO_HYST_EN        (* (reg8 *) pinPWM__SIO_HYST_EN)
    #define pinPWM_SIO_REG_HIFREQ     (* (reg8 *) pinPWM__SIO_REG_HIFREQ)
    #define pinPWM_SIO_CFG            (* (reg8 *) pinPWM__SIO_CFG)
    #define pinPWM_SIO_DIFF           (* (reg8 *) pinPWM__SIO_DIFF)
#endif /* (pinPWM__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinPWM__INTSTAT)
    #define pinPWM_INTSTAT             (* (reg8 *) pinPWM__INTSTAT)
    #define pinPWM_SNAP                (* (reg8 *) pinPWM__SNAP)
    
	#define pinPWM_0_INTTYPE_REG 		(* (reg8 *) pinPWM__0__INTTYPE)
#endif /* (pinPWM__INTSTAT) */

#endif /* End Pins pinPWM_H */


/* [] END OF FILE */
