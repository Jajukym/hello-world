// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.
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


