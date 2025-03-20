#include <Keypad.h>
//Para puente h
int entrada1 = 5;
int entrada2 = 3;
bool flag = true;

//Para teclado matricial
const byte rows = 4;
const byte cols = 3;
String text = String("");
char hexaKeyers[rows][cols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte row_Pins[rows] = {9, 8, 7, 6};
byte col_Pins[cols] = {12, 11, 10};

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
    delay(2000);
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
      delay(2000);
      analogWrite(entrada1, 0);
      analogWrite(entrada2, 0);
    }else{
      Serial.println("Pase");
    }
    text = "";
  }
}