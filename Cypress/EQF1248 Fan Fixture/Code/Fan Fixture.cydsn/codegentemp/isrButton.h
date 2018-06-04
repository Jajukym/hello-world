/*******************************************************************************
* File Name: isrButton.h
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

#if !defined(CY_ISR_isrButton_H)
#define CY_ISR_isrButton_H

#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isrButton_Start(void) ;
void isrButton_StartEx(cyisraddress address) ;
void isrButton_Stop(void) ;

CY_ISR_PROTO(isrButton_Interrupt);

void isrButton_SetVector(cyisraddress address) ;
cyisraddress isrButton_GetVector(void) ;

void isrButton_SetPriority(uint8 priority) ;
uint8 isrButton_GetPriority(void) ;

void isrButton_Enable(void) ;
uint8 isrButton_GetState(void) ;
void isrButton_Disable(void) ;

void isrButton_SetPending(void) ;
void isrButton_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isrButton ISR. */
#define isrButton_INTC_VECTOR            ((reg16 *) isrButton__INTC_VECT)

/* Address of the isrButton ISR priority. */
#define isrButton_INTC_PRIOR             ((reg8 *) isrButton__INTC_PRIOR_REG)

/* Priority of the isrButton interrupt. */
#define isrButton_INTC_PRIOR_NUMBER      isrButton__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isrButton interrupt. */
#define isrButton_INTC_SET_EN            ((reg8 *) isrButton__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isrButton interrupt. */
#define isrButton_INTC_CLR_EN            ((reg8 *) isrButton__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isrButton interrupt state to pending. */
#define isrButton_INTC_SET_PD            ((reg8 *) isrButton__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isrButton interrupt. */
#define isrButton_INTC_CLR_PD            ((reg8 *) isrButton__INTC_CLR_PD_REG)



#endif /* CY_ISR_isrButton_H */


/* [] END OF FILE */
