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
int y = 0; //cycle count of full test









int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    initialize();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        LCD_Position(0,11);
        LCD_PrintNumber(y+1);
        int x = 0; //cycle count of rapid switch test
        if (x < 7)
        {
            rapid_switch();
            x++;
        }
        test();
        y++;
        /* Place your application code here. */
    }
}

/* [] END OF FILE */


void initialize()
{
    
    LCD_Start();
    LCD_ClearDisplay();
    LCD_Position(0,1);
    LCD_PrintString("AC Power Cycle");
    LCD_Position(1,5);
    LCD_PrintString("Test");
    CyDelay(500);
    pinSwitchIndicator_Write(0);
    CyDelay(250);
    pinSwitchIndicator_Write(1);
    CyDelay(250);
    LCD_ClearDisplay();
    LCD_Position(0,0);
    LCD_PrintString("Cycle #: ");
}

void rapid_switch()
{
    pinRelay_Write(0);                  //1/5 quick switch off 1 second/on 5 seconds
    pinSwitchIndicator_Write(1);
    CyDelay(1000);
    pinRelay_Write(1);
    pinSwitchIndicator_Write(0);
    CyDelay(5000);
}

void test()
{
    pinRelay_Write(0);                  //1/60 load test off 5 seconds/on 5 minutes
    pinSwitchIndicator_Write(1);
    CyDelay(5000);
    pinRelay_Write(1);
    pinSwitchIndicator_Write(0);
    CyDelay(300000);
}