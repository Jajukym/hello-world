/*******************************************************************************
* File Name: pinDMK.h  
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

#if !defined(CY_PINS_pinDMK_H) /* Pins pinDMK_H */
#define CY_PINS_pinDMK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinDMK_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinDMK__PORT == 15 && ((pinDMK__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinDMK_Write(uint8 value);
void    pinDMK_SetDriveMode(uint8 mode);
uint8   pinDMK_ReadDataReg(void);
uint8   pinDMK_Read(void);
void    pinDMK_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinDMK_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinDMK_SetDriveMode() function.
     *  @{
     */
        #define pinDMK_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinDMK_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinDMK_DM_RES_UP          PIN_DM_RES_UP
        #define pinDMK_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinDMK_DM_OD_LO           PIN_DM_OD_LO
        #define pinDMK_DM_OD_HI           PIN_DM_OD_HI
        #define pinDMK_DM_STRONG          PIN_DM_STRONG
        #define pinDMK_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinDMK_MASK               pinDMK__MASK
#define pinDMK_SHIFT              pinDMK__SHIFT
#define pinDMK_WIDTH              1u

/* Interrupt constants */
#if defined(pinDMK__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinDMK_SetInterruptMode() function.
     *  @{
     */
        #define pinDMK_INTR_NONE      (uint16)(0x0000u)
        #define pinDMK_INTR_RISING    (uint16)(0x0001u)
        #define pinDMK_INTR_FALLING   (uint16)(0x0002u)
        #define pinDMK_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinDMK_INTR_MASK      (0x01u) 
#endif /* (pinDMK__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinDMK_PS                     (* (reg8 *) pinDMK__PS)
/* Data Register */
#define pinDMK_DR                     (* (reg8 *) pinDMK__DR)
/* Port Number */
#define pinDMK_PRT_NUM                (* (reg8 *) pinDMK__PRT) 
/* Connect to Analog Globals */                                                  
#define pinDMK_AG                     (* (reg8 *) pinDMK__AG)                       
/* Analog MUX bux enable */
#define pinDMK_AMUX                   (* (reg8 *) pinDMK__AMUX) 
/* Bidirectional Enable */                                                        
#define pinDMK_BIE                    (* (reg8 *) pinDMK__BIE)
/* Bit-mask for Aliased Register Access */
#define pinDMK_BIT_MASK               (* (reg8 *) pinDMK__BIT_MASK)
/* Bypass Enable */
#define pinDMK_BYP                    (* (reg8 *) pinDMK__BYP)
/* Port wide control signals */                                                   
#define pinDMK_CTL                    (* (reg8 *) pinDMK__CTL)
/* Drive Modes */
#define pinDMK_DM0                    (* (reg8 *) pinDMK__DM0) 
#define pinDMK_DM1                    (* (reg8 *) pinDMK__DM1)
#define pinDMK_DM2                    (* (reg8 *) pinDMK__DM2) 
/* Input Buffer Disable Override */
#define pinDMK_INP_DIS                (* (reg8 *) pinDMK__INP_DIS)
/* LCD Common or Segment Drive */
#define pinDMK_LCD_COM_SEG            (* (reg8 *) pinDMK__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinDMK_LCD_EN                 (* (reg8 *) pinDMK__LCD_EN)
/* Slew Rate Control */
#define pinDMK_SLW                    (* (reg8 *) pinDMK__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinDMK_PRTDSI__CAPS_SEL       (* (reg8 *) pinDMK__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinDMK_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinDMK__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinDMK_PRTDSI__OE_SEL0        (* (reg8 *) pinDMK__PRTDSI__OE_SEL0) 
#define pinDMK_PRTDSI__OE_SEL1        (* (reg8 *) pinDMK__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinDMK_PRTDSI__OUT_SEL0       (* (reg8 *) pinDMK__PRTDSI__OUT_SEL0) 
#define pinDMK_PRTDSI__OUT_SEL1       (* (reg8 *) pinDMK__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinDMK_PRTDSI__SYNC_OUT       (* (reg8 *) pinDMK__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinDMK__SIO_CFG)
    #define pinDMK_SIO_HYST_EN        (* (reg8 *) pinDMK__SIO_HYST_EN)
    #define pinDMK_SIO_REG_HIFREQ     (* (reg8 *) pinDMK__SIO_REG_HIFREQ)
    #define pinDMK_SIO_CFG            (* (reg8 *) pinDMK__SIO_CFG)
    #define pinDMK_SIO_DIFF           (* (reg8 *) pinDMK__SIO_DIFF)
#endif /* (pinDMK__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinDMK__INTSTAT)
    #define pinDMK_INTSTAT            (* (reg8 *) pinDMK__INTSTAT)
    #define pinDMK_SNAP               (* (reg8 *) pinDMK__SNAP)
    
	#define pinDMK_0_INTTYPE_REG 		(* (reg8 *) pinDMK__0__INTTYPE)
#endif /* (pinDMK__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinDMK_H */


/* [] END OF FILE */
