///////////Shift register 74HC595N
//Pin connected to ST_CP of 74HC595 RCK
int latchPin = 11;
//Pin connected to SH_CP of 74HC595 SCK
int clockPin = 13;
////Pin connected to DS of 74HC595 Serial in SER
int dataPin = 12;
//////////////////////////RGB off = 255, 255,255
int redPin = 10;
int greenPin =8;
int bluePin = 9;
///////Button panel
int buttonUp = 7;
int ledUp = 6;
int buttonDown = 5;
int ledDown = 4;
int buttonStateUp = 0;
int buttonStateDown = 0;
boolean currentStateUp;
boolean currentStateDown;
//In Bits Floor 0 = 63, F1 = 6, F2 = 91, F3 = 79, F4= 102 etc etc...
//Bits = 1(segment a), 2(segment b), 4 (segment c), 8 (d), 16 (e) , 32 (f) ,64(g), 128(DP)
int floors[] = {63,6,91,79,102,109,125,7,103}; 

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(buttonUp,INPUT);
  pinMode(buttonDown,INPUT);
  pinMode(ledUp,OUTPUT);
  pinMode(ledDown,OUTPUT);
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
}
 
 void setColor(int red, int green, int blue)
    {
     red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
      analogWrite(redPin, red);
      analogWrite(greenPin, green);
      analogWrite(bluePin, blue);  
    }

void loop() {
digitalWrite(latchPin, LOW);
buttonStateUp = digitalRead(buttonUp);
buttonStateDown = digitalRead(buttonDown);
if(buttonStateUp == LOW && currentStateUp == true)
{
  setColor(0, 255, 255);
  digitalWrite(ledUp,LOW);
  currentStateUp = false;
  shiftOut(dataPin, clockPin, MSBFIRST, floors[1]);  
  digitalWrite(latchPin, HIGH);
  delay(200);
}
else if(buttonStateUp== LOW && currentStateUp == false)
{
  setColor(255, 255, 150);
  currentStateUp = true;
  digitalWrite(ledUp,HIGH); 
  shiftOut(dataPin, clockPin, MSBFIRST, floors[0]);  
  digitalWrite(latchPin, HIGH);
  delay(200);
}
 if(buttonStateDown == LOW && currentStateDown == true)
{
  setColor(150, 255, 255);
  digitalWrite(ledDown,LOW);
  currentStateDown = false;
  shiftOut(dataPin, clockPin, MSBFIRST, floors[1]);  
  digitalWrite(latchPin, HIGH);
  delay(200);
}
else if(buttonStateDown== LOW && currentStateDown == false)
{
  setColor(255, 255,150);
  currentStateDown = true;
  digitalWrite(ledDown,HIGH); 
  shiftOut(dataPin, clockPin, MSBFIRST, floors[0]);  
  digitalWrite(latchPin, HIGH);
  delay(200);
}
else
{

delay(1);
}

}
