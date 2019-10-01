/*******************************************************************************
* File Name: pinPower.h  
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

#if !defined(CY_PINS_pinPower_ALIASES_H) /* Pins pinPower_ALIASES_H */
#define CY_PINS_pinPower_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pinPower_0			(pinPower__0__PC)
#define pinPower_0_PS		(pinPower__0__PS)
#define pinPower_0_PC		(pinPower__0__PC)
#define pinPower_0_DR		(pinPower__0__DR)
#define pinPower_0_SHIFT	(pinPower__0__SHIFT)
#define pinPower_0_INTR	((uint16)((uint16)0x0003u << (pinPower__0__SHIFT*2u)))

#define pinPower_INTR_ALL	 ((uint16)(pinPower_0_INTR))


#endif /* End Pins pinPower_ALIASES_H */


/* [] END OF FILE */
