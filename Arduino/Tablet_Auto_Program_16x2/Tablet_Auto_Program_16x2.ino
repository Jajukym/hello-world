// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int pin_Reset = 3;
int pin_Power = 2;
int x = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Program #:");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print(x);
  
  pinMode(pin_Reset, OUTPUT);
  pinMode(pin_Power, OUTPUT);
  digitalWrite(pin_Reset, HIGH);
  digitalWrite(pin_Power, LOW);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // Tablet reset and power
  if (x < 1000)
  {
  digitalWrite(pin_Reset, LOW);
  delay(500);
  digitalWrite(pin_Reset, HIGH);
  delay(500);
  digitalWrite(pin_Power, HIGH);
  delay(1000);
  digitalWrite(pin_Power, LOW);
  //program time delay and count
  delay(335000);
  x ++;
  lcd.print(x);
 }
 else
 {
  digitalWrite(pin_Reset, HIGH);
  digitalWrite(pin_Power, LOW); 
 }
}

