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

/*******************************************************************************
* This project displays Cypress Logo (bitmap image) and some strings
* It uses bit-banging method (sending the data bit-by-bit from CPU)
********************************************************************************/

#include <project.h>
#include "Nokia5110LCD.h"


/* CapSense Slider resoluton is set to 127 (7 bits).
*  Since PWM has 16 bit resolution, slider position value should be shifted left
*  by 9 bits.
*/
#define SLIDER_POS_TO_COMPARE_SHIFT    (9u)

void CapSense_DisplayState(void);

uint16 curPos, oldPos;




int main()
{
    /* Enable global interrupts */
    CyGlobalIntEnable;
   
    /* Initialize the LCD */
    LCD_Init();
    
    
    /* Start PWM and CapSense components */
    PWM_FanDriver_Start();
    CapSense_CSD_Start();	

    /* Initialize baselines */ 
    CapSense_CSD_InitializeAllBaselines();
    
   
    
    for(;;)
    {
        /* Update all baselines */
        CapSense_CSD_UpdateEnabledBaselines();
        
   		/* Start scanning all enabled sensors */
    	CapSense_CSD_ScanEnabledWidgets();
    
        /* Wait for scanning to complete */
		while(CapSense_CSD_IsBusy() != 0)
		{
			/* Loop until condition true */
		}

		/* Display CapSense state using LEDs */
        CapSense_DisplayState();
    }
}

/* [] END OF FILE */



/*******************************************************************************
* Function Name: CapSense_DisplayState
********************************************************************************
* Summary:
*  Changes LEDs brightness by changing the duty cycle of PWM signals.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_DisplayState(void)
{
    /* Find Slider Position */
    curPos = CapSense_CSD_GetCentroidPos(CapSense_CSD_LINEARSLIDER0__LS);    
    
    /* Reset position */
    if(curPos == 0xFFFFu)
    {
        curPos = 0x0u;
    }
                
    /* Move bargraph */
    if (curPos != oldPos)
    {
        oldPos = curPos;
        /* Display Slider bargraph */
        if (curPos != 0x0u)
        {
            PWM_FanDriver_WriteCompare((uint32)curPos << SLIDER_POS_TO_COMPARE_SHIFT);
        }        
    }
}