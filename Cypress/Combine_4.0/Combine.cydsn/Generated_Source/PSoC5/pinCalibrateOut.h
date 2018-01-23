/*******************************************************************************
* File Name: pinCalibrateOut.h  
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

#if !defined(CY_PINS_pinCalibrateOut_H) /* Pins pinCalibrateOut_H */
#define CY_PINS_pinCalibrateOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinCalibrateOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinCalibrateOut__PORT == 15 && ((pinCalibrateOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinCalibrateOut_Write(uint8 value);
void    pinCalibrateOut_SetDriveMode(uint8 mode);
uint8   pinCalibrateOut_ReadDataReg(void);
uint8   pinCalibrateOut_Read(void);
void    pinCalibrateOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinCalibrateOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinCalibrateOut_SetDriveMode() function.
     *  @{
     */
        #define pinCalibrateOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinCalibrateOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinCalibrateOut_DM_RES_UP          PIN_DM_RES_UP
        #define pinCalibrateOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinCalibrateOut_DM_OD_LO           PIN_DM_OD_LO
        #define pinCalibrateOut_DM_OD_HI           PIN_DM_OD_HI
        #define pinCalibrateOut_DM_STRONG          PIN_DM_STRONG
        #define pinCalibrateOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinCalibrateOut_MASK               pinCalibrateOut__MASK
#define pinCalibrateOut_SHIFT              pinCalibrateOut__SHIFT
#define pinCalibrateOut_WIDTH              1u

/* Interrupt constants */
#if defined(pinCalibrateOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinCalibrateOut_SetInterruptMode() function.
     *  @{
     */
        #define pinCalibrateOut_INTR_NONE      (uint16)(0x0000u)
        #define pinCalibrateOut_INTR_RISING    (uint16)(0x0001u)
        #define pinCalibrateOut_INTR_FALLING   (uint16)(0x0002u)
        #define pinCalibrateOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinCalibrateOut_INTR_MASK      (0x01u) 
#endif /* (pinCalibrateOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinCalibrateOut_PS                     (* (reg8 *) pinCalibrateOut__PS)
/* Data Register */
#define pinCalibrateOut_DR                     (* (reg8 *) pinCalibrateOut__DR)
/* Port Number */
#define pinCalibrateOut_PRT_NUM                (* (reg8 *) pinCalibrateOut__PRT) 
/* Connect to Analog Globals */                                                  
#define pinCalibrateOut_AG                     (* (reg8 *) pinCalibrateOut__AG)                       
/* Analog MUX bux enable */
#define pinCalibrateOut_AMUX                   (* (reg8 *) pinCalibrateOut__AMUX) 
/* Bidirectional Enable */                                                        
#define pinCalibrateOut_BIE                    (* (reg8 *) pinCalibrateOut__BIE)
/* Bit-mask for Aliased Register Access */
#define pinCalibrateOut_BIT_MASK               (* (reg8 *) pinCalibrateOut__BIT_MASK)
/* Bypass Enable */
#define pinCalibrateOut_BYP                    (* (reg8 *) pinCalibrateOut__BYP)
/* Port wide control signals */                                                   
#define pinCalibrateOut_CTL                    (* (reg8 *) pinCalibrateOut__CTL)
/* Drive Modes */
#define pinCalibrateOut_DM0                    (* (reg8 *) pinCalibrateOut__DM0) 
#define pinCalibrateOut_DM1                    (* (reg8 *) pinCalibrateOut__DM1)
#define pinCalibrateOut_DM2                    (* (reg8 *) pinCalibrateOut__DM2) 
/* Input Buffer Disable Override */
#define pinCalibrateOut_INP_DIS                (* (reg8 *) pinCalibrateOut__INP_DIS)
/* LCD Common or Segment Drive */
#define pinCalibrateOut_LCD_COM_SEG            (* (reg8 *) pinCalibrateOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinCalibrateOut_LCD_EN                 (* (reg8 *) pinCalibrateOut__LCD_EN)
/* Slew Rate Control */
#define pinCalibrateOut_SLW                    (* (reg8 *) pinCalibrateOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinCalibrateOut_PRTDSI__CAPS_SEL       (* (reg8 *) pinCalibrateOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinCalibrateOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinCalibrateOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinCalibrateOut_PRTDSI__OE_SEL0        (* (reg8 *) pinCalibrateOut__PRTDSI__OE_SEL0) 
#define pinCalibrateOut_PRTDSI__OE_SEL1        (* (reg8 *) pinCalibrateOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinCalibrateOut_PRTDSI__OUT_SEL0       (* (reg8 *) pinCalibrateOut__PRTDSI__OUT_SEL0) 
#define pinCalibrateOut_PRTDSI__OUT_SEL1       (* (reg8 *) pinCalibrateOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinCalibrateOut_PRTDSI__SYNC_OUT       (* (reg8 *) pinCalibrateOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinCalibrateOut__SIO_CFG)
    #define pinCalibrateOut_SIO_HYST_EN        (* (reg8 *) pinCalibrateOut__SIO_HYST_EN)
    #define pinCalibrateOut_SIO_REG_HIFREQ     (* (reg8 *) pinCalibrateOut__SIO_REG_HIFREQ)
    #define pinCalibrateOut_SIO_CFG            (* (reg8 *) pinCalibrateOut__SIO_CFG)
    #define pinCalibrateOut_SIO_DIFF           (* (reg8 *) pinCalibrateOut__SIO_DIFF)
#endif /* (pinCalibrateOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinCalibrateOut__INTSTAT)
    #define pinCalibrateOut_INTSTAT            (* (reg8 *) pinCalibrateOut__INTSTAT)
    #define pinCalibrateOut_SNAP               (* (reg8 *) pinCalibrateOut__SNAP)
    
	#define pinCalibrateOut_0_INTTYPE_REG 		(* (reg8 *) pinCalibrateOut__0__INTTYPE)
#endif /* (pinCalibrateOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinCalibrateOut_H */


/* [] END OF FILE */
