/*******************************************************************************
* File Name: shiftregSender.c
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

#include "shiftregSender.h"

uint8 shiftregSender_initVar = 0u;


/*******************************************************************************
* Function Name: shiftregSender_Start
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
*  shiftregSender_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void shiftregSender_Start(void) 
{
    if(0u == shiftregSender_initVar)
    {
        shiftregSender_Init();
        shiftregSender_initVar = 1u; /* Component initialized */
    }

    shiftregSender_Enable();
}


/*******************************************************************************
* Function Name: shiftregSender_Enable
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
void shiftregSender_Enable(void) 
{
    /* Changing address in Datapath Control Store
       from NOP to component state machine commands space */
    shiftregSender_SR_CONTROL |= shiftregSender_CLK_EN;

    shiftregSender_EnableInt();
}


/*******************************************************************************
* Function Name: shiftregSender_Init
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
void shiftregSender_Init(void) 
{
    shiftregSender_SetIntMode(shiftregSender_INT_SRC);
}


/*******************************************************************************
* Function Name: shiftregSender_Stop
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
void shiftregSender_Stop(void) 
{
    /*changing Datapath Control Store address to NOP space*/
    shiftregSender_SR_CONTROL &= ((uint8) ~shiftregSender_CLK_EN);
    shiftregSender_DisableInt();
}


/*******************************************************************************
* Function Name: shiftregSender_EnableInt
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
void shiftregSender_EnableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    shiftregSender_SR_AUX_CONTROL |= shiftregSender_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: shiftregSender_DisableInt
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
void shiftregSender_DisableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    shiftregSender_SR_AUX_CONTROL &= ((uint8) ~shiftregSender_INTERRUPTS_ENABLE);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: shiftregSender_GetFIFOStatus
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
uint8 shiftregSender_GetFIFOStatus(uint8 fifoId) 
{
    uint8 result;

    result = shiftregSender_RET_FIFO_NOT_DEFINED;

    #if(0u != shiftregSender_USE_INPUT_FIFO)
        if(shiftregSender_IN_FIFO == fifoId)
        {
            switch(shiftregSender_GET_IN_FIFO_STS)
            {
                case shiftregSender_IN_FIFO_FULL :
                    result = shiftregSender_RET_FIFO_FULL;
                    break;

                case shiftregSender_IN_FIFO_EMPTY :
                    result = shiftregSender_RET_FIFO_EMPTY;
                    break;

                case shiftregSender_IN_FIFO_PARTIAL:
                    result = shiftregSender_RET_FIFO_PARTIAL;
                    break;
                    
                default:
                    /* Initial result value, while 
                       IN_FIFO_EMPTY case is false 
                     */
                    result = shiftregSender_RET_FIFO_EMPTY;
                    break;
            }   
        }
    #endif /* (0u != shiftregSender_USE_INPUT_FIFO) */

    if(shiftregSender_OUT_FIFO == fifoId)
    {
        switch(shiftregSender_GET_OUT_FIFO_STS)
        {
            case shiftregSender_OUT_FIFO_FULL :
                result = shiftregSender_RET_FIFO_FULL;
                break;

            case shiftregSender_OUT_FIFO_EMPTY :
                result = shiftregSender_RET_FIFO_EMPTY;
                break;

            case shiftregSender_OUT_FIFO_PARTIAL :
                result = shiftregSender_RET_FIFO_PARTIAL;
                break;

            default:
                /* Initial result value, while 
                   OUT_FIFO_FULL case is false 
                 */
                result = shiftregSender_RET_FIFO_FULL;
                break;
        }
    }

    return(result);
}


/*******************************************************************************
* Function Name: shiftregSender_SetIntMode
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
void shiftregSender_SetIntMode(uint8 interruptSource) 
{
    shiftregSender_SR_STATUS_MASK &= ((uint8) ~shiftregSender_INTS_EN_MASK);          /* Clear existing int */
    shiftregSender_SR_STATUS_MASK |= (interruptSource & shiftregSender_INTS_EN_MASK); /* Set int */
}


/*******************************************************************************
* Function Name: shiftregSender_GetIntStatus
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
uint8 shiftregSender_GetIntStatus(void) 
{
    return(shiftregSender_SR_STATUS & shiftregSender_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: shiftregSender_WriteRegValue
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
void shiftregSender_WriteRegValue(uint8 shiftData)
                                                                     
{
    CY_SET_REG8(shiftregSender_SHIFT_REG_LSB_PTR, shiftData);
}


#if(0u != shiftregSender_USE_INPUT_FIFO)
    /*******************************************************************************
    * Function Name: shiftregSender_WriteData
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
    cystatus shiftregSender_WriteData(uint8 shiftData)
                                                                         
    {
        cystatus result;

        result = CYRET_INVALID_STATE;

        /* Writes data into the input FIFO if it is not FULL */
        if(shiftregSender_RET_FIFO_FULL != (shiftregSender_GetFIFOStatus(shiftregSender_IN_FIFO)))
        {
            CY_SET_REG8(shiftregSender_IN_FIFO_VAL_LSB_PTR, shiftData);
            result = CYRET_SUCCESS;
        }

        return(result);
    }
#endif /* (0u != shiftregSender_USE_INPUT_FIFO) */


#if(0u != shiftregSender_USE_OUTPUT_FIFO)
    /*******************************************************************************
    * Function Name: shiftregSender_ReadData
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
    uint8 shiftregSender_ReadData(void) 
    {
        return(CY_GET_REG8(shiftregSender_OUT_FIFO_VAL_LSB_PTR));
    }
#endif /* (0u != shiftregSender_USE_OUTPUT_FIFO) */


/*******************************************************************************
* Function Name: shiftregSender_ReadRegValue
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
uint8 shiftregSender_ReadRegValue(void) 
{
    uint8 result;

    /* Clear FIFO before software capture */
    while(shiftregSender_RET_FIFO_EMPTY != shiftregSender_GetFIFOStatus(shiftregSender_OUT_FIFO))
    {
        (void) CY_GET_REG8(shiftregSender_OUT_FIFO_VAL_LSB_PTR);
    }

    /* Read of 8 bits from A1 causes capture to output FIFO */
    (void) CY_GET_REG8(shiftregSender_SHIFT_REG_CAPTURE_PTR);

    /* Read output FIFO */
    result  = CY_GET_REG8(shiftregSender_OUT_FIFO_VAL_LSB_PTR);
    
    #if(0u != (shiftregSender_SR_SIZE % 8u))
        result &= ((uint8) shiftregSender_SR_MASK);
    #endif /* (0u != (shiftregSender_SR_SIZE % 8u)) */
    
    return(result);
}


/* [] END OF FILE */
