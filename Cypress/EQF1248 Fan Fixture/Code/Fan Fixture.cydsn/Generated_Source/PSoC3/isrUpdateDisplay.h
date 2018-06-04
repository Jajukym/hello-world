/*******************************************************************************
* File Name: isrUpdateDisplay.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_ISR_isrUpdateDisplay_H)
#define CY_ISR_isrUpdateDisplay_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isrUpdateDisplay_Start(void) ;
void isrUpdateDisplay_StartEx(cyisraddress address) ;
void isrUpdateDisplay_Stop(void) ;

CY_ISR_PROTO(isrUpdateDisplay_Interrupt);

void isrUpdateDisplay_SetVector(cyisraddress address) ;
cyisraddress isrUpdateDisplay_GetVector(void) ;

void isrUpdateDisplay_SetPriority(uint8 priority) ;
uint8 isrUpdateDisplay_GetPriority(void) ;

void isrUpdateDisplay_Enable(void) ;
uint8 isrUpdateDisplay_GetState(void) ;
void isrUpdateDisplay_Disable(void) ;

void isrUpdateDisplay_SetPending(void) ;
void isrUpdateDisplay_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isrUpdateDisplay ISR. */
#define isrUpdateDisplay_INTC_VECTOR            ((reg16 *) isrUpdateDisplay__INTC_VECT)

/* Address of the isrUpdateDisplay ISR priority. */
#define isrUpdateDisplay_INTC_PRIOR             ((reg8 *) isrUpdateDisplay__INTC_PRIOR_REG)

/* Priority of the isrUpdateDisplay interrupt. */
#define isrUpdateDisplay_INTC_PRIOR_NUMBER      isrUpdateDisplay__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isrUpdateDisplay interrupt. */
#define isrUpdateDisplay_INTC_SET_EN            ((reg8 *) isrUpdateDisplay__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isrUpdateDisplay interrupt. */
#define isrUpdateDisplay_INTC_CLR_EN            ((reg8 *) isrUpdateDisplay__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isrUpdateDisplay interrupt state to pending. */
#define isrUpdateDisplay_INTC_SET_PD            ((reg8 *) isrUpdateDisplay__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isrUpdateDisplay interrupt. */
#define isrUpdateDisplay_INTC_CLR_PD            ((reg8 *) isrUpdateDisplay__INTC_CLR_PD_REG)



#endif /* CY_ISR_isrUpdateDisplay_H */


/* [] END OF FILE */
