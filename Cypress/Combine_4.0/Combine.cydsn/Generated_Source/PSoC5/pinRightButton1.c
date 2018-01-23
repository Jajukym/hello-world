/*******************************************************************************
* File Name: pinRightButton1.c  
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
#include "pinRightButton1.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 pinRightButton1__PORT == 15 && ((pinRightButton1__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: pinRightButton1_Write
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
void pinRightButton1_Write(uint8 value) 
{
    uint8 staticBits = (pinRightButton1_DR & (uint8)(~pinRightButton1_MASK));
    pinRightButton1_DR = staticBits | ((uint8)(value << pinRightButton1_SHIFT) & pinRightButton1_MASK);
}


/*******************************************************************************
* Function Name: pinRightButton1_SetDriveMode
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
void pinRightButton1_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(pinRightButton1_0, mode);
}


/*******************************************************************************
* Function Name: pinRightButton1_Read
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
*  Macro pinRightButton1_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 pinRightButton1_Read(void) 
{
    return (pinRightButton1_PS & pinRightButton1_MASK) >> pinRightButton1_SHIFT;
}


/*******************************************************************************
* Function Name: pinRightButton1_ReadDataReg
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
uint8 pinRightButton1_ReadDataReg(void) 
{
    return (pinRightButton1_DR & pinRightButton1_MASK) >> pinRightButton1_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(pinRightButton1_INTSTAT) 

    /*******************************************************************************
    * Function Name: pinRightButton1_ClearInterrupt
    ********************************************************************************
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
    uint8 pinRightButton1_ClearInterrupt(void) 
    {
        return (pinRightButton1_INTSTAT & pinRightButton1_MASK) >> pinRightButton1_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
