const int LDR = A0;

void setup()
{
  Serial.begin(9600);
}

void loop(){
  uint32_t output = analogRead(LDR);
  byte * buffer = (byte*)&output;
  Serial.write(buffer, 4);
  delay(1000);
}
