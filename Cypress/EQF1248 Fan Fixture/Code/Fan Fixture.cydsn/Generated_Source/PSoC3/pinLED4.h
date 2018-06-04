/*******************************************************************************
* File Name: pinLED4.h  
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

#if !defined(CY_PINS_pinLED4_H) /* Pins pinLED4_H */
#define CY_PINS_pinLED4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinLED4_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    pinLED4_Write(uint8 value) ;
void    pinLED4_SetDriveMode(uint8 mode) ;
uint8   pinLED4_ReadDataReg(void) ;
uint8   pinLED4_Read(void) ;
uint8   pinLED4_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pinLED4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pinLED4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pinLED4_DM_RES_UP          PIN_DM_RES_UP
#define pinLED4_DM_RES_DWN         PIN_DM_RES_DWN
#define pinLED4_DM_OD_LO           PIN_DM_OD_LO
#define pinLED4_DM_OD_HI           PIN_DM_OD_HI
#define pinLED4_DM_STRONG          PIN_DM_STRONG
#define pinLED4_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pinLED4_MASK               pinLED4__MASK
#define pinLED4_SHIFT              pinLED4__SHIFT
#define pinLED4_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinLED4_PS                     (* (reg8 *) pinLED4__PS)
/* Data Register */
#define pinLED4_DR                     (* (reg8 *) pinLED4__DR)
/* Port Number */
#define pinLED4_PRT_NUM                (* (reg8 *) pinLED4__PRT) 
/* Connect to Analog Globals */                                                  
#define pinLED4_AG                     (* (reg8 *) pinLED4__AG)                       
/* Analog MUX bux enable */
#define pinLED4_AMUX                   (* (reg8 *) pinLED4__AMUX) 
/* Bidirectional Enable */                                                        
#define pinLED4_BIE                    (* (reg8 *) pinLED4__BIE)
/* Bit-mask for Aliased Register Access */
#define pinLED4_BIT_MASK               (* (reg8 *) pinLED4__BIT_MASK)
/* Bypass Enable */
#define pinLED4_BYP                    (* (reg8 *) pinLED4__BYP)
/* Port wide control signals */                                                   
#define pinLED4_CTL                    (* (reg8 *) pinLED4__CTL)
/* Drive Modes */
#define pinLED4_DM0                    (* (reg8 *) pinLED4__DM0) 
#define pinLED4_DM1                    (* (reg8 *) pinLED4__DM1)
#define pinLED4_DM2                    (* (reg8 *) pinLED4__DM2) 
/* Input Buffer Disable Override */
#define pinLED4_INP_DIS                (* (reg8 *) pinLED4__INP_DIS)
/* LCD Common or Segment Drive */
#define pinLED4_LCD_COM_SEG            (* (reg8 *) pinLED4__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinLED4_LCD_EN                 (* (reg8 *) pinLED4__LCD_EN)
/* Slew Rate Control */
#define pinLED4_SLW                    (* (reg8 *) pinLED4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinLED4_PRTDSI__CAPS_SEL       (* (reg8 *) pinLED4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinLED4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinLED4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinLED4_PRTDSI__OE_SEL0        (* (reg8 *) pinLED4__PRTDSI__OE_SEL0) 
#define pinLED4_PRTDSI__OE_SEL1        (* (reg8 *) pinLED4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinLED4_PRTDSI__OUT_SEL0       (* (reg8 *) pinLED4__PRTDSI__OUT_SEL0) 
#define pinLED4_PRTDSI__OUT_SEL1       (* (reg8 *) pinLED4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinLED4_PRTDSI__SYNC_OUT       (* (reg8 *) pinLED4__PRTDSI__SYNC_OUT) 


#if defined(pinLED4__INTSTAT)  /* Interrupt Registers */

    #define pinLED4_INTSTAT                (* (reg8 *) pinLED4__INTSTAT)
    #define pinLED4_SNAP                   (* (reg8 *) pinLED4__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins pinLED4_H */


/* [] END OF FILE */
