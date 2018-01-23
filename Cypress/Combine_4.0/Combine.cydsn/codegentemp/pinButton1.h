/*******************************************************************************
* File Name: pinButton1.h  
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

#if !defined(CY_PINS_pinButton1_H) /* Pins pinButton1_H */
#define CY_PINS_pinButton1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinButton1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinButton1__PORT == 15 && ((pinButton1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinButton1_Write(uint8 value);
void    pinButton1_SetDriveMode(uint8 mode);
uint8   pinButton1_ReadDataReg(void);
uint8   pinButton1_Read(void);
void    pinButton1_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinButton1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinButton1_SetDriveMode() function.
     *  @{
     */
        #define pinButton1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinButton1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinButton1_DM_RES_UP          PIN_DM_RES_UP
        #define pinButton1_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinButton1_DM_OD_LO           PIN_DM_OD_LO
        #define pinButton1_DM_OD_HI           PIN_DM_OD_HI
        #define pinButton1_DM_STRONG          PIN_DM_STRONG
        #define pinButton1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinButton1_MASK               pinButton1__MASK
#define pinButton1_SHIFT              pinButton1__SHIFT
#define pinButton1_WIDTH              1u

/* Interrupt constants */
#if defined(pinButton1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinButton1_SetInterruptMode() function.
     *  @{
     */
        #define pinButton1_INTR_NONE      (uint16)(0x0000u)
        #define pinButton1_INTR_RISING    (uint16)(0x0001u)
        #define pinButton1_INTR_FALLING   (uint16)(0x0002u)
        #define pinButton1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinButton1_INTR_MASK      (0x01u) 
#endif /* (pinButton1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinButton1_PS                     (* (reg8 *) pinButton1__PS)
/* Data Register */
#define pinButton1_DR                     (* (reg8 *) pinButton1__DR)
/* Port Number */
#define pinButton1_PRT_NUM                (* (reg8 *) pinButton1__PRT) 
/* Connect to Analog Globals */                                                  
#define pinButton1_AG                     (* (reg8 *) pinButton1__AG)                       
/* Analog MUX bux enable */
#define pinButton1_AMUX                   (* (reg8 *) pinButton1__AMUX) 
/* Bidirectional Enable */                                                        
#define pinButton1_BIE                    (* (reg8 *) pinButton1__BIE)
/* Bit-mask for Aliased Register Access */
#define pinButton1_BIT_MASK               (* (reg8 *) pinButton1__BIT_MASK)
/* Bypass Enable */
#define pinButton1_BYP                    (* (reg8 *) pinButton1__BYP)
/* Port wide control signals */                                                   
#define pinButton1_CTL                    (* (reg8 *) pinButton1__CTL)
/* Drive Modes */
#define pinButton1_DM0                    (* (reg8 *) pinButton1__DM0) 
#define pinButton1_DM1                    (* (reg8 *) pinButton1__DM1)
#define pinButton1_DM2                    (* (reg8 *) pinButton1__DM2) 
/* Input Buffer Disable Override */
#define pinButton1_INP_DIS                (* (reg8 *) pinButton1__INP_DIS)
/* LCD Common or Segment Drive */
#define pinButton1_LCD_COM_SEG            (* (reg8 *) pinButton1__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinButton1_LCD_EN                 (* (reg8 *) pinButton1__LCD_EN)
/* Slew Rate Control */
#define pinButton1_SLW                    (* (reg8 *) pinButton1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinButton1_PRTDSI__CAPS_SEL       (* (reg8 *) pinButton1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinButton1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinButton1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinButton1_PRTDSI__OE_SEL0        (* (reg8 *) pinButton1__PRTDSI__OE_SEL0) 
#define pinButton1_PRTDSI__OE_SEL1        (* (reg8 *) pinButton1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinButton1_PRTDSI__OUT_SEL0       (* (reg8 *) pinButton1__PRTDSI__OUT_SEL0) 
#define pinButton1_PRTDSI__OUT_SEL1       (* (reg8 *) pinButton1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinButton1_PRTDSI__SYNC_OUT       (* (reg8 *) pinButton1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinButton1__SIO_CFG)
    #define pinButton1_SIO_HYST_EN        (* (reg8 *) pinButton1__SIO_HYST_EN)
    #define pinButton1_SIO_REG_HIFREQ     (* (reg8 *) pinButton1__SIO_REG_HIFREQ)
    #define pinButton1_SIO_CFG            (* (reg8 *) pinButton1__SIO_CFG)
    #define pinButton1_SIO_DIFF           (* (reg8 *) pinButton1__SIO_DIFF)
#endif /* (pinButton1__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinButton1__INTSTAT)
    #define pinButton1_INTSTAT            (* (reg8 *) pinButton1__INTSTAT)
    #define pinButton1_SNAP               (* (reg8 *) pinButton1__SNAP)
    
	#define pinButton1_0_INTTYPE_REG 		(* (reg8 *) pinButton1__0__INTTYPE)
#endif /* (pinButton1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinButton1_H */


/* [] END OF FILE */
