/*******************************************************************************
* File Name: pinReset.h  
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

#if !defined(CY_PINS_pinReset_ALIASES_H) /* Pins pinReset_ALIASES_H */
#define CY_PINS_pinReset_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pinReset_0			(pinReset__0__PC)
#define pinReset_0_PS		(pinReset__0__PS)
#define pinReset_0_PC		(pinReset__0__PC)
#define pinReset_0_DR		(pinReset__0__DR)
#define pinReset_0_SHIFT	(pinReset__0__SHIFT)
#define pinReset_0_INTR	((uint16)((uint16)0x0003u << (pinReset__0__SHIFT*2u)))

#define pinReset_INTR_ALL	 ((uint16)(pinReset_0_INTR))


#endif /* End Pins pinReset_ALIASES_H */


/* [] END OF FILE */
