/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>

uint16 sliderval;
uint16 oldsliderval = 0xFFFF;
char msg[10];

void buttonPress();

int main()
{      
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    UART_1_Start();
    CapSense_1_Start();
    CapSense_1_InitializeEnabledBaselines();
    CapSense_1_ScanEnabledWidgets();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        if(!CapSense_1_IsBusy())
        {
            sliderval = CapSense_1_GetCentroidPos(CapSense_1_LINEARSLIDER0__LS);
            
            if (sliderval != 0xFFFF && sliderval != oldsliderval)
            
            {
                sprintf(msg, "%3d\r\n", sliderval);
                UART_1_UartPutString(msg);
                oldsliderval = sliderval;
            }
            CapSense_1_UpdateEnabledBaselines();
            CapSense_1_ScanEnabledWidgets();
            
        }
    }
}

/* [] END OF FILE */


void buttonPress()
{
    if(sliderval == oldsliderval && sliderval <= 20)
    {
        
    }
}