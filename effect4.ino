void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne, int duration) {
  Now = millis() ; 
  Serial.println("twinkle");
  while(millis() - Now < duration) { 
  runner.execute();
  setAll(0,0,0, 1, NUM_LEDS1);
  for (int i=0; i<Count; i++) {
      runner.execute();

     setPixel(random(NUM_LEDS1),random(0,255),random(0,255),random(0,255), 1 );
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0, 1 ,NUM_LEDS1); 
     }
   }
  
  delay(SpeedDelay);
  }
}
