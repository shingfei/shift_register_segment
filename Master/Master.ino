#include <Wire.h>

int testButton = 13;
int buttonState =0;
boolean set = false;
int currentSlaveAdress = 8;
byte x = 0;
long previous;
const int amountSlaves = 2; //Change this to apply multiple slaves connection
int slaveCounter = 1;
int floorChecking[amountSlaves];

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
else
{
checkingConnection();
connectionDelay();  
}
  
  minusDelay();  
}

void checkingConnection()
  {
    if(set == true)
    {
  Serial.println("True");
  Wire.beginTransmission(currentSlaveAdress); // transmit to device #8
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  x++;
  connectionDelay();
    }
else if(set == false)
    {
  Wire.requestFrom(currentSlaveAdress, 1);    // request 6 bytes from slave device #8
  while (Wire.available()) 
    { // slave may send less than requested
  int receivingByte = Wire.read(); // receive a byte as character
  
  Serial.println(receivingByte);         // print the character
  Serial.println("recieving from slave");
   if(slaveCounter == amountSlaves )
    {
       currentSlaveAdress = 8;
       slaveCounter = 1;
       connectionDelay();
    }
  else if(receivingByte > 0)
  {
    currentSlaveAdress = currentSlaveAdress+ 1;
    slaveCounter = slaveCounter + 1;
    connectionDelay();
  }

  else
       {
          connectionDelay();
        }
     }
    }
  }

int minusDelay()
{
  previous = millis();
  while(millis()-previous <= 500){};
}

int connectionDelay()
{ 
  previous = millis();
  while(millis()-previous <= 100){};
}

