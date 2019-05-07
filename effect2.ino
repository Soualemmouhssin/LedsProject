void FadeInOut(byte red, byte green, byte blue, int duration){
  uint8_t r,g,b ; 

  Serial.println("FadeInOut");
   Serial.println(" red  " + String(red) + " blue  " + String(blue));
  Now = millis() ; 
  while(millis() - Now < duration) { 
    runner.execute();
    if (readCode() == 1) {
            strip.setBrightness(P_Bright);
            if (primaryMode == 0 ){
             red == colors[EventsCol][0] ; 
              blue == colors[EventsCol][2] ;
               green == colors[EventsCol][1] ;}
            }   
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/255.0)*red;
    g = (k/255.0)*green;
    b = (k/255.0)*blue;
    setAll(r,g,b,NUM_LEDS1);
  }
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/255.0)*red;
    g = (k/255.0)*green;
    b = (k/255.0)*blue;
    setAll(r,g,b,NUM_LEDS1);
  }
  Serial.println("new cycle");
  }
}



