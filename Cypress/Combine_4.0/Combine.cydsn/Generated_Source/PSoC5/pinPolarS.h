/*******************************************************************************
* File Name: pinPolarS.h  
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

#if !defined(CY_PINS_pinPolarS_H) /* Pins pinPolarS_H */
#define CY_PINS_pinPolarS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinPolarS_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinPolarS__PORT == 15 && ((pinPolarS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinPolarS_Write(uint8 value);
void    pinPolarS_SetDriveMode(uint8 mode);
uint8   pinPolarS_ReadDataReg(void);
uint8   pinPolarS_Read(void);
void    pinPolarS_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinPolarS_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinPolarS_SetDriveMode() function.
     *  @{
     */
        #define pinPolarS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinPolarS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinPolarS_DM_RES_UP          PIN_DM_RES_UP
        #define pinPolarS_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinPolarS_DM_OD_LO           PIN_DM_OD_LO
        #define pinPolarS_DM_OD_HI           PIN_DM_OD_HI
        #define pinPolarS_DM_STRONG          PIN_DM_STRONG
        #define pinPolarS_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinPolarS_MASK               pinPolarS__MASK
#define pinPolarS_SHIFT              pinPolarS__SHIFT
#define pinPolarS_WIDTH              1u

/* Interrupt constants */
#if defined(pinPolarS__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinPolarS_SetInterruptMode() function.
     *  @{
     */
        #define pinPolarS_INTR_NONE      (uint16)(0x0000u)
        #define pinPolarS_INTR_RISING    (uint16)(0x0001u)
        #define pinPolarS_INTR_FALLING   (uint16)(0x0002u)
        #define pinPolarS_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinPolarS_INTR_MASK      (0x01u) 
#endif /* (pinPolarS__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinPolarS_PS                     (* (reg8 *) pinPolarS__PS)
/* Data Register */
#define pinPolarS_DR                     (* (reg8 *) pinPolarS__DR)
/* Port Number */
#define pinPolarS_PRT_NUM                (* (reg8 *) pinPolarS__PRT) 
/* Connect to Analog Globals */                                                  
#define pinPolarS_AG                     (* (reg8 *) pinPolarS__AG)                       
/* Analog MUX bux enable */
#define pinPolarS_AMUX                   (* (reg8 *) pinPolarS__AMUX) 
/* Bidirectional Enable */                                                        
#define pinPolarS_BIE                    (* (reg8 *) pinPolarS__BIE)
/* Bit-mask for Aliased Register Access */
#define pinPolarS_BIT_MASK               (* (reg8 *) pinPolarS__BIT_MASK)
/* Bypass Enable */
#define pinPolarS_BYP                    (* (reg8 *) pinPolarS__BYP)
/* Port wide control signals */                                                   
#define pinPolarS_CTL                    (* (reg8 *) pinPolarS__CTL)
/* Drive Modes */
#define pinPolarS_DM0                    (* (reg8 *) pinPolarS__DM0) 
#define pinPolarS_DM1                    (* (reg8 *) pinPolarS__DM1)
#define pinPolarS_DM2                    (* (reg8 *) pinPolarS__DM2) 
/* Input Buffer Disable Override */
#define pinPolarS_INP_DIS                (* (reg8 *) pinPolarS__INP_DIS)
/* LCD Common or Segment Drive */
#define pinPolarS_LCD_COM_SEG            (* (reg8 *) pinPolarS__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinPolarS_LCD_EN                 (* (reg8 *) pinPolarS__LCD_EN)
/* Slew Rate Control */
#define pinPolarS_SLW                    (* (reg8 *) pinPolarS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinPolarS_PRTDSI__CAPS_SEL       (* (reg8 *) pinPolarS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinPolarS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinPolarS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinPolarS_PRTDSI__OE_SEL0        (* (reg8 *) pinPolarS__PRTDSI__OE_SEL0) 
#define pinPolarS_PRTDSI__OE_SEL1        (* (reg8 *) pinPolarS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinPolarS_PRTDSI__OUT_SEL0       (* (reg8 *) pinPolarS__PRTDSI__OUT_SEL0) 
#define pinPolarS_PRTDSI__OUT_SEL1       (* (reg8 *) pinPolarS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinPolarS_PRTDSI__SYNC_OUT       (* (reg8 *) pinPolarS__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinPolarS__SIO_CFG)
    #define pinPolarS_SIO_HYST_EN        (* (reg8 *) pinPolarS__SIO_HYST_EN)
    #define pinPolarS_SIO_REG_HIFREQ     (* (reg8 *) pinPolarS__SIO_REG_HIFREQ)
    #define pinPolarS_SIO_CFG            (* (reg8 *) pinPolarS__SIO_CFG)
    #define pinPolarS_SIO_DIFF           (* (reg8 *) pinPolarS__SIO_DIFF)
#endif /* (pinPolarS__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinPolarS__INTSTAT)
    #define pinPolarS_INTSTAT            (* (reg8 *) pinPolarS__INTSTAT)
    #define pinPolarS_SNAP               (* (reg8 *) pinPolarS__SNAP)
    
	#define pinPolarS_0_INTTYPE_REG 		(* (reg8 *) pinPolarS__0__INTTYPE)
#endif /* (pinPolarS__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinPolarS_H */


/* [] END OF FILE */
