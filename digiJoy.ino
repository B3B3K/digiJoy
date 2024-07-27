//DigiJoystick test and usage documentation
#define XPIN A0
#define YPIN A1
#define AVG_READ 100
#define ANALOG_MAX 1023

#include "DigiJoystick.h"
long x_centre;
long y_centre;

long avg_reading(uint8_t pin) {
  long t = 0;
  for (int i = 0; i < AVG_READ; i++) {
    delay(10);
    t += analogRead(pin);
  }
  return t / AVG_READ;
}

byte map_reading(long v, long v_centre, long out_from, long out_centre, long out_to) {
  if (v == v_centre) {
    return out_centre;
  } else if (v < v_centre) {
    return map(v, 0, v_centre, out_from, out_centre);
  } else { // v > v_centre
    return map(v, v_centre, ANALOG_MAX, out_centre, out_to);
  }
}

void setup() {
//TO BE CLEAR, IF YOUR P5 IS RESETTING THE DIGISPARK, PLEASE FOLLOW THIS>>>> https://ihackedathing.blogspot.com/2016/11/digispark-reset-disable.html THIS WEB PAGE SHOWS YOU HOW TO CHANGE FUSE, DO IT ON YOUR RESPONSIBILITY. IF YOU WANNA REUSE P5 AS RESET, GOOGLE ABOUT ATTINY HIGH VOLTAGE PROGRAMMING
  pinMode(A0, INPUT); //X or Y axis, idk (P0)
  pinMode(A1, INPUT); //X or Y axis, idk this too (P5)
  pinMode(0, INPUT_PULLUP); // joyistick with sw bbutton on it, as B button
  pinMode(1, INPUT_PULLUP); // 5v ------ switch ------- P1 >>>> as A button 
  x_centre = avg_reading(XPIN);
  y_centre = avg_reading(YPIN);
}


void loop() {

  DigiJoystick.setX(map_reading(analogRead(XPIN), x_centre, 0, 128, 255));
  DigiJoystick.setY(map_reading(analogRead(YPIN), y_centre, 255, 128, 0));
  DigiJoystick.setButtons(
    (char)((digitalRead(1) ? 0x00 : 0x01) | (digitalRead(0) ? 0x02 : 0x00)),
    0x00
);


  DigiJoystick.delay(50); // wait 50 milliseconds

}
