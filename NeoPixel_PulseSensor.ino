/*

 NeoPixel + Pulse Sensor
 
 MGDS-PET
 
 When a pulse is sensed, the interrupt is triggered.
 The three NeoPixels blink red in a heartrate-monitor-type pattern.
 
 Created on December 10, 2014
 
 References:
 * http://pulsesensor.myshopify.com/pages/code-and-guide
 * https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library
 
 Wiring:
 * All pins are on the Bean, BUT the pulse sensor seems to only work well
 when supplied with 5 V; I just used an Uno to supply this
 
 */


#include <Adafruit_NeoPixel.h>

int pulsePin = A0;     // Pulse Sensor purple wire connected to analog pin 0
int neoPin = 3;       // first NeoPixel data in
int vibPin = 5;       // vib motor

// these variables are volatile because they are used during the interrupt service routine
volatile int BPM;                  // used to hold the pulse rate
volatile int Signal;               // holds the incoming raw data
volatile int IBI = 600;            // holds the time between beats, must be seeded! 
volatile boolean Pulse = false;    // true when pulse wave is high, false when it's low
volatile boolean QS = false;       // becomes true when Arduoino finds a beat.

Adafruit_NeoPixel trio = Adafruit_NeoPixel(3, neoPin, NEO_GRB + NEO_KHZ800);    // three NeoPixels in series


void setup()
{
  trio.begin();
  trio.show();

  pinMode(neoPin, OUTPUT);
  pinMode(vibPin, OUTPUT);

  interruptSetup();            // sets up to read Pulse Sensor signal every 2mS 
}


void loop()
{
  // Everything happens in Interrupt
}


void stableNeo()
{
  trio.setPixelColor(0, trio.Color(20, 0, 0));
  trio.setPixelColor(1, trio.Color(20, 0, 0));
  trio.setPixelColor(2, trio.Color(20, 0, 0));

  trio.show();
}  


void pulseNeo()
{
  trio.setPixelColor(0, trio.Color(255, 0, 0));
  trio.setPixelColor(1, trio.Color(20, 0, 0));
  trio.setPixelColor(2, trio.Color(20, 0, 0));
  trio.show();
  delay(70);

  trio.setPixelColor(0, trio.Color(20, 0, 0));
  trio.setPixelColor(1, trio.Color(255, 0, 0));
  trio.setPixelColor(2, trio.Color(20, 0, 0));
  trio.show();
  delay(70);

  trio.setPixelColor(0, trio.Color(20, 0, 0));
  trio.setPixelColor(1, trio.Color(20, 0, 0));
  trio.setPixelColor(2, trio.Color(255, 0, 0));
  trio.show();
  delay(70);
}

