const int LDR = A0;
uint8_t i = 0;

void setup(){
  Serial.begin(9600);
}

void loop(){
  uint32_t output = analogRead(LDR);
  Serial.println(String(output));
  delay(100);     
}
