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
   
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    PWM_Start();
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        PWM_WriteCompare(500);
        CyDelay(1000);
        PWM_WriteCompare(9500);
        CyDelay(1000);
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
