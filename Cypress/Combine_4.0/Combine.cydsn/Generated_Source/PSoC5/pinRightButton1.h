/*******************************************************************************
* File Name: pinRightButton1.h  
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

#if !defined(CY_PINS_pinRightButton1_H) /* Pins pinRightButton1_H */
#define CY_PINS_pinRightButton1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinRightButton1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinRightButton1__PORT == 15 && ((pinRightButton1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    pinRightButton1_Write(uint8 value) ;
void    pinRightButton1_SetDriveMode(uint8 mode) ;
uint8   pinRightButton1_ReadDataReg(void) ;
uint8   pinRightButton1_Read(void) ;
uint8   pinRightButton1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pinRightButton1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pinRightButton1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pinRightButton1_DM_RES_UP          PIN_DM_RES_UP
#define pinRightButton1_DM_RES_DWN         PIN_DM_RES_DWN
#define pinRightButton1_DM_OD_LO           PIN_DM_OD_LO
#define pinRightButton1_DM_OD_HI           PIN_DM_OD_HI
#define pinRightButton1_DM_STRONG          PIN_DM_STRONG
#define pinRightButton1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pinRightButton1_MASK               pinRightButton1__MASK
#define pinRightButton1_SHIFT              pinRightButton1__SHIFT
#define pinRightButton1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinRightButton1_PS                     (* (reg8 *) pinRightButton1__PS)
/* Data Register */
#define pinRightButton1_DR                     (* (reg8 *) pinRightButton1__DR)
/* Port Number */
#define pinRightButton1_PRT_NUM                (* (reg8 *) pinRightButton1__PRT) 
/* Connect to Analog Globals */                                                  
#define pinRightButton1_AG                     (* (reg8 *) pinRightButton1__AG)                       
/* Analog MUX bux enable */
#define pinRightButton1_AMUX                   (* (reg8 *) pinRightButton1__AMUX) 
/* Bidirectional Enable */                                                        
#define pinRightButton1_BIE                    (* (reg8 *) pinRightButton1__BIE)
/* Bit-mask for Aliased Register Access */
#define pinRightButton1_BIT_MASK               (* (reg8 *) pinRightButton1__BIT_MASK)
/* Bypass Enable */
#define pinRightButton1_BYP                    (* (reg8 *) pinRightButton1__BYP)
/* Port wide control signals */                                                   
#define pinRightButton1_CTL                    (* (reg8 *) pinRightButton1__CTL)
/* Drive Modes */
#define pinRightButton1_DM0                    (* (reg8 *) pinRightButton1__DM0) 
#define pinRightButton1_DM1                    (* (reg8 *) pinRightButton1__DM1)
#define pinRightButton1_DM2                    (* (reg8 *) pinRightButton1__DM2) 
/* Input Buffer Disable Override */
#define pinRightButton1_INP_DIS                (* (reg8 *) pinRightButton1__INP_DIS)
/* LCD Common or Segment Drive */
#define pinRightButton1_LCD_COM_SEG            (* (reg8 *) pinRightButton1__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinRightButton1_LCD_EN                 (* (reg8 *) pinRightButton1__LCD_EN)
/* Slew Rate Control */
#define pinRightButton1_SLW                    (* (reg8 *) pinRightButton1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinRightButton1_PRTDSI__CAPS_SEL       (* (reg8 *) pinRightButton1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinRightButton1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinRightButton1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinRightButton1_PRTDSI__OE_SEL0        (* (reg8 *) pinRightButton1__PRTDSI__OE_SEL0) 
#define pinRightButton1_PRTDSI__OE_SEL1        (* (reg8 *) pinRightButton1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinRightButton1_PRTDSI__OUT_SEL0       (* (reg8 *) pinRightButton1__PRTDSI__OUT_SEL0) 
#define pinRightButton1_PRTDSI__OUT_SEL1       (* (reg8 *) pinRightButton1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinRightButton1_PRTDSI__SYNC_OUT       (* (reg8 *) pinRightButton1__PRTDSI__SYNC_OUT) 


#if defined(pinRightButton1__INTSTAT)  /* Interrupt Registers */

    #define pinRightButton1_INTSTAT                (* (reg8 *) pinRightButton1__INTSTAT)
    #define pinRightButton1_SNAP                   (* (reg8 *) pinRightButton1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinRightButton1_H */


/* [] END OF FILE */
