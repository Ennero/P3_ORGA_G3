//importaciones
#include <Keypad.h>

//inicializar variables para teclado matricial
const byte rows = 1;
const byte cols = 4;

String text = String("");
char hexaKeyers[rows][cols] = {
  {'1', '2', '3'}
};
byte row_Pins[rows] = {8};
byte col_Pins[cols] = {7, 6, 5};                                                                                                                                                                                                                                                                                                                              

Keypad cust_keypad = Keypad(makeKeymap(hexaKeyers), row_Pins, col_Pins, rows, cols);

//Inicilizar variables puente H
int entrada1 = 9;
int entrada2 = 10;
bool flagInicial = true;
bool flagCerrado = false;

//Inicializar variables alarma
int salidaBocina = 11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(entrada1, OUTPUT);
  pinMode(entrada2, OUTPUT);
  pinMode(salidaBocina, OUTPUT);
}

void loop() {
  if(flagInicial){
    analogWrite(entrada1, 100);
    analogWrite(entrada2, 0);
    delay(500);
    analogWrite(entrada1, 0);
    analogWrite(entrada2, 0);
    flagInicial = false;
  }
  // put your main code here, to run repeatedly:
  char cust_key = cust_keypad.getKey();
  if(cust_key){
    Serial.println(cust_key);
    text.concat(cust_key);
  }
  if(text.length() == 3){
    Serial.println(text);
    if(flagCerrado){
      if(text == "123"){
        analogWrite(entrada1, 100);
        analogWrite(entrada2, 0);
        delay(500);
        analogWrite(entrada1, 0);
        analogWrite(entrada2, 0);
        digitalWrite(salidaBocina, LOW);
        flagCerrado = false;
      }
    }else{
      if(!text.equals("123")){
        analogWrite(entrada1, 0);
        analogWrite(entrada2, 70);
        delay(170);
        analogWrite(entrada1, 0);
        analogWrite(entrada2, 0);
        digitalWrite(salidaBocina, HIGH);
        flagCerrado = true;
      }
    }
    text = "";
  }
}
