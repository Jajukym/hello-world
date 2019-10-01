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
#include <project.h>
#include <cyapicallbacks.h>

int16 x = 0;                            //Number of programs
void ButtonFunction();



int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    ADC_SAR_Seq_Button_Start();
    ADC_SAR_Seq_Button_StartConvert();
    PWMBacklight_Start();
    PWMBacklight_WriteCompare(32768);
    LCD_Start();
    LCD_ClearDisplay();
    LCD_Position(0,1);
    LCD_PrintString("Legacy Program");
    LCD_Position(1,5);
    LCD_PrintString("Test");
    CyDelay(2000);
    LCD_ClearDisplay();
    LCD_Position(0,0);
    LCD_PrintString("Program #: ");
    LCD_Position(0,11);
    LCD_PrintNumber(x);
    


    for(;;)
    {
        int16 button = ADC_SAR_Seq_Button_GetResult16(0);
        LCD_Position(1,0);
        LCD_PrintString("       ");
        if (button != NO)
        {
            ButtonFunction();
        }
        LCD_Position(0,11);
        if (x < 1000)
        {
            pinReset_Write(1);
            CyDelay(500);
            pinReset_Write(0);
            CyDelay(500);
            pinPower_Write(1);
            CyDelay(1000);
            pinPower_Write(0);
            CyDelay(335000);                  //Programming time
            x ++;
            LCD_PrintNumber(x);
        }
        else
        {
           //do nothing
        }
    }
}

/* [] END OF FILE */

/*************************************************************
Button functions
*************************************************************/
void ButtonFunction()
{
    int16 buttonfunction = ADC_SAR_Seq_Button_GetResult16(0);
    switch (buttonfunction)
        {
            case U:
            {
                LCD_Position(1,0);
                LCD_PrintString("UP");
                break;
            }
            case D:
            {
                LCD_Position(1,0);
                LCD_PrintString("DOWN");
                break;
            }
            case L:
            {
                LCD_Position(1,0);
                LCD_PrintString("LEFT");
                break;
            }
            case R:
            {
                LCD_Position(1,0);
                LCD_PrintString("RIGHT");
                break;
            }
            case S:
            {
                LCD_Position(1,0);
                LCD_PrintString("SELECT");
                break;
            }
            default:
            {
                LCD_Position(1,0);
                LCD_PrintString("       ");
                break;
               
            }
        }
}