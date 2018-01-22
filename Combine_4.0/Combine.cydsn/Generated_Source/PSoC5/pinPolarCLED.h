/*******************************************************************************
* File Name: pinPolarCLED.h  
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

#if !defined(CY_PINS_pinPolarCLED_H) /* Pins pinPolarCLED_H */
#define CY_PINS_pinPolarCLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinPolarCLED_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinPolarCLED__PORT == 15 && ((pinPolarCLED__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinPolarCLED_Write(uint8 value);
void    pinPolarCLED_SetDriveMode(uint8 mode);
uint8   pinPolarCLED_ReadDataReg(void);
uint8   pinPolarCLED_Read(void);
void    pinPolarCLED_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinPolarCLED_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinPolarCLED_SetDriveMode() function.
     *  @{
     */
        #define pinPolarCLED_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinPolarCLED_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinPolarCLED_DM_RES_UP          PIN_DM_RES_UP
        #define pinPolarCLED_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinPolarCLED_DM_OD_LO           PIN_DM_OD_LO
        #define pinPolarCLED_DM_OD_HI           PIN_DM_OD_HI
        #define pinPolarCLED_DM_STRONG          PIN_DM_STRONG
        #define pinPolarCLED_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinPolarCLED_MASK               pinPolarCLED__MASK
#define pinPolarCLED_SHIFT              pinPolarCLED__SHIFT
#define pinPolarCLED_WIDTH              1u

/* Interrupt constants */
#if defined(pinPolarCLED__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinPolarCLED_SetInterruptMode() function.
     *  @{
     */
        #define pinPolarCLED_INTR_NONE      (uint16)(0x0000u)
        #define pinPolarCLED_INTR_RISING    (uint16)(0x0001u)
        #define pinPolarCLED_INTR_FALLING   (uint16)(0x0002u)
        #define pinPolarCLED_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinPolarCLED_INTR_MASK      (0x01u) 
#endif /* (pinPolarCLED__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinPolarCLED_PS                     (* (reg8 *) pinPolarCLED__PS)
/* Data Register */
#define pinPolarCLED_DR                     (* (reg8 *) pinPolarCLED__DR)
/* Port Number */
#define pinPolarCLED_PRT_NUM                (* (reg8 *) pinPolarCLED__PRT) 
/* Connect to Analog Globals */                                                  
#define pinPolarCLED_AG                     (* (reg8 *) pinPolarCLED__AG)                       
/* Analog MUX bux enable */
#define pinPolarCLED_AMUX                   (* (reg8 *) pinPolarCLED__AMUX) 
/* Bidirectional Enable */                                                        
#define pinPolarCLED_BIE                    (* (reg8 *) pinPolarCLED__BIE)
/* Bit-mask for Aliased Register Access */
#define pinPolarCLED_BIT_MASK               (* (reg8 *) pinPolarCLED__BIT_MASK)
/* Bypass Enable */
#define pinPolarCLED_BYP                    (* (reg8 *) pinPolarCLED__BYP)
/* Port wide control signals */                                                   
#define pinPolarCLED_CTL                    (* (reg8 *) pinPolarCLED__CTL)
/* Drive Modes */
#define pinPolarCLED_DM0                    (* (reg8 *) pinPolarCLED__DM0) 
#define pinPolarCLED_DM1                    (* (reg8 *) pinPolarCLED__DM1)
#define pinPolarCLED_DM2                    (* (reg8 *) pinPolarCLED__DM2) 
/* Input Buffer Disable Override */
#define pinPolarCLED_INP_DIS                (* (reg8 *) pinPolarCLED__INP_DIS)
/* LCD Common or Segment Drive */
#define pinPolarCLED_LCD_COM_SEG            (* (reg8 *) pinPolarCLED__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinPolarCLED_LCD_EN                 (* (reg8 *) pinPolarCLED__LCD_EN)
/* Slew Rate Control */
#define pinPolarCLED_SLW                    (* (reg8 *) pinPolarCLED__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinPolarCLED_PRTDSI__CAPS_SEL       (* (reg8 *) pinPolarCLED__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinPolarCLED_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinPolarCLED__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinPolarCLED_PRTDSI__OE_SEL0        (* (reg8 *) pinPolarCLED__PRTDSI__OE_SEL0) 
#define pinPolarCLED_PRTDSI__OE_SEL1        (* (reg8 *) pinPolarCLED__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinPolarCLED_PRTDSI__OUT_SEL0       (* (reg8 *) pinPolarCLED__PRTDSI__OUT_SEL0) 
#define pinPolarCLED_PRTDSI__OUT_SEL1       (* (reg8 *) pinPolarCLED__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinPolarCLED_PRTDSI__SYNC_OUT       (* (reg8 *) pinPolarCLED__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinPolarCLED__SIO_CFG)
    #define pinPolarCLED_SIO_HYST_EN        (* (reg8 *) pinPolarCLED__SIO_HYST_EN)
    #define pinPolarCLED_SIO_REG_HIFREQ     (* (reg8 *) pinPolarCLED__SIO_REG_HIFREQ)
    #define pinPolarCLED_SIO_CFG            (* (reg8 *) pinPolarCLED__SIO_CFG)
    #define pinPolarCLED_SIO_DIFF           (* (reg8 *) pinPolarCLED__SIO_DIFF)
#endif /* (pinPolarCLED__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinPolarCLED__INTSTAT)
    #define pinPolarCLED_INTSTAT            (* (reg8 *) pinPolarCLED__INTSTAT)
    #define pinPolarCLED_SNAP               (* (reg8 *) pinPolarCLED__SNAP)
    
	#define pinPolarCLED_0_INTTYPE_REG 		(* (reg8 *) pinPolarCLED__0__INTTYPE)
#endif /* (pinPolarCLED__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinPolarCLED_H */


/* [] END OF FILE */
