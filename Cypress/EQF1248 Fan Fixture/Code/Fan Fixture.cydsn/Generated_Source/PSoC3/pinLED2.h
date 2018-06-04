/*******************************************************************************
* File Name: pinLED2.h  
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

#if !defined(CY_PINS_pinLED2_H) /* Pins pinLED2_H */
#define CY_PINS_pinLED2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinLED2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    pinLED2_Write(uint8 value) ;
void    pinLED2_SetDriveMode(uint8 mode) ;
uint8   pinLED2_ReadDataReg(void) ;
uint8   pinLED2_Read(void) ;
uint8   pinLED2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pinLED2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pinLED2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pinLED2_DM_RES_UP          PIN_DM_RES_UP
#define pinLED2_DM_RES_DWN         PIN_DM_RES_DWN
#define pinLED2_DM_OD_LO           PIN_DM_OD_LO
#define pinLED2_DM_OD_HI           PIN_DM_OD_HI
#define pinLED2_DM_STRONG          PIN_DM_STRONG
#define pinLED2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pinLED2_MASK               pinLED2__MASK
#define pinLED2_SHIFT              pinLED2__SHIFT
#define pinLED2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinLED2_PS                     (* (reg8 *) pinLED2__PS)
/* Data Register */
#define pinLED2_DR                     (* (reg8 *) pinLED2__DR)
/* Port Number */
#define pinLED2_PRT_NUM                (* (reg8 *) pinLED2__PRT) 
/* Connect to Analog Globals */                                                  
#define pinLED2_AG                     (* (reg8 *) pinLED2__AG)                       
/* Analog MUX bux enable */
#define pinLED2_AMUX                   (* (reg8 *) pinLED2__AMUX) 
/* Bidirectional Enable */                                                        
#define pinLED2_BIE                    (* (reg8 *) pinLED2__BIE)
/* Bit-mask for Aliased Register Access */
#define pinLED2_BIT_MASK               (* (reg8 *) pinLED2__BIT_MASK)
/* Bypass Enable */
#define pinLED2_BYP                    (* (reg8 *) pinLED2__BYP)
/* Port wide control signals */                                                   
#define pinLED2_CTL                    (* (reg8 *) pinLED2__CTL)
/* Drive Modes */
#define pinLED2_DM0                    (* (reg8 *) pinLED2__DM0) 
#define pinLED2_DM1                    (* (reg8 *) pinLED2__DM1)
#define pinLED2_DM2                    (* (reg8 *) pinLED2__DM2) 
/* Input Buffer Disable Override */
#define pinLED2_INP_DIS                (* (reg8 *) pinLED2__INP_DIS)
/* LCD Common or Segment Drive */
#define pinLED2_LCD_COM_SEG            (* (reg8 *) pinLED2__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinLED2_LCD_EN                 (* (reg8 *) pinLED2__LCD_EN)
/* Slew Rate Control */
#define pinLED2_SLW                    (* (reg8 *) pinLED2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinLED2_PRTDSI__CAPS_SEL       (* (reg8 *) pinLED2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinLED2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinLED2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinLED2_PRTDSI__OE_SEL0        (* (reg8 *) pinLED2__PRTDSI__OE_SEL0) 
#define pinLED2_PRTDSI__OE_SEL1        (* (reg8 *) pinLED2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinLED2_PRTDSI__OUT_SEL0       (* (reg8 *) pinLED2__PRTDSI__OUT_SEL0) 
#define pinLED2_PRTDSI__OUT_SEL1       (* (reg8 *) pinLED2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinLED2_PRTDSI__SYNC_OUT       (* (reg8 *) pinLED2__PRTDSI__SYNC_OUT) 


#if defined(pinLED2__INTSTAT)  /* Interrupt Registers */

    #define pinLED2_INTSTAT                (* (reg8 *) pinLED2__INTSTAT)
    #define pinLED2_SNAP                   (* (reg8 *) pinLED2__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins pinLED2_H */


/* [] END OF FILE */
