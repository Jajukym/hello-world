/*******************************************************************************
* File Name: Sender.c
* Version 2.10
*
* Description:
*  This file provides the API source code for the Shift Register component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#include "Sender.h"
#include "CyLib.h"


uint8 Sender_initVar = 0u;


/*******************************************************************************
* Function Name: Sender_Start
********************************************************************************
*
* Summary:
*  Starts the Shift Register.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Sender_initVar - used to check initial configuration, modified on 
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Sender_Start(void) 
{
    if (Sender_initVar == 0u)
    {
        Sender_Init();
        /* variable _initVar is set to indicate the fact of initialization */
        Sender_initVar = 1u; 
    }

    Sender_Enable();
}


/*******************************************************************************
* Function Name: Sender_Enable
********************************************************************************
*
* Summary:
*  Enables the Shift Register.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void Sender_Enable(void) 
{
    /* changing address in Datapath Control Store
       from NOP to component state machine commands space */
    Sender_SR_CONTROL |= Sender_CLK_EN; 
    
    Sender_EnableInt();
}


/*******************************************************************************
* Function Name: Sender_Init
********************************************************************************
*
* Summary:
*  Initializes Tx and/or Rx interrupt sources with initial values.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void Sender_Init(void) 
{
    Sender_SetIntMode(Sender_INT_SRC);
}


/*******************************************************************************
* Function Name: Sender_Stop
********************************************************************************
*
* Summary:
*  Disables the Shift Register
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Sender_Stop(void) 
{
    /*changing Datapath Control Store address to NOP space*/
    Sender_SR_CONTROL &= ~Sender_CLK_EN; 
    Sender_DisableInt();
}


/*******************************************************************************
* Function Name: Sender_EnableInt
********************************************************************************
*
* Summary:
*  Enables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Sender_EnableInt(void) 
{
    uint8 interruptState = CyEnterCriticalSection();
    Sender_SR_AUX_CONTROL |= Sender_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Sender_DisableInt
********************************************************************************
*
* Summary:
*  Disables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Sender_DisableInt(void) 
{
    uint8 interruptState = CyEnterCriticalSection();
    Sender_SR_AUX_CONTROL &= ~Sender_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Sender_GetFIFOStatus
********************************************************************************
*
* Summary:
*  Returns current status of input or output FIFO.
*
* Parameters:
*  fifoId.
*
* Return:
*  FIFO status.
*
*******************************************************************************/
uint8 Sender_GetFIFOStatus(uint8 fifoId) 
{
    uint8 result;

    result = Sender_RET_FIFO_NOT_DEFINED; /*default status value*/

    #if (Sender_USE_INPUT_FIFO == 1u)
        
        if(fifoId == Sender_IN_FIFO)
        {    
            switch((Sender_SR_STATUS & Sender_IN_FIFO_MASK) >> 
                    Sender_IN_FIFO_SHFT_MASK)
            {
                case Sender_IN_FIFO_FULL :
                    result = Sender_RET_FIFO_FULL;
                    break;

                case Sender_IN_FIFO_EMPTY :
                    result = Sender_RET_FIFO_EMPTY;
                    break;

                case Sender_IN_FIFO_NOT_EMPTY :
                    result = Sender_RET_FIFO_NOT_EMPTY;
                    break;
                default:
                    result = Sender_RET_FIFO_EMPTY;
            }
        }
    #endif/*(Sender_USE_INPUT_FIFO == 1u)*/
    
    if(fifoId == Sender_OUT_FIFO)
    {
        switch((Sender_SR_STATUS & Sender_OUT_FIFO_MASK) >> 
                Sender_OUT_FIFO_SHFT_MASK)
        {
            case Sender_OUT_FIFO_FULL :
                result = Sender_RET_FIFO_FULL;
                break;

            case Sender_OUT_FIFO_EMPTY :
                result = Sender_RET_FIFO_EMPTY;
                break;

            case Sender_OUT_FIFO_NOT_EMPTY :
                result = Sender_RET_FIFO_NOT_EMPTY;
                break;

            default:
                result = Sender_RET_FIFO_FULL;
        }
    }

    return (result);
}


/*******************************************************************************
* Function Name: Sender_SetIntMode
********************************************************************************
*
* Summary:
*  Sets the Interrupt Source for the Shift Register interrupt. Multiple
*  sources may be ORed together
*
* Parameters:
*  interruptSource: Byte containing the constant for the selected interrupt
*  source/s.
*
* Return:
*  None.
*
*******************************************************************************/
void Sender_SetIntMode(uint8 interruptSource) 
{
    Sender_SR_STATUS_MASK = (Sender_SR_STATUS_MASK & ~Sender_INTS_EN_MASK) | \
                                      (interruptSource & Sender_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: Sender_GetIntStatus
********************************************************************************
*
* Summary:
*  Gets the Shift Register Interrupt status.
*
* Parameters:
*  None.
*
* Return:
*  Byte containing the constant for the selected interrupt source/s.
*
*******************************************************************************/
uint8 Sender_GetIntStatus(void) 
{
    return(Sender_SR_STATUS & Sender_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: Sender_WriteRegValue
********************************************************************************
*
* Summary:
*  Send state directly to shift register
*
* Parameters:
*  shiftData: containing shift register state.
*
* Return:
*  None.
*
*******************************************************************************/
void Sender_WriteRegValue(uint8 shiftData) \
                
{
    CY_SET_REG8(Sender_SHIFT_REG_LSB_PTR, shiftData);
}


#if (Sender_USE_INPUT_FIFO == 1u) /* if input FIFO is used */

    /*******************************************************************************
    * Function Name: Sender_WriteData
    ********************************************************************************
    *
    * Summary:
    *  Send state to FIFO for later transfer to shift register based on the Load
    *  input
    *
    * Parameters:
    *  shiftData: containing shift register state.
    *
    * Return:
    *  Indicates: successful execution of function
    *  when FIFO is empty; and error when
    *  FIFO is full.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 Sender_WriteData(uint8 shiftData) \
                    
    {
        uint8 result;
    
        result = CYRET_INVALID_STATE;/*default result state*/
    
        /*write data to input FIFO if FIFO is not full*/
        if((Sender_GetFIFOStatus(Sender_IN_FIFO)) != Sender_RET_FIFO_FULL)
        {
            CY_SET_REG8(Sender_IN_FIFO_VAL_LSB_PTR, shiftData);
            result = CYRET_SUCCESS; /*return 'success' status*/
        }
        return(result);
    }


#endif/*(Sender_USE_INPUT_FIFO == 1u)*/

#if (Sender_USE_OUTPUT_FIFO == 1u)/*if output FIFO is used*/

    /*******************************************************************************
    * Function Name: Sender_ReadData
    ********************************************************************************
    *
    * Summary:
    *  Returns state in FIFO due to Store input.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Shift Register state
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 Sender_ReadData(void) \
            
    {
        return(CY_GET_REG8(Sender_OUT_FIFO_VAL_LSB_PTR));
    }

#endif/*(Sender_USE_OUTPUT_FIFO == 1u)*/


/*******************************************************************************
* Function Name: Sender_ReadRegValue
********************************************************************************
*
* Summary:
*  Directly returns current state in shift register, not data in FIFO due
*  to Store input.
*
* Parameters:
*  None.
*
* Return:
*  Shift Register state
*
*  Clears output FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 Sender_ReadRegValue(void) 
{
    uint8 result;

    /* Clear FIFO before software capture */

    while(Sender_GetFIFOStatus(Sender_OUT_FIFO) != Sender_RET_FIFO_EMPTY)
    {
        result = CY_GET_REG8(Sender_OUT_FIFO_VAL_LSB_PTR);
    }
    
    /* Capture A1 to output FIFO */
    result = CY_GET_REG8(Sender_SHIFT_REG_VALUE_LSB_PTR);
    
    /* Read output FIFO */
    result = CY_GET_REG8(Sender_OUT_FIFO_VAL_LSB_PTR);
    result = result & Sender_SR_MASK;

    return(result);
}

/* [] END OF FILE */
