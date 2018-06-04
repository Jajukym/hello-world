/*******************************************************************************
* File Name: pinVFan.h  
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

#if !defined(CY_PINS_pinVFan_ALIASES_H) /* Pins pinVFan_ALIASES_H */
#define CY_PINS_pinVFan_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define pinVFan_0			(pinVFan__0__PC)
#define pinVFan_0_INTR	((uint16)((uint16)0x0001u << pinVFan__0__SHIFT))

#define pinVFan_INTR_ALL	 ((uint16)(pinVFan_0_INTR))

#endif /* End Pins pinVFan_ALIASES_H */


/* [] END OF FILE */
