/*******************************************************************************
* File Name: pinVFan.h  
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

#if !defined(CY_PINS_pinVFan_H) /* Pins pinVFan_H */
#define CY_PINS_pinVFan_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinVFan_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinVFan_Write(uint8 value) ;
void    pinVFan_SetDriveMode(uint8 mode) ;
uint8   pinVFan_ReadDataReg(void) ;
uint8   pinVFan_Read(void) ;
void    pinVFan_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   pinVFan_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinVFan_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define pinVFan_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define pinVFan_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define pinVFan_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define pinVFan_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define pinVFan_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define pinVFan_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define pinVFan_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define pinVFan_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinVFan_MASK               pinVFan__MASK
#define pinVFan_SHIFT              pinVFan__SHIFT
#define pinVFan_WIDTH              1u

/* Interrupt constants */
#if defined(pinVFan__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinVFan_SetInterruptMode() function.
     *  @{
     */
        #define pinVFan_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define pinVFan_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define pinVFan_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define pinVFan_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define pinVFan_INTR_MASK      (0x01u)
#endif /* (pinVFan__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinVFan_PS                     (* (reg8 *) pinVFan__PS)
/* Data Register */
#define pinVFan_DR                     (* (reg8 *) pinVFan__DR)
/* Port Number */
#define pinVFan_PRT_NUM                (* (reg8 *) pinVFan__PRT) 
/* Connect to Analog Globals */                                                  
#define pinVFan_AG                     (* (reg8 *) pinVFan__AG)                       
/* Analog MUX bux enable */
#define pinVFan_AMUX                   (* (reg8 *) pinVFan__AMUX) 
/* Bidirectional Enable */                                                        
#define pinVFan_BIE                    (* (reg8 *) pinVFan__BIE)
/* Bit-mask for Aliased Register Access */
#define pinVFan_BIT_MASK               (* (reg8 *) pinVFan__BIT_MASK)
/* Bypass Enable */
#define pinVFan_BYP                    (* (reg8 *) pinVFan__BYP)
/* Port wide control signals */                                                   
#define pinVFan_CTL                    (* (reg8 *) pinVFan__CTL)
/* Drive Modes */
#define pinVFan_DM0                    (* (reg8 *) pinVFan__DM0) 
#define pinVFan_DM1                    (* (reg8 *) pinVFan__DM1)
#define pinVFan_DM2                    (* (reg8 *) pinVFan__DM2) 
/* Input Buffer Disable Override */
#define pinVFan_INP_DIS                (* (reg8 *) pinVFan__INP_DIS)
/* LCD Common or Segment Drive */
#define pinVFan_LCD_COM_SEG            (* (reg8 *) pinVFan__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinVFan_LCD_EN                 (* (reg8 *) pinVFan__LCD_EN)
/* Slew Rate Control */
#define pinVFan_SLW                    (* (reg8 *) pinVFan__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinVFan_PRTDSI__CAPS_SEL       (* (reg8 *) pinVFan__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinVFan_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinVFan__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinVFan_PRTDSI__OE_SEL0        (* (reg8 *) pinVFan__PRTDSI__OE_SEL0) 
#define pinVFan_PRTDSI__OE_SEL1        (* (reg8 *) pinVFan__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinVFan_PRTDSI__OUT_SEL0       (* (reg8 *) pinVFan__PRTDSI__OUT_SEL0) 
#define pinVFan_PRTDSI__OUT_SEL1       (* (reg8 *) pinVFan__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinVFan_PRTDSI__SYNC_OUT       (* (reg8 *) pinVFan__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinVFan__SIO_CFG)
    #define pinVFan_SIO_HYST_EN        (* (reg8 *) pinVFan__SIO_HYST_EN)
    #define pinVFan_SIO_REG_HIFREQ     (* (reg8 *) pinVFan__SIO_REG_HIFREQ)
    #define pinVFan_SIO_CFG            (* (reg8 *) pinVFan__SIO_CFG)
    #define pinVFan_SIO_DIFF           (* (reg8 *) pinVFan__SIO_DIFF)
#endif /* (pinVFan__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinVFan__INTSTAT)
    #define pinVFan_INTSTAT             (* (reg8 *) pinVFan__INTSTAT)
    #define pinVFan_SNAP                (* (reg8 *) pinVFan__SNAP)
    
	#define pinVFan_0_INTTYPE_REG 		(* (reg8 *) pinVFan__0__INTTYPE)
#endif /* (pinVFan__INTSTAT) */

#endif /* End Pins pinVFan_H */


/* [] END OF FILE */
