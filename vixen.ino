/*
Based loosly on code from Neil Tapp 22 July 2011
v0.1 its upto the user to ensure channel count = incoming channel #
Due to 'Vixen generic serial using only ascii and not utf8, we cant
have a distinct header footer marker, thus no 'buffer / data set / error checks'
*/

#include "Utils.h"

/************************************************************************************/
/*     This is the beginning of the section that you customize for your leds.       */
/*     Everything you'll need to set is right below here.                           */
/*                                                                                  */
/*     The settings below are for a typical 8 channel Arduino output on pins        */  
/*     4-11. You can customize this for your own preference.                        */
/*                                                                                  */
/************************************************************************************/

// Define a pin for each of your leds and name them accordingly. Check the Arduino specs 
// to be sure you put in valid numbers. Invalid numbers may cause your Arduino to be bricked.
// For clarity's sake name all additional pins LED and the next value. 

#define LED1 4
#define LED2 5
#define LED3 6
#define LED4 7
#define LED5 8
#define LED6 9
#define LED7 10
#define LED8 11

// set the value of this to the number of LED pins defined above. Again, validate that the
// number is correct or you could brick your Arduino
#define CHANNELS_LENGTH 8

// Initalize this array with each of the LED values defined above. Same warning about bricking.
const int chanDigital[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};

// Triple check all of your changes above or you will brick your Arduino.

/************************************************************************************/
/*      This is the beginning of the section that you customize for your leds.      */
/*      Don't touch anything below here unless you know what you are confident in   */ 
/*      what you are  doing.                                                        */  
/************************************************************************************/

int incomingByte[CHANNELS_LENGTH]; // size of the chanPWM array

// specifically for the uno
#include <avr/interrupt.h>


// The rest should work automagically.
int i = 0;     // Loop counter

//setup the pins/ inputs & outputs
void setup(){
  //chanDigitalCount = sizeof(chanDigital);

  // specifically for the UNO
  sei();  

 // initalize PWM Channels / Pins
 for (i=0; i < CHANNELS_LENGTH + 1; i++){
    pinMode(chanDigital[i], OUTPUT);
 }

 //we cant define the buffer here :(
 testSequence();
 
 // use 9600 , None 8, 1 for UNO
  Serial.begin(9600);        // set up Serial at 9600 bps
}

void loop()
{
  
   if (Serial.available() >= CHANNELS_LENGTH+2) {
     int uno = Serial.read();
     if (uno == 126){
       
       int dos = Serial.read();
       if (dos == 33){
   
         for (int i=0; i < CHANNELS_LENGTH + 1; i++) {
             // read each byte
          incomingByte[i] = Serial.read();
         }

         //Serial.println("Data Read");
         //for (int i=0; i<8; i++) {
           // read each byte
         //  Serial.print("Byte: ");Serial.println(incomingByte[i]);
         //}


         for (int i=0; i < CHANNELS_LENGTH + 1; i++) {
          led(chanDigital[i], incomingByte[i]);
         }

       }
     }
   }
}

void led(int pin, int value){
  if (value < 49){
    turnOff(pin);
  }
  else
  {
   turnOn(pin);
  }
}


void testSequence(){

 for (i=0; i < CHANNELS_LENGTH; i++){
     turnOn(chanDigital[i], 500);
     turnOff(chanDigital[i], 500);
 }

}

