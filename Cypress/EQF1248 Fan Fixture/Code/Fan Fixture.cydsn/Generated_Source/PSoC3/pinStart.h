/*******************************************************************************
* File Name: pinStart.h  
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

#if !defined(CY_PINS_pinStart_H) /* Pins pinStart_H */
#define CY_PINS_pinStart_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinStart_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinStart_Write(uint8 value) ;
void    pinStart_SetDriveMode(uint8 mode) ;
uint8   pinStart_ReadDataReg(void) ;
uint8   pinStart_Read(void) ;
void    pinStart_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   pinStart_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinStart_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define pinStart_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define pinStart_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define pinStart_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define pinStart_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define pinStart_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define pinStart_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define pinStart_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define pinStart_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinStart_MASK               pinStart__MASK
#define pinStart_SHIFT              pinStart__SHIFT
#define pinStart_WIDTH              1u

/* Interrupt constants */
#if defined(pinStart__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinStart_SetInterruptMode() function.
     *  @{
     */
        #define pinStart_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define pinStart_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define pinStart_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define pinStart_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define pinStart_INTR_MASK      (0x01u)
#endif /* (pinStart__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinStart_PS                     (* (reg8 *) pinStart__PS)
/* Data Register */
#define pinStart_DR                     (* (reg8 *) pinStart__DR)
/* Port Number */
#define pinStart_PRT_NUM                (* (reg8 *) pinStart__PRT) 
/* Connect to Analog Globals */                                                  
#define pinStart_AG                     (* (reg8 *) pinStart__AG)                       
/* Analog MUX bux enable */
#define pinStart_AMUX                   (* (reg8 *) pinStart__AMUX) 
/* Bidirectional Enable */                                                        
#define pinStart_BIE                    (* (reg8 *) pinStart__BIE)
/* Bit-mask for Aliased Register Access */
#define pinStart_BIT_MASK               (* (reg8 *) pinStart__BIT_MASK)
/* Bypass Enable */
#define pinStart_BYP                    (* (reg8 *) pinStart__BYP)
/* Port wide control signals */                                                   
#define pinStart_CTL                    (* (reg8 *) pinStart__CTL)
/* Drive Modes */
#define pinStart_DM0                    (* (reg8 *) pinStart__DM0) 
#define pinStart_DM1                    (* (reg8 *) pinStart__DM1)
#define pinStart_DM2                    (* (reg8 *) pinStart__DM2) 
/* Input Buffer Disable Override */
#define pinStart_INP_DIS                (* (reg8 *) pinStart__INP_DIS)
/* LCD Common or Segment Drive */
#define pinStart_LCD_COM_SEG            (* (reg8 *) pinStart__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinStart_LCD_EN                 (* (reg8 *) pinStart__LCD_EN)
/* Slew Rate Control */
#define pinStart_SLW                    (* (reg8 *) pinStart__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinStart_PRTDSI__CAPS_SEL       (* (reg8 *) pinStart__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinStart_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinStart__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinStart_PRTDSI__OE_SEL0        (* (reg8 *) pinStart__PRTDSI__OE_SEL0) 
#define pinStart_PRTDSI__OE_SEL1        (* (reg8 *) pinStart__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinStart_PRTDSI__OUT_SEL0       (* (reg8 *) pinStart__PRTDSI__OUT_SEL0) 
#define pinStart_PRTDSI__OUT_SEL1       (* (reg8 *) pinStart__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinStart_PRTDSI__SYNC_OUT       (* (reg8 *) pinStart__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinStart__SIO_CFG)
    #define pinStart_SIO_HYST_EN        (* (reg8 *) pinStart__SIO_HYST_EN)
    #define pinStart_SIO_REG_HIFREQ     (* (reg8 *) pinStart__SIO_REG_HIFREQ)
    #define pinStart_SIO_CFG            (* (reg8 *) pinStart__SIO_CFG)
    #define pinStart_SIO_DIFF           (* (reg8 *) pinStart__SIO_DIFF)
#endif /* (pinStart__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinStart__INTSTAT)
    #define pinStart_INTSTAT             (* (reg8 *) pinStart__INTSTAT)
    #define pinStart_SNAP                (* (reg8 *) pinStart__SNAP)
    
	#define pinStart_0_INTTYPE_REG 		(* (reg8 *) pinStart__0__INTTYPE)
#endif /* (pinStart__INTSTAT) */

#endif /* End Pins pinStart_H */


/* [] END OF FILE */
