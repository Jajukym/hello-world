/*******************************************************************************
* File Name: pinDB7.h  
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

#if !defined(CY_PINS_pinDB7_ALIASES_H) /* Pins pinDB7_ALIASES_H */
#define CY_PINS_pinDB7_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pinDB7_0			(pinDB7__0__PC)
#define pinDB7_0_PS		(pinDB7__0__PS)
#define pinDB7_0_PC		(pinDB7__0__PC)
#define pinDB7_0_DR		(pinDB7__0__DR)
#define pinDB7_0_SHIFT	(pinDB7__0__SHIFT)
#define pinDB7_0_INTR	((uint16)((uint16)0x0003u << (pinDB7__0__SHIFT*2u)))

#define pinDB7_INTR_ALL	 ((uint16)(pinDB7_0_INTR))


#endif /* End Pins pinDB7_ALIASES_H */


/* [] END OF FILE */
