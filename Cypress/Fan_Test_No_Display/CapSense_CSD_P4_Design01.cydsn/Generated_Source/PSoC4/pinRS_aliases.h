/*******************************************************************************
* File Name: pinRS.h  
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

#if !defined(CY_PINS_pinRS_ALIASES_H) /* Pins pinRS_ALIASES_H */
#define CY_PINS_pinRS_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pinRS_0			(pinRS__0__PC)
#define pinRS_0_PS		(pinRS__0__PS)
#define pinRS_0_PC		(pinRS__0__PC)
#define pinRS_0_DR		(pinRS__0__DR)
#define pinRS_0_SHIFT	(pinRS__0__SHIFT)
#define pinRS_0_INTR	((uint16)((uint16)0x0003u << (pinRS__0__SHIFT*2u)))

#define pinRS_INTR_ALL	 ((uint16)(pinRS_0_INTR))


#endif /* End Pins pinRS_ALIASES_H */


/* [] END OF FILE */
