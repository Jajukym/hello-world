/*******************************************************************************
* File Name: pinDB4.h  
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

#if !defined(CY_PINS_pinDB4_ALIASES_H) /* Pins pinDB4_ALIASES_H */
#define CY_PINS_pinDB4_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pinDB4_0			(pinDB4__0__PC)
#define pinDB4_0_PS		(pinDB4__0__PS)
#define pinDB4_0_PC		(pinDB4__0__PC)
#define pinDB4_0_DR		(pinDB4__0__DR)
#define pinDB4_0_SHIFT	(pinDB4__0__SHIFT)
#define pinDB4_0_INTR	((uint16)((uint16)0x0003u << (pinDB4__0__SHIFT*2u)))

#define pinDB4_INTR_ALL	 ((uint16)(pinDB4_0_INTR))


#endif /* End Pins pinDB4_ALIASES_H */


/* [] END OF FILE */
