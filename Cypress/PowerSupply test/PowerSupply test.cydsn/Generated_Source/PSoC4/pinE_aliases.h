/*******************************************************************************
* File Name: pinE.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_pinE_ALIASES_H) /* Pins pinE_ALIASES_H */
#define CY_PINS_pinE_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pinE_0			(pinE__0__PC)
#define pinE_0_PS		(pinE__0__PS)
#define pinE_0_PC		(pinE__0__PC)
#define pinE_0_DR		(pinE__0__DR)
#define pinE_0_SHIFT	(pinE__0__SHIFT)
#define pinE_0_INTR	((uint16)((uint16)0x0003u << (pinE__0__SHIFT*2u)))

#define pinE_INTR_ALL	 ((uint16)(pinE_0_INTR))


#endif /* End Pins pinE_ALIASES_H */


/* [] END OF FILE */
