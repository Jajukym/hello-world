/*******************************************************************************
* File Name: pinLED3.h  
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

#if !defined(CY_PINS_pinLED3_H) /* Pins pinLED3_H */
#define CY_PINS_pinLED3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinLED3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    pinLED3_Write(uint8 value) ;
void    pinLED3_SetDriveMode(uint8 mode) ;
uint8   pinLED3_ReadDataReg(void) ;
uint8   pinLED3_Read(void) ;
uint8   pinLED3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pinLED3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pinLED3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pinLED3_DM_RES_UP          PIN_DM_RES_UP
#define pinLED3_DM_RES_DWN         PIN_DM_RES_DWN
#define pinLED3_DM_OD_LO           PIN_DM_OD_LO
#define pinLED3_DM_OD_HI           PIN_DM_OD_HI
#define pinLED3_DM_STRONG          PIN_DM_STRONG
#define pinLED3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pinLED3_MASK               pinLED3__MASK
#define pinLED3_SHIFT              pinLED3__SHIFT
#define pinLED3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinLED3_PS                     (* (reg8 *) pinLED3__PS)
/* Data Register */
#define pinLED3_DR                     (* (reg8 *) pinLED3__DR)
/* Port Number */
#define pinLED3_PRT_NUM                (* (reg8 *) pinLED3__PRT) 
/* Connect to Analog Globals */                                                  
#define pinLED3_AG                     (* (reg8 *) pinLED3__AG)                       
/* Analog MUX bux enable */
#define pinLED3_AMUX                   (* (reg8 *) pinLED3__AMUX) 
/* Bidirectional Enable */                                                        
#define pinLED3_BIE                    (* (reg8 *) pinLED3__BIE)
/* Bit-mask for Aliased Register Access */
#define pinLED3_BIT_MASK               (* (reg8 *) pinLED3__BIT_MASK)
/* Bypass Enable */
#define pinLED3_BYP                    (* (reg8 *) pinLED3__BYP)
/* Port wide control signals */                                                   
#define pinLED3_CTL                    (* (reg8 *) pinLED3__CTL)
/* Drive Modes */
#define pinLED3_DM0                    (* (reg8 *) pinLED3__DM0) 
#define pinLED3_DM1                    (* (reg8 *) pinLED3__DM1)
#define pinLED3_DM2                    (* (reg8 *) pinLED3__DM2) 
/* Input Buffer Disable Override */
#define pinLED3_INP_DIS                (* (reg8 *) pinLED3__INP_DIS)
/* LCD Common or Segment Drive */
#define pinLED3_LCD_COM_SEG            (* (reg8 *) pinLED3__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinLED3_LCD_EN                 (* (reg8 *) pinLED3__LCD_EN)
/* Slew Rate Control */
#define pinLED3_SLW                    (* (reg8 *) pinLED3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinLED3_PRTDSI__CAPS_SEL       (* (reg8 *) pinLED3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinLED3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinLED3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinLED3_PRTDSI__OE_SEL0        (* (reg8 *) pinLED3__PRTDSI__OE_SEL0) 
#define pinLED3_PRTDSI__OE_SEL1        (* (reg8 *) pinLED3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinLED3_PRTDSI__OUT_SEL0       (* (reg8 *) pinLED3__PRTDSI__OUT_SEL0) 
#define pinLED3_PRTDSI__OUT_SEL1       (* (reg8 *) pinLED3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinLED3_PRTDSI__SYNC_OUT       (* (reg8 *) pinLED3__PRTDSI__SYNC_OUT) 


#if defined(pinLED3__INTSTAT)  /* Interrupt Registers */

    #define pinLED3_INTSTAT                (* (reg8 *) pinLED3__INTSTAT)
    #define pinLED3_SNAP                   (* (reg8 *) pinLED3__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins pinLED3_H */


/* [] END OF FILE */
