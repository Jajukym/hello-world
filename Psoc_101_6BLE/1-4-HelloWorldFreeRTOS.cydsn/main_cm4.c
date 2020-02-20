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

void LED_TASK(void *arg)
{
    for(;;)
    {
        Cy_GPIO_Write(RED_PORT,RED_NUM,1);
        vTaskDelay(500);
        Cy_GPIO_Write(RED_PORT,RED_NUM,0);
        vTaskDelay(500);
        
    }
}

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    xTaskCreate(LED_TASK,"LED_TASK",400,NULL,1,0);
    vTaskStartScheduler();
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
