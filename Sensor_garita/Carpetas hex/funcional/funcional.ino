#include <Servo.h>

Servo myServo;  
const int servoPin = 9;  
const int trigPin = 12;  
const int echoPin = 13;
const int proximityThreshold = 20;  // Aumenté el umbral a 20 cm para mejor detección

void setup() {
  myServo.attach(servoPin);
  myServo.write(0);  // Asegurar que inicie en 0 grados
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  long duration;
  int distance;

  // Envía un pulso ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);  // Pequeña pausa para estabilizar
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lee el tiempo de respuesta del pulso
  duration = pulseIn(echoPin, HIGH, 30000); // Espera máximo 30ms (evita bloqueos)
  
  // Si el sensor no detecta nada, devuelve una distancia alta (como 999 cm)
  if (duration == 0) {
    distance = 999; 
  } else {
    // Calcula la distancia en cm
    distance = duration * 0.034 / 2;
  }

  // Imprime la distancia en el monitor serial
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Si la distancia es menor que el umbral, activa el servomotor
  if (distance < proximityThreshold) {
    Serial.println("Vehículo detectado! Abriendo barrera...");
    myServo.write(90);  // Mueve el servomotor a 90 grados
    delay(5000);  // Espera 5 segundos (puedes cambiarlo a 20s si quieres)
    myServo.write(0);  // Mueve el servomotor de vuelta a 0 grados
    Serial.println("Cerrando barrera...");
  }

  delay(500);  // Pequeño delay para estabilizar lecturas del sensor
}
