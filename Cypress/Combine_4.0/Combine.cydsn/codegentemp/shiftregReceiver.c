/*******************************************************************************
* File Name: shiftregReceiver.c
* Version 2.30
*
* Description:
*  This file provides the API source code for the Shift Register component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "shiftregReceiver.h"

uint8 shiftregReceiver_initVar = 0u;


/*******************************************************************************
* Function Name: shiftregReceiver_Start
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
*  shiftregReceiver_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void shiftregReceiver_Start(void) 
{
    if(0u == shiftregReceiver_initVar)
    {
        shiftregReceiver_Init();
        shiftregReceiver_initVar = 1u; /* Component initialized */
    }

    shiftregReceiver_Enable();
}


/*******************************************************************************
* Function Name: shiftregReceiver_Enable
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
void shiftregReceiver_Enable(void) 
{
    /* Changing address in Datapath Control Store
       from NOP to component state machine commands space */
    shiftregReceiver_SR_CONTROL |= shiftregReceiver_CLK_EN;

    shiftregReceiver_EnableInt();
}


/*******************************************************************************
* Function Name: shiftregReceiver_Init
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
void shiftregReceiver_Init(void) 
{
    shiftregReceiver_SetIntMode(shiftregReceiver_INT_SRC);
}


/*******************************************************************************
* Function Name: shiftregReceiver_Stop
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
void shiftregReceiver_Stop(void) 
{
    /*changing Datapath Control Store address to NOP space*/
    shiftregReceiver_SR_CONTROL &= ((uint8) ~shiftregReceiver_CLK_EN);
    shiftregReceiver_DisableInt();
}


/*******************************************************************************
* Function Name: shiftregReceiver_EnableInt
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
void shiftregReceiver_EnableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    shiftregReceiver_SR_AUX_CONTROL |= shiftregReceiver_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: shiftregReceiver_DisableInt
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
void shiftregReceiver_DisableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    shiftregReceiver_SR_AUX_CONTROL &= ((uint8) ~shiftregReceiver_INTERRUPTS_ENABLE);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: shiftregReceiver_GetFIFOStatus
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
uint8 shiftregReceiver_GetFIFOStatus(uint8 fifoId) 
{
    uint8 result;

    result = shiftregReceiver_RET_FIFO_NOT_DEFINED;

    #if(0u != shiftregReceiver_USE_INPUT_FIFO)
        if(shiftregReceiver_IN_FIFO == fifoId)
        {
            switch(shiftregReceiver_GET_IN_FIFO_STS)
            {
                case shiftregReceiver_IN_FIFO_FULL :
                    result = shiftregReceiver_RET_FIFO_FULL;
                    break;

                case shiftregReceiver_IN_FIFO_EMPTY :
                    result = shiftregReceiver_RET_FIFO_EMPTY;
                    break;

                case shiftregReceiver_IN_FIFO_PARTIAL:
                    result = shiftregReceiver_RET_FIFO_PARTIAL;
                    break;
                    
                default:
                    /* Initial result value, while 
                       IN_FIFO_EMPTY case is false 
                     */
                    result = shiftregReceiver_RET_FIFO_EMPTY;
                    break;
            }   
        }
    #endif /* (0u != shiftregReceiver_USE_INPUT_FIFO) */

    if(shiftregReceiver_OUT_FIFO == fifoId)
    {
        switch(shiftregReceiver_GET_OUT_FIFO_STS)
        {
            case shiftregReceiver_OUT_FIFO_FULL :
                result = shiftregReceiver_RET_FIFO_FULL;
                break;

            case shiftregReceiver_OUT_FIFO_EMPTY :
                result = shiftregReceiver_RET_FIFO_EMPTY;
                break;

            case shiftregReceiver_OUT_FIFO_PARTIAL :
                result = shiftregReceiver_RET_FIFO_PARTIAL;
                break;

            default:
                /* Initial result value, while 
                   OUT_FIFO_FULL case is false 
                 */
                result = shiftregReceiver_RET_FIFO_FULL;
                break;
        }
    }

    return(result);
}


/*******************************************************************************
* Function Name: shiftregReceiver_SetIntMode
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
void shiftregReceiver_SetIntMode(uint8 interruptSource) 
{
    shiftregReceiver_SR_STATUS_MASK &= ((uint8) ~shiftregReceiver_INTS_EN_MASK);          /* Clear existing int */
    shiftregReceiver_SR_STATUS_MASK |= (interruptSource & shiftregReceiver_INTS_EN_MASK); /* Set int */
}


/*******************************************************************************
* Function Name: shiftregReceiver_GetIntStatus
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
uint8 shiftregReceiver_GetIntStatus(void) 
{
    return(shiftregReceiver_SR_STATUS & shiftregReceiver_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: shiftregReceiver_WriteRegValue
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
void shiftregReceiver_WriteRegValue(uint8 shiftData)
                                                                     
{
    CY_SET_REG8(shiftregReceiver_SHIFT_REG_LSB_PTR, shiftData);
}


#if(0u != shiftregReceiver_USE_INPUT_FIFO)
    /*******************************************************************************
    * Function Name: shiftregReceiver_WriteData
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
    *  when FIFO is empty; and error when FIFO is full.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    cystatus shiftregReceiver_WriteData(uint8 shiftData)
                                                                         
    {
        cystatus result;

        result = CYRET_INVALID_STATE;

        /* Writes data into the input FIFO if it is not FULL */
        if(shiftregReceiver_RET_FIFO_FULL != (shiftregReceiver_GetFIFOStatus(shiftregReceiver_IN_FIFO)))
        {
            CY_SET_REG8(shiftregReceiver_IN_FIFO_VAL_LSB_PTR, shiftData);
            result = CYRET_SUCCESS;
        }

        return(result);
    }
#endif /* (0u != shiftregReceiver_USE_INPUT_FIFO) */


#if(0u != shiftregReceiver_USE_OUTPUT_FIFO)
    /*******************************************************************************
    * Function Name: shiftregReceiver_ReadData
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
    uint8 shiftregReceiver_ReadData(void) 
    {
        return(CY_GET_REG8(shiftregReceiver_OUT_FIFO_VAL_LSB_PTR));
    }
#endif /* (0u != shiftregReceiver_USE_OUTPUT_FIFO) */


/*******************************************************************************
* Function Name: shiftregReceiver_ReadRegValue
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
*  Shift Register state. Clears output FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 shiftregReceiver_ReadRegValue(void) 
{
    uint8 result;

    /* Clear FIFO before software capture */
    while(shiftregReceiver_RET_FIFO_EMPTY != shiftregReceiver_GetFIFOStatus(shiftregReceiver_OUT_FIFO))
    {
        (void) CY_GET_REG8(shiftregReceiver_OUT_FIFO_VAL_LSB_PTR);
    }

    /* Read of 8 bits from A1 causes capture to output FIFO */
    (void) CY_GET_REG8(shiftregReceiver_SHIFT_REG_CAPTURE_PTR);

    /* Read output FIFO */
    result  = CY_GET_REG8(shiftregReceiver_OUT_FIFO_VAL_LSB_PTR);
    
    #if(0u != (shiftregReceiver_SR_SIZE % 8u))
        result &= ((uint8) shiftregReceiver_SR_MASK);
    #endif /* (0u != (shiftregReceiver_SR_SIZE % 8u)) */
    
    return(result);
}


/* [] END OF FILE */
