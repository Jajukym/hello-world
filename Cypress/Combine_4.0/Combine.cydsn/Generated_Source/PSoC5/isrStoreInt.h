/*******************************************************************************
* File Name: isrStoreInt.h
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
#if !defined(CY_ISR_isrStoreInt_H)
#define CY_ISR_isrStoreInt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isrStoreInt_Start(void);
void isrStoreInt_StartEx(cyisraddress address);
void isrStoreInt_Stop(void);

CY_ISR_PROTO(isrStoreInt_Interrupt);

void isrStoreInt_SetVector(cyisraddress address);
cyisraddress isrStoreInt_GetVector(void);

void isrStoreInt_SetPriority(uint8 priority);
uint8 isrStoreInt_GetPriority(void);

void isrStoreInt_Enable(void);
uint8 isrStoreInt_GetState(void);
void isrStoreInt_Disable(void);

void isrStoreInt_SetPending(void);
void isrStoreInt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isrStoreInt ISR. */
#define isrStoreInt_INTC_VECTOR            ((reg32 *) isrStoreInt__INTC_VECT)

/* Address of the isrStoreInt ISR priority. */
#define isrStoreInt_INTC_PRIOR             ((reg8 *) isrStoreInt__INTC_PRIOR_REG)

/* Priority of the isrStoreInt interrupt. */
#define isrStoreInt_INTC_PRIOR_NUMBER      isrStoreInt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isrStoreInt interrupt. */
#define isrStoreInt_INTC_SET_EN            ((reg32 *) isrStoreInt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isrStoreInt interrupt. */
#define isrStoreInt_INTC_CLR_EN            ((reg32 *) isrStoreInt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isrStoreInt interrupt state to pending. */
#define isrStoreInt_INTC_SET_PD            ((reg32 *) isrStoreInt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isrStoreInt interrupt. */
#define isrStoreInt_INTC_CLR_PD            ((reg32 *) isrStoreInt__INTC_CLR_PD_REG)


#endif /* CY_ISR_isrStoreInt_H */


/* [] END OF FILE */
