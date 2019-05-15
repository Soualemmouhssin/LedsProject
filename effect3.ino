void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay ,int duration){
Now = millis(); 
Serial.println("cycle bounce") ;
while (millis()- Now < duration) {
  for(int i = 0; i < NUM_LEDS1-EyeSize-2; i++) {
    setAll(0,0,0,NUM_LEDS1);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    strip.show();
    delay(SpeedDelay);
    if(millis()- Now > duration)  return ; 
  }

  delay(ReturnDelay);

  for(int i = NUM_LEDS1-EyeSize-2; i > 0; i--) {
    setAll(0,0,0,NUM_LEDS1);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    strip.show();
    delay(SpeedDelay);
    if(millis()- Now > duration)  return ;
  }
  
  delay(ReturnDelay);
}
}

