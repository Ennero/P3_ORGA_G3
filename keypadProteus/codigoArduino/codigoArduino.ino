#include <Keypad.h>
//Para puente h
int entrada1 = 10;
int entrada2 = 11;
bool flag = true;

//Para teclado matricial
const byte rows = 1;
const byte cols = 4;
String text = String("");
char hexaKeyers[rows][cols] = {
  {'1', '2', '3', '4'}
};
byte row_Pins[rows] = {5};
byte col_Pins[cols] = {6, 7, 8, 9};

Keypad cust_keypad = Keypad(makeKeymap(hexaKeyers), row_Pins, col_Pins, rows, cols);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(entrada1, OUTPUT);
  pinMode(entrada2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(flag){
    analogWrite(entrada1, 100);
    analogWrite(entrada2, 0);
    delay(400);
    analogWrite(entrada1, 0);
    analogWrite(entrada2, 0);
    flag = false;
  }
  char cust_key = cust_keypad.getKey();
  if(cust_key){
    text.concat(cust_key);
  }
  if(text.length() == 3){
    if(text != "123"){
      Serial.println("Error");
      analogWrite(entrada1, 0);
      analogWrite(entrada2, 100);
      delay(300);
      analogWrite(entrada1, 0);
      analogWrite(entrada2, 0);
    }else{
      Serial.println("Pase");
    }
    text = "";
  }
}