/*******************************************************************************
* File Name: NC_43.h  
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

#if !defined(CY_PINS_NC_43_H) /* Pins NC_43_H */
#define CY_PINS_NC_43_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "NC_43_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 NC_43__PORT == 15 && ((NC_43__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    NC_43_Write(uint8 value);
void    NC_43_SetDriveMode(uint8 mode);
uint8   NC_43_ReadDataReg(void);
uint8   NC_43_Read(void);
void    NC_43_SetInterruptMode(uint16 position, uint16 mode);
uint8   NC_43_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the NC_43_SetDriveMode() function.
     *  @{
     */
        #define NC_43_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define NC_43_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define NC_43_DM_RES_UP          PIN_DM_RES_UP
        #define NC_43_DM_RES_DWN         PIN_DM_RES_DWN
        #define NC_43_DM_OD_LO           PIN_DM_OD_LO
        #define NC_43_DM_OD_HI           PIN_DM_OD_HI
        #define NC_43_DM_STRONG          PIN_DM_STRONG
        #define NC_43_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define NC_43_MASK               NC_43__MASK
#define NC_43_SHIFT              NC_43__SHIFT
#define NC_43_WIDTH              1u

/* Interrupt constants */
#if defined(NC_43__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in NC_43_SetInterruptMode() function.
     *  @{
     */
        #define NC_43_INTR_NONE      (uint16)(0x0000u)
        #define NC_43_INTR_RISING    (uint16)(0x0001u)
        #define NC_43_INTR_FALLING   (uint16)(0x0002u)
        #define NC_43_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define NC_43_INTR_MASK      (0x01u) 
#endif /* (NC_43__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NC_43_PS                     (* (reg8 *) NC_43__PS)
/* Data Register */
#define NC_43_DR                     (* (reg8 *) NC_43__DR)
/* Port Number */
#define NC_43_PRT_NUM                (* (reg8 *) NC_43__PRT) 
/* Connect to Analog Globals */                                                  
#define NC_43_AG                     (* (reg8 *) NC_43__AG)                       
/* Analog MUX bux enable */
#define NC_43_AMUX                   (* (reg8 *) NC_43__AMUX) 
/* Bidirectional Enable */                                                        
#define NC_43_BIE                    (* (reg8 *) NC_43__BIE)
/* Bit-mask for Aliased Register Access */
#define NC_43_BIT_MASK               (* (reg8 *) NC_43__BIT_MASK)
/* Bypass Enable */
#define NC_43_BYP                    (* (reg8 *) NC_43__BYP)
/* Port wide control signals */                                                   
#define NC_43_CTL                    (* (reg8 *) NC_43__CTL)
/* Drive Modes */
#define NC_43_DM0                    (* (reg8 *) NC_43__DM0) 
#define NC_43_DM1                    (* (reg8 *) NC_43__DM1)
#define NC_43_DM2                    (* (reg8 *) NC_43__DM2) 
/* Input Buffer Disable Override */
#define NC_43_INP_DIS                (* (reg8 *) NC_43__INP_DIS)
/* LCD Common or Segment Drive */
#define NC_43_LCD_COM_SEG            (* (reg8 *) NC_43__LCD_COM_SEG)
/* Enable Segment LCD */
#define NC_43_LCD_EN                 (* (reg8 *) NC_43__LCD_EN)
/* Slew Rate Control */
#define NC_43_SLW                    (* (reg8 *) NC_43__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define NC_43_PRTDSI__CAPS_SEL       (* (reg8 *) NC_43__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define NC_43_PRTDSI__DBL_SYNC_IN    (* (reg8 *) NC_43__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define NC_43_PRTDSI__OE_SEL0        (* (reg8 *) NC_43__PRTDSI__OE_SEL0) 
#define NC_43_PRTDSI__OE_SEL1        (* (reg8 *) NC_43__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define NC_43_PRTDSI__OUT_SEL0       (* (reg8 *) NC_43__PRTDSI__OUT_SEL0) 
#define NC_43_PRTDSI__OUT_SEL1       (* (reg8 *) NC_43__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define NC_43_PRTDSI__SYNC_OUT       (* (reg8 *) NC_43__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(NC_43__SIO_CFG)
    #define NC_43_SIO_HYST_EN        (* (reg8 *) NC_43__SIO_HYST_EN)
    #define NC_43_SIO_REG_HIFREQ     (* (reg8 *) NC_43__SIO_REG_HIFREQ)
    #define NC_43_SIO_CFG            (* (reg8 *) NC_43__SIO_CFG)
    #define NC_43_SIO_DIFF           (* (reg8 *) NC_43__SIO_DIFF)
#endif /* (NC_43__SIO_CFG) */

/* Interrupt Registers */
#if defined(NC_43__INTSTAT)
    #define NC_43_INTSTAT            (* (reg8 *) NC_43__INTSTAT)
    #define NC_43_SNAP               (* (reg8 *) NC_43__SNAP)
    
	#define NC_43_0_INTTYPE_REG 		(* (reg8 *) NC_43__0__INTTYPE)
#endif /* (NC_43__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_NC_43_H */


/* [] END OF FILE */
