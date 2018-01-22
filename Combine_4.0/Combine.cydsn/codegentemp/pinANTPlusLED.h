/*******************************************************************************
* File Name: pinANTPlusLED.h  
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

#if !defined(CY_PINS_pinANTPlusLED_H) /* Pins pinANTPlusLED_H */
#define CY_PINS_pinANTPlusLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinANTPlusLED_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinANTPlusLED__PORT == 15 && ((pinANTPlusLED__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinANTPlusLED_Write(uint8 value);
void    pinANTPlusLED_SetDriveMode(uint8 mode);
uint8   pinANTPlusLED_ReadDataReg(void);
uint8   pinANTPlusLED_Read(void);
void    pinANTPlusLED_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinANTPlusLED_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinANTPlusLED_SetDriveMode() function.
     *  @{
     */
        #define pinANTPlusLED_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinANTPlusLED_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinANTPlusLED_DM_RES_UP          PIN_DM_RES_UP
        #define pinANTPlusLED_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinANTPlusLED_DM_OD_LO           PIN_DM_OD_LO
        #define pinANTPlusLED_DM_OD_HI           PIN_DM_OD_HI
        #define pinANTPlusLED_DM_STRONG          PIN_DM_STRONG
        #define pinANTPlusLED_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinANTPlusLED_MASK               pinANTPlusLED__MASK
#define pinANTPlusLED_SHIFT              pinANTPlusLED__SHIFT
#define pinANTPlusLED_WIDTH              1u

/* Interrupt constants */
#if defined(pinANTPlusLED__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinANTPlusLED_SetInterruptMode() function.
     *  @{
     */
        #define pinANTPlusLED_INTR_NONE      (uint16)(0x0000u)
        #define pinANTPlusLED_INTR_RISING    (uint16)(0x0001u)
        #define pinANTPlusLED_INTR_FALLING   (uint16)(0x0002u)
        #define pinANTPlusLED_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinANTPlusLED_INTR_MASK      (0x01u) 
#endif /* (pinANTPlusLED__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinANTPlusLED_PS                     (* (reg8 *) pinANTPlusLED__PS)
/* Data Register */
#define pinANTPlusLED_DR                     (* (reg8 *) pinANTPlusLED__DR)
/* Port Number */
#define pinANTPlusLED_PRT_NUM                (* (reg8 *) pinANTPlusLED__PRT) 
/* Connect to Analog Globals */                                                  
#define pinANTPlusLED_AG                     (* (reg8 *) pinANTPlusLED__AG)                       
/* Analog MUX bux enable */
#define pinANTPlusLED_AMUX                   (* (reg8 *) pinANTPlusLED__AMUX) 
/* Bidirectional Enable */                                                        
#define pinANTPlusLED_BIE                    (* (reg8 *) pinANTPlusLED__BIE)
/* Bit-mask for Aliased Register Access */
#define pinANTPlusLED_BIT_MASK               (* (reg8 *) pinANTPlusLED__BIT_MASK)
/* Bypass Enable */
#define pinANTPlusLED_BYP                    (* (reg8 *) pinANTPlusLED__BYP)
/* Port wide control signals */                                                   
#define pinANTPlusLED_CTL                    (* (reg8 *) pinANTPlusLED__CTL)
/* Drive Modes */
#define pinANTPlusLED_DM0                    (* (reg8 *) pinANTPlusLED__DM0) 
#define pinANTPlusLED_DM1                    (* (reg8 *) pinANTPlusLED__DM1)
#define pinANTPlusLED_DM2                    (* (reg8 *) pinANTPlusLED__DM2) 
/* Input Buffer Disable Override */
#define pinANTPlusLED_INP_DIS                (* (reg8 *) pinANTPlusLED__INP_DIS)
/* LCD Common or Segment Drive */
#define pinANTPlusLED_LCD_COM_SEG            (* (reg8 *) pinANTPlusLED__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinANTPlusLED_LCD_EN                 (* (reg8 *) pinANTPlusLED__LCD_EN)
/* Slew Rate Control */
#define pinANTPlusLED_SLW                    (* (reg8 *) pinANTPlusLED__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinANTPlusLED_PRTDSI__CAPS_SEL       (* (reg8 *) pinANTPlusLED__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinANTPlusLED_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinANTPlusLED__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinANTPlusLED_PRTDSI__OE_SEL0        (* (reg8 *) pinANTPlusLED__PRTDSI__OE_SEL0) 
#define pinANTPlusLED_PRTDSI__OE_SEL1        (* (reg8 *) pinANTPlusLED__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinANTPlusLED_PRTDSI__OUT_SEL0       (* (reg8 *) pinANTPlusLED__PRTDSI__OUT_SEL0) 
#define pinANTPlusLED_PRTDSI__OUT_SEL1       (* (reg8 *) pinANTPlusLED__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinANTPlusLED_PRTDSI__SYNC_OUT       (* (reg8 *) pinANTPlusLED__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinANTPlusLED__SIO_CFG)
    #define pinANTPlusLED_SIO_HYST_EN        (* (reg8 *) pinANTPlusLED__SIO_HYST_EN)
    #define pinANTPlusLED_SIO_REG_HIFREQ     (* (reg8 *) pinANTPlusLED__SIO_REG_HIFREQ)
    #define pinANTPlusLED_SIO_CFG            (* (reg8 *) pinANTPlusLED__SIO_CFG)
    #define pinANTPlusLED_SIO_DIFF           (* (reg8 *) pinANTPlusLED__SIO_DIFF)
#endif /* (pinANTPlusLED__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinANTPlusLED__INTSTAT)
    #define pinANTPlusLED_INTSTAT            (* (reg8 *) pinANTPlusLED__INTSTAT)
    #define pinANTPlusLED_SNAP               (* (reg8 *) pinANTPlusLED__SNAP)
    
	#define pinANTPlusLED_0_INTTYPE_REG 		(* (reg8 *) pinANTPlusLED__0__INTTYPE)
#endif /* (pinANTPlusLED__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinANTPlusLED_H */


/* [] END OF FILE */
