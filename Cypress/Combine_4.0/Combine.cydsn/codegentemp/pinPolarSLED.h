/*******************************************************************************
* File Name: pinPolarSLED.h  
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

#if !defined(CY_PINS_pinPolarSLED_H) /* Pins pinPolarSLED_H */
#define CY_PINS_pinPolarSLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinPolarSLED_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinPolarSLED__PORT == 15 && ((pinPolarSLED__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinPolarSLED_Write(uint8 value);
void    pinPolarSLED_SetDriveMode(uint8 mode);
uint8   pinPolarSLED_ReadDataReg(void);
uint8   pinPolarSLED_Read(void);
void    pinPolarSLED_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinPolarSLED_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinPolarSLED_SetDriveMode() function.
     *  @{
     */
        #define pinPolarSLED_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinPolarSLED_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinPolarSLED_DM_RES_UP          PIN_DM_RES_UP
        #define pinPolarSLED_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinPolarSLED_DM_OD_LO           PIN_DM_OD_LO
        #define pinPolarSLED_DM_OD_HI           PIN_DM_OD_HI
        #define pinPolarSLED_DM_STRONG          PIN_DM_STRONG
        #define pinPolarSLED_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinPolarSLED_MASK               pinPolarSLED__MASK
#define pinPolarSLED_SHIFT              pinPolarSLED__SHIFT
#define pinPolarSLED_WIDTH              1u

/* Interrupt constants */
#if defined(pinPolarSLED__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinPolarSLED_SetInterruptMode() function.
     *  @{
     */
        #define pinPolarSLED_INTR_NONE      (uint16)(0x0000u)
        #define pinPolarSLED_INTR_RISING    (uint16)(0x0001u)
        #define pinPolarSLED_INTR_FALLING   (uint16)(0x0002u)
        #define pinPolarSLED_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinPolarSLED_INTR_MASK      (0x01u) 
#endif /* (pinPolarSLED__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinPolarSLED_PS                     (* (reg8 *) pinPolarSLED__PS)
/* Data Register */
#define pinPolarSLED_DR                     (* (reg8 *) pinPolarSLED__DR)
/* Port Number */
#define pinPolarSLED_PRT_NUM                (* (reg8 *) pinPolarSLED__PRT) 
/* Connect to Analog Globals */                                                  
#define pinPolarSLED_AG                     (* (reg8 *) pinPolarSLED__AG)                       
/* Analog MUX bux enable */
#define pinPolarSLED_AMUX                   (* (reg8 *) pinPolarSLED__AMUX) 
/* Bidirectional Enable */                                                        
#define pinPolarSLED_BIE                    (* (reg8 *) pinPolarSLED__BIE)
/* Bit-mask for Aliased Register Access */
#define pinPolarSLED_BIT_MASK               (* (reg8 *) pinPolarSLED__BIT_MASK)
/* Bypass Enable */
#define pinPolarSLED_BYP                    (* (reg8 *) pinPolarSLED__BYP)
/* Port wide control signals */                                                   
#define pinPolarSLED_CTL                    (* (reg8 *) pinPolarSLED__CTL)
/* Drive Modes */
#define pinPolarSLED_DM0                    (* (reg8 *) pinPolarSLED__DM0) 
#define pinPolarSLED_DM1                    (* (reg8 *) pinPolarSLED__DM1)
#define pinPolarSLED_DM2                    (* (reg8 *) pinPolarSLED__DM2) 
/* Input Buffer Disable Override */
#define pinPolarSLED_INP_DIS                (* (reg8 *) pinPolarSLED__INP_DIS)
/* LCD Common or Segment Drive */
#define pinPolarSLED_LCD_COM_SEG            (* (reg8 *) pinPolarSLED__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinPolarSLED_LCD_EN                 (* (reg8 *) pinPolarSLED__LCD_EN)
/* Slew Rate Control */
#define pinPolarSLED_SLW                    (* (reg8 *) pinPolarSLED__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinPolarSLED_PRTDSI__CAPS_SEL       (* (reg8 *) pinPolarSLED__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinPolarSLED_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinPolarSLED__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinPolarSLED_PRTDSI__OE_SEL0        (* (reg8 *) pinPolarSLED__PRTDSI__OE_SEL0) 
#define pinPolarSLED_PRTDSI__OE_SEL1        (* (reg8 *) pinPolarSLED__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinPolarSLED_PRTDSI__OUT_SEL0       (* (reg8 *) pinPolarSLED__PRTDSI__OUT_SEL0) 
#define pinPolarSLED_PRTDSI__OUT_SEL1       (* (reg8 *) pinPolarSLED__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinPolarSLED_PRTDSI__SYNC_OUT       (* (reg8 *) pinPolarSLED__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinPolarSLED__SIO_CFG)
    #define pinPolarSLED_SIO_HYST_EN        (* (reg8 *) pinPolarSLED__SIO_HYST_EN)
    #define pinPolarSLED_SIO_REG_HIFREQ     (* (reg8 *) pinPolarSLED__SIO_REG_HIFREQ)
    #define pinPolarSLED_SIO_CFG            (* (reg8 *) pinPolarSLED__SIO_CFG)
    #define pinPolarSLED_SIO_DIFF           (* (reg8 *) pinPolarSLED__SIO_DIFF)
#endif /* (pinPolarSLED__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinPolarSLED__INTSTAT)
    #define pinPolarSLED_INTSTAT            (* (reg8 *) pinPolarSLED__INTSTAT)
    #define pinPolarSLED_SNAP               (* (reg8 *) pinPolarSLED__SNAP)
    
	#define pinPolarSLED_0_INTTYPE_REG 		(* (reg8 *) pinPolarSLED__0__INTTYPE)
#endif /* (pinPolarSLED__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinPolarSLED_H */


/* [] END OF FILE */
