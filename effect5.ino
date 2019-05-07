void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause,int duration){
  Now = millis() ; 
  Serial.println("strobe") ;
  while(millis() - Now < duration) {
  runner.execute();
  if (readCode() == 1) {
            strip.setBrightness(P_Bright);
            if (primaryMode == 0 ){
             red == colors[EventsCol][0] ; 
              blue == colors[EventsCol][2] ;
               green == colors[EventsCol][1] ;}
            }   
  for(int j = 0; j < StrobeCount; j++) {
    setAll(red,green,blue,NUM_LEDS1);
    delay(FlashDelay);
    setAll(0,0,0, NUM_LEDS1);
    delay(FlashDelay);
  }
 delay(EndPause);
}
}
