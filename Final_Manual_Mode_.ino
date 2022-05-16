/*
This is a program designed to control a light loop where an LED is the actuator 
and a LDR is the sensor with Manual Control.
*/

#include <LiquidCrystal.h>                                          // Adds the LiquidCrystal librairy in order to use the lcd srceen 
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;         // Define which of the Arduino pins are connected to the LCD's pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                          // Define the LCD pin numbers that are in use

int sensor = A1;                                                    // Associating pin A5 to the word sensor
int BTN1 = 0;                                                       // Creating a varibale called BTN1
int BTN2 = 0;                                                       // Creating a varibale called BTN1
int actuator = 6;                                                   // Associating pin 9 to the word sensor                                     
int PV = 0;                                                         // Creating a variable called PV
int SCRN = 0;                                                       // Creating a varible called SCRN
int SCRNOLD = 0;                                                    // CReating a variable called SCRNOLD
int i = 0;                                                          // Creating a variable called i
int CO = 0;                                                         // Creating a variable called CO

void setup() {
  // put your setup code here, to run once:
  
Serial.begin (9600);                                                // Initializing the serial communication
lcd.begin(16, 2);                                                   // Initializing a 16x2 LCD screen in order to display something on it
pinMode(actuator,OUTPUT);                                           // Declare the pin associated with actuator as an output
pinMode(sensor,INPUT);                                              // Declare the pin associated with sensor as an input
pinMode(8 ,INPUT);                                                  // Declare the pin 7 as an input
pinMode(9 ,INPUT);                                                  // Declare the pin 6 as an input
pinMode(10 ,INPUT);                                                  // Declare the pin 8 as an input
}

void loop() {
  // put your main code here, to run repeatedly:
  
BTN1 = digitalRead(8);                                              // BTN1 will read the current state of pin 7
BTN2 = digitalRead(9);                                              // BTN2 will read the current state of pin 6
SCRN = digitalRead(10);                                              // SCRN will read the current state of pin 8
PV = analogRead(sensor);                                            // PV SCRN will read the current state of the sensor 

if (SCRNOLD==0 && SCRN==1){                                         // This is the code that will allow you to change pages on the LCD screen
  if (i==0){
    i=1;
  }
else{ i=0;;
 }
}
SCRNOLD = SCRN;

if (i == 0){                                                        // One page will print the C.O. and the other page will print the PV
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("CO = ");
 lcd.print(CO);
}
else{
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("PV = ");
 lcd.print(PV);
}

Serial.print(CO);
Serial.print(PV);
Serial.println();

if (i == 0){                                                       // When button 1 is pushed increase the C.O by 1
 if (BTN1 == HIGH){
   CO = CO + 1;
  
 }
 else{
  CO = CO;
 }

 if (BTN2 == HIGH){                                               // When button 2 is pushed decrease the C.O by 1
  CO = CO - 1;
  
 }
 else{
  CO = CO;
 }
}

analogWrite(actuator,CO);                                         // Control the brightness of the LED base on the value of the C.O.

if (CO < 0){                                                      // Putting a maximum and minimum cap for the C.O.
  CO = 0;
}

if (CO > 255){
  CO = 255;
}

}
