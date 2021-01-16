const int LDR = A0;
uint8_t i = 0;

void setup()
{
  Serial.begin(19200);
}

void loop(){
  // Multiply with 10 for better noise filtering
  uint32_t output = analogRead(LDR);

  // Encode string to remove noise
  // Not the best method, could use some coding theory for this purpose but this works fine enough.
  String encoded = "f" + String(output) + "e";
  Serial.println(encoded);
  delay(10);     
}
