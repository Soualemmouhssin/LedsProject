#include <FastLED.h>
//#include "Entropy.h"
#define _TASK_SLEEP_ON_IDLE_RUN
#include "TaskScheduler.h"

#define NUM_LEDS1 7
CRGB leds_1[NUM_LEDS1];
#define PIN1 4

#define NUM_LEDS2 7
CRGB leds_2[NUM_LEDS2];
#define PIN2 3


void sparkleTask();
Scheduler runner;
Task spark(60000, TASK_FOREVER, &sparkleTask); // task for sparkling every one hour

int sparkleDuration = 3000 ; // sparkle effect duration is 1  minute
int sparklSpeed = 10 ;
byte sparkeBright = 255 ;

uint16_t Position = 0;
unsigned long Now = 0 ;

void setup()
{
  FastLED.addLeds<WS2811, PIN1, GRB>(leds_1, NUM_LEDS1).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<WS2811, PIN2, GRB>(leds_2, NUM_LEDS2).setCorrection( TypicalLEDStrip );
  LEDS.setBrightness(84);
  runner.addTask(spark);
  spark.enable() ;
  runner.startNow();
  Serial.begin(115200) ;
  randomSeed(25) ; 

}


void loop() {
  runner.execute();
  //RunningLights(255, 255 , 255 , 200 , 2000) ;
  
  switch (random(0,5)) {
  case 0 :
    RunningLights(255, 0, 255, 100, random(2000, 6000) );
    break ;
  case 1 : 
    FadeInOut(0, 255, 0,  random(2000, 6000));
    break ; 
  case 2 : 
    rainbowCycle( 20, random(2000, 6000) ) ;
    break ;
  case 3 : 
    Strobe( 0, 0, 255, 3, 100, 500, random(2000, 6000));
    break ;
  case 4 : 
    TwinkleRandom(3,50,100,random(2000, 6000)) ; 
  break ; 
  }

}

void sparkleTask() {
  Now = millis();
  Serial.println(Now / 1000);
  Serial.println("spark") ;
  LEDS.setBrightness(sparkleDuration);
  setAll(0, 0, 0, 1, NUM_LEDS1) ;
  while (millis() - Now < sparkleDuration) {
    //Entropy.Initialize();
    int Pixel =  random(NUM_LEDS2);
    setPixel(Pixel, 0xFF, 0xFF, 0xFF, 1);
    delay(100 / sparklSpeed);
    setPixel(Pixel, 0, 0, 0, 1);
  }
}


void setPixel(int Pixel, byte red, byte green, byte blue, byte strip) {
  if (strip == 1) {
    leds_1[Pixel].r = red;
    leds_1[Pixel].g = green;
    leds_1[Pixel].b = blue;
  }
  else {
    leds_2[Pixel].r = red;
    leds_2[Pixel].g = green;
    leds_2[Pixel].b = blue;
  }
  FastLED.show();
}

void setAll(byte red, byte green, byte blue, uint8_t strip, int numleds ) {
  for (int i = 0; i < numleds; i++ ) {
    setPixel(i, red, green, blue, strip);
  }
  FastLED.show();
}
