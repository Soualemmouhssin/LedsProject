void FadeInOut(byte red, byte green, byte blue, int duration){
  float r, g, b;
  Serial.println("FadeInOut");
  Now = millis() ; 
  while(millis() - Now < duration) {    
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b,1,NUM_LEDS1);
  }
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b,1,NUM_LEDS1);
  }
  }
}


