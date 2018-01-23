/*******************************************************************************
* File Name: Receiver.c
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


#include "Receiver.h"
#include "CyLib.h"


uint8 Receiver_initVar = 0u;


/*******************************************************************************
* Function Name: Receiver_Start
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
*  Receiver_initVar - used to check initial configuration, modified on 
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Receiver_Start(void) 
{
    if (Receiver_initVar == 0u)
    {
        Receiver_Init();
        /* variable _initVar is set to indicate the fact of initialization */
        Receiver_initVar = 1u; 
    }

    Receiver_Enable();
}


/*******************************************************************************
* Function Name: Receiver_Enable
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
void Receiver_Enable(void) 
{
    /* changing address in Datapath Control Store
       from NOP to component state machine commands space */
    Receiver_SR_CONTROL |= Receiver_CLK_EN; 
    
    Receiver_EnableInt();
}


/*******************************************************************************
* Function Name: Receiver_Init
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
void Receiver_Init(void) 
{
    Receiver_SetIntMode(Receiver_INT_SRC);
}


/*******************************************************************************
* Function Name: Receiver_Stop
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
void Receiver_Stop(void) 
{
    /*changing Datapath Control Store address to NOP space*/
    Receiver_SR_CONTROL &= ~Receiver_CLK_EN; 
    Receiver_DisableInt();
}


/*******************************************************************************
* Function Name: Receiver_EnableInt
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
void Receiver_EnableInt(void) 
{
    uint8 interruptState = CyEnterCriticalSection();
    Receiver_SR_AUX_CONTROL |= Receiver_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Receiver_DisableInt
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
void Receiver_DisableInt(void) 
{
    uint8 interruptState = CyEnterCriticalSection();
    Receiver_SR_AUX_CONTROL &= ~Receiver_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Receiver_GetFIFOStatus
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
uint8 Receiver_GetFIFOStatus(uint8 fifoId) 
{
    uint8 result;

    result = Receiver_RET_FIFO_NOT_DEFINED; /*default status value*/

    #if (Receiver_USE_INPUT_FIFO == 1u)
        
        if(fifoId == Receiver_IN_FIFO)
        {    
            switch((Receiver_SR_STATUS & Receiver_IN_FIFO_MASK) >> 
                    Receiver_IN_FIFO_SHFT_MASK)
            {
                case Receiver_IN_FIFO_FULL :
                    result = Receiver_RET_FIFO_FULL;
                    break;

                case Receiver_IN_FIFO_EMPTY :
                    result = Receiver_RET_FIFO_EMPTY;
                    break;

                case Receiver_IN_FIFO_NOT_EMPTY :
                    result = Receiver_RET_FIFO_NOT_EMPTY;
                    break;
                default:
                    result = Receiver_RET_FIFO_EMPTY;
            }
        }
    #endif/*(Receiver_USE_INPUT_FIFO == 1u)*/
    
    if(fifoId == Receiver_OUT_FIFO)
    {
        switch((Receiver_SR_STATUS & Receiver_OUT_FIFO_MASK) >> 
                Receiver_OUT_FIFO_SHFT_MASK)
        {
            case Receiver_OUT_FIFO_FULL :
                result = Receiver_RET_FIFO_FULL;
                break;

            case Receiver_OUT_FIFO_EMPTY :
                result = Receiver_RET_FIFO_EMPTY;
                break;

            case Receiver_OUT_FIFO_NOT_EMPTY :
                result = Receiver_RET_FIFO_NOT_EMPTY;
                break;

            default:
                result = Receiver_RET_FIFO_FULL;
        }
    }

    return (result);
}


/*******************************************************************************
* Function Name: Receiver_SetIntMode
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
void Receiver_SetIntMode(uint8 interruptSource) 
{
    Receiver_SR_STATUS_MASK = (Receiver_SR_STATUS_MASK & ~Receiver_INTS_EN_MASK) | \
                                      (interruptSource & Receiver_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: Receiver_GetIntStatus
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
uint8 Receiver_GetIntStatus(void) 
{
    return(Receiver_SR_STATUS & Receiver_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: Receiver_WriteRegValue
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
void Receiver_WriteRegValue(uint8 shiftData) \
                
{
    CY_SET_REG8(Receiver_SHIFT_REG_LSB_PTR, shiftData);
}


#if (Receiver_USE_INPUT_FIFO == 1u) /* if input FIFO is used */

    /*******************************************************************************
    * Function Name: Receiver_WriteData
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
    uint8 Receiver_WriteData(uint8 shiftData) \
                    
    {
        uint8 result;
    
        result = CYRET_INVALID_STATE;/*default result state*/
    
        /*write data to input FIFO if FIFO is not full*/
        if((Receiver_GetFIFOStatus(Receiver_IN_FIFO)) != Receiver_RET_FIFO_FULL)
        {
            CY_SET_REG8(Receiver_IN_FIFO_VAL_LSB_PTR, shiftData);
            result = CYRET_SUCCESS; /*return 'success' status*/
        }
        return(result);
    }


#endif/*(Receiver_USE_INPUT_FIFO == 1u)*/

#if (Receiver_USE_OUTPUT_FIFO == 1u)/*if output FIFO is used*/

    /*******************************************************************************
    * Function Name: Receiver_ReadData
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
    uint8 Receiver_ReadData(void) \
            
    {
        return(CY_GET_REG8(Receiver_OUT_FIFO_VAL_LSB_PTR));
    }

#endif/*(Receiver_USE_OUTPUT_FIFO == 1u)*/


/*******************************************************************************
* Function Name: Receiver_ReadRegValue
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
uint8 Receiver_ReadRegValue(void) 
{
    uint8 result;

    /* Clear FIFO before software capture */

    while(Receiver_GetFIFOStatus(Receiver_OUT_FIFO) != Receiver_RET_FIFO_EMPTY)
    {
        result = CY_GET_REG8(Receiver_OUT_FIFO_VAL_LSB_PTR);
    }
    
    /* Capture A1 to output FIFO */
    result = CY_GET_REG8(Receiver_SHIFT_REG_VALUE_LSB_PTR);
    
    /* Read output FIFO */
    result = CY_GET_REG8(Receiver_OUT_FIFO_VAL_LSB_PTR);
    result = result & Receiver_SR_MASK;

    return(result);
}

/* [] END OF FILE */
