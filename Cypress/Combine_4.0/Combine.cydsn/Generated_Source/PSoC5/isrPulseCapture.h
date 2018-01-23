/*******************************************************************************
* File Name: isrPulseCapture.h
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
#if !defined(CY_ISR_isrPulseCapture_H)
#define CY_ISR_isrPulseCapture_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isrPulseCapture_Start(void);
void isrPulseCapture_StartEx(cyisraddress address);
void isrPulseCapture_Stop(void);

CY_ISR_PROTO(isrPulseCapture_Interrupt);

void isrPulseCapture_SetVector(cyisraddress address);
cyisraddress isrPulseCapture_GetVector(void);

void isrPulseCapture_SetPriority(uint8 priority);
uint8 isrPulseCapture_GetPriority(void);

void isrPulseCapture_Enable(void);
uint8 isrPulseCapture_GetState(void);
void isrPulseCapture_Disable(void);

void isrPulseCapture_SetPending(void);
void isrPulseCapture_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isrPulseCapture ISR. */
#define isrPulseCapture_INTC_VECTOR            ((reg32 *) isrPulseCapture__INTC_VECT)

/* Address of the isrPulseCapture ISR priority. */
#define isrPulseCapture_INTC_PRIOR             ((reg8 *) isrPulseCapture__INTC_PRIOR_REG)

/* Priority of the isrPulseCapture interrupt. */
#define isrPulseCapture_INTC_PRIOR_NUMBER      isrPulseCapture__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isrPulseCapture interrupt. */
#define isrPulseCapture_INTC_SET_EN            ((reg32 *) isrPulseCapture__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isrPulseCapture interrupt. */
#define isrPulseCapture_INTC_CLR_EN            ((reg32 *) isrPulseCapture__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isrPulseCapture interrupt state to pending. */
#define isrPulseCapture_INTC_SET_PD            ((reg32 *) isrPulseCapture__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isrPulseCapture interrupt. */
#define isrPulseCapture_INTC_CLR_PD            ((reg32 *) isrPulseCapture__INTC_CLR_PD_REG)


#endif /* CY_ISR_isrPulseCapture_H */


/* [] END OF FILE */
