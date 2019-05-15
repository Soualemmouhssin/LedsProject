#define analogPIN 33  

void setup() {
   Serial.begin(115200);
}

void loop()
{
   int x = analogRead( analogPIN );
   Serial.println( x );
   delay(100);
}
