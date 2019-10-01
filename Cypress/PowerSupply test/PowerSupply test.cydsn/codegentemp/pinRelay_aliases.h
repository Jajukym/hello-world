/*******************************************************************************
* File Name: pinRelay.h  
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

#if !defined(CY_PINS_pinRelay_ALIASES_H) /* Pins pinRelay_ALIASES_H */
#define CY_PINS_pinRelay_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pinRelay_0			(pinRelay__0__PC)
#define pinRelay_0_PS		(pinRelay__0__PS)
#define pinRelay_0_PC		(pinRelay__0__PC)
#define pinRelay_0_DR		(pinRelay__0__DR)
#define pinRelay_0_SHIFT	(pinRelay__0__SHIFT)
#define pinRelay_0_INTR	((uint16)((uint16)0x0003u << (pinRelay__0__SHIFT*2u)))

#define pinRelay_INTR_ALL	 ((uint16)(pinRelay_0_INTR))


#endif /* End Pins pinRelay_ALIASES_H */


/* [] END OF FILE */
