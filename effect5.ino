void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause,int duration){
  Now = millis() ; 
  Serial.println("strobe") ;
  while(millis() - Now < duration) {
  runner.execute();
  for(int j = 0; j < StrobeCount; j++) {
    setAll(red,green,blue, 1, NUM_LEDS1);
    delay(FlashDelay);
    setAll(0,0,0, 1, NUM_LEDS1);
    delay(FlashDelay);
  }
 delay(EndPause);
}
}
