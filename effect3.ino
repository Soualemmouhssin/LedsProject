void rainbowCycle(int SpeedDelay, int duration ) {
  byte *c;
  uint16_t i, j;
  Serial.println("rainbow");
  Now = millis() ; 
  while(millis() - Now <duration) {
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS1; i++) {
      runner.execute();
      c=Wheel(((i * 256 / NUM_LEDS1) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    delay(SpeedDelay);
  }
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }
  return c;
}
