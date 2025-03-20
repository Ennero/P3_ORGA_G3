const int numParqueos = 4; // Cambia esto al número real de espacios de estacionamiento
const int sensoresParqueo[] = {2, 3, 4, 5}; // Pines digitales del Arduino conectados a los sensores
int estadoParqueo[numParqueos];
int estadoAnteriorParqueo[numParqueos];
const int clockPin = 6;   // Pin para el reloj del contador
const int direccionPin = 7; // Pin para controlar la dirección del contador

void setup() {
  for (int i = 0; i < numParqueos; i++) {
    pinMode(sensoresParqueo[i], INPUT);
    estadoParqueo[i] = digitalRead(sensoresParqueo[i]);
    estadoAnteriorParqueo[i] = estadoParqueo[i];
  }
  pinMode(clockPin, OUTPUT);
  pinMode(direccionPin, OUTPUT);
  digitalWrite(clockPin, LOW);
  digitalWrite(direccionPin, HIGH); // Inicializar dirección a ascendente (ejemplo)
}

void loop() {
  for (int i = 0; i < numParqueos; i++) {
    estadoParqueo[i] = digitalRead(sensoresParqueo[i]);

    // Detección de entrada (flanco de subida)
    if (estadoParqueo[i] == HIGH && estadoAnteriorParqueo[i] == LOW) {
      // Configurar dirección para ascendente (incrementar)
      digitalWrite(direccionPin, HIGH);
      // Generar pulso de reloj
      generarPulsoReloj();
    }

    // Detección de salida (flanco de bajada)
    if (estadoParqueo[i] == LOW && estadoAnteriorParqueo[i] == HIGH) {
      // Configurar dirección para descendente (decrementar)
      digitalWrite(direccionPin, LOW);
      // Generar pulso de reloj
      generarPulsoReloj();
    }

    estadoAnteriorParqueo[i] = estadoParqueo[i];
  }
  delay(50); // Pequeño delay para evitar lecturas múltiples rápidas
}

void generarPulsoReloj() {
  digitalWrite(clockPin, HIGH);
  delayMicroseconds(10); // Pulso corto
  digitalWrite(clockPin, LOW);
}
