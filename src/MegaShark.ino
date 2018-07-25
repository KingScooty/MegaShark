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

void loop() {
    // tlc.setLED(0, 65535, 0, 0);
    // tlc.setLED(0, 0, 65535, 0);
    // Particle.publish("Turn on LED??");
    // delay(200);
    // tlc.setLED(0, 0, 0, 0);
    // delay(200);


    // eyeLeft();
  //colorWipe(65535, 0, 0, 100); // "Red" (depending on your LED wiring)



  // delay(200);
  // colorWipe(0, 65535, 0, 100); // "Green" (depending on your LED wiring)
  // delay(200);
  // colorWipe(0, 0, 65535, 100); // "Blue" (depending on your LED wiring)
  // delay(200);
  //
  // rainbowCycle(5);
}


// Fill the dots one after the other with a color
void colorWipe(uint16_t r, uint16_t g, uint16_t b, uint8_t wait) {
  for(uint16_t i=0; i<8*NUM_TLC59711; i++) {
      tlc.setLED(i, r, g, b);
      tlc.write();
      delay(wait);
  }
}

void eyeLeft() {
    //65535, 0, 0, 100
    tlc.setLED(2, 65535, 0 , 0);
    // tlc.write();
    // delay(wait);
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
