/*******************************************************************************
* File Name: main.c
*
* Version: 2.20
*
* Description:
*   This is a source code for example project of ADC single ended mode.
*
*   Variable resistor(pot) is connected to +ve input of ADC using the I/O pin.
*   P0.0. When voltage to positive terminal of ADC is 0, the output displayed
*   on the LCD pannel is 0x0000. As voltage on positive terminal goes on
*   increasing, the  converted value goes on increasing from 0x0000 and reaches
*   0xFFFF when voltage becomes 1.024V. Futher increase in voltage value,
*   doesn't cause any changes to values displayed in the LCD.
*
* Hardware Connections:
*  Connect analog input from Variable resistor to port P0[0] of DVK1 board.
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <device.h>
uint16 output;
uint16 DEC;



int main()
{
    

    /* Start the components */

    LCD_Start();
    ADC_DelSig_1_Start();
    PWM_Start();
   

    /* Start the ADC conversion */
    ADC_DelSig_1_StartConvert();

    /* Display the value of ADC output on LCD */
    LCD_Position(0u, 0u);
    LCD_PrintString("ADC_Output");

    for(;;)
    {
        if(ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_RETURN_STATUS))
        {
            output = ADC_DelSig_1_GetResult16();
            LCD_Position(1u, 0u);
            LCD_PrintInt16(output);
            if (output < 0x0033)
            {
            PWM_WriteCompare(0);
            LCD_Position(3,0);
            LCD_PrintString("MIN");
            }
            else if (output > 0x00CD)
            {
            PWM_WriteCompare(0x00CD * 64);
            LCD_Position(3,0);
            LCD_PrintString("MAX");
            }
            else
            {
            PWM_WriteCompare(output * 64);
            LCD_Position(3,0);
            LCD_PrintString("   ");
            }
        }
    }
}


/* [] END OF FILE */
