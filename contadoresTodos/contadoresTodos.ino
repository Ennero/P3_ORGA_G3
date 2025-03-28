  const int numParqueos1 = 3;
  int lectura1[numParqueos1];
  const int sensoresParqueo1[] = {A9, A10, A11}; // Pines digitales del Arduino conectados a los sensores
  int estadoParqueo1[numParqueos1];
  int estadoAnteriorParqueo1[numParqueos1];
  const int clockPin1 = 51;   // Pin para el reloj del contador
  const int direccionPin1 = 53; // Pin para controlar la dirección del contador
  
  const int numParqueos2 = 4;
  int lectura2[numParqueos2];
  const int sensoresParqueo2[] = {A5, A6, A7, A8};
  int estadoParqueo2[numParqueos2];
  int estadoAnteriorParqueo2[numParqueos2];
  const int clockPin2 = 47;
  const int direccionPin2 = 49;

  const int numParqueos3 = 5;
  int lectura3[numParqueos3];
  const int sensoresParqueo3[] = {A0, A1, A2, A3, A4};
  int estadoParqueo3[numParqueos3];
  int estadoAnteriorParqueo3[numParqueos3];
  const int clockPin3 = 43;
  const int direccionPin3 = 45;

  const int salidaTodosLlenos = 39;
  const int UMBRAL = 75;
  
  void setup() {
    Serial.begin(9600);
    pinMode(salidaTodosLlenos, OUTPUT);
    digitalWrite(salidaTodosLlenos, LOW);
    
    for (int i = 0; i < numParqueos1; i++) {
      pinMode(sensoresParqueo1[i], INPUT);
      digitalWrite(sensoresParqueo1[i], LOW);
    }

    pinMode(direccionPin1, OUTPUT);
    pinMode(clockPin1, OUTPUT);
    digitalWrite(direccionPin1, HIGH);
    digitalWrite(clockPin1, LOW);
    
    for (int i = 0; i < numParqueos2; i++) {
      pinMode(sensoresParqueo2[i], INPUT);
      digitalWrite(sensoresParqueo2[i], LOW);
    }
    
    pinMode(direccionPin2, OUTPUT);
    pinMode(clockPin2, OUTPUT);
    digitalWrite(direccionPin2, HIGH);
    digitalWrite(clockPin2, LOW);

    for (int i = 0; i < numParqueos3; i++) {
      pinMode(sensoresParqueo3[i], INPUT);
      digitalWrite(sensoresParqueo3[i], LOW);
    }
    
    pinMode(direccionPin3, OUTPUT);
    pinMode(clockPin3, OUTPUT);
    digitalWrite(direccionPin3, HIGH);
    digitalWrite(clockPin3, LOW);
  }
  
  void loop() {
    for (int i = 0; i < numParqueos1; i++) {

      lectura1[i] = analogRead(sensoresParqueo1[i]);

      if(lectura1[i] > UMBRAL) {
        estadoParqueo1[i] = LOW;
      } else {
        estadoParqueo1[i] = HIGH;
      }
  
      if (estadoParqueo1[i] == HIGH && estadoAnteriorParqueo1[i] == LOW) {
        Serial.print("Se ocupo el parqueo ");
        Serial.println(String(i));
        digitalWrite(direccionPin1, HIGH);
        generarPulsoReloj1();
      }
  
      if (estadoParqueo1[i] == LOW && estadoAnteriorParqueo1[i] == HIGH) {
        Serial.print("Se desocupo el parqueo ");
        Serial.println(String(i));
        digitalWrite(direccionPin1, LOW);
        generarPulsoReloj1();
      }
  
      estadoAnteriorParqueo1[i] = estadoParqueo1[i];
    }

    for (int i = 0; i < numParqueos2; i++) {

      lectura2[i] = analogRead(sensoresParqueo2 [i]);

      if(lectura2[i] > UMBRAL) {
        estadoParqueo2[i] = LOW;
      } else {
        estadoParqueo2[i] = HIGH;
      }
  
      if (estadoParqueo2[i] == HIGH && estadoAnteriorParqueo2[i] == LOW) {
        Serial.print("Se ocupo el parqueo ");
        Serial.println(String(i));
        digitalWrite(direccionPin2, HIGH);
        generarPulsoReloj2();
      }
  
      if (estadoParqueo2[i] == LOW && estadoAnteriorParqueo2[i] == HIGH) {
        Serial.print("Se desocupo el parqueo ");
        Serial.println(String(i));
        digitalWrite(direccionPin2, LOW);
        generarPulsoReloj2();
      }
  
      estadoAnteriorParqueo2[i] = estadoParqueo2[i];
    }


    for (int i = 0; i < numParqueos3; i++) {

      lectura3[i] = analogRead(sensoresParqueo3[i]);

      if(lectura3[i] > UMBRAL) {
        estadoParqueo3[i] = LOW;
      } else {
        estadoParqueo3[i] = HIGH;
      }
  
      if (estadoParqueo3[i] == HIGH && estadoAnteriorParqueo3[i] == LOW) {
        Serial.print("Se ocupo el parqueo ");
        Serial.println(String(i));
        digitalWrite(direccionPin3, HIGH);
        generarPulsoReloj3();
      }
  
      if (estadoParqueo3[i] == LOW && estadoAnteriorParqueo3[i] == HIGH) {
        Serial.print("Se desocupo el parqueo ");
        Serial.println(String(i));
        digitalWrite(direccionPin3, LOW);
        generarPulsoReloj3();
      }
  
      estadoAnteriorParqueo3[i] = estadoParqueo3[i];
    }

    if (todosLosParqueosLlenos()) {
        digitalWrite(salidaTodosLlenos, HIGH);
        Serial.println("TODOS LOS PARQUEOS ESTÁN LLENOS");
    } else {
        digitalWrite(salidaTodosLlenos, LOW);
    }
    
    delay(50);
  }
  
  void generarPulsoReloj1() {
    digitalWrite(clockPin1, HIGH);
    delay(50); // Pulso corto
    digitalWrite(clockPin1, LOW);
  }

  void generarPulsoReloj2() {
    digitalWrite(clockPin2, HIGH);
    delay(50); // Pulso corto
    digitalWrite(clockPin2, LOW);
  }

  void generarPulsoReloj3() {
    digitalWrite(clockPin3, HIGH);
    delay(50); // Pulso corto
    digitalWrite(clockPin3, LOW);
  }

  bool todosLosParqueosLlenos() {
    for (int i = 0; i < numParqueos1; i++) {
        if (estadoParqueo1[i] == HIGH) return false;
    }
    for (int i = 0; i < numParqueos2; i++) {
        if (estadoParqueo2[i] == HIGH) return false;
    }
    for (int i = 0; i < numParqueos3; i++) {
        if (estadoParqueo3[i] == HIGH) return false;
    }
    return true; // Si todos están en LOW, significa que están ocupados
  }
