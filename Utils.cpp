#include "Utils.h"
#include "pins_arduino.h"
#include "Arduino.h"

// this method is here for testing purposes only 
//bool isValidPin(int pin) {
//  // do not put serial println here it takes too much time and disturbs switching
//  if (pin == LED1 | pin == LED2 | pin == LED3 | pin == LED4 | pin == LED5 | pin == LED6 | pin == LED7 | pin == LED8 ){ return true; }
//  else  {
//    // Serial.print("ERROR: Not a Valid Pin");
//    return false;
//  }
//}

/* Turn a given pin off */
void turnOn(int pin){ digitalWrite(pin, HIGH); }
/* Turn a given pin on */
void turnOff(int pin){ digitalWrite(pin, LOW); }

/* Turn a given pin on then delay*/
void turnOn(int pin, int dlay){ turnOn(pin); delay(dlay);}

/* Turn a given pin off then delay*/
void turnOff(int pin, int dlay){ turnOff(pin); delay(dlay);}


