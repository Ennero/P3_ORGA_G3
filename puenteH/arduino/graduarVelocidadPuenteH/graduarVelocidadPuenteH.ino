int entrada1 = 9;
int entrada2 = 10;
int velocidad = 100;

void setup() {
  pinMode(entrada1, OUTPUT);
  pinMode(entrada2, OUTPUT);
}

void loop() {
  analogWrite(entrada1, 100);
  analogWrite(entrada2, 0);
  delay(3000);

  analogWrite(entrada1, 0);
  analogWrite(entrada2, 100);
  delay(3000);
}
