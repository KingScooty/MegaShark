/*
 * Project MegaShark
 * Description:
 * Author:
 * Date:
 */

// define RGB_NOTIFICATIONS_CONNECTING_ONLY
// #include "Adafruit_TLC59711.h"
//
// // setup() runs once, when the device is first turned on.
// void setup() {
//   // Put initialization like pinMode and begin functions here.
//   RGB.control(true);
//   RGB.color(0, 0, 0);
// }
//
// // loop() runs over and over again, as quickly as it can execute.
// void loop() {
//   // The core of your code will likely live here.
//
// }






#include "Adafruit_TLC59711.h"
#include "Particle.h"

#include <math.h>

// How many boards do you have chained?
#define NUM_TLC59711 1

#define data   A5
#define clock  A3

Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data);
//Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711);

void setup() {
  // Put initialization like pinMode and begin functions here.
  RGB.control(true);
  RGB.color(0, 0, 0);


  Serial.begin(9600);

  Serial.println("TLC59711 test");
  pinMode(A2, OUTPUT);
  tlc.begin();
  tlc.write();

  Particle.publish("Finish setup");
}

class fader {
  // private:


  // public:
  //   fade(int channel, float offset):
  public:
    void fade(int channel, float offset) {
      static float PI = 3.1415;
      static float inDefault = PI * offset; //4.712; //0;
      static float in = inDefault;
      static float stop = (PI * 2) + in;
      float out;

      in = in + 0.01;

      if (in > stop)
        in = inDefault;

      out = sin(in) * 32667.5 + 32667.5;
      tlc.setPWM(channel, out);
      tlc.write();
    }


};

fader f1;
fader f2;

void loop() {
    // tlc.setLED(0, 65535, 0, 0);
    // tlc.setLED(0, 0, 65535, 0);
    // Particle.publish("Turn on LED??");
    // delay(200);
    // tlc.setLED(0, 0, 0, 0);
    // delay(200);

    // channels 0 - 11
    // max PWM = 65335
    // tlc.setPWM(0, 65335);
    // tlc.write();

    // float in1, out1;
    //
    // for (in1 = 0; in1 < 6.283; in1 = in1 + 0.001)
    // {
    //   out1 = sin(in1) * 32667.5 + 32667.5;
    //     tlc.setPWM(0, out1);
    //     tlc.setPWM(1, out1);
    //     tlc.write();
    // }

    f1.fade(1, 0);
    f2.fade(0, 1.5);

    // float in2, out2;
    //
    // for (in2 = 0; in2 < 6.283; in2 = in2 + 0.001)
    // {
    //   out2 = sin(in2) * 32667.5 + 32667.5;
    //     tlc.setPWM(1, out2);
    //     tlc.write();
    // }


    // tlc.setPWM(0, 65335);
    // tlc.setPWM(11, 10);
    // tlc.write();
    // tlc.setPWM(1, 65335);
    // tlc.setPWM(2, 65335);
    // tlc.setPWM(3, 65335);
    // tlc.setPWM(4, 65335);
    // tlc.setPWM(5, 65335);
    // tlc.setPWM(6, 65335);
    // tlc.setPWM(7, 65335);
    // tlc.setPWM(8, 65335);
    // tlc.setPWM(9, 65335);



  // colorWipe(65535, 0, 0, 100); // "Red" (depending on your LED wiring)
  // delay(200);
  // colorWipe(0, 65535, 0, 100); // "Green" (depending on your LED wiring)
  // delay(200);
  // colorWipe(0, 0, 65535, 100); // "Blue" (depending on your LED wiring)
  // delay(200);
  //
  // rainbowCycle(5);
}

// void fade(int channel, float offset) {
//   static float PI = 3.1415;
//   static float inDefault = PI * offset; //4.712; //0;
//   static float in = inDefault;
//   static float stop = (PI * 2) + in;
//   float out;
//
//   in = in + 0.01;
//
//   if (in > stop)
//     in = inDefault;
//
//   out = sin(in) * 32667.5 + 32667.5;
//   tlc.setPWM(channel, out);
//   tlc.write();
// }

// Fill the dots one after the other with a color
void colorWipe(uint16_t r, uint16_t g, uint16_t b, uint8_t wait) {
  for(uint16_t i=0; i<8*NUM_TLC59711; i++) {
      tlc.setLED(i, r, g, b);
      tlc.write();
      delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint32_t i, j;

  for(j=0; j<65535; j+=10) { // 1 cycle of all colors on wheel
    for(i=0; i < 4*NUM_TLC59711; i++) {
      Wheel(i, ((i * 65535 / (4*NUM_TLC59711)) + j) & 65535);
    }
    tlc.write();
    delay(wait);
  }
}

// Input a value 0 to 4095 to get a color value.
// The colours are a transition r - g - b - back to r.
void Wheel(uint8_t ledn, uint16_t WheelPos) {
  if(WheelPos < 21845) {
    tlc.setLED(ledn, 3*WheelPos, 65535 - 3*WheelPos, 0);
  } else if(WheelPos < 43690) {
    WheelPos -= 21845;
    tlc.setLED(ledn, 65535 - 3*WheelPos, 0, 3*WheelPos);
  } else {
    WheelPos -= 43690;
    tlc.setLED(ledn, 0, 3*WheelPos, 65535 - 3*WheelPos);
  }
}
