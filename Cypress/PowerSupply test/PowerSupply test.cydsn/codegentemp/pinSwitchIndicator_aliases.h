/*******************************************************************************
* File Name: pinSwitchIndicator.h  
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

#if !defined(CY_PINS_pinSwitchIndicator_ALIASES_H) /* Pins pinSwitchIndicator_ALIASES_H */
#define CY_PINS_pinSwitchIndicator_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pinSwitchIndicator_0			(pinSwitchIndicator__0__PC)
#define pinSwitchIndicator_0_PS		(pinSwitchIndicator__0__PS)
#define pinSwitchIndicator_0_PC		(pinSwitchIndicator__0__PC)
#define pinSwitchIndicator_0_DR		(pinSwitchIndicator__0__DR)
#define pinSwitchIndicator_0_SHIFT	(pinSwitchIndicator__0__SHIFT)
#define pinSwitchIndicator_0_INTR	((uint16)((uint16)0x0003u << (pinSwitchIndicator__0__SHIFT*2u)))

#define pinSwitchIndicator_INTR_ALL	 ((uint16)(pinSwitchIndicator_0_INTR))


#endif /* End Pins pinSwitchIndicator_ALIASES_H */


/* [] END OF FILE */
