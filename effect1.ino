void RunningLights(byte red, byte green, byte blue, int WaveDelay, int duration ) {
  Position=0;

  Now = millis() ; 
  Serial.println("running light " + String(Now/1000)) ; 
  while (millis()- Now < duration) {
  for(int j=0; j<NUM_LEDS1*2; j++)
      {   runner.execute();
          if (readCode() == 1) {
            LEDS.setBrightness(P_Bright);
            if (primaryMode == 0 ){
             red == colors[EventsCol][0] ; 
              blue == colors[EventsCol][2] ;
               green == colors[EventsCol][1] ;}
            }
          Position++; // = 0; //Position + Rate;
          for(int i=0; i<NUM_LEDS1; i++) {
            setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                       ((sin(i+Position) * 127 + 128)/255)*green,
                       ((sin(i+Position) * 127 + 128)/255)*blue, 1 );
          }
          delay(WaveDelay);
      }
  }
  Serial.println("running stop " + String(millis()/1000)) ; 
}
