/*******************************************************************************
* File Name: pinLED1.h  
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

#if !defined(CY_PINS_pinLED1_H) /* Pins pinLED1_H */
#define CY_PINS_pinLED1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinLED1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    pinLED1_Write(uint8 value) ;
void    pinLED1_SetDriveMode(uint8 mode) ;
uint8   pinLED1_ReadDataReg(void) ;
uint8   pinLED1_Read(void) ;
uint8   pinLED1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pinLED1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pinLED1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pinLED1_DM_RES_UP          PIN_DM_RES_UP
#define pinLED1_DM_RES_DWN         PIN_DM_RES_DWN
#define pinLED1_DM_OD_LO           PIN_DM_OD_LO
#define pinLED1_DM_OD_HI           PIN_DM_OD_HI
#define pinLED1_DM_STRONG          PIN_DM_STRONG
#define pinLED1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pinLED1_MASK               pinLED1__MASK
#define pinLED1_SHIFT              pinLED1__SHIFT
#define pinLED1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinLED1_PS                     (* (reg8 *) pinLED1__PS)
/* Data Register */
#define pinLED1_DR                     (* (reg8 *) pinLED1__DR)
/* Port Number */
#define pinLED1_PRT_NUM                (* (reg8 *) pinLED1__PRT) 
/* Connect to Analog Globals */                                                  
#define pinLED1_AG                     (* (reg8 *) pinLED1__AG)                       
/* Analog MUX bux enable */
#define pinLED1_AMUX                   (* (reg8 *) pinLED1__AMUX) 
/* Bidirectional Enable */                                                        
#define pinLED1_BIE                    (* (reg8 *) pinLED1__BIE)
/* Bit-mask for Aliased Register Access */
#define pinLED1_BIT_MASK               (* (reg8 *) pinLED1__BIT_MASK)
/* Bypass Enable */
#define pinLED1_BYP                    (* (reg8 *) pinLED1__BYP)
/* Port wide control signals */                                                   
#define pinLED1_CTL                    (* (reg8 *) pinLED1__CTL)
/* Drive Modes */
#define pinLED1_DM0                    (* (reg8 *) pinLED1__DM0) 
#define pinLED1_DM1                    (* (reg8 *) pinLED1__DM1)
#define pinLED1_DM2                    (* (reg8 *) pinLED1__DM2) 
/* Input Buffer Disable Override */
#define pinLED1_INP_DIS                (* (reg8 *) pinLED1__INP_DIS)
/* LCD Common or Segment Drive */
#define pinLED1_LCD_COM_SEG            (* (reg8 *) pinLED1__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinLED1_LCD_EN                 (* (reg8 *) pinLED1__LCD_EN)
/* Slew Rate Control */
#define pinLED1_SLW                    (* (reg8 *) pinLED1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinLED1_PRTDSI__CAPS_SEL       (* (reg8 *) pinLED1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinLED1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinLED1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinLED1_PRTDSI__OE_SEL0        (* (reg8 *) pinLED1__PRTDSI__OE_SEL0) 
#define pinLED1_PRTDSI__OE_SEL1        (* (reg8 *) pinLED1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinLED1_PRTDSI__OUT_SEL0       (* (reg8 *) pinLED1__PRTDSI__OUT_SEL0) 
#define pinLED1_PRTDSI__OUT_SEL1       (* (reg8 *) pinLED1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinLED1_PRTDSI__SYNC_OUT       (* (reg8 *) pinLED1__PRTDSI__SYNC_OUT) 


#if defined(pinLED1__INTSTAT)  /* Interrupt Registers */

    #define pinLED1_INTSTAT                (* (reg8 *) pinLED1__INTSTAT)
    #define pinLED1_SNAP                   (* (reg8 *) pinLED1__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins pinLED1_H */


/* [] END OF FILE */
