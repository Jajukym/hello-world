/*******************************************************************************
* File Name: pinRightButton2.h  
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

#if !defined(CY_PINS_pinRightButton2_H) /* Pins pinRightButton2_H */
#define CY_PINS_pinRightButton2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinRightButton2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinRightButton2__PORT == 15 && ((pinRightButton2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    pinRightButton2_Write(uint8 value) ;
void    pinRightButton2_SetDriveMode(uint8 mode) ;
uint8   pinRightButton2_ReadDataReg(void) ;
uint8   pinRightButton2_Read(void) ;
uint8   pinRightButton2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pinRightButton2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pinRightButton2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pinRightButton2_DM_RES_UP          PIN_DM_RES_UP
#define pinRightButton2_DM_RES_DWN         PIN_DM_RES_DWN
#define pinRightButton2_DM_OD_LO           PIN_DM_OD_LO
#define pinRightButton2_DM_OD_HI           PIN_DM_OD_HI
#define pinRightButton2_DM_STRONG          PIN_DM_STRONG
#define pinRightButton2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pinRightButton2_MASK               pinRightButton2__MASK
#define pinRightButton2_SHIFT              pinRightButton2__SHIFT
#define pinRightButton2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinRightButton2_PS                     (* (reg8 *) pinRightButton2__PS)
/* Data Register */
#define pinRightButton2_DR                     (* (reg8 *) pinRightButton2__DR)
/* Port Number */
#define pinRightButton2_PRT_NUM                (* (reg8 *) pinRightButton2__PRT) 
/* Connect to Analog Globals */                                                  
#define pinRightButton2_AG                     (* (reg8 *) pinRightButton2__AG)                       
/* Analog MUX bux enable */
#define pinRightButton2_AMUX                   (* (reg8 *) pinRightButton2__AMUX) 
/* Bidirectional Enable */                                                        
#define pinRightButton2_BIE                    (* (reg8 *) pinRightButton2__BIE)
/* Bit-mask for Aliased Register Access */
#define pinRightButton2_BIT_MASK               (* (reg8 *) pinRightButton2__BIT_MASK)
/* Bypass Enable */
#define pinRightButton2_BYP                    (* (reg8 *) pinRightButton2__BYP)
/* Port wide control signals */                                                   
#define pinRightButton2_CTL                    (* (reg8 *) pinRightButton2__CTL)
/* Drive Modes */
#define pinRightButton2_DM0                    (* (reg8 *) pinRightButton2__DM0) 
#define pinRightButton2_DM1                    (* (reg8 *) pinRightButton2__DM1)
#define pinRightButton2_DM2                    (* (reg8 *) pinRightButton2__DM2) 
/* Input Buffer Disable Override */
#define pinRightButton2_INP_DIS                (* (reg8 *) pinRightButton2__INP_DIS)
/* LCD Common or Segment Drive */
#define pinRightButton2_LCD_COM_SEG            (* (reg8 *) pinRightButton2__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinRightButton2_LCD_EN                 (* (reg8 *) pinRightButton2__LCD_EN)
/* Slew Rate Control */
#define pinRightButton2_SLW                    (* (reg8 *) pinRightButton2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinRightButton2_PRTDSI__CAPS_SEL       (* (reg8 *) pinRightButton2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinRightButton2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinRightButton2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinRightButton2_PRTDSI__OE_SEL0        (* (reg8 *) pinRightButton2__PRTDSI__OE_SEL0) 
#define pinRightButton2_PRTDSI__OE_SEL1        (* (reg8 *) pinRightButton2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinRightButton2_PRTDSI__OUT_SEL0       (* (reg8 *) pinRightButton2__PRTDSI__OUT_SEL0) 
#define pinRightButton2_PRTDSI__OUT_SEL1       (* (reg8 *) pinRightButton2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinRightButton2_PRTDSI__SYNC_OUT       (* (reg8 *) pinRightButton2__PRTDSI__SYNC_OUT) 


#if defined(pinRightButton2__INTSTAT)  /* Interrupt Registers */

    #define pinRightButton2_INTSTAT                (* (reg8 *) pinRightButton2__INTSTAT)
    #define pinRightButton2_SNAP                   (* (reg8 *) pinRightButton2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinRightButton2_H */


/* [] END OF FILE */
