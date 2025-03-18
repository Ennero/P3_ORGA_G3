#include <NewPing.h>

const int TRIG_PIN = 4;   // Pin de disparo (Trigger)
const int ECHO_PIN = 5;   // Pin de eco (Echo)
const int MAX_DIST = 200; // Distancia máxima en cm
const int LED = 12;       // Pin del LED

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DIST);

void setup() {
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int distancia = sonar.ping_cm(); // Mide la distancia en cm

    if (distancia > 0 && distancia < 10) {  // Si un objeto está a menos de 10 cm
        digitalWrite(LED, HIGH);  // Enciende el LED
        Serial.print("Objeto detectado a ");
        Serial.print(distancia);
        Serial.println(" cm");
    } else {
        digitalWrite(LED, LOW);  // Apaga el LED
        Serial.println("No hay objeto cercano");
    }

    delay(100);
}
