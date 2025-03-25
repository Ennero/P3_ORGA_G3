#include <Servo.h>

// -------------------- Configuración del Primer Servo y Sensor --------------------
Servo myServo;
const int servoPin = 9;
const int trigPin = 12;
const int echoPin = 13;
const int proximityThreshold = 5;

// -------------------- Configuración del Segundo Servo y Sensor --------------------
Servo myServo2;
const int servoPin2 = 5;
const int trigPin2 = 7;
const int echoPin2 = 11;
const int proximityThreshold2 = 5;

void setup() {
    Serial.begin(9600);

    // Inicialización del primer servo y sensor
    myServo.attach(servoPin);
    myServo.write(0);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Inicialización del segundo servo y sensor
    myServo2.attach(servoPin2);
    myServo2.write(0);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
}

// -------------------- Funciones para medir distancia --------------------
int medirDistancia(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);
    if (duration == 0) return 999;

    return duration * 0.034 / 2;
}

// -------------------- Funciones para controlar las barreras --------------------
void controlarBarrera(Servo &servo, int distancia, int umbral) {
    if (distancia < umbral) {
        Serial.println("Vehículo detectado! Abriendo barrera...");
        servo.write(90);
        delay(5000);
        servo.write(0);
        Serial.println("Cerrando barrera...");
    }
}

void loop() {
    // -------------------- Lógica para el Primer Servo y Sensor --------------------
    int distancia1 = medirDistancia(trigPin, echoPin);
    Serial.print("Distancia Sensor 1: ");
    Serial.print(distancia1);
    Serial.println(" cm");
    controlarBarrera(myServo, distancia1, proximityThreshold);

    delay(100);  // Pequeña pausa para evitar interferencias entre sensores

    // -------------------- Lógica para el Segundo Servo y Sensor --------------------
    int distancia2 = medirDistancia(trigPin2, echoPin2);
    Serial.print("Distancia Sensor 2: ");
    Serial.print(distancia2);
    Serial.println(" cm");
    controlarBarrera(myServo2, distancia2, proximityThreshold2);

    delay(500);  // Estabilizar mediciones
}

