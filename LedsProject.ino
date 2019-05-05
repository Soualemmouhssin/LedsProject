#include <FastLED.h>
#include <EEPROM.h>
//#include "Entropy.h"
#define _TASK_SLEEP_ON_IDLE_RUN
#include "TaskScheduler.h"

byte colors [10][3] = {
  {255,255,255}, //white
  {255,0,0}, //red
  {0,0,255}, //blue 
  {0,255,0}, //green
  {255,255,0}, //yelow
  {0,255,255}, //cryan
  {255,215,0}, //gold
  {148,0,211}, //violet
  {255,105,180}, //pink
  {210,126,0}, //orange
};
String colornames[10] ={"white","red","blue","green","yelow","cry","gold","violet","pink","orange"};
#define NUM_LEDS1 7
CRGB leds_1[NUM_LEDS1];
#define PIN1 15

#define NUM_LEDS2 7
CRGB leds_2[NUM_LEDS2];
#define PIN2 5

#define defaultSparkleDuration 3 // default sparkling effect duration  in minutes 
#define sparkledurationAdd 5 // position in EEPROM
byte sparkleDuration = defaultSparkleDuration; // sparkle effect duration in minutes

#define defaultPrimaryMode  1 // default primary system mode (1 for normal 0 for events mode 
#define ModeAdd 6 // position in EEPROM
byte primaryMode = defaultPrimaryMode ; 

#define eventsR 255 // default red value for events mode 
#define RAdd 7 // position in EEPROM
byte eventsRed = eventsR ; 

#define eventsG 255 // default green value for events mode 
#define GAdd 8 // position in EEPROM
byte eventsGreen = eventsG ; 

#define eventsB 255 // default blue  value for events mode  
#define BAdd 9 // position in EEPROM
byte eventsBlue = eventsB ; 

#define defaultSparkeSpeed 5 // default blue  value for events mode 5 > 25 blink per second 
#define SpeedAdd 10 // position in EEPROM
byte sparklSpeed = defaultSparkeSpeed ;

#define defaultBright 100 // default blue  value for events mode 5 > 25 blink per second 
#define brigfhtAdd 11 // position in EEPROM
byte sparkleBright = defaultBright;

#define P_defaultBright 100 // default blue  value for events mode 5 > 25 blink per second 
#define P_brigfhtAdd 12 // position in EEPROM
byte P_Bright = P_defaultBright;

#define EventsColDefault 0 // default blue  value for events mode 5 > 25 blink per second 
#define EventsColAdd 13 // position in EEPROM
byte EventsCol = EventsColDefault;

void sparkleTask();
Scheduler runner;
Task spark(300000, TASK_FOREVER, &sparkleTask); // task for sparkling every one hour

uint16_t Position = 0;
unsigned long Now = 0 ;

void setup()
{

   Serial.begin(115200) ;
  getConfig() ;
  FastLED.addLeds<WS2812, PIN1, GRB>(leds_1, NUM_LEDS1);
  FastLED.addLeds<WS2812, PIN2, GRB>(leds_2, NUM_LEDS2);
  LEDS.setBrightness(P_Bright);
 // for (int k =  0 ; k<10 ; k++) {Serial.println( "colotr " + colornames[k]) ; setAll(colors[k][0], colors[k][1], colors[k][2], 1, NUM_LEDS1); delay(2000); }
   byte randomColor = random(0,10) ;
  Serial.println("selected color " + colornames[randomColor]); 
   FadeInOut(colors[randomColor][0], colors[randomColor][1], colors[randomColor][2],  random(2000, 6000));
  runner.addTask(spark);
  spark.enable() ;
  runner.startNow();
  
 

}


void loop() {
  runner.execute();
  //RunningLights(255, 255 , 255 , 200 , 2000) ;
  LEDS.setBrightness(P_Bright);
  byte randomColor = random(0,10) ;
  if (primaryMode == 0 ){
    randomColor = EventsCol ; 
    Serial.println("events mode color " + colornames[EventsCol]); 
  }
  Serial.println("selected color " + colornames[randomColor]); 
  switch (random(0,5)) {
  case 0 :
    RunningLights(colors[randomColor][0], colors[randomColor][1], colors[randomColor][2],10, random(2000, 6000) );
    break ;
  case 1 : 
    FadeInOut(colors[randomColor][0], colors[randomColor][1], colors[randomColor][2],  random(2000, 6000));
    break ; 
  case 2 : 
    rainbowCycle( 10, random(2000, 6000) ) ;
    break ;
  case 3 : 
    Strobe( colors[randomColor][0], colors[randomColor][1], colors[randomColor][2], 3, 100, 500, random(2000, 6000));
    break ;
  case 4 : 
    TwinkleRandom(colors[randomColor][0], colors[randomColor][1], colors[randomColor][2],random(2000, 6000)) ; 
  break ; 
  }

}

void sparkleTask() {
  Now = millis();
  Serial.println(Now / 1000);
  Serial.println("spark for  1 min brightness " + String(sparkleBright)  ) ;
  LEDS.setBrightness(sparkleBright*25);
  int delayDuration = (-5*sparklSpeed) +505 ; 
  setAll(0, 0, 0, 1, NUM_LEDS1) ;
  Serial.println("Spatkle delay " + String(delayDuration) + " speed " + String(sparklSpeed)) ; 
  setAll(0, 0, 0, 2, NUM_LEDS2) ;
  while (millis() - Now < 60000) {
    //Entropy.Initialize();
    if (readCode()) {
      LEDS.setBrightness(sparkleBright*25);
      delayDuration = (-5*sparklSpeed) +505 ;
    }
    int Pixel =  random(NUM_LEDS2);
    setPixel(Pixel, 0xFF, 0xFF, 0xFF, 2);
    delay(delayDuration);
    setPixel(Pixel, 0, 0, 0, 2);
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

void setAll(byte red, byte green, byte blue, byte strip, int numleds ) {
  for (int i = 0; i < numleds; i++ ) {
    setPixel(i, red, green, blue, strip);
  }
  FastLED.show();
}


// configuration saved in EEPROM
void getConfig() { 
  // check if device is previously configured
  for (byte  i = 0  ; i<4 ; i++) {
    if(char(EEPROM.read(i)) != 77){
      Serial.println("device not configured inserting default values") ; 
      EEPROM.write(sparkledurationAdd,defaultSparkleDuration );
      EEPROM.write(ModeAdd,defaultPrimaryMode);
      EEPROM.write(RAdd, eventsR);
      EEPROM.write(GAdd,eventsG );
      EEPROM.write(BAdd, eventsB);
      EEPROM.write(SpeedAdd,defaultSparkeSpeed );
      EEPROM.write(brigfhtAdd,defaultBright );
      EEPROM.write(P_brigfhtAdd,P_defaultBright );
      EEPROM.write(EventsColAdd,EventsColDefault );
       for (byte  b = 0  ; i<4 ; i++) EEPROM.write(i,77);

      return ; 
    }
    Serial.println("device getting saved values ") ; 
    sparkleBright = EEPROM.read(brigfhtAdd)  ;
    Serial.println("sparkle brightness "  + String(sparkleBright)) ; 
    P_Bright = EEPROM.read(P_brigfhtAdd)  ;
    Serial.println("primary brightness "  + String(P_brigfhtAdd)) ; 
    sparkleDuration = EEPROM.read(sparkledurationAdd)  ;
    primaryMode = EEPROM.read(ModeAdd)  ;
    Serial.println("primary mode "  + String(primaryMode)) ; 
    eventsRed = EEPROM.read(RAdd)  ;
   
    eventsGreen = EEPROM.read(GAdd)  ;
    eventsBlue = EEPROM.read(BAdd)  ;
    sparklSpeed = EEPROM.read(SpeedAdd)  ;
     Serial.println("sparkle speed "  + String(sparklSpeed)) ; 
    EventsCol = EEPROM.read(EventsColAdd);
     Serial.println("events color "  + colornames[EventsCol]) ; 
  }
}

bool readCode() {
  String btdata = "";
 if(Serial.available()>0){
    Serial.println("getting configuration ") ; 
    delay(5);
    while(Serial.available()>0){
      char temp=Serial.read();
      btdata = btdata + temp;
    }
    Serial.println("got config "  + btdata) ; 

    // setting sparkling speed
    if (btdata.substring(0,2).equals("ss") && btdata.length() <= 5 && btdata.length() >= 3 ) {
      if (btdata.substring(1).toInt() >=0 && btdata.substring(2).toInt() <= 100) {
        Serial.println ("settign sparkling speed to " + btdata.substring(2)) ; 
        EEPROM.write(SpeedAdd, btdata.substring(2).toInt()) ; 
        sparklSpeed = btdata.substring(2).toInt();
        return 1 ;
      }
    }
    
    if (btdata.substring(0,2).equals("sb") && btdata.length() <= 5 && btdata.length() >= 3 ) {
      if (btdata.substring(1).toInt() >=0 && btdata.substring(2).toInt() <= 100) {
        Serial.println ("settign sparkling brightness to " + btdata.substring(2)) ; 
        EEPROM.write(brigfhtAdd, btdata.substring(2).toInt()) ; 
        sparkleBright = btdata.substring(2).toInt();
        return 1 ;
      }
    }

     if (btdata.substring(0,2).equals("pb") && btdata.length() <= 5 && btdata.length() >= 3 ) {
      if (btdata.substring(1).toInt() >=0 && btdata.substring(2).toInt() <= 100) {
        Serial.println ("settign primary system brightness to " + btdata.substring(2)) ; 
        EEPROM.write(P_brigfhtAdd, btdata.substring(2).toInt()) ; 
        P_Bright = btdata.substring(2).toInt();
        return 1 ;
      }
    }

    if (btdata.substring(0,2).equals("pm") && btdata.length() <= 5 && btdata.length() >= 3 ) {
      if (btdata.substring(1).toInt() >=0 && btdata.substring(2).toInt() <= 100) {
        if (btdata.substring(2,3).toInt() == 0) {
          Serial.println("Setting events mode") ; 
          EEPROM.write(ModeAdd,0 );
          primaryMode = 0 ;
        }
        else if (btdata.substring(2,3).toInt() == 1) {
          Serial.println("Setting Normal mode") ; 
          EEPROM.write(ModeAdd,1 );
          primaryMode = 1 ;
        }
          if (btdata.substring(3).toInt() >= 0 && btdata.substring(3).toInt() <= 10) {
            EEPROM.write(EventsColAdd,btdata.substring(3).toInt());
            EventsCol = btdata.substring(3).toInt(); 
            Serial.println("setting color to "  + colornames[EventsCol]);
          }
        }

      }
    }
 }
  



