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
#include <device.h>

#define forever 1

CY_ISR_PROTO(StoreISR);
CY_ISR(PulseCapture);



int pinDMK;
int CaptureFlag;
uint8 statusButtonRead; //0xFF starting point
uint8 Polar_C_Pulse_Count;
uint8 Polar_S_Pulse_Count;
uint8 ANTplus_Pulse_Count;
uint8 ShiftData[255];



void InitializeHardware()
{
	CyGlobalIntEnable;                                   //ISR
	isrStoreInt_StartEx(StoreISR);
    isrPulseCapture_StartEx(PulseCapture);
    
    
    lcdDisplay_Start();
    lcdDisplay_ClearDisplay();
    pgaPolarC_Start();                                   //Polar Chest Pulse buffer
    counterPolarC_Start();
    pgaPolarS_Start();                                   //Polar Hand Pulse buffer
    counterPolarS_Start();
    pgaANTPlus_Start();                                  //ANT+ Chest Pulse buffer
    counterANTPlus_Start();
    PWMPulseCapture_Start();                             //Capture Clock
	counterShift_Start();                                //Membrane Button Read components
    shiftregSender_Start();
    shiftregSender_WriteData(0x00);
    CyDelay(250);
    shiftregReceiver_Start();	 
}
//***********************************************************************************

int main()
{
    //uint8 ii = 0x00;      //Calibration
    uint8 Status;
	InitializeHardware();
    clockShift_SetDivider(128);
    lcdDisplay_Position(0,8);
    lcdDisplay_PrintString("BETA");
    lcdDisplay_Position(1,0);
    lcdDisplay_PrintString("DMK:");
    lcdDisplay_Position(2,0);
    lcdDisplay_PrintString("Buttons:");
    lcdDisplay_Position(3,0);
    lcdDisplay_PrintString("Pulse:");
    
    
    for(;;)
    {
        if (pinDMK_Read() == 0)                     //DMK function
        {
            lcdDisplay_Position(1,5);
            lcdDisplay_PrintString("ON ");
        }
        else
        {
            lcdDisplay_Position(1,5);
            lcdDisplay_PrintString("OFF");
        }
        if (CaptureFlag == 1)
       {
            CaptureFlag = 0;
            
            Polar_C_Pulse_Count = counterPolarC_ReadCapture();
            lcdDisplay_Position (3,7);
            lcdDisplay_PrintString("Chest");
            
            
            /*Polar_S_Pulse_Count = counterPolarS_ReadCapture();
            lcdDisplay_Position (3,7);
            lcdDisplay_PrintString("Hand");
            
            
            ANTplus_Pulse_Count = counterANTPlus_ReadCapture();
            lcdDisplay_Position (3,7);
            lcdDisplay_PrintString("ANTplus");*/
                        
        }
        
        
        
        statusButton_Read();  //Button Hex strings...Left1:FE, Left2:FD, Rigth1:FB, and Right2:F7
        {
            /*lcdDisplay_Position(2,9);  //Button Hex Strings...InclineD:FE, InclineU:FD, Run:FB, Stop:F7, Speed-:EF, Speed+:DF
            lcdDisplay_PrintInt8(statusButton_Read());*/
            shiftregReceiver_WriteRegValue(statusButton_Read());//Writes to the Shift Register
        }
    	
		if(!((Status = shiftregSender_GetFIFOStatus(shiftregSender_IN_FIFO)) == shiftregSender_RET_FIFO_FULL))
		{
			/*shiftregSender_WriteData(++ii);//FOR CALIBRATION ONLY. WILL COUNT UP FROM 0X00 TO 0XFF.*/
            {
                lcdDisplay_Position(2,9);
                lcdDisplay_PrintInt8(shiftregReceiver_ReadData());
            }
		}
           
      }      
}
/*END OF FILE */


/************************************************************************************/
CY_ISR(StoreISR)
{
uint8 Status;
	while((Status = shiftregReceiver_GetFIFOStatus(shiftregReceiver_OUT_FIFO)) == shiftregReceiver_RET_FIFO_NOT_EMPTY)
	{
		shiftregReceiver_ReadData();   
	}
}

/**********************************************************************************/
CY_ISR(PulseCapture)
{
    CaptureFlag = 1;
}