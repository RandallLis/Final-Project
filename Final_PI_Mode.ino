/*
This is a program designed to control a light loop where an LED is the actuator 
and a LDR is the sensor with P Control.
*/

#include <LiquidCrystal.h>                                    // Adds the LiquidCrystal librairy in order to use the lcd srceen 
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;   // Define which of the Arduino pins are connected to the LCD's pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                    // Define the LCD pin numbers that are in use

int sensor = A1;                                              // Associating pin A5 to the word sensor
int actuator = 6;                                             // Associating pin 9 to the word acutator
int PV = 0;                                                   // Creating a variable called PV
int CO = 0;                                                   // Creating a variable called CO
int setpoint = 0;                                             // Creating a variable called setpoint
int Error = 0;                                                // Creating a variable called Error
float pGain = 0.00;                                           // Creating a variable called pGain
float iGain = 0.00;                                           // Creating a variable called iGain
int integralAction;                                           // Creating a variable called integralAction
unsigned long previousMillis = 0;                             // Creating a variable called previousMillis
const long interval = 100;                                    // Creating a variable called interval that has a value of 100
unsigned long currentMillis;                                  // Creating a variable called currentMillis
int BTN1 = 0;                                                 // Creating a variable called BTN1
int BTN2 = 0;                                                 // Creating a variable called BTN2
int SCRN = 0;                                                 // Creating a variable called SCRN
int SCRNOLD = 0;                                              // Creating a variable called SCRNOLD
int SLECT = 0;                                                // Creating a variable called SLECT
int SLECTOLD = 0;                                             // Creating a variable called SLECTOLD
int i = 0;                                                    // Creating a variable called i
int j = 0;                                                    // Creating a variable called j
 
void setup() {
  // put your setup code here, to run once:

Serial.begin (9600);                                          // Initializing the serial communication
lcd.begin(16, 2);                                             // Initializing a 16x2 LCD screen in order to display something on it
pinMode(actuator,OUTPUT);                                     // Declare the pin associated with actuator as an output
pinMode(sensor,INPUT);                                        // Declare the pin associated with sensor as an input
pinMode(8 ,INPUT);                                            // Declare the pin 7 as an input
pinMode(9 ,INPUT);                                            // Declare the pin 6 as an input
pinMode(10 ,INPUT);                                            // Declare the pin 8 as an input
pinMode(13 ,INPUT);                                           // Declare the pin 13 as an input

}

void loop() {
  // put your main code here, to run repeatedly:

BTN1 = digitalRead(8);                                        // BTN1 will read the current state of pin 7
BTN2 = digitalRead(9);                                        // BTN2 will read the current state of pin 6
SCRN = digitalRead(10);                                        // SCRN will read the current state of pin 8
SLECT = digitalRead(13);                                      // SLECT will read the current state of pin 13
PV = analogRead(sensor);                                      // PV will read the current state of the sensor

if (SCRNOLD==0 && SCRN==1){                                   // This is the code that will allow you to change pages on the LCD screen
  if (i==0){
    i=1;
  }
else{ i=0;;
 }
}
SCRNOLD = SCRN;

if (SLECTOLD==0 && SLECT==1){                                // This is the code that will allow you to select if you wnat change the Kp or the Ki when they are both on the LCD screen
  if (j==0){
    j=1;
  }
else{ j=0;;
 }
}
SLECTOLD = SLECT;

if (i == 0){                                                 // When i is 0 it will print the PV and the SP on the LCD screen
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("PV = ");
 lcd.print(PV);
 lcd.setCursor(0,1);
 lcd.print("SP = ");
 lcd.print(setpoint);
  
}
else if (i == 1 && j ==0){                                  // When i is 1 and j is 0 it will print the Kp and the Ki onthe LCD screen and you will only be able to modify the value of the Kp
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Kp = ");
 lcd.print(pGain);
 lcd.setCursor(11,0);
 lcd.print ("-");
 lcd.setCursor(0,1);
 lcd.print("Ki = ");
 lcd.print(iGain);
}

else if (i == 1 && j == 1){                                  // When i is 1 and j is 1 it will print the Kp and the Ki onthe LCD screen and you will only be able to modify the value of the Ki
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Kp = ");
 lcd.print(pGain);
 lcd.setCursor(0,1);
 lcd.print("Ki = ");
 lcd.print(iGain);
 lcd.setCursor(11,1);
 lcd.print ("-");
}

Serial.print(PV);
Serial.print(setpoint);
Serial.print(pGain);
Serial.print(iGain);
Serial.println();

if (i == 0){                                                 // When SP is being displyed button 1 will increase the SP by 1
 if (BTN1 == HIGH){
   setpoint = setpoint + 1;
  
 }
 else{
  setpoint = setpoint;
 }

 if (BTN2 == HIGH){                                          // When SP is being displayed button 2 will decrease the SP by 1
  setpoint = setpoint - 1;
  
 }
 else{
  setpoint = setpoint;
 }
}
else if(i == 1 && j == 0){

 if (BTN1 == HIGH){                                         // When Kp is being displayed and selected button 1 will increase the Kp by 0.01
   pGain = pGain + 0.01;
  
 }
 else{
   pGain = pGain;
 }

 if (BTN2 == HIGH){                                         // When Kp is being displayed and selected button 2 will decrease the Kp by 0.01
   pGain = pGain - 0.01;
  
 }
 else{
   pGain = pGain;
 }
}
else if(i == 1 && j == 1){

 if (BTN1 == HIGH){                                          // When Ki is being displayed and selected button 1 will increase the Ki by 0.01
   iGain = iGain + 0.01;
  
 }
 else{
   iGain = iGain;
 }

 if (BTN2 == HIGH){                                           // When Ki is being displayed and selected button 2 will decrease the Ki by 0.01
   iGain = iGain - 0.01;
  
 }
 else{
   iGain = iGain;
 }
}

currentMillis = millis();                                    // currentMillis will represent the amount of time since the prgram has been uplaoded

if (currentMillis - previousMillis >= interval){             // Calcuations to find the C.O. in PI control
  previousMillis = currentMillis;
  Error = setpoint-PV;
  integralAction = (integralAction + Error);
  CO = (pGain * Error) + (iGain * integralAction);
}

if (CO > 255){                                               // Putting a maximum cap for the C.O.
  CO = 255;
}
if (CO < 0){                                                 // Putting a minimum cap for the C.O.
  CO = 0;
}

if (integralAction > 250){                                   // Putting a maximum cap for the integralAction
  integralAction = 250;
}

analogWrite(actuator, CO);                                   // Control the brightness of the LED base on the value of the C.O.

}
