/*******************************************************************************
* File Name: pinANTPlus.h  
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

#if !defined(CY_PINS_pinANTPlus_ALIASES_H) /* Pins pinANTPlus_ALIASES_H */
#define CY_PINS_pinANTPlus_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define pinANTPlus_0			(pinANTPlus__0__PC)
#define pinANTPlus_0_INTR	((uint16)((uint16)0x0001u << pinANTPlus__0__SHIFT))

#define pinANTPlus_INTR_ALL	 ((uint16)(pinANTPlus_0_INTR))

#endif /* End Pins pinANTPlus_ALIASES_H */


/* [] END OF FILE */
