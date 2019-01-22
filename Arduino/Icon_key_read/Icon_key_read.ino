//This code reads Icon captouch boards..................

#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(80, 2);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    int c = Wire.read(); // receive a byte as integer
    Serial.print(c, HEX);
  }
  Serial.println("");
  delay(500);
}
