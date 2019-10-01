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


void initialize();
void test();
void rapid_switch();








int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    initialize();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        test();
        int x = 0;
        if (x < 7)
        {
            rapid_switch();
            x++;
        }
        /* Place your application code here. */
    }
}

/* [] END OF FILE */


void initialize()
{
    int y = 0;
    if (y < 5)
    {
        pinSwitchIndicator_Write(0);
        CyDelay(250);
        pinSwitchIndicator_Write(1);
        CyDelay(250);
    }
   
}
void test()
{
    pinRelay_Write(0);                  //1/12
    pinSwitchIndicator_Write(1);
    CyDelay(5000);
    pinRelay_Write(1);
    pinSwitchIndicator_Write(0);
    CyDelay(300000);
}

void rapid_switch()
{
    pinRelay_Write(0);                  //1/5
    pinSwitchIndicator_Write(1);
    CyDelay(1000);
    pinRelay_Write(1);
    pinSwitchIndicator_Write(0);
    CyDelay(3000);
}