/*******************************************************************************
* File Name: pinButton2.h  
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

#if !defined(CY_PINS_pinButton2_H) /* Pins pinButton2_H */
#define CY_PINS_pinButton2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinButton2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinButton2__PORT == 15 && ((pinButton2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinButton2_Write(uint8 value);
void    pinButton2_SetDriveMode(uint8 mode);
uint8   pinButton2_ReadDataReg(void);
uint8   pinButton2_Read(void);
void    pinButton2_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinButton2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinButton2_SetDriveMode() function.
     *  @{
     */
        #define pinButton2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinButton2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinButton2_DM_RES_UP          PIN_DM_RES_UP
        #define pinButton2_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinButton2_DM_OD_LO           PIN_DM_OD_LO
        #define pinButton2_DM_OD_HI           PIN_DM_OD_HI
        #define pinButton2_DM_STRONG          PIN_DM_STRONG
        #define pinButton2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinButton2_MASK               pinButton2__MASK
#define pinButton2_SHIFT              pinButton2__SHIFT
#define pinButton2_WIDTH              1u

/* Interrupt constants */
#if defined(pinButton2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinButton2_SetInterruptMode() function.
     *  @{
     */
        #define pinButton2_INTR_NONE      (uint16)(0x0000u)
        #define pinButton2_INTR_RISING    (uint16)(0x0001u)
        #define pinButton2_INTR_FALLING   (uint16)(0x0002u)
        #define pinButton2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinButton2_INTR_MASK      (0x01u) 
#endif /* (pinButton2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinButton2_PS                     (* (reg8 *) pinButton2__PS)
/* Data Register */
#define pinButton2_DR                     (* (reg8 *) pinButton2__DR)
/* Port Number */
#define pinButton2_PRT_NUM                (* (reg8 *) pinButton2__PRT) 
/* Connect to Analog Globals */                                                  
#define pinButton2_AG                     (* (reg8 *) pinButton2__AG)                       
/* Analog MUX bux enable */
#define pinButton2_AMUX                   (* (reg8 *) pinButton2__AMUX) 
/* Bidirectional Enable */                                                        
#define pinButton2_BIE                    (* (reg8 *) pinButton2__BIE)
/* Bit-mask for Aliased Register Access */
#define pinButton2_BIT_MASK               (* (reg8 *) pinButton2__BIT_MASK)
/* Bypass Enable */
#define pinButton2_BYP                    (* (reg8 *) pinButton2__BYP)
/* Port wide control signals */                                                   
#define pinButton2_CTL                    (* (reg8 *) pinButton2__CTL)
/* Drive Modes */
#define pinButton2_DM0                    (* (reg8 *) pinButton2__DM0) 
#define pinButton2_DM1                    (* (reg8 *) pinButton2__DM1)
#define pinButton2_DM2                    (* (reg8 *) pinButton2__DM2) 
/* Input Buffer Disable Override */
#define pinButton2_INP_DIS                (* (reg8 *) pinButton2__INP_DIS)
/* LCD Common or Segment Drive */
#define pinButton2_LCD_COM_SEG            (* (reg8 *) pinButton2__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinButton2_LCD_EN                 (* (reg8 *) pinButton2__LCD_EN)
/* Slew Rate Control */
#define pinButton2_SLW                    (* (reg8 *) pinButton2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinButton2_PRTDSI__CAPS_SEL       (* (reg8 *) pinButton2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinButton2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinButton2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinButton2_PRTDSI__OE_SEL0        (* (reg8 *) pinButton2__PRTDSI__OE_SEL0) 
#define pinButton2_PRTDSI__OE_SEL1        (* (reg8 *) pinButton2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinButton2_PRTDSI__OUT_SEL0       (* (reg8 *) pinButton2__PRTDSI__OUT_SEL0) 
#define pinButton2_PRTDSI__OUT_SEL1       (* (reg8 *) pinButton2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinButton2_PRTDSI__SYNC_OUT       (* (reg8 *) pinButton2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinButton2__SIO_CFG)
    #define pinButton2_SIO_HYST_EN        (* (reg8 *) pinButton2__SIO_HYST_EN)
    #define pinButton2_SIO_REG_HIFREQ     (* (reg8 *) pinButton2__SIO_REG_HIFREQ)
    #define pinButton2_SIO_CFG            (* (reg8 *) pinButton2__SIO_CFG)
    #define pinButton2_SIO_DIFF           (* (reg8 *) pinButton2__SIO_DIFF)
#endif /* (pinButton2__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinButton2__INTSTAT)
    #define pinButton2_INTSTAT            (* (reg8 *) pinButton2__INTSTAT)
    #define pinButton2_SNAP               (* (reg8 *) pinButton2__SNAP)
    
	#define pinButton2_0_INTTYPE_REG 		(* (reg8 *) pinButton2__0__INTTYPE)
#endif /* (pinButton2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinButton2_H */


/* [] END OF FILE */
