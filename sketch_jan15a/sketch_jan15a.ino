const int LDR = A0;
uint8_t i = 0;

void setup()
{
  Serial.begin(19200);
}

void loop(){
  // Multiply with 10 for better noise filtering
  uint32_t output = analogRead(LDR) * 10;
  Serial.println(String(output));
  delay(10);     
}
