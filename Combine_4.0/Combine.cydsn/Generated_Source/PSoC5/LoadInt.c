/*******************************************************************************
* File Name: LoadInt.c  
* Version 1.60
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include <CYDEVICE.H>
#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <LoadInt.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START LoadInt_intc` */

/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE	16
#endif
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);

/*******************************************************************************
* Function Name: LoadInt_Start
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void LoadInt_Start(void)
{
    /* For all we know the interrupt is active. */
    LoadInt_Disable();

    /* Set the ISR to point to the LoadInt Interrupt. */
    LoadInt_SetVector(LoadInt_Interrupt);

    /* Set the priority. */
    LoadInt_SetPriority(LoadInt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    LoadInt_Enable();
}

/*******************************************************************************
* Function Name: LoadInt_StartEx
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*******************************************************************************/
void LoadInt_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    LoadInt_Disable();

    /* Set the ISR to point to the LoadInt Interrupt. */
    LoadInt_SetVector(address);

    /* Set the priority. */
    LoadInt_SetPriority(LoadInt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    LoadInt_Enable();
}

/*******************************************************************************
* Function Name: LoadInt_Stop
********************************************************************************
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
void LoadInt_Stop(void) 
{
    /* Disable this interrupt. */
    LoadInt_Disable();

    /* Set the ISR to point to the passive one. */
    LoadInt_SetVector(IntDefaultHandler);
}

/*******************************************************************************
* Function Name: LoadInt_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for LoadInt.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
*
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(LoadInt_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START LoadInt_Interrupt` */

    /* `#END` */
}

/*******************************************************************************
* Function Name: LoadInt_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling LoadInt_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use LoadInt_StartEx instead.
*
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void LoadInt_SetVector(cyisraddress address) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + LoadInt__INTC_NUMBER] = address;
}

/*******************************************************************************
* Function Name: LoadInt_GetVector
********************************************************************************
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*
*******************************************************************************/
cyisraddress LoadInt_GetVector(void) 
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + LoadInt__INTC_NUMBER];
}

/*******************************************************************************
* Function Name: LoadInt_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling LoadInt_Start
*   or LoadInt_StartEx will override any effect this method would have had. 
*	This method should only be called after LoadInt_Start or 
*	LoadInt_StartEx has been called. To set the initial
*	priority for the component use the cydwr file in the tool.
*
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void LoadInt_SetPriority(uint8 priority) 
{
    *LoadInt_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: LoadInt_GetPriority
********************************************************************************
* Summary:
*   Gets the Priority of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
*******************************************************************************/
uint8 LoadInt_GetPriority(void) 
{
    uint8 priority;


    priority = *LoadInt_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: LoadInt_Enable
********************************************************************************
* Summary:
*   Enables the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void LoadInt_Enable(void) 
{
    /* Enable the general interrupt. */
    *LoadInt_INTC_SET_EN = LoadInt__INTC_MASK;
}

/*******************************************************************************
* Function Name: LoadInt_GetState
********************************************************************************
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   1 if enabled, 0 if disabled.
*
*
*******************************************************************************/
uint8 LoadInt_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*LoadInt_INTC_SET_EN & LoadInt__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: LoadInt_Disable
********************************************************************************
* Summary:
*   Disables the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void LoadInt_Disable(void) 
{
    /* Disable the general interrupt. */
    *LoadInt_INTC_CLR_EN = LoadInt__INTC_MASK;
}

/*******************************************************************************
* Function Name: LoadInt_SetPending
********************************************************************************
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void LoadInt_SetPending(void) 
{
    *LoadInt_INTC_SET_PD = LoadInt__INTC_MASK;
}

/*******************************************************************************
* Function Name: LoadInt_ClearPending
********************************************************************************
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void LoadInt_ClearPending(void) 
{
    *LoadInt_INTC_CLR_PD = LoadInt__INTC_MASK;
}
