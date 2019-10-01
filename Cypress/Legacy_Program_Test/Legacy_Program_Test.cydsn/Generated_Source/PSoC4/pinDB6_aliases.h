/*******************************************************************************
* File Name: pinDB6.h  
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

#if !defined(CY_PINS_pinDB6_ALIASES_H) /* Pins pinDB6_ALIASES_H */
#define CY_PINS_pinDB6_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pinDB6_0			(pinDB6__0__PC)
#define pinDB6_0_PS		(pinDB6__0__PS)
#define pinDB6_0_PC		(pinDB6__0__PC)
#define pinDB6_0_DR		(pinDB6__0__DR)
#define pinDB6_0_SHIFT	(pinDB6__0__SHIFT)
#define pinDB6_0_INTR	((uint16)((uint16)0x0003u << (pinDB6__0__SHIFT*2u)))

#define pinDB6_INTR_ALL	 ((uint16)(pinDB6_0_INTR))


#endif /* End Pins pinDB6_ALIASES_H */


/* [] END OF FILE */
