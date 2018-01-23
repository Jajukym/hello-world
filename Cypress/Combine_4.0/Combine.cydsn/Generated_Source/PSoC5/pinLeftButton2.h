/*******************************************************************************
* File Name: pinLeftButton2.h  
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

#if !defined(CY_PINS_pinLeftButton2_H) /* Pins pinLeftButton2_H */
#define CY_PINS_pinLeftButton2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pinLeftButton2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pinLeftButton2__PORT == 15 && ((pinLeftButton2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    pinLeftButton2_Write(uint8 value) ;
void    pinLeftButton2_SetDriveMode(uint8 mode) ;
uint8   pinLeftButton2_ReadDataReg(void) ;
uint8   pinLeftButton2_Read(void) ;
uint8   pinLeftButton2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define pinLeftButton2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define pinLeftButton2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define pinLeftButton2_DM_RES_UP          PIN_DM_RES_UP
#define pinLeftButton2_DM_RES_DWN         PIN_DM_RES_DWN
#define pinLeftButton2_DM_OD_LO           PIN_DM_OD_LO
#define pinLeftButton2_DM_OD_HI           PIN_DM_OD_HI
#define pinLeftButton2_DM_STRONG          PIN_DM_STRONG
#define pinLeftButton2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define pinLeftButton2_MASK               pinLeftButton2__MASK
#define pinLeftButton2_SHIFT              pinLeftButton2__SHIFT
#define pinLeftButton2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pinLeftButton2_PS                     (* (reg8 *) pinLeftButton2__PS)
/* Data Register */
#define pinLeftButton2_DR                     (* (reg8 *) pinLeftButton2__DR)
/* Port Number */
#define pinLeftButton2_PRT_NUM                (* (reg8 *) pinLeftButton2__PRT) 
/* Connect to Analog Globals */                                                  
#define pinLeftButton2_AG                     (* (reg8 *) pinLeftButton2__AG)                       
/* Analog MUX bux enable */
#define pinLeftButton2_AMUX                   (* (reg8 *) pinLeftButton2__AMUX) 
/* Bidirectional Enable */                                                        
#define pinLeftButton2_BIE                    (* (reg8 *) pinLeftButton2__BIE)
/* Bit-mask for Aliased Register Access */
#define pinLeftButton2_BIT_MASK               (* (reg8 *) pinLeftButton2__BIT_MASK)
/* Bypass Enable */
#define pinLeftButton2_BYP                    (* (reg8 *) pinLeftButton2__BYP)
/* Port wide control signals */                                                   
#define pinLeftButton2_CTL                    (* (reg8 *) pinLeftButton2__CTL)
/* Drive Modes */
#define pinLeftButton2_DM0                    (* (reg8 *) pinLeftButton2__DM0) 
#define pinLeftButton2_DM1                    (* (reg8 *) pinLeftButton2__DM1)
#define pinLeftButton2_DM2                    (* (reg8 *) pinLeftButton2__DM2) 
/* Input Buffer Disable Override */
#define pinLeftButton2_INP_DIS                (* (reg8 *) pinLeftButton2__INP_DIS)
/* LCD Common or Segment Drive */
#define pinLeftButton2_LCD_COM_SEG            (* (reg8 *) pinLeftButton2__LCD_COM_SEG)
/* Enable Segment LCD */
#define pinLeftButton2_LCD_EN                 (* (reg8 *) pinLeftButton2__LCD_EN)
/* Slew Rate Control */
#define pinLeftButton2_SLW                    (* (reg8 *) pinLeftButton2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pinLeftButton2_PRTDSI__CAPS_SEL       (* (reg8 *) pinLeftButton2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pinLeftButton2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pinLeftButton2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pinLeftButton2_PRTDSI__OE_SEL0        (* (reg8 *) pinLeftButton2__PRTDSI__OE_SEL0) 
#define pinLeftButton2_PRTDSI__OE_SEL1        (* (reg8 *) pinLeftButton2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pinLeftButton2_PRTDSI__OUT_SEL0       (* (reg8 *) pinLeftButton2__PRTDSI__OUT_SEL0) 
#define pinLeftButton2_PRTDSI__OUT_SEL1       (* (reg8 *) pinLeftButton2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pinLeftButton2_PRTDSI__SYNC_OUT       (* (reg8 *) pinLeftButton2__PRTDSI__SYNC_OUT) 


#if defined(pinLeftButton2__INTSTAT)  /* Interrupt Registers */

    #define pinLeftButton2_INTSTAT                (* (reg8 *) pinLeftButton2__INTSTAT)
    #define pinLeftButton2_SNAP                   (* (reg8 *) pinLeftButton2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pinLeftButton2_H */


/* [] END OF FILE */
