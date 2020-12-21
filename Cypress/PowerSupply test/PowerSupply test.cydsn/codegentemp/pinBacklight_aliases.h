/*******************************************************************************
* File Name: pinBacklight.h  
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

#if !defined(CY_PINS_pinBacklight_ALIASES_H) /* Pins pinBacklight_ALIASES_H */
#define CY_PINS_pinBacklight_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pinBacklight_0			(pinBacklight__0__PC)
#define pinBacklight_0_PS		(pinBacklight__0__PS)
#define pinBacklight_0_PC		(pinBacklight__0__PC)
#define pinBacklight_0_DR		(pinBacklight__0__DR)
#define pinBacklight_0_SHIFT	(pinBacklight__0__SHIFT)
#define pinBacklight_0_INTR	((uint16)((uint16)0x0003u << (pinBacklight__0__SHIFT*2u)))

#define pinBacklight_INTR_ALL	 ((uint16)(pinBacklight_0_INTR))


#endif /* End Pins pinBacklight_ALIASES_H */


/* [] END OF FILE */
