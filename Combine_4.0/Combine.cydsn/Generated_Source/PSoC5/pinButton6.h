/*******************************************************************************
* File Name: pinButton6.h  
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

#if !defined(CY_PINS_pinButton6_H) /* Pins pinButton6_H */
#define CY_PINS_pinButton6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinButton6_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinButton6__PORT == 15 && ((pinButton6__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinButton6_Write(uint8 value);
void    pinButton6_SetDriveMode(uint8 mode);
uint8   pinButton6_ReadDataReg(void);
uint8   pinButton6_Read(void);
void    pinButton6_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinButton6_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinButton6_SetDriveMode() function.
     *  @{
     */
        #define pinButton6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinButton6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinButton6_DM_RES_UP          PIN_DM_RES_UP
        #define pinButton6_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinButton6_DM_OD_LO           PIN_DM_OD_LO
        #define pinButton6_DM_OD_HI           PIN_DM_OD_HI
        #define pinButton6_DM_STRONG          PIN_DM_STRONG
        #define pinButton6_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinButton6_MASK               pinButton6__MASK
#define pinButton6_SHIFT              pinButton6__SHIFT
#define pinButton6_WIDTH              1u

/* Interrupt constants */
#if defined(pinButton6__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinButton6_SetInterruptMode() function.
     *  @{
     */
        #define pinButton6_INTR_NONE      (uint16)(0x0000u)
        #define pinButton6_INTR_RISING    (uint16)(0x0001u)
        #define pinButton6_INTR_FALLING   (uint16)(0x0002u)
        #define pinButton6_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinButton6_INTR_MASK      (0x01u) 
#endif /* (pinButton6__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinButton6_PS                     (* (reg8 *) pinButton6__PS)
/* Data Register */
#define pinButton6_DR                     (* (reg8 *) pinButton6__DR)
/* Port Number */
#define pinButton6_PRT_NUM                (* (reg8 *) pinButton6__PRT) 
/* Connect to Analog Globals */                                                  
#define pinButton6_AG                     (* (reg8 *) pinButton6__AG)                       
/* Analog MUX bux enable */
#define pinButton6_AMUX                   (* (reg8 *) pinButton6__AMUX) 
/* Bidirectional Enable */                                                        
#define pinButton6_BIE                    (* (reg8 *) pinButton6__BIE)
/* Bit-mask for Aliased Register Access */
#define pinButton6_BIT_MASK               (* (reg8 *) pinButton6__BIT_MASK)
/* Bypass Enable */
#define pinButton6_BYP                    (* (reg8 *) pinButton6__BYP)
/* Port wide control signals */                                                   
#define pinButton6_CTL                    (* (reg8 *) pinButton6__CTL)
/* Drive Modes */
#define pinButton6_DM0                    (* (reg8 *) pinButton6__DM0) 
#define pinButton6_DM1                    (* (reg8 *) pinButton6__DM1)
#define pinButton6_DM2                    (* (reg8 *) pinButton6__DM2) 
/* Input Buffer Disable Override */
#define pinButton6_INP_DIS                (* (reg8 *) pinButton6__INP_DIS)
/* LCD Common or Segment Drive */
#define pinButton6_LCD_COM_SEG            (* (reg8 *) pinButton6__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinButton6_LCD_EN                 (* (reg8 *) pinButton6__LCD_EN)
/* Slew Rate Control */
#define pinButton6_SLW                    (* (reg8 *) pinButton6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinButton6_PRTDSI__CAPS_SEL       (* (reg8 *) pinButton6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinButton6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinButton6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinButton6_PRTDSI__OE_SEL0        (* (reg8 *) pinButton6__PRTDSI__OE_SEL0) 
#define pinButton6_PRTDSI__OE_SEL1        (* (reg8 *) pinButton6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinButton6_PRTDSI__OUT_SEL0       (* (reg8 *) pinButton6__PRTDSI__OUT_SEL0) 
#define pinButton6_PRTDSI__OUT_SEL1       (* (reg8 *) pinButton6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinButton6_PRTDSI__SYNC_OUT       (* (reg8 *) pinButton6__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinButton6__SIO_CFG)
    #define pinButton6_SIO_HYST_EN        (* (reg8 *) pinButton6__SIO_HYST_EN)
    #define pinButton6_SIO_REG_HIFREQ     (* (reg8 *) pinButton6__SIO_REG_HIFREQ)
    #define pinButton6_SIO_CFG            (* (reg8 *) pinButton6__SIO_CFG)
    #define pinButton6_SIO_DIFF           (* (reg8 *) pinButton6__SIO_DIFF)
#endif /* (pinButton6__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinButton6__INTSTAT)
    #define pinButton6_INTSTAT            (* (reg8 *) pinButton6__INTSTAT)
    #define pinButton6_SNAP               (* (reg8 *) pinButton6__SNAP)
    
	#define pinButton6_0_INTTYPE_REG 		(* (reg8 *) pinButton6__0__INTTYPE)
#endif /* (pinButton6__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinButton6_H */


/* [] END OF FILE */
