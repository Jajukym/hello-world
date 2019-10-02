
#include <device.h>



void main()
{
    uint8 output;
    uint8 lastread;
    
 
    /* Start the components */

    LCD_Start();
    ADC_DelSig_1_Start();
   

    /* Start the ADC conversion */
    ADC_DelSig_1_StartConvert();
    

    /* Display the value of ADC output on LCD */
    LCD_Position(0u, 0u);
    LCD_PrintString("ADC_Output");

    for(;;)
    {
        if(ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_RETURN_STATUS))
        {
            output = ADC_DelSig_1_GetResult8();
            LCD_Position(1u, 0u);
            LCD_PrintInt8(output); 
           
            if ((lastread >= 0xFD) && (output < 0x03))
            {
                output = 0xFF;
            }
            if ((output < 0xAA) && (output > 0x55))
            {
                LCD_Position(2,0);
                LCD_PrintString("         DEAD          ");
            }
            else
            {
                LCD_Position(2,0);
                LCD_PrintString("                      ");
            }
            if(output <= 0x55)
            {
                LCD_Position(3,10);
                LCD_PrintString("Down");
            }
             else
            {
                LCD_Position(3,10);
                LCD_PrintString("     ");
            }
            if(output >= 0xAA)
            {
                LCD_Position(3,0);
                LCD_PrintString("Up");
            }
            else
            {
            LCD_Position(3,0);
            LCD_PrintString("     ");
            }
            lastread = output;
        }
    }
}


/* [] END OF FILE */
