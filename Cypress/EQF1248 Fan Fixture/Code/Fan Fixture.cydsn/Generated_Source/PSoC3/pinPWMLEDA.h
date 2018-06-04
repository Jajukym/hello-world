/*******************************************************************************
* File Name: pinPWMLEDA.h  
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

#if !defined(CY_PINS_pinPWMLEDA_H) /* Pins pinPWMLEDA_H */
#define CY_PINS_pinPWMLEDA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinPWMLEDA_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    pinPWMLEDA_Write(uint8 value) ;
void    pinPWMLEDA_SetDriveMode(uint8 mode) ;
uint8   pinPWMLEDA_ReadDataReg(void) ;
uint8   pinPWMLEDA_Read(void) ;
uint8   pinPWMLEDA_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pinPWMLEDA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pinPWMLEDA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pinPWMLEDA_DM_RES_UP          PIN_DM_RES_UP
#define pinPWMLEDA_DM_RES_DWN         PIN_DM_RES_DWN
#define pinPWMLEDA_DM_OD_LO           PIN_DM_OD_LO
#define pinPWMLEDA_DM_OD_HI           PIN_DM_OD_HI
#define pinPWMLEDA_DM_STRONG          PIN_DM_STRONG
#define pinPWMLEDA_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pinPWMLEDA_MASK               pinPWMLEDA__MASK
#define pinPWMLEDA_SHIFT              pinPWMLEDA__SHIFT
#define pinPWMLEDA_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinPWMLEDA_PS                     (* (reg8 *) pinPWMLEDA__PS)
/* Data Register */
#define pinPWMLEDA_DR                     (* (reg8 *) pinPWMLEDA__DR)
/* Port Number */
#define pinPWMLEDA_PRT_NUM                (* (reg8 *) pinPWMLEDA__PRT) 
/* Connect to Analog Globals */                                                  
#define pinPWMLEDA_AG                     (* (reg8 *) pinPWMLEDA__AG)                       
/* Analog MUX bux enable */
#define pinPWMLEDA_AMUX                   (* (reg8 *) pinPWMLEDA__AMUX) 
/* Bidirectional Enable */                                                        
#define pinPWMLEDA_BIE                    (* (reg8 *) pinPWMLEDA__BIE)
/* Bit-mask for Aliased Register Access */
#define pinPWMLEDA_BIT_MASK               (* (reg8 *) pinPWMLEDA__BIT_MASK)
/* Bypass Enable */
#define pinPWMLEDA_BYP                    (* (reg8 *) pinPWMLEDA__BYP)
/* Port wide control signals */                                                   
#define pinPWMLEDA_CTL                    (* (reg8 *) pinPWMLEDA__CTL)
/* Drive Modes */
#define pinPWMLEDA_DM0                    (* (reg8 *) pinPWMLEDA__DM0) 
#define pinPWMLEDA_DM1                    (* (reg8 *) pinPWMLEDA__DM1)
#define pinPWMLEDA_DM2                    (* (reg8 *) pinPWMLEDA__DM2) 
/* Input Buffer Disable Override */
#define pinPWMLEDA_INP_DIS                (* (reg8 *) pinPWMLEDA__INP_DIS)
/* LCD Common or Segment Drive */
#define pinPWMLEDA_LCD_COM_SEG            (* (reg8 *) pinPWMLEDA__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinPWMLEDA_LCD_EN                 (* (reg8 *) pinPWMLEDA__LCD_EN)
/* Slew Rate Control */
#define pinPWMLEDA_SLW                    (* (reg8 *) pinPWMLEDA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinPWMLEDA_PRTDSI__CAPS_SEL       (* (reg8 *) pinPWMLEDA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinPWMLEDA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinPWMLEDA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinPWMLEDA_PRTDSI__OE_SEL0        (* (reg8 *) pinPWMLEDA__PRTDSI__OE_SEL0) 
#define pinPWMLEDA_PRTDSI__OE_SEL1        (* (reg8 *) pinPWMLEDA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinPWMLEDA_PRTDSI__OUT_SEL0       (* (reg8 *) pinPWMLEDA__PRTDSI__OUT_SEL0) 
#define pinPWMLEDA_PRTDSI__OUT_SEL1       (* (reg8 *) pinPWMLEDA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinPWMLEDA_PRTDSI__SYNC_OUT       (* (reg8 *) pinPWMLEDA__PRTDSI__SYNC_OUT) 


#if defined(pinPWMLEDA__INTSTAT)  /* Interrupt Registers */

    #define pinPWMLEDA_INTSTAT                (* (reg8 *) pinPWMLEDA__INTSTAT)
    #define pinPWMLEDA_SNAP                   (* (reg8 *) pinPWMLEDA__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins pinPWMLEDA_H */


/* [] END OF FILE */
