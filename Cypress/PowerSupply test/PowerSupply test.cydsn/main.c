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
#include <cyapicallbacks.h>

/*Functions*/
void initialize();
void test();
void rapid_switch();
void smartbell_test();
void adc_buttons();
void LCD_update();

/*Global Variables*/
int x = 0; //cycle count of rapid switch test
int y = 0; //cycle count of full test
int z_on = 5000; //time on for smartbell_test()
int z_off = 15000; //time off for smartbell_test()









int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    initialize();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    for(;;)
    {
        LCD_Position(0,9);
        LCD_PrintNumber(y+1);
        adc_buttons();
        LCD_update();
       
        /*if (x < 7) //load test loop
        {
            rapid_switch();
            x++;
        }
        test();*/
        smartbell_test();
        y++;
        
        /* Place your application code here. */
    }
}

/* [] END OF FILE */


void initialize()
{
    ADC_SAR_Seq_Button_Start();
    ADC_SAR_Seq_Button_StartConvert();    
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

void smartbell_test()
{
    pinRelay_Write(0);                  // 1/1 5 seconds on / 15 seconds off
    pinSwitchIndicator_Write(1);
    CyDelay(z_off);
    pinRelay_Write(1);
    pinSwitchIndicator_Write(0);
    CyDelay(z_on);
}

void adc_buttons()
{
    uint16 button = ADC_SAR_Seq_Button_GetResult16(0);
    
        switch (button)
        {
            case U: //on time up
            {
                //LCD_Position(1,0);
                //LCD_PrintString("UP");
                z_on = z_on + 1000;
                break;
            }
            case D: //on time down
            {
                //LCD_Position(1,0);
                //LCD_PrintString("DOWN");
                z_on = z_on - 1000;
                if (z_on <= 1000)
                {
                    z_on = 1000;
                }
                break;
            }
            case L: //off time down
            {
                //LCD_Position(1,0);
                //LCD_PrintString("LEFT");
                z_off = z_off - 1000;
                if (z_off <= 1000)
                {
                    z_off = 1000;
                }
                break;
            }
            case R: //off time up
            {
                //LCD_Position(1,0);
                //LCD_PrintString("RIGHT");
                z_off = z_off + 1000;
                break;
            }
            case S: //default on/off 1/3
            {
                //LCD_Position(1,0);
                //LCD_PrintString("SELECT");
                z_on = 5000;
                z_off = 15000;
                break;
            }
            default:
            {
                //LCD_Position(1,0);
                //LCD_PrintString("       ");
                break;
               
            }
        }
        //Uncomment to debug button ADC register values.
        /*LCD_Position(1,0);
        LCD_PrintString("Button Data:");
        LCD_PrintInt16(ADC_SAR_Seq_Button_GetResult16(0));*/
}
void LCD_update()
{
    LCD_Position(1,0);
    LCD_PrintString("OFF:");
    LCD_PrintNumber(z_off/1000);
    LCD_Position(1,8);
    LCD_PrintString("ON:");
    LCD_PrintNumber(z_on/1000);
}