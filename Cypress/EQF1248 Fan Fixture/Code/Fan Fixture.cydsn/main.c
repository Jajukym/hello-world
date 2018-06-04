

#include <device.h>

/* Functions */
void ButtonPress(void);
void UpdateDisplay(void);
void UpdateTime(void);

/* Declares */
uint8   intButtonPress;
uint8   uint8Compare;
int     Pin12FanLevel;
int     Pin6FanLevel;
uint16  uint16ADC;
uint16  uint16FanV;
int     intVoltagePlace[4];
uint16   uint16Temp;
uint16  uint16LoV;
uint16  uint16HiV;
uint8   uint8Loop;
uint8   uint8Multiply;
bit     bitFanOn;
uint16 uint16FanAverage[10];
int     intLoop;
bit     bitDisplayTimer;
//Timer Declares
uint8   uint8TimerLCD;
uint8   uint8SaveTime[4]; //Array to hold EEPROM Values
uint8   uint8HourTempLo;
uint8   uint8HourTempHi;
bit     bitUpdateTime;
bit     bitUpdateEEPROM;
uint8   intSecond;
uint8   intMinute;
uint16  intHour;
uint8   uint8TenthSecond;
uint8 uint8Index;
reg8 * RegPointer; //EEPROM register pointer
bit     bitWriteTime;
bit     bitUpdateDisplay;
bit     bitButtonPress;

int main()
{

    /* Starts */
    lcdDisplay_Start();     //Start LCD
    pwmFan_Start();         //Start 3 pin PWM
    pwmFan2_Start();        //Start 2 pin PWM
    adcVFan_Start();        //Start ADC
    clkDisplay_Start();     //Start clock display
    rtcClock_Start();		//Start the Real Time Clock
    eepromTime_Start();		//Start EEPROM
   
    
    /*Interrupts */
    isrButton_StartEx(ButtonPress);             //Interupt for button presses
    isrUpdateDisplay_StartEx(UpdateDisplay);    //Interut to update display
    statusButtons_InterruptEnable();            //Enables interupts in button status register
    CyGlobalIntEnable;                          //Enable Global Interupts
    
    
    
    /* Run Once */
    lcdDisplay_ClearDisplay();                                  //Clear Display
    lcdDisplay_Position(0,0);                                   //Setup LCD
    lcdDisplay_PrintString("Fan PWM:");
    lcdDisplay_Position(1,0);
    lcdDisplay_PrintString("Voltage:");
    rtcClock_WriteIntervalMask(rtcClock_INTERVAL_SEC_MASK);     //Enable interupt in RTC for seconds
    adcVFan_StartConvert();                                     //Start ADC converting
    bitFanOn =  0;                                              //Set fan off
    
    /* Retrieve time from EEPROM */     
	RegPointer = (reg8 *) CYDEV_EE_BASE;                        //setup register
	for (uint8Index = 0u; uint8Index < 3; uint8Index++)         //Loop to read register
		{
			uint8SaveTime[uint8Index] = RegPointer[uint8Index]; //Retrieve data from EEPROM
		}
		uint8HourTempHi = intHour >> 8 ;                        //Convert register data to readable time
		intHour = uint8SaveTime[0];
		intHour = intHour <<8;
		intHour = uint8SaveTime[1];
		intMinute = uint8SaveTime[2];
		intSecond = uint8SaveTime[3];
    
    /* Main Loop */
    for(;;)
    {
        if (bitUpdateTime)  //update time and EEPROM
			{
			bitUpdateTime = 0;  //Reset bit
			UpdateTime();	    
			} //end IF bitUpdateTime
		
		//uint8TimerLCD = tmrUpdateLCD_ReadStatusRegister();
    
    	/* Get ADC Value */
		if (adcVFan_IsEndConversion(adcVFan_WAIT_FOR_RESULT) ) //Wait until ADC has good value
        	{
            uint16ADC = adcVFan_GetResult16();	//Get Compare number from ADC
            //Create Voltage Reading
		    //uint16FanV = ((uint16ADC-15) / 2.33);  //Convert ADC to Voltage
            uint16FanV = ((uint16ADC-15)/2.5);  //Convert ADC to Voltage
    
             
            uint16Temp = uint16FanV;
            //Validate Voltage
                if (uint16FanV > 15000)
                    uint16FanV = 0;
                if (uint16Temp > 99)
                    {
                    uint16HiV = uint16Temp / 100;
                    uint16LoV = uint16Temp % 100;
                    }
                else
                    {
                    uint16HiV = 0;
                    uint16LoV = uint16Temp;
                    }
                
                
			
            }  //End ADC conversion IF
	/* Button Press  */
    if (bitButtonPress)
    {
        bitButtonPress = 0;                                     //Reset Bit
    
        intButtonPress = statusButtons_Read();                  //Read Status Register / clears interrupt

        switch (intButtonPress)
            {
            case Button_UP:  //Up Button - increase PWM %
                {
                if (Pin12FanLevel >= 95)
                    Pin12FanLevel = 100;
                else
                    Pin12FanLevel = Pin12FanLevel + 5;
                    
                break;
                }
            case Button_DN:  //Down Button - decrease PWM % / Reset Timer
                {
                if (!bitDisplayTimer)      //If NOT displaying timer                    
                    {
                    if (Pin12FanLevel <= 5)
                         Pin12FanLevel = 0;
                    else
                        Pin12FanLevel = Pin12FanLevel - 5 ;
                    }
                else
                    {
                    //Reset time to Zero
                	intSecond = 0;
                	intMinute = 0;
                	intHour = 0;
                	rtcClock_WriteSecond(0); //Set seconds on RCT to Zero
                	bitUpdateEEPROM = 1;  //Force a write to the EEPROM
                    UpdateTime();
                    }
                break;
                }
            case Button_Start: //Start Button
                {
                if (bitFanOn) //If fan on, turn off. If off, turn on.
                    {
                    bitFanOn=0;    
                    pwmFan2_Stop();
                    pwmFan_Stop();
                    }
                else
                    {
                    bitFanOn=1;
                    pwmFan2_Start();
                    pwmFan_Start();
                    }
                break;
                }
            case Button_Timer:  //Timer - Display Timer or Fan info
                {
                if (bitDisplayTimer)
                    {
                    bitDisplayTimer = 0;
                    lcdDisplay_ClearDisplay();
                    lcdDisplay_Position(0,0);
                    lcdDisplay_PrintString("Fan PWM:");
                    lcdDisplay_Position(1,0);
                    lcdDisplay_PrintString("Voltage:");
                    }
                else
                    {
                    bitDisplayTimer = 1;
                    lcdDisplay_ClearDisplay();
                    lcdDisplay_PrintString("Timer:");
                    
                    }
                break;    
                }
            }
            pwmFan2_WriteCompare(Pin12FanLevel);    //Write PWM 
            pwmFan_WriteCompare(Pin12FanLevel);     //Write PWM
            if (Pin12FanLevel < 5)
                {
                bitFanOn=0;                         
                pwmFan2_Stop();                     //Stop PWM
                pwmFan_Stop();                      //Stop PWM
                }
    } //End Button Press IF
 
    
    /* Update Display */
    if (bitUpdateDisplay)
        {
        bitUpdateDisplay = 0;   //Reset Bit
        if (!bitDisplayTimer)   //If NOT displaying timer show fan info
            {
            lcdDisplay_ClearDisplay();              //setup LCD
            lcdDisplay_Position(0,0);
            lcdDisplay_PrintString("Fan PWM:");
            lcdDisplay_Position(1,0);
            lcdDisplay_PrintString("Voltage:");

            lcdDisplay_Position(0,8);
            lcdDisplay_PrintNumber(pwmFan_ReadCompare());       //Display PWM
            lcdDisplay_PrintString("% ");
            lcdDisplay_Position(0,13);
            if (bitFanOn)                                       //Display if fan is on or off
                lcdDisplay_PrintString("On ");
            else
                lcdDisplay_PrintString("Off");
            lcdDisplay_Position(1,8);
            lcdDisplay_PrintNumber(uint16HiV);                    //Display voltage
            lcdDisplay_PrintString(".");
            lcdDisplay_PrintNumber(uint16LoV);
            lcdDisplay_PrintString("v   ");
            }
        else                //if displaying Timer, show timer.
            {
            lcdDisplay_Position(0,6);
            lcdDisplay_PrintNumber(intHour); //Print Hour
            lcdDisplay_PrintString(":");
            lcdDisplay_PrintNumber(intMinute / 10); //Print Minute
            lcdDisplay_PrintNumber(intMinute % 10); //Print Minute
            lcdDisplay_PrintString(":");
            lcdDisplay_PrintNumber(intSecond / 10); //Print Seconds
            lcdDisplay_PrintNumber(intSecond % 10); //Print Seconds
            lcdDisplay_PrintString("     ");
            }
            

        } //End IF Update Display
    
    }
}
/* Interupt to update display  */
CY_ISR(UpdateDisplay)
{
bitUpdateDisplay = 1;   //Update Display
}
CY_ISR(ButtonPress)  //Interpt to handle Buttons
{
bitButtonPress = 1;      //Button has been pressed
}


void UpdateTime()  //Updates time and EEPROM
{
	if (bitFanOn) //Fan On 
		{
		intSecond++;
		if (intSecond > 59)         //increase minutes
			{
			intSecond = 0;
			intMinute ++;
			bitUpdateEEPROM = 1;
			}
		if (intMinute > 59)     //Increase Hours
			{
			intMinute = 0;
			intHour ++;
			}
		if (bitUpdateEEPROM)    //Write Timer value to EEPROM
			{
			bitUpdateEEPROM = 0;

                //convert data and write to eeprom
				uint8HourTempLo = intHour;
				uint8HourTempHi = intHour >> 8 ;
				uint8SaveTime[0] = uint8HourTempHi;
				uint8SaveTime[1] = uint8HourTempLo;
				uint8SaveTime[2] = intMinute;
				uint8SaveTime[3] = intSecond;
                 /* Get the die temp before write */
			    if(CySetTemp() == CYRET_SUCCESS)
        	  	    eepromTime_Write(uint8SaveTime, 0u); 
			}
		} 
    
}

/* [] END OF FILE */