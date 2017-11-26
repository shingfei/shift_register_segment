// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>
//COM3
// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

int testButton = 13;
int buttonState =0;
boolean set = false;
int a = 8;
byte x = 0;
byte y = 0;
long previous;


void setup() 
{
  pinMode(testButton,INPUT);
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}


void loop() {
buttonState = digitalRead(testButton);

if(buttonState ==HIGH && set == true)
{
  set = false;
  Serial.println("recieve");
  minusDelay();
}
else if(buttonState ==HIGH && set == false)
{
  set = true;
  Serial.println("send");
  minusDelay();
}
if(set == true)
{
  Serial.println("True");
  Wire.beginTransmission(a); // transmit to device #8
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  x++;
  minusDelay();
}
else if(set == false)
{
  Wire.requestFrom(a, 1);    // request 6 bytes from slave device #8
  while (Wire.available()) 
    { // slave may send less than requested
  int c = Wire.read(); // receive a byte as character
  
  Serial.println(c);         // print the character
  Serial.println("false");
  if(c == 1)
  {
    Serial.println("Hello from the other side");
    a = a+1;
    minusDelay();
  }
   else if(c == 2)
  {
    a = a -1;
    Serial.println("Hello from the other 2nd side");
    minusDelay();
  }
  else
  {
    minusDelay();
  }
   }
  }
else
{
Serial.println("waiting");
minusDelay();  
}
  
}

int minusDelay()
{
  previous = millis();
  while(millis()-previous <= 500){};
}

