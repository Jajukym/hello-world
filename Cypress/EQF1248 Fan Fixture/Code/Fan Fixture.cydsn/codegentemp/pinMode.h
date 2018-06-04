/*******************************************************************************
* File Name: pinMode.h  
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

#if !defined(CY_PINS_pinMode_H) /* Pins pinMode_H */
#define CY_PINS_pinMode_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinMode_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinMode_Write(uint8 value) ;
void    pinMode_SetDriveMode(uint8 mode) ;
uint8   pinMode_ReadDataReg(void) ;
uint8   pinMode_Read(void) ;
void    pinMode_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   pinMode_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinMode_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define pinMode_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define pinMode_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define pinMode_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define pinMode_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define pinMode_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define pinMode_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define pinMode_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define pinMode_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinMode_MASK               pinMode__MASK
#define pinMode_SHIFT              pinMode__SHIFT
#define pinMode_WIDTH              1u

/* Interrupt constants */
#if defined(pinMode__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinMode_SetInterruptMode() function.
     *  @{
     */
        #define pinMode_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define pinMode_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define pinMode_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define pinMode_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define pinMode_INTR_MASK      (0x01u)
#endif /* (pinMode__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinMode_PS                     (* (reg8 *) pinMode__PS)
/* Data Register */
#define pinMode_DR                     (* (reg8 *) pinMode__DR)
/* Port Number */
#define pinMode_PRT_NUM                (* (reg8 *) pinMode__PRT) 
/* Connect to Analog Globals */                                                  
#define pinMode_AG                     (* (reg8 *) pinMode__AG)                       
/* Analog MUX bux enable */
#define pinMode_AMUX                   (* (reg8 *) pinMode__AMUX) 
/* Bidirectional Enable */                                                        
#define pinMode_BIE                    (* (reg8 *) pinMode__BIE)
/* Bit-mask for Aliased Register Access */
#define pinMode_BIT_MASK               (* (reg8 *) pinMode__BIT_MASK)
/* Bypass Enable */
#define pinMode_BYP                    (* (reg8 *) pinMode__BYP)
/* Port wide control signals */                                                   
#define pinMode_CTL                    (* (reg8 *) pinMode__CTL)
/* Drive Modes */
#define pinMode_DM0                    (* (reg8 *) pinMode__DM0) 
#define pinMode_DM1                    (* (reg8 *) pinMode__DM1)
#define pinMode_DM2                    (* (reg8 *) pinMode__DM2) 
/* Input Buffer Disable Override */
#define pinMode_INP_DIS                (* (reg8 *) pinMode__INP_DIS)
/* LCD Common or Segment Drive */
#define pinMode_LCD_COM_SEG            (* (reg8 *) pinMode__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinMode_LCD_EN                 (* (reg8 *) pinMode__LCD_EN)
/* Slew Rate Control */
#define pinMode_SLW                    (* (reg8 *) pinMode__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinMode_PRTDSI__CAPS_SEL       (* (reg8 *) pinMode__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinMode_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinMode__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinMode_PRTDSI__OE_SEL0        (* (reg8 *) pinMode__PRTDSI__OE_SEL0) 
#define pinMode_PRTDSI__OE_SEL1        (* (reg8 *) pinMode__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinMode_PRTDSI__OUT_SEL0       (* (reg8 *) pinMode__PRTDSI__OUT_SEL0) 
#define pinMode_PRTDSI__OUT_SEL1       (* (reg8 *) pinMode__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinMode_PRTDSI__SYNC_OUT       (* (reg8 *) pinMode__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinMode__SIO_CFG)
    #define pinMode_SIO_HYST_EN        (* (reg8 *) pinMode__SIO_HYST_EN)
    #define pinMode_SIO_REG_HIFREQ     (* (reg8 *) pinMode__SIO_REG_HIFREQ)
    #define pinMode_SIO_CFG            (* (reg8 *) pinMode__SIO_CFG)
    #define pinMode_SIO_DIFF           (* (reg8 *) pinMode__SIO_DIFF)
#endif /* (pinMode__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinMode__INTSTAT)
    #define pinMode_INTSTAT             (* (reg8 *) pinMode__INTSTAT)
    #define pinMode_SNAP                (* (reg8 *) pinMode__SNAP)
    
	#define pinMode_0_INTTYPE_REG 		(* (reg8 *) pinMode__0__INTTYPE)
#endif /* (pinMode__INTSTAT) */

#endif /* End Pins pinMode_H */


/* [] END OF FILE */
