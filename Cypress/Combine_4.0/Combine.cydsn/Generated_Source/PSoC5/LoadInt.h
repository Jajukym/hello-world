/*******************************************************************************
* File Name: LoadInt.h
* Version 1.60
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
#if !defined(__LoadInt_INTC_H__)
#define __LoadInt_INTC_H__


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void LoadInt_Start(void);
void LoadInt_StartEx(cyisraddress address);
void LoadInt_Stop(void) ;

CY_ISR_PROTO(LoadInt_Interrupt);

void LoadInt_SetVector(cyisraddress address) ;
cyisraddress LoadInt_GetVector(void) ;

void LoadInt_SetPriority(uint8 priority) ;
uint8 LoadInt_GetPriority(void) ;

void LoadInt_Enable(void) ;
uint8 LoadInt_GetState(void) ;
void LoadInt_Disable(void) ;

void LoadInt_SetPending(void) ;
void LoadInt_ClearPending(void) ;


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the LoadInt ISR. */
#define LoadInt_INTC_VECTOR            ((reg32 *) LoadInt__INTC_VECT)

/* Address of the LoadInt ISR priority. */
#define LoadInt_INTC_PRIOR             ((reg8 *) LoadInt__INTC_PRIOR_REG)

/* Priority of the LoadInt interrupt. */
#define LoadInt_INTC_PRIOR_NUMBER      LoadInt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable LoadInt interrupt. */
#define LoadInt_INTC_SET_EN            ((reg32 *) LoadInt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the LoadInt interrupt. */
#define LoadInt_INTC_CLR_EN            ((reg32 *) LoadInt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the LoadInt interrupt state to pending. */
#define LoadInt_INTC_SET_PD            ((reg32 *) LoadInt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the LoadInt interrupt. */
#define LoadInt_INTC_CLR_PD            ((reg32 *) LoadInt__INTC_CLR_PD_REG)



/* __LoadInt_INTC_H__ */
#endif
