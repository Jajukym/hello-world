/*******************************************************************************
* File Name: pinButton4.h  
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

#if !defined(CY_PINS_pinButton4_H) /* Pins pinButton4_H */
#define CY_PINS_pinButton4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinButton4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinButton4__PORT == 15 && ((pinButton4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinButton4_Write(uint8 value);
void    pinButton4_SetDriveMode(uint8 mode);
uint8   pinButton4_ReadDataReg(void);
uint8   pinButton4_Read(void);
void    pinButton4_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinButton4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinButton4_SetDriveMode() function.
     *  @{
     */
        #define pinButton4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinButton4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinButton4_DM_RES_UP          PIN_DM_RES_UP
        #define pinButton4_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinButton4_DM_OD_LO           PIN_DM_OD_LO
        #define pinButton4_DM_OD_HI           PIN_DM_OD_HI
        #define pinButton4_DM_STRONG          PIN_DM_STRONG
        #define pinButton4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinButton4_MASK               pinButton4__MASK
#define pinButton4_SHIFT              pinButton4__SHIFT
#define pinButton4_WIDTH              1u

/* Interrupt constants */
#if defined(pinButton4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinButton4_SetInterruptMode() function.
     *  @{
     */
        #define pinButton4_INTR_NONE      (uint16)(0x0000u)
        #define pinButton4_INTR_RISING    (uint16)(0x0001u)
        #define pinButton4_INTR_FALLING   (uint16)(0x0002u)
        #define pinButton4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinButton4_INTR_MASK      (0x01u) 
#endif /* (pinButton4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinButton4_PS                     (* (reg8 *) pinButton4__PS)
/* Data Register */
#define pinButton4_DR                     (* (reg8 *) pinButton4__DR)
/* Port Number */
#define pinButton4_PRT_NUM                (* (reg8 *) pinButton4__PRT) 
/* Connect to Analog Globals */                                                  
#define pinButton4_AG                     (* (reg8 *) pinButton4__AG)                       
/* Analog MUX bux enable */
#define pinButton4_AMUX                   (* (reg8 *) pinButton4__AMUX) 
/* Bidirectional Enable */                                                        
#define pinButton4_BIE                    (* (reg8 *) pinButton4__BIE)
/* Bit-mask for Aliased Register Access */
#define pinButton4_BIT_MASK               (* (reg8 *) pinButton4__BIT_MASK)
/* Bypass Enable */
#define pinButton4_BYP                    (* (reg8 *) pinButton4__BYP)
/* Port wide control signals */                                                   
#define pinButton4_CTL                    (* (reg8 *) pinButton4__CTL)
/* Drive Modes */
#define pinButton4_DM0                    (* (reg8 *) pinButton4__DM0) 
#define pinButton4_DM1                    (* (reg8 *) pinButton4__DM1)
#define pinButton4_DM2                    (* (reg8 *) pinButton4__DM2) 
/* Input Buffer Disable Override */
#define pinButton4_INP_DIS                (* (reg8 *) pinButton4__INP_DIS)
/* LCD Common or Segment Drive */
#define pinButton4_LCD_COM_SEG            (* (reg8 *) pinButton4__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinButton4_LCD_EN                 (* (reg8 *) pinButton4__LCD_EN)
/* Slew Rate Control */
#define pinButton4_SLW                    (* (reg8 *) pinButton4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinButton4_PRTDSI__CAPS_SEL       (* (reg8 *) pinButton4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinButton4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinButton4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinButton4_PRTDSI__OE_SEL0        (* (reg8 *) pinButton4__PRTDSI__OE_SEL0) 
#define pinButton4_PRTDSI__OE_SEL1        (* (reg8 *) pinButton4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinButton4_PRTDSI__OUT_SEL0       (* (reg8 *) pinButton4__PRTDSI__OUT_SEL0) 
#define pinButton4_PRTDSI__OUT_SEL1       (* (reg8 *) pinButton4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinButton4_PRTDSI__SYNC_OUT       (* (reg8 *) pinButton4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinButton4__SIO_CFG)
    #define pinButton4_SIO_HYST_EN        (* (reg8 *) pinButton4__SIO_HYST_EN)
    #define pinButton4_SIO_REG_HIFREQ     (* (reg8 *) pinButton4__SIO_REG_HIFREQ)
    #define pinButton4_SIO_CFG            (* (reg8 *) pinButton4__SIO_CFG)
    #define pinButton4_SIO_DIFF           (* (reg8 *) pinButton4__SIO_DIFF)
#endif /* (pinButton4__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinButton4__INTSTAT)
    #define pinButton4_INTSTAT            (* (reg8 *) pinButton4__INTSTAT)
    #define pinButton4_SNAP               (* (reg8 *) pinButton4__SNAP)
    
	#define pinButton4_0_INTTYPE_REG 		(* (reg8 *) pinButton4__0__INTTYPE)
#endif /* (pinButton4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinButton4_H */


/* [] END OF FILE */
