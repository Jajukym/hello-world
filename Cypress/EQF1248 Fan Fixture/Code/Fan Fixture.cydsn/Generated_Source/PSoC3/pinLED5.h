/*******************************************************************************
* File Name: pinLED5.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_pinLED5_H) /* Pins pinLED5_H */
#define CY_PINS_pinLED5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinLED5_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    pinLED5_Write(uint8 value) ;
void    pinLED5_SetDriveMode(uint8 mode) ;
uint8   pinLED5_ReadDataReg(void) ;
uint8   pinLED5_Read(void) ;
uint8   pinLED5_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pinLED5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pinLED5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pinLED5_DM_RES_UP          PIN_DM_RES_UP
#define pinLED5_DM_RES_DWN         PIN_DM_RES_DWN
#define pinLED5_DM_OD_LO           PIN_DM_OD_LO
#define pinLED5_DM_OD_HI           PIN_DM_OD_HI
#define pinLED5_DM_STRONG          PIN_DM_STRONG
#define pinLED5_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pinLED5_MASK               pinLED5__MASK
#define pinLED5_SHIFT              pinLED5__SHIFT
#define pinLED5_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinLED5_PS                     (* (reg8 *) pinLED5__PS)
/* Data Register */
#define pinLED5_DR                     (* (reg8 *) pinLED5__DR)
/* Port Number */
#define pinLED5_PRT_NUM                (* (reg8 *) pinLED5__PRT) 
/* Connect to Analog Globals */                                                  
#define pinLED5_AG                     (* (reg8 *) pinLED5__AG)                       
/* Analog MUX bux enable */
#define pinLED5_AMUX                   (* (reg8 *) pinLED5__AMUX) 
/* Bidirectional Enable */                                                        
#define pinLED5_BIE                    (* (reg8 *) pinLED5__BIE)
/* Bit-mask for Aliased Register Access */
#define pinLED5_BIT_MASK               (* (reg8 *) pinLED5__BIT_MASK)
/* Bypass Enable */
#define pinLED5_BYP                    (* (reg8 *) pinLED5__BYP)
/* Port wide control signals */                                                   
#define pinLED5_CTL                    (* (reg8 *) pinLED5__CTL)
/* Drive Modes */
#define pinLED5_DM0                    (* (reg8 *) pinLED5__DM0) 
#define pinLED5_DM1                    (* (reg8 *) pinLED5__DM1)
#define pinLED5_DM2                    (* (reg8 *) pinLED5__DM2) 
/* Input Buffer Disable Override */
#define pinLED5_INP_DIS                (* (reg8 *) pinLED5__INP_DIS)
/* LCD Common or Segment Drive */
#define pinLED5_LCD_COM_SEG            (* (reg8 *) pinLED5__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinLED5_LCD_EN                 (* (reg8 *) pinLED5__LCD_EN)
/* Slew Rate Control */
#define pinLED5_SLW                    (* (reg8 *) pinLED5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinLED5_PRTDSI__CAPS_SEL       (* (reg8 *) pinLED5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinLED5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinLED5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinLED5_PRTDSI__OE_SEL0        (* (reg8 *) pinLED5__PRTDSI__OE_SEL0) 
#define pinLED5_PRTDSI__OE_SEL1        (* (reg8 *) pinLED5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinLED5_PRTDSI__OUT_SEL0       (* (reg8 *) pinLED5__PRTDSI__OUT_SEL0) 
#define pinLED5_PRTDSI__OUT_SEL1       (* (reg8 *) pinLED5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinLED5_PRTDSI__SYNC_OUT       (* (reg8 *) pinLED5__PRTDSI__SYNC_OUT) 


#if defined(pinLED5__INTSTAT)  /* Interrupt Registers */

    #define pinLED5_INTSTAT                (* (reg8 *) pinLED5__INTSTAT)
    #define pinLED5_SNAP                   (* (reg8 *) pinLED5__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins pinLED5_H */


/* [] END OF FILE */
