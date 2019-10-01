/*******************************************************************************
* File Name: pinDB5.h  
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

#if !defined(CY_PINS_pinDB5_ALIASES_H) /* Pins pinDB5_ALIASES_H */
#define CY_PINS_pinDB5_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pinDB5_0			(pinDB5__0__PC)
#define pinDB5_0_PS		(pinDB5__0__PS)
#define pinDB5_0_PC		(pinDB5__0__PC)
#define pinDB5_0_DR		(pinDB5__0__DR)
#define pinDB5_0_SHIFT	(pinDB5__0__SHIFT)
#define pinDB5_0_INTR	((uint16)((uint16)0x0003u << (pinDB5__0__SHIFT*2u)))

#define pinDB5_INTR_ALL	 ((uint16)(pinDB5_0_INTR))


#endif /* End Pins pinDB5_ALIASES_H */


/* [] END OF FILE */
