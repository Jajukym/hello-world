/*******************************************************************************
* File Name: statusButtonRead.h  
* Version 1.80
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_statusButtonRead_H) /* CY_STATUS_REG_statusButtonRead_H */
#define CY_STATUS_REG_statusButtonRead_H

#include "cytypes.h"
#include "CyLib.h"


/***************************************
*        Function Prototypes
***************************************/

uint8 statusButtonRead_Read(void) ;
void statusButtonRead_InterruptEnable(void) ;
void statusButtonRead_InterruptDisable(void) ;
void statusButtonRead_WriteMask(uint8 mask) ;
uint8 statusButtonRead_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define statusButtonRead_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define statusButtonRead_INPUTS              4


/***************************************
*             Registers
***************************************/

/* Status Register */
#define statusButtonRead_Status             (* (reg8 *) statusButtonRead_sts_sts_reg__STATUS_REG )
#define statusButtonRead_Status_PTR         (  (reg8 *) statusButtonRead_sts_sts_reg__STATUS_REG )
#define statusButtonRead_Status_Mask        (* (reg8 *) statusButtonRead_sts_sts_reg__MASK_REG )
#define statusButtonRead_Status_Aux_Ctrl    (* (reg8 *) statusButtonRead_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_statusButtonRead_H */


/* [] END OF FILE */
