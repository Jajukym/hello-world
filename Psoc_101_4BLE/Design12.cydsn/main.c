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

int main(void)
{
    UART_Start();
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    UART_UartPutString("\n\r************************************************************");
    UART_UartPutString("\n\r***************** BLE UART example project *****************");
    UART_UartPutString("\n\r************************************************************\n\r");
    UART_UartPutString("\n\rDevice role \t: TX");

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
