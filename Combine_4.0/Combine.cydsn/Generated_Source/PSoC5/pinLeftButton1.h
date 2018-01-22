/*******************************************************************************
* File Name: pinLeftButton1.h  
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

#if !defined(CY_PINS_pinLeftButton1_H) /* Pins pinLeftButton1_H */
#define CY_PINS_pinLeftButton1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinLeftButton1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinLeftButton1__PORT == 15 && ((pinLeftButton1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    pinLeftButton1_Write(uint8 value) ;
void    pinLeftButton1_SetDriveMode(uint8 mode) ;
uint8   pinLeftButton1_ReadDataReg(void) ;
uint8   pinLeftButton1_Read(void) ;
uint8   pinLeftButton1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pinLeftButton1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pinLeftButton1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pinLeftButton1_DM_RES_UP          PIN_DM_RES_UP
#define pinLeftButton1_DM_RES_DWN         PIN_DM_RES_DWN
#define pinLeftButton1_DM_OD_LO           PIN_DM_OD_LO
#define pinLeftButton1_DM_OD_HI           PIN_DM_OD_HI
#define pinLeftButton1_DM_STRONG          PIN_DM_STRONG
#define pinLeftButton1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pinLeftButton1_MASK               pinLeftButton1__MASK
#define pinLeftButton1_SHIFT              pinLeftButton1__SHIFT
#define pinLeftButton1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinLeftButton1_PS                     (* (reg8 *) pinLeftButton1__PS)
/* Data Register */
#define pinLeftButton1_DR                     (* (reg8 *) pinLeftButton1__DR)
/* Port Number */
#define pinLeftButton1_PRT_NUM                (* (reg8 *) pinLeftButton1__PRT) 
/* Connect to Analog Globals */                                                  
#define pinLeftButton1_AG                     (* (reg8 *) pinLeftButton1__AG)                       
/* Analog MUX bux enable */
#define pinLeftButton1_AMUX                   (* (reg8 *) pinLeftButton1__AMUX) 
/* Bidirectional Enable */                                                        
#define pinLeftButton1_BIE                    (* (reg8 *) pinLeftButton1__BIE)
/* Bit-mask for Aliased Register Access */
#define pinLeftButton1_BIT_MASK               (* (reg8 *) pinLeftButton1__BIT_MASK)
/* Bypass Enable */
#define pinLeftButton1_BYP                    (* (reg8 *) pinLeftButton1__BYP)
/* Port wide control signals */                                                   
#define pinLeftButton1_CTL                    (* (reg8 *) pinLeftButton1__CTL)
/* Drive Modes */
#define pinLeftButton1_DM0                    (* (reg8 *) pinLeftButton1__DM0) 
#define pinLeftButton1_DM1                    (* (reg8 *) pinLeftButton1__DM1)
#define pinLeftButton1_DM2                    (* (reg8 *) pinLeftButton1__DM2) 
/* Input Buffer Disable Override */
#define pinLeftButton1_INP_DIS                (* (reg8 *) pinLeftButton1__INP_DIS)
/* LCD Common or Segment Drive */
#define pinLeftButton1_LCD_COM_SEG            (* (reg8 *) pinLeftButton1__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinLeftButton1_LCD_EN                 (* (reg8 *) pinLeftButton1__LCD_EN)
/* Slew Rate Control */
#define pinLeftButton1_SLW                    (* (reg8 *) pinLeftButton1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinLeftButton1_PRTDSI__CAPS_SEL       (* (reg8 *) pinLeftButton1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinLeftButton1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinLeftButton1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinLeftButton1_PRTDSI__OE_SEL0        (* (reg8 *) pinLeftButton1__PRTDSI__OE_SEL0) 
#define pinLeftButton1_PRTDSI__OE_SEL1        (* (reg8 *) pinLeftButton1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinLeftButton1_PRTDSI__OUT_SEL0       (* (reg8 *) pinLeftButton1__PRTDSI__OUT_SEL0) 
#define pinLeftButton1_PRTDSI__OUT_SEL1       (* (reg8 *) pinLeftButton1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinLeftButton1_PRTDSI__SYNC_OUT       (* (reg8 *) pinLeftButton1__PRTDSI__SYNC_OUT) 


#if defined(pinLeftButton1__INTSTAT)  /* Interrupt Registers */

    #define pinLeftButton1_INTSTAT                (* (reg8 *) pinLeftButton1__INTSTAT)
    #define pinLeftButton1_SNAP                   (* (reg8 *) pinLeftButton1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinLeftButton1_H */


/* [] END OF FILE */
