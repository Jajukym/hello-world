/*  ---Programming note: Cannot be initially Uploaded/Programmed with wire harness connected.
 *  ---Also designed to be used with the Serial Monitor to show the inputs on the screen

This is used to Test the Pulse Bar FMTL39818
Picture locations should also be sent with this file
Connections for pins from the Pulse Bar as follows:

5 Pin Harness:
Pin 1 Connect to Vin DNS
Pin 2 Connect to GND or DNS       (Pulsebar pin 4 GND)
Pin 3 Connect to GND              (Pulsebar pin 1 GND)
Pin 4 Connect to 3.3VCD           (Pulsebar pin 2 3.3VCD)
Pin 5 Connect to 5VCD             (Pulsebar pin 5 5VCD)

5 Pin Harness
Pin 1 Connect to RX DNS
Pin 2 Connect to TX DNS
Pin 3 Connect to Digital pin 2    (Pulsebar pin 6 H-PULSE)
Pin 4 Connect to Digital pin 3    (Pulsebar pin 7C-PULSE)
Pin 5 Connect to Digital pin 4    (Pulsebar pin 3 DMK INPUT)

5 Pin Harness
Pin 1 Connect to Digital pin 8    (Pulsebar pin 8 MEMB1)
Pin 2 Connect to Digital pin 9    (Pulsebar pin 9 MEMB2)
Pin 3 Connect to Digital pin 10   (Pulsebar pin 10 MEMB3)
Pin 4 Connect to Digital pin 11   (Pulsebar pin 11 MEMB4)
Pin 5 Connect to Digital pin 12   (Pulsebar pin 12 MEMB5)
*/

// Initialize values for pins for digital input. 
int dmk = 4;          //digital io pin 0
int memb1 = 8;        //digital io pin 1
int memb2 = 9;        //digital io pin 4
int memb3 = 10;        //digital io pin 5
int memb4 = 11;        //digital io pin 6
int memb5 = 12;        //digital io pin 7

// digital interupt pins used for pwm data from heart rate called in the setup()

// ---------used to get timing values for heart rate
// needs volatile as they are changed with an interrupt call
volatile int pwm_value = 0;
volatile int prev_time = 0;
volatile int low_value = 0;
volatile int low_time = 0;
volatile int pwm_valueC = 0;
volatile int prev_timeC = 0;
volatile int low_valueC = 0;
volatile int low_timeC = 0;


//---------Used to toggle input reads to prevent screen scrolling.
int dmkCheck = 0;
int hPulseCheck = 0;
int cPulseCheck = 0;

//---------Used as a wait for miliseconds timer to prevent screen scrolling.
int msDelay = 200;



// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:   ---im sure any speed above 9600 will work.
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(dmk, INPUT_PULLUP);
  pinMode(memb1, INPUT);
  pinMode(memb2, INPUT);
  pinMode(memb3, INPUT);
  pinMode(memb4, INPUT);
  pinMode(memb5, INPUT);

//---- assinging the digital interrupt  pins
  attachInterrupt(1,hRising,RISING);  //digital io pin 2
  attachInterrupt(0,cRising,RISING);  //digital io pin 3
}


// the loop routine runs over and over again forever:
void loop() {
  pulsebarButtons();
  pulsebarDMK();
}


//----------------------Heart rate from hand, using interrupt--------------//
void hRising(){
  attachInterrupt(1,hFalling,FALLING);
  prev_time = millis();
  low_value = millis() - low_time;
  if(low_value >= 400 && low_value <= 1200){
      Serial.print ("Heart Rate data from hands: ");
      Serial.println (low_value);
  }
}
void hFalling(){
  attachInterrupt(1,hRising,RISING);
  pwm_value = millis() - prev_time;
  low_time = millis();
  if(pwm_value >= 49 && pwm_value <= 51){
    Serial.println ("------------Heart Rate-----------");
    Serial.println ("Hand on pulse bar.. -hold to get heart rate data");
    }
  if(pwm_value >= 19 && pwm_value <= 21){
    Serial.println ("------------Heart Rate-----------");
    Serial.println ("Hand holding pulse bar");
    }
  if(pwm_value >= 69 && pwm_value <= 71){
    Serial.println ("------------Heart Rate-----------");
    Serial.println ("Hand released pulse bar");
    }  
}

//----------------------Heart rate from wireless, using interrupt-------------//
void cRising(){
  attachInterrupt(0,cFalling,FALLING);
  prev_timeC = millis();
  low_valueC = millis() - low_timeC;
  if(low_valueC >= 400 && low_valueC <= 1200){
     Serial.println ("------------Heart Rate-----------");
     Serial.print ("Heart Rate data from Wireless: ");
     Serial.println (low_valueC);
  }
}
void cFalling(){
  attachInterrupt(0,cRising,RISING);
  pwm_valueC = millis() - prev_timeC;
  low_timeC = millis();
  if(pwm_valueC >= 49 && pwm_valueC <= 51){
    Serial.println ("------------Heart Rate-----------");
    Serial.println ("Wireless Heart rate active");
    }
}


//----------------Print line Function----------------//
void prnt(String button, String type){
  Serial.print("--------------------");
  Serial.print(type);
  Serial.print("--------------------\n");
  Serial.println(button);
}

//---------------Pulse Bar Functions-----------------//

  //---Activly reads/checks for the inputs---//
void pulsebarDMK(){
  int buttonDMK = digitalRead(dmk);
  //-------------------DMK------------------//
  if (buttonDMK == 0 && dmkCheck == 0){
    prnt("DMK Inserted","DMK");
    dmkCheck = 1;                             //--added dmkCheck to toggle read prevents screen scrolling
  }
  if (buttonDMK == 1 && dmkCheck == 1){
    prnt("DMK Removed","DMK");
    dmkCheck = 0;
  }
}


//------------------------Membrane function-----------------//
void pulsebarButtons(){
  int buttonMemb1 = digitalRead(memb1);
  int buttonMemb2 = digitalRead(memb2);
  int buttonMemb3 = digitalRead(memb3);
  int buttonMemb4 = digitalRead(memb4);
  int buttonMemb5 = digitalRead(memb5);
  



//------------------------Buttons-----------------------------------//
//Incline up    =     memb 1&2     
//Incline down  =     memb 2&4    
//Speed up      =     memb 2&3
//Speed down    =     memb 3&4
//Start         =     memb 1&3
//Stop          =     memb 1&4
//Pause         =     memb 3&5

  if (buttonMemb1 == 0 && buttonMemb2 == 0){
    prnt("Incline Up","Button Pressed");
    delay(msDelay);                                //--Added msDelay(in miliseconds) delay if button is held down to prevent screen scrolling
  }
  if (buttonMemb2 == 0 && buttonMemb4 == 0){
    prnt("Incline Down","Button Pressed");
    delay(msDelay);
  }
  if (buttonMemb2 == 0 && buttonMemb3 == 0){
    prnt("Speed Up","Button Pressed");
    delay(msDelay);
  }
  if (buttonMemb3 == 0 && buttonMemb4 == 0){
    prnt("Speed Down","Button Pressed");
    delay(msDelay);
  }
  if (buttonMemb1 == 0 &&buttonMemb3 == 0){
    prnt("Start","Button Pressed");
    delay(msDelay);
  }
  if (buttonMemb1 == 0 && buttonMemb4 == 0){
    prnt("Stop","Button Pressed");
    delay(msDelay);
  }
  if (buttonMemb3 == 0 && buttonMemb5 == 0){
    prnt("Pause","Button Pressed");
    delay(msDelay);
  }

}


/*//Old Code done by Bryan.Lee
  // read the input pin:
  int buttonDMK = digitalRead(dmk);//----------------------------------DMK--------------------------------
  // print out the state of the button:
  if (buttonDMK == 0)
  Serial.println(" DMK Inserted");
  else
  Serial.println("DMK Removed");
  delay(1);        // delay in between reads for stability
  int buttonHand = digitalRead(hPulse);//-----------------------------------H-Pulse-------------------------------
  // print out the state of the button:
  if (buttonDMK == 0)
  Serial.println("Hand Detected");
  else
  Serial.println("No Hand Detected");
  delay(1);        // delay in between reads for stability
  int buttonChest = digitalRead(cPulse);//-----------------------------------C-Pulse-------------------------------
  // print out the state of the button:
  if (buttonDMK == 0)
  Serial.println("Polar Detected");
  else
  Serial.println("No Polar Detected");
  delay(1);        // delay in between reads for stability

  int buttonMemb1 = digitalRead(memb1);
  int buttonMemb2 = digitalRead(memb2);
  int buttonMemb3 = digitalRead(memb3);
  int buttonMemb4 = digitalRead(memb4);
  int buttonMemb5 = digitalRead(memb5);
  
  //-----------------------------------button1-------------------------------
  // print out the state of the button:
  if (memb1 == 0 && memb2 == 0)
  {
  Serial.println("button1");
  }
  else{
  Serial.println("No Button Pressed");
  delay(1);        // delay in between reads for stability
  }
  
*/
