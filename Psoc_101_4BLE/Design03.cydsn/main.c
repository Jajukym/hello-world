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

CY_ISR(Pin_SW2_Handler)
{
    Pin_Red_Write(~Pin_Red_Read());
    Pin_Blue_Write(~Pin_Blue_Read());
    Pin_SW2_ClearInterrupt();
}

int main(void)
{
    Pin_Blue_Write(0);
    CyGlobalIntEnable; /* Enable global interrupts. */
    Pin_SW2_int_StartEx(Pin_SW2_Handler);

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
