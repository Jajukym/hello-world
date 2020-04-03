/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*   Enumerates as a Virtual Com port.  Receives data from hyper terminal, then 
*   send received data backward. LCD shows the Line settings.
*   
*  To test project:
*   1. Build the project and program the hex file on to the target device.
*   2. Select 3.3V in SW3 and plug-in power to the CY8CKIT-001
*   3. Connect USB cable from the computer to the CY8CKIT-001.
*   4. Select the USB_UART.inf file from the project directory, as the driver 
*      for this example once Windows asks for it.
*   5. Open "Device Manager" and note the COM port number for "Example Project"
*      device.
*   6. Open "HyperTerminal" application and make new connection to noted COM port
*   7. Type the message, observe echo data received.
*
* Related Document:
*  Universal Serial Bus Specification Revision 2.0 
*  Universal Serial Bus Class Definitions for Communications Devices 
*  Revision 1.2
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <device.h>
#include "stdio.h"

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow the usage of floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
    asm (".global _printf_float");
#endif

/* The size of the buffer is equal to maximum packet size of the 
*  IN and OUT bulk endpoints. 
*/
#define BUFFER_LEN  64u

#define RD_BUFFER_LEN           (64u)
#define WR_BUFFER_LEN           (64u)
#define MUX_SIZE                (4u)

/* ASCII value of decimal zero is 48 */
#define ASCII_DECIMAL_ZERO      (48u)

/* Any value above 0x07 is an illegal input for mux channel selection */
#define ERROR_MASK              (0xF8u)

/* Function that encapsulates the process of writing text strings to USBUART */
void PrintToUSBUART(char8 * outText);

char8 *parity[] = { "None", "Odd", "Even", "Mark", "Space" };
char8 *stop[] = { "1", "1.5", "2" };

int main()
{
    /* adcReading holds the converted 16-bit data from the ADC */
    uint16 adcReading = 0u;
    uint8 rdBuffer[RD_BUFFER_LEN];
    uint8 wrBuffer[WR_BUFFER_LEN];
    uint8 rdValue;
    uint8 temp;

    /* Enable Global interrupts - used for USB communication */
    CyGlobalIntEnable;

    SPIM_Start();
    USBUART_1_Start(0u, USBUART_1_3V_OPERATION);
    /*LCD_Char_Start();
    LCD_Char_Init();
    LCD_Char_ClearDisplay();
    LCD_Char_PrintString("USB to UART test");*/
    SPIM_Start();
    ADC_SAR_0_Start();
    ADC_SAR_1_Start();
    PWM_Load_Start();

    /* When implementing a <=4 channel mux, the Analog sequencing Mux is faster
     * on an average than the Analog Hardware mux. However, additional code is
     * required to select channels non-sequentially.
     */
    AMux_0_Start();
    AMux_1_Start();

    /* Wait for Device to enumerate */
    while(!USBUART_1_GetConfiguration());

    /* Enumeration is complete, enable OUT endpoint for received data from Host */
    USBUART_1_CDC_Init();

    for(;;)
    {
        PWM_Load_WriteCompare(25);
        pin_12v_enable_Write(1);        
        PrintToUSBUART("Please choose the channel (0-7) \n\r");

        /* Wait for input data from PC */
        while(USBUART_1_DataIsReady() == 0u);
        USBUART_1_GetAll(rdBuffer);

        /* Convert ASCII value in rdBuffer to numerical value:
         * Note that ASCII 48, 49,...,57 (decimal) corresponds to 0,1,...,9
         */
        rdValue = rdBuffer[0] - ASCII_DECIMAL_ZERO;

        /* If the value read is not a number in the range [0,7] */
        if(rdValue & ERROR_MASK)
        {
            //LCD_Char_ClearDisplay();
            //LCD_Char_PrintString("Input Error");
            sprintf((char *)wrBuffer, "Input Error, (%d) \n\r",(int)(rdValue));
            PrintToUSBUART((char8 *)wrBuffer);
        }

        else /* The input from user is valid */
        {
            /* If this input is in the range [0,3], use mux0 */
            if(!(rdValue/MUX_SIZE))
            {
                AMux_0_FastSelect(rdValue);

                /* Initiate a single conversion of input data (ADC is in triggered
                 * mode).
                 */
                ADC_SAR_0_StartConvert();
                //ADC_SAR_0_IsEndConversion(ADC_SAR_0_WAIT_FOR_RESULT);
                adcReading = ADC_SAR_0_GetResult16();

                sprintf((char *)wrBuffer, "The ADC_0 channel(%d) is: 0x%4x \n\r\n\r",
                                                            (int)rdValue, adcReading);
            }

            else
            {
                /* If rdValue is between [4,7], scale down to [0,3] */
                AMux_1_FastSelect(rdValue % MUX_SIZE);

                ADC_SAR_1_StartConvert();
                //ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT);
                adcReading = ADC_SAR_1_GetResult16();

                sprintf((char *)wrBuffer, "The ADC_1 channel(%d) is: 0x%4x \n\r\n\r",
                                                (int)(rdValue % MUX_SIZE), adcReading);
            }

            PrintToUSBUART((char8 *)wrBuffer);
        }

        /* For verification purposes, display the adcReading on the LCD
        LCD_Char_ClearDisplay();
        LCD_Char_PrintString("0x");
        LCD_Char_PrintInt16(adcReading);
        LCD_Char_Position(1,0);
        LCD_Char_PrintInt8(rdValue);
        LCD_Char_Position(2,0);
        LCD_Char_PrintInt8(rdBuffer[0]);
        LCD_Char_Position(3,0);
        LCD_Char_PrintString("end");*/
        

        /* Clear the transmit buffer before next reading (good practice) */
        SPIM_ClearTxBuffer();

        temp = SPIM_ReadTxStatus();

        /* Ensure that previous SPI read is done, or SPI is idle before sending data */
        if((temp & (SPIM_STS_SPI_DONE | SPIM_STS_SPI_IDLE)))
        {
            SPIM_WriteTxData(adcReading);
        }

    }  /* End of forever loop */
}  /* End of main */


/*******************************************************************************
* Function Name: PrintToUSBUART
********************************************************************************
*
* Summary:
*  The input string passed to the function is printed to the USBUART
*  interface when the CDC device is ready.
*
* Parameters:
*  Text to be printed to USBUART as a string.
*
* Return:
*  None.
*
*******************************************************************************/

void PrintToUSBUART(char8 * outText)
{
    /* Wait till the CDC device is ready before sending data */
    while(USBUART_1_CDCIsReady() == 0u);
    /* Send strlen number of characters of wrBuffer to USBUART */
    USBUART_1_PutData((uint8 *)outText, strlen(outText));
}


/* [] END OF FILE */
