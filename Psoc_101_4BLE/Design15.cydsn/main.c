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

#define NUM_CHANNELS        (2)



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    uint8 ctlval = 0;
    
    PWM_Start();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        PWM_WriteCompare(16634);
        Control_Write(ctlval);
        ctlval++;
        
        if(ctlval >= NUM_CHANNELS)
        {
            ctlval = 0;
        }
        CyDelay(500);
    }
}

/* [] END OF FILE */
