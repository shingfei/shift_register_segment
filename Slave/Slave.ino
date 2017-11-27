#include <Wire.h>

int testButton =12;
int buttonState =0;
const int slaveAdress = 8;
long previous;
boolean set = false;
int response = 1;

void setup() {
  pinMode(testButton,INPUT);
  Wire.begin(slaveAdress);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent);
  Serial.begin(9600);           // start serial for output
}

void loop() {
  buttonStates();
  //setSR();
  minusDelay();
}

void buttonStates()
{
  buttonState = digitalRead(testButton);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer

}

void setSR()
{
  if(buttonState == HIGH && set == true)
  {
  set = false;
  Serial.println("recieve");
  minusDelay();
  }
  if(buttonState == HIGH && set == false)
  {
  set = true;
  Serial.println("recieve");
  minusDelay();
  }
}


// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write(response); // respond with message of 6 bytes
  // as expected by master
}

int minusDelay()
{
  previous = millis();
  while(millis()-previous <= 500){};
}

