/*******************************************************************************
* File Name: pinCalibrateIn.h  
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

#if !defined(CY_PINS_pinCalibrateIn_H) /* Pins pinCalibrateIn_H */
#define CY_PINS_pinCalibrateIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinCalibrateIn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinCalibrateIn__PORT == 15 && ((pinCalibrateIn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pinCalibrateIn_Write(uint8 value);
void    pinCalibrateIn_SetDriveMode(uint8 mode);
uint8   pinCalibrateIn_ReadDataReg(void);
uint8   pinCalibrateIn_Read(void);
void    pinCalibrateIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   pinCalibrateIn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pinCalibrateIn_SetDriveMode() function.
     *  @{
     */
        #define pinCalibrateIn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pinCalibrateIn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pinCalibrateIn_DM_RES_UP          PIN_DM_RES_UP
        #define pinCalibrateIn_DM_RES_DWN         PIN_DM_RES_DWN
        #define pinCalibrateIn_DM_OD_LO           PIN_DM_OD_LO
        #define pinCalibrateIn_DM_OD_HI           PIN_DM_OD_HI
        #define pinCalibrateIn_DM_STRONG          PIN_DM_STRONG
        #define pinCalibrateIn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pinCalibrateIn_MASK               pinCalibrateIn__MASK
#define pinCalibrateIn_SHIFT              pinCalibrateIn__SHIFT
#define pinCalibrateIn_WIDTH              1u

/* Interrupt constants */
#if defined(pinCalibrateIn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pinCalibrateIn_SetInterruptMode() function.
     *  @{
     */
        #define pinCalibrateIn_INTR_NONE      (uint16)(0x0000u)
        #define pinCalibrateIn_INTR_RISING    (uint16)(0x0001u)
        #define pinCalibrateIn_INTR_FALLING   (uint16)(0x0002u)
        #define pinCalibrateIn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pinCalibrateIn_INTR_MASK      (0x01u) 
#endif /* (pinCalibrateIn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinCalibrateIn_PS                     (* (reg8 *) pinCalibrateIn__PS)
/* Data Register */
#define pinCalibrateIn_DR                     (* (reg8 *) pinCalibrateIn__DR)
/* Port Number */
#define pinCalibrateIn_PRT_NUM                (* (reg8 *) pinCalibrateIn__PRT) 
/* Connect to Analog Globals */                                                  
#define pinCalibrateIn_AG                     (* (reg8 *) pinCalibrateIn__AG)                       
/* Analog MUX bux enable */
#define pinCalibrateIn_AMUX                   (* (reg8 *) pinCalibrateIn__AMUX) 
/* Bidirectional Enable */                                                        
#define pinCalibrateIn_BIE                    (* (reg8 *) pinCalibrateIn__BIE)
/* Bit-mask for Aliased Register Access */
#define pinCalibrateIn_BIT_MASK               (* (reg8 *) pinCalibrateIn__BIT_MASK)
/* Bypass Enable */
#define pinCalibrateIn_BYP                    (* (reg8 *) pinCalibrateIn__BYP)
/* Port wide control signals */                                                   
#define pinCalibrateIn_CTL                    (* (reg8 *) pinCalibrateIn__CTL)
/* Drive Modes */
#define pinCalibrateIn_DM0                    (* (reg8 *) pinCalibrateIn__DM0) 
#define pinCalibrateIn_DM1                    (* (reg8 *) pinCalibrateIn__DM1)
#define pinCalibrateIn_DM2                    (* (reg8 *) pinCalibrateIn__DM2) 
/* Input Buffer Disable Override */
#define pinCalibrateIn_INP_DIS                (* (reg8 *) pinCalibrateIn__INP_DIS)
/* LCD Common or Segment Drive */
#define pinCalibrateIn_LCD_COM_SEG            (* (reg8 *) pinCalibrateIn__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinCalibrateIn_LCD_EN                 (* (reg8 *) pinCalibrateIn__LCD_EN)
/* Slew Rate Control */
#define pinCalibrateIn_SLW                    (* (reg8 *) pinCalibrateIn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinCalibrateIn_PRTDSI__CAPS_SEL       (* (reg8 *) pinCalibrateIn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinCalibrateIn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinCalibrateIn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinCalibrateIn_PRTDSI__OE_SEL0        (* (reg8 *) pinCalibrateIn__PRTDSI__OE_SEL0) 
#define pinCalibrateIn_PRTDSI__OE_SEL1        (* (reg8 *) pinCalibrateIn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinCalibrateIn_PRTDSI__OUT_SEL0       (* (reg8 *) pinCalibrateIn__PRTDSI__OUT_SEL0) 
#define pinCalibrateIn_PRTDSI__OUT_SEL1       (* (reg8 *) pinCalibrateIn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinCalibrateIn_PRTDSI__SYNC_OUT       (* (reg8 *) pinCalibrateIn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pinCalibrateIn__SIO_CFG)
    #define pinCalibrateIn_SIO_HYST_EN        (* (reg8 *) pinCalibrateIn__SIO_HYST_EN)
    #define pinCalibrateIn_SIO_REG_HIFREQ     (* (reg8 *) pinCalibrateIn__SIO_REG_HIFREQ)
    #define pinCalibrateIn_SIO_CFG            (* (reg8 *) pinCalibrateIn__SIO_CFG)
    #define pinCalibrateIn_SIO_DIFF           (* (reg8 *) pinCalibrateIn__SIO_DIFF)
#endif /* (pinCalibrateIn__SIO_CFG) */

/* Interrupt Registers */
#if defined(pinCalibrateIn__INTSTAT)
    #define pinCalibrateIn_INTSTAT            (* (reg8 *) pinCalibrateIn__INTSTAT)
    #define pinCalibrateIn_SNAP               (* (reg8 *) pinCalibrateIn__SNAP)
    
	#define pinCalibrateIn_0_INTTYPE_REG 		(* (reg8 *) pinCalibrateIn__0__INTTYPE)
#endif /* (pinCalibrateIn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinCalibrateIn_H */


/* [] END OF FILE */
