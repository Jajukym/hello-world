/*******************************************************************************
* File Name: pinPWMLEDB.h  
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

#if !defined(CY_PINS_pinPWMLEDB_H) /* Pins pinPWMLEDB_H */
#define CY_PINS_pinPWMLEDB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinPWMLEDB_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    pinPWMLEDB_Write(uint8 value) ;
void    pinPWMLEDB_SetDriveMode(uint8 mode) ;
uint8   pinPWMLEDB_ReadDataReg(void) ;
uint8   pinPWMLEDB_Read(void) ;
uint8   pinPWMLEDB_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pinPWMLEDB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pinPWMLEDB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pinPWMLEDB_DM_RES_UP          PIN_DM_RES_UP
#define pinPWMLEDB_DM_RES_DWN         PIN_DM_RES_DWN
#define pinPWMLEDB_DM_OD_LO           PIN_DM_OD_LO
#define pinPWMLEDB_DM_OD_HI           PIN_DM_OD_HI
#define pinPWMLEDB_DM_STRONG          PIN_DM_STRONG
#define pinPWMLEDB_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pinPWMLEDB_MASK               pinPWMLEDB__MASK
#define pinPWMLEDB_SHIFT              pinPWMLEDB__SHIFT
#define pinPWMLEDB_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinPWMLEDB_PS                     (* (reg8 *) pinPWMLEDB__PS)
/* Data Register */
#define pinPWMLEDB_DR                     (* (reg8 *) pinPWMLEDB__DR)
/* Port Number */
#define pinPWMLEDB_PRT_NUM                (* (reg8 *) pinPWMLEDB__PRT) 
/* Connect to Analog Globals */                                                  
#define pinPWMLEDB_AG                     (* (reg8 *) pinPWMLEDB__AG)                       
/* Analog MUX bux enable */
#define pinPWMLEDB_AMUX                   (* (reg8 *) pinPWMLEDB__AMUX) 
/* Bidirectional Enable */                                                        
#define pinPWMLEDB_BIE                    (* (reg8 *) pinPWMLEDB__BIE)
/* Bit-mask for Aliased Register Access */
#define pinPWMLEDB_BIT_MASK               (* (reg8 *) pinPWMLEDB__BIT_MASK)
/* Bypass Enable */
#define pinPWMLEDB_BYP                    (* (reg8 *) pinPWMLEDB__BYP)
/* Port wide control signals */                                                   
#define pinPWMLEDB_CTL                    (* (reg8 *) pinPWMLEDB__CTL)
/* Drive Modes */
#define pinPWMLEDB_DM0                    (* (reg8 *) pinPWMLEDB__DM0) 
#define pinPWMLEDB_DM1                    (* (reg8 *) pinPWMLEDB__DM1)
#define pinPWMLEDB_DM2                    (* (reg8 *) pinPWMLEDB__DM2) 
/* Input Buffer Disable Override */
#define pinPWMLEDB_INP_DIS                (* (reg8 *) pinPWMLEDB__INP_DIS)
/* LCD Common or Segment Drive */
#define pinPWMLEDB_LCD_COM_SEG            (* (reg8 *) pinPWMLEDB__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinPWMLEDB_LCD_EN                 (* (reg8 *) pinPWMLEDB__LCD_EN)
/* Slew Rate Control */
#define pinPWMLEDB_SLW                    (* (reg8 *) pinPWMLEDB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinPWMLEDB_PRTDSI__CAPS_SEL       (* (reg8 *) pinPWMLEDB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinPWMLEDB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinPWMLEDB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinPWMLEDB_PRTDSI__OE_SEL0        (* (reg8 *) pinPWMLEDB__PRTDSI__OE_SEL0) 
#define pinPWMLEDB_PRTDSI__OE_SEL1        (* (reg8 *) pinPWMLEDB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinPWMLEDB_PRTDSI__OUT_SEL0       (* (reg8 *) pinPWMLEDB__PRTDSI__OUT_SEL0) 
#define pinPWMLEDB_PRTDSI__OUT_SEL1       (* (reg8 *) pinPWMLEDB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinPWMLEDB_PRTDSI__SYNC_OUT       (* (reg8 *) pinPWMLEDB__PRTDSI__SYNC_OUT) 


#if defined(pinPWMLEDB__INTSTAT)  /* Interrupt Registers */

    #define pinPWMLEDB_INTSTAT                (* (reg8 *) pinPWMLEDB__INTSTAT)
    #define pinPWMLEDB_SNAP                   (* (reg8 *) pinPWMLEDB__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins pinPWMLEDB_H */


/* [] END OF FILE */
