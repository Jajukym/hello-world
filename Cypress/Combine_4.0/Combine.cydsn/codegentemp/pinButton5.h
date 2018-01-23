/*******************************************************************************
* File Name: pinButton5.h  
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

#if !defined(CY_PINS_pinButton5_H) /* Pins pinButton5_H */
#define CY_PINS_pinButton5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinButton5_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinButton5__PORT == 15 && ((pinButton5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinButton5_Write(uint8 value);
void    pinButton5_SetDriveMode(uint8 mode);
uint8   pinButton5_ReadDataReg(void);
uint8   pinButton5_Read(void);
void    pinButton5_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinButton5_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinButton5_SetDriveMode() function.
     *  @{
     */
        #define pinButton5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinButton5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinButton5_DM_RES_UP          PIN_DM_RES_UP
        #define pinButton5_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinButton5_DM_OD_LO           PIN_DM_OD_LO
        #define pinButton5_DM_OD_HI           PIN_DM_OD_HI
        #define pinButton5_DM_STRONG          PIN_DM_STRONG
        #define pinButton5_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinButton5_MASK               pinButton5__MASK
#define pinButton5_SHIFT              pinButton5__SHIFT
#define pinButton5_WIDTH              1u

/* Interrupt constants */
#if defined(pinButton5__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinButton5_SetInterruptMode() function.
     *  @{
     */
        #define pinButton5_INTR_NONE      (uint16)(0x0000u)
        #define pinButton5_INTR_RISING    (uint16)(0x0001u)
        #define pinButton5_INTR_FALLING   (uint16)(0x0002u)
        #define pinButton5_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinButton5_INTR_MASK      (0x01u) 
#endif /* (pinButton5__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinButton5_PS                     (* (reg8 *) pinButton5__PS)
/* Data Register */
#define pinButton5_DR                     (* (reg8 *) pinButton5__DR)
/* Port Number */
#define pinButton5_PRT_NUM                (* (reg8 *) pinButton5__PRT) 
/* Connect to Analog Globals */                                                  
#define pinButton5_AG                     (* (reg8 *) pinButton5__AG)                       
/* Analog MUX bux enable */
#define pinButton5_AMUX                   (* (reg8 *) pinButton5__AMUX) 
/* Bidirectional Enable */                                                        
#define pinButton5_BIE                    (* (reg8 *) pinButton5__BIE)
/* Bit-mask for Aliased Register Access */
#define pinButton5_BIT_MASK               (* (reg8 *) pinButton5__BIT_MASK)
/* Bypass Enable */
#define pinButton5_BYP                    (* (reg8 *) pinButton5__BYP)
/* Port wide control signals */                                                   
#define pinButton5_CTL                    (* (reg8 *) pinButton5__CTL)
/* Drive Modes */
#define pinButton5_DM0                    (* (reg8 *) pinButton5__DM0) 
#define pinButton5_DM1                    (* (reg8 *) pinButton5__DM1)
#define pinButton5_DM2                    (* (reg8 *) pinButton5__DM2) 
/* Input Buffer Disable Override */
#define pinButton5_INP_DIS                (* (reg8 *) pinButton5__INP_DIS)
/* LCD Common or Segment Drive */
#define pinButton5_LCD_COM_SEG            (* (reg8 *) pinButton5__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinButton5_LCD_EN                 (* (reg8 *) pinButton5__LCD_EN)
/* Slew Rate Control */
#define pinButton5_SLW                    (* (reg8 *) pinButton5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinButton5_PRTDSI__CAPS_SEL       (* (reg8 *) pinButton5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinButton5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinButton5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinButton5_PRTDSI__OE_SEL0        (* (reg8 *) pinButton5__PRTDSI__OE_SEL0) 
#define pinButton5_PRTDSI__OE_SEL1        (* (reg8 *) pinButton5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinButton5_PRTDSI__OUT_SEL0       (* (reg8 *) pinButton5__PRTDSI__OUT_SEL0) 
#define pinButton5_PRTDSI__OUT_SEL1       (* (reg8 *) pinButton5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinButton5_PRTDSI__SYNC_OUT       (* (reg8 *) pinButton5__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinButton5__SIO_CFG)
    #define pinButton5_SIO_HYST_EN        (* (reg8 *) pinButton5__SIO_HYST_EN)
    #define pinButton5_SIO_REG_HIFREQ     (* (reg8 *) pinButton5__SIO_REG_HIFREQ)
    #define pinButton5_SIO_CFG            (* (reg8 *) pinButton5__SIO_CFG)
    #define pinButton5_SIO_DIFF           (* (reg8 *) pinButton5__SIO_DIFF)
#endif /* (pinButton5__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinButton5__INTSTAT)
    #define pinButton5_INTSTAT            (* (reg8 *) pinButton5__INTSTAT)
    #define pinButton5_SNAP               (* (reg8 *) pinButton5__SNAP)
    
	#define pinButton5_0_INTTYPE_REG 		(* (reg8 *) pinButton5__0__INTTYPE)
#endif /* (pinButton5__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinButton5_H */


/* [] END OF FILE */
