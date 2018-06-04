/*******************************************************************************
* File Name: pinLED4.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "pinLED4.h"


/*******************************************************************************
* Function Name: pinLED4_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void pinLED4_Write(uint8 value) 
{
    uint8 staticBits = (pinLED4_DR & (uint8)(~pinLED4_MASK));
    pinLED4_DR = staticBits | ((uint8)(value << pinLED4_SHIFT) & pinLED4_MASK);
}


/*******************************************************************************
* Function Name: pinLED4_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void pinLED4_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(pinLED4_0, mode);
}


/*******************************************************************************
* Function Name: pinLED4_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro pinLED4_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 pinLED4_Read(void) 
{
    return (pinLED4_PS & pinLED4_MASK) >> pinLED4_SHIFT;
}


/*******************************************************************************
* Function Name: pinLED4_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 pinLED4_ReadDataReg(void) 
{
    return (pinLED4_DR & pinLED4_MASK) >> pinLED4_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(pinLED4_INTSTAT) 

    /*******************************************************************************
    * Function Name: pinLED4_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 pinLED4_ClearInterrupt(void) 
    {
        return (pinLED4_INTSTAT & pinLED4_MASK) >> pinLED4_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
