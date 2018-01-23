/*******************************************************************************
* File Name: pinPolarC.h  
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

#if !defined(CY_PINS_pinPolarC_H) /* Pins pinPolarC_H */
#define CY_PINS_pinPolarC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinPolarC_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinPolarC__PORT == 15 && ((pinPolarC__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinPolarC_Write(uint8 value);
void    pinPolarC_SetDriveMode(uint8 mode);
uint8   pinPolarC_ReadDataReg(void);
uint8   pinPolarC_Read(void);
void    pinPolarC_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinPolarC_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinPolarC_SetDriveMode() function.
     *  @{
     */
        #define pinPolarC_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinPolarC_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinPolarC_DM_RES_UP          PIN_DM_RES_UP
        #define pinPolarC_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinPolarC_DM_OD_LO           PIN_DM_OD_LO
        #define pinPolarC_DM_OD_HI           PIN_DM_OD_HI
        #define pinPolarC_DM_STRONG          PIN_DM_STRONG
        #define pinPolarC_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinPolarC_MASK               pinPolarC__MASK
#define pinPolarC_SHIFT              pinPolarC__SHIFT
#define pinPolarC_WIDTH              1u

/* Interrupt constants */
#if defined(pinPolarC__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinPolarC_SetInterruptMode() function.
     *  @{
     */
        #define pinPolarC_INTR_NONE      (uint16)(0x0000u)
        #define pinPolarC_INTR_RISING    (uint16)(0x0001u)
        #define pinPolarC_INTR_FALLING   (uint16)(0x0002u)
        #define pinPolarC_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinPolarC_INTR_MASK      (0x01u) 
#endif /* (pinPolarC__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinPolarC_PS                     (* (reg8 *) pinPolarC__PS)
/* Data Register */
#define pinPolarC_DR                     (* (reg8 *) pinPolarC__DR)
/* Port Number */
#define pinPolarC_PRT_NUM                (* (reg8 *) pinPolarC__PRT) 
/* Connect to Analog Globals */                                                  
#define pinPolarC_AG                     (* (reg8 *) pinPolarC__AG)                       
/* Analog MUX bux enable */
#define pinPolarC_AMUX                   (* (reg8 *) pinPolarC__AMUX) 
/* Bidirectional Enable */                                                        
#define pinPolarC_BIE                    (* (reg8 *) pinPolarC__BIE)
/* Bit-mask for Aliased Register Access */
#define pinPolarC_BIT_MASK               (* (reg8 *) pinPolarC__BIT_MASK)
/* Bypass Enable */
#define pinPolarC_BYP                    (* (reg8 *) pinPolarC__BYP)
/* Port wide control signals */                                                   
#define pinPolarC_CTL                    (* (reg8 *) pinPolarC__CTL)
/* Drive Modes */
#define pinPolarC_DM0                    (* (reg8 *) pinPolarC__DM0) 
#define pinPolarC_DM1                    (* (reg8 *) pinPolarC__DM1)
#define pinPolarC_DM2                    (* (reg8 *) pinPolarC__DM2) 
/* Input Buffer Disable Override */
#define pinPolarC_INP_DIS                (* (reg8 *) pinPolarC__INP_DIS)
/* LCD Common or Segment Drive */
#define pinPolarC_LCD_COM_SEG            (* (reg8 *) pinPolarC__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinPolarC_LCD_EN                 (* (reg8 *) pinPolarC__LCD_EN)
/* Slew Rate Control */
#define pinPolarC_SLW                    (* (reg8 *) pinPolarC__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinPolarC_PRTDSI__CAPS_SEL       (* (reg8 *) pinPolarC__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinPolarC_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinPolarC__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinPolarC_PRTDSI__OE_SEL0        (* (reg8 *) pinPolarC__PRTDSI__OE_SEL0) 
#define pinPolarC_PRTDSI__OE_SEL1        (* (reg8 *) pinPolarC__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinPolarC_PRTDSI__OUT_SEL0       (* (reg8 *) pinPolarC__PRTDSI__OUT_SEL0) 
#define pinPolarC_PRTDSI__OUT_SEL1       (* (reg8 *) pinPolarC__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinPolarC_PRTDSI__SYNC_OUT       (* (reg8 *) pinPolarC__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinPolarC__SIO_CFG)
    #define pinPolarC_SIO_HYST_EN        (* (reg8 *) pinPolarC__SIO_HYST_EN)
    #define pinPolarC_SIO_REG_HIFREQ     (* (reg8 *) pinPolarC__SIO_REG_HIFREQ)
    #define pinPolarC_SIO_CFG            (* (reg8 *) pinPolarC__SIO_CFG)
    #define pinPolarC_SIO_DIFF           (* (reg8 *) pinPolarC__SIO_DIFF)
#endif /* (pinPolarC__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinPolarC__INTSTAT)
    #define pinPolarC_INTSTAT            (* (reg8 *) pinPolarC__INTSTAT)
    #define pinPolarC_SNAP               (* (reg8 *) pinPolarC__SNAP)
    
	#define pinPolarC_0_INTTYPE_REG 		(* (reg8 *) pinPolarC__0__INTTYPE)
#endif /* (pinPolarC__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinPolarC_H */


/* [] END OF FILE */
