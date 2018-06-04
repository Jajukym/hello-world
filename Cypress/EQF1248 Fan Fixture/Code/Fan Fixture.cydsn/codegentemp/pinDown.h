/*******************************************************************************
* File Name: pinDown.h  
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

#if !defined(CY_PINS_pinDown_H) /* Pins pinDown_H */
#define CY_PINS_pinDown_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinDown_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinDown_Write(uint8 value) ;
void    pinDown_SetDriveMode(uint8 mode) ;
uint8   pinDown_ReadDataReg(void) ;
uint8   pinDown_Read(void) ;
void    pinDown_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   pinDown_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinDown_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define pinDown_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define pinDown_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define pinDown_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define pinDown_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define pinDown_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define pinDown_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define pinDown_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define pinDown_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinDown_MASK               pinDown__MASK
#define pinDown_SHIFT              pinDown__SHIFT
#define pinDown_WIDTH              1u

/* Interrupt constants */
#if defined(pinDown__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinDown_SetInterruptMode() function.
     *  @{
     */
        #define pinDown_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define pinDown_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define pinDown_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define pinDown_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define pinDown_INTR_MASK      (0x01u)
#endif /* (pinDown__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinDown_PS                     (* (reg8 *) pinDown__PS)
/* Data Register */
#define pinDown_DR                     (* (reg8 *) pinDown__DR)
/* Port Number */
#define pinDown_PRT_NUM                (* (reg8 *) pinDown__PRT) 
/* Connect to Analog Globals */                                                  
#define pinDown_AG                     (* (reg8 *) pinDown__AG)                       
/* Analog MUX bux enable */
#define pinDown_AMUX                   (* (reg8 *) pinDown__AMUX) 
/* Bidirectional Enable */                                                        
#define pinDown_BIE                    (* (reg8 *) pinDown__BIE)
/* Bit-mask for Aliased Register Access */
#define pinDown_BIT_MASK               (* (reg8 *) pinDown__BIT_MASK)
/* Bypass Enable */
#define pinDown_BYP                    (* (reg8 *) pinDown__BYP)
/* Port wide control signals */                                                   
#define pinDown_CTL                    (* (reg8 *) pinDown__CTL)
/* Drive Modes */
#define pinDown_DM0                    (* (reg8 *) pinDown__DM0) 
#define pinDown_DM1                    (* (reg8 *) pinDown__DM1)
#define pinDown_DM2                    (* (reg8 *) pinDown__DM2) 
/* Input Buffer Disable Override */
#define pinDown_INP_DIS                (* (reg8 *) pinDown__INP_DIS)
/* LCD Common or Segment Drive */
#define pinDown_LCD_COM_SEG            (* (reg8 *) pinDown__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinDown_LCD_EN                 (* (reg8 *) pinDown__LCD_EN)
/* Slew Rate Control */
#define pinDown_SLW                    (* (reg8 *) pinDown__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinDown_PRTDSI__CAPS_SEL       (* (reg8 *) pinDown__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinDown_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinDown__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinDown_PRTDSI__OE_SEL0        (* (reg8 *) pinDown__PRTDSI__OE_SEL0) 
#define pinDown_PRTDSI__OE_SEL1        (* (reg8 *) pinDown__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinDown_PRTDSI__OUT_SEL0       (* (reg8 *) pinDown__PRTDSI__OUT_SEL0) 
#define pinDown_PRTDSI__OUT_SEL1       (* (reg8 *) pinDown__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinDown_PRTDSI__SYNC_OUT       (* (reg8 *) pinDown__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinDown__SIO_CFG)
    #define pinDown_SIO_HYST_EN        (* (reg8 *) pinDown__SIO_HYST_EN)
    #define pinDown_SIO_REG_HIFREQ     (* (reg8 *) pinDown__SIO_REG_HIFREQ)
    #define pinDown_SIO_CFG            (* (reg8 *) pinDown__SIO_CFG)
    #define pinDown_SIO_DIFF           (* (reg8 *) pinDown__SIO_DIFF)
#endif /* (pinDown__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinDown__INTSTAT)
    #define pinDown_INTSTAT             (* (reg8 *) pinDown__INTSTAT)
    #define pinDown_SNAP                (* (reg8 *) pinDown__SNAP)
    
	#define pinDown_0_INTTYPE_REG 		(* (reg8 *) pinDown__0__INTTYPE)
#endif /* (pinDown__INTSTAT) */

#endif /* End Pins pinDown_H */


/* [] END OF FILE */
