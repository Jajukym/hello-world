/*******************************************************************************
* File Name: pinLED2.c  
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
#include "pinLED2.h"


/*******************************************************************************
* Function Name: pinLED2_Write
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
void pinLED2_Write(uint8 value) 
{
    uint8 staticBits = (pinLED2_DR & (uint8)(~pinLED2_MASK));
    pinLED2_DR = staticBits | ((uint8)(value << pinLED2_SHIFT) & pinLED2_MASK);
}


/*******************************************************************************
* Function Name: pinLED2_SetDriveMode
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
void pinLED2_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(pinLED2_0, mode);
}


/*******************************************************************************
* Function Name: pinLED2_Read
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
*  Macro pinLED2_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 pinLED2_Read(void) 
{
    return (pinLED2_PS & pinLED2_MASK) >> pinLED2_SHIFT;
}


/*******************************************************************************
* Function Name: pinLED2_ReadDataReg
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
uint8 pinLED2_ReadDataReg(void) 
{
    return (pinLED2_DR & pinLED2_MASK) >> pinLED2_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(pinLED2_INTSTAT) 

    /*******************************************************************************
    * Function Name: pinLED2_ClearInterrupt
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
    uint8 pinLED2_ClearInterrupt(void) 
    {
        return (pinLED2_INTSTAT & pinLED2_MASK) >> pinLED2_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
