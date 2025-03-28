<div align="center" style="font-family: 'Times New Roman', Times, serif;">

# UNIVERSIDAD DE SAN CARLOS DE GUATEMALA  
## FACULTAD DE INGENIERÍA  
### ORGANIZACIÓN COMPUTACIONAL  

**CATEDRÁTICO:** ING. OTTO RENE ESCOBAR LEIVA  
**TUTOR ACADÉMICO:** JUAN JOSUE ZULETA BEB  


<div style="position: relative; display: inline-block;">
    <img src="img y otros/logo.png" alt="Imagen de fondo" width="500">
    <div style="position: absolute; top: 20px; left: 50px; color: white; font-size: 24px; font-weight: bold;">
        - 
    </div>
</div>








##              Integrantes
 **Enner Esaí Mendizabal Castro** - 202302220  
 **Esteban Sánchez Túchez** - 202300769  
 **Juan José Sandoval Ruiz** - 202300710  
 **Brandon Antonio Marroquin Pérez** - 202300813  
 **David Estuardo Barrios Ramírez** - 202300670  

**GUATEMALA, 22 DE MARZO DEL 2025**  
</div>

<div style="font-family: 'Times New Roman', Times, serif;">

# ÍNDICE  

1. [INTRODUCCIÓN](#introducción)  
2. [OBJETIVOS](#objetivos)  
   - Objetivo general  
   - Objetivos específicos  
3. [CONTENIDO](#contenido)  
4. [DIAGRAMAS DE DISEÑO DEL CIRCUITO](#diagramas-de-diseño-del-circuito)  
   - DIAGRAMA DEL PUENTEH
   - DIAGRAMA SERVOMOTORES
   - DIAGRAMA DE LA CONFIGURACION DEL TECLADO
   - DIAGRAMA LOS CONTADORES 
5. [EQUIPO UTILIZADO](#equipo-utilizado)  
6. [PRESUPUESTO](#presupuesto)  
7. [APORTE INDIVIDUAL DE CADA INTEGRANTE](#aporte-individual-de-cada-integrante)  
   - Aporte de Enner Mendizabal - 202302220  
   - Aporte de Esteban Sánchez Túchez  
   - Aporte de Juan José Sandoval Ruiz  
   - Aporte de David Estuardo Barrios Ramírez  
   - Aporte de Brandon Antonio Marroquin Pérez  
8. [CONCLUSIONES](#conclusiones)  
9. [ANEXOS](#anexos)  
   - [APORTE DE TODOS LOS INTEGRANTES DEL GRUPO](#aporte-de-todos-los-integrantes-del-grupo)  
   - [DIAGRAMA DEL CIRCUITO IMPRESO](#diagrama-del-circuito-impreso)  
   - [FOTOGRAFÍA DE LOS CIRCUITOS FÍSICOS](#fotografía-de-los-circuitos-físicos)  
9. [Videos del funcionamiento de manera separada](#videos-del-funcionamiento-de-manera-separada)  

## INTRODUCCIÓN  

En el presente informe se documenta el desarrollo e implementación de un prototipo funcional de una torre de parqueo automatizada, basado en circuitos combinacionales y secuenciales. Este proyecto se realizó con la ayuda de la lógica combinacional y secuencial, y la integración de componentes electrónicos para la simulación y construcción de un sistema de control eficiente.  

El sistema diseñado consta de tres niveles de estacionamiento, cada uno con una cantidad específica de espacios disponibles, los cuales son monitoreados mediante sensores de proximidad y controlados mediante contadores ascendentes y descendentes implementados con flip-flops. Además, se integraron garitas automáticas para la entrada y salida de vehículos, utilizando servomotores para la manipulación de barreras, así como un sistema de validación de tickets mediante un teclado numérico.  

Para mejorar la seguridad del sistema, se diseñó un mecanismo de restricción que impide el acceso cuando los espacios están llenos y activa una alarma de robo en caso de intentos de salida no autorizados. Asimismo, se implementó una puerta automatizada controlada con un puente H, la cual se activa en situaciones específicas, como intentos de robo o cuando el parqueo se encuentra en su máxima capacidad.  

La simulación de este proyecto se llevó a cabo en Proteus, asegurando que la lógica digital funcione correctamente antes de la implementación física. Se respetaron los requisitos de la práctica, garantizando la funcionalidad del sistema sin el uso de Arduino en la gestión de los contadores de parqueos ocupados y vacíos, lo cual fue manejado exclusivamente con circuitos lógicos.  




## OBJETIVOS  

## Objetivo General  
Desarrollar e implementar un sistema de parqueo automatizado basado en circuitos combinacionales y secuenciales, utilizando sensores, flip-flops y compuertas lógicas para el control de acceso, conteo de vehículos y medidas de seguridad, garantizando una operación eficiente y segura.  

## Objetivos Específicos  
1. Diseñar y simular en Proteus un sistema digital de control de parqueo que integre lógica combinacional y secuencial para la gestión de espacios disponibles.  
2. Implementar un mecanismo de seguridad que impida accesos no autorizados, mediante un sistema de validación de tickets y una alarma de robo en caso de intentos de salida no autorizados.  
3. Construir físicamente el sistema respetando las restricciones de hardware, asegurando su correcto funcionamiento con la menor cantidad de dispositivos posibles.  



## CONTENIDO  

### Código de Arduino para la Configuración del Teclado

```c
#include <Keypad.h>

// Inicializar variables para teclado matricial
const byte rows = 1;
const byte cols = 4;

String text = String("");
char hexaKeyers[rows][cols] = {
  {'1', '2', '3'}
};
byte row_Pins[rows] = {8};
byte col_Pins[cols] = {7, 6, 5};

Keypad cust_keypad = Keypad(makeKeymap(hexaKeyers), row_Pins, col_Pins, rows, cols);

// Inicializar variables puente H
int entrada1 = 9;
int entrada2 = 10;
bool flagInicial = true;
bool flagCerrado = false;

// Inicializar variables alarma
int salidaBocina = 11;

void setup() {
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
```


-**Codigo de arduino para la configuracion del pueteH**

```c
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
```


- **Codigo de arduino para la configuracion del sensor ultrasonico**
```c
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
```

- **Codigo de arduino para la configuracion del contador de 3**

```c
const int numParqueos = 3; // Cambia esto al número real de espacios de estacionamiento
const int sensoresParqueo[] = {1, 2, 3}; // Pines digitales del Arduino conectados a los sensores
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
```
- **Codigo de arduino para la configuracion del contador de 4**
```c
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

- **Codigo de arduino para la configuracion del contador de 5**

const int numParqueos = 5; // Cambia esto al número real de espacios de estacionamiento
const int sensoresParqueo[] = {1, 2, 3, 4, 5}; // Pines digitales del Arduino conectados a los sensores
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
```
---

## DIAGRAMAS DE DISEÑO DEL CIRCUITO  

- **DIAGRAMA DEL PUENTEH**

![alt text](/img%20y%20otros/puenteH.png)

- **DIAGRAMA SERVOMOTORES**

![alt text](/img%20y%20otros/SERMOTORES.png)

- **DIAGRAMA DE LA CONFIGURACION DEL TECLADO**

![alt text](/img%20y%20otros/TECLADO.png)

- **DIAGRAMA LOS CONTADORES**
    - **CONTADOR DE 4**

![alt text](/img%20y%20otros/4.png)

   - **CONTADOR DE 5**

![alt text](/img%20y%20otros/5.png)

   - **CONTADOR DE 3**

![alt text](/img%20y%20otros/3.png)




## Equipo Utilizado

El equipo utilizado para la realización del proyecto, tanto adquirido como proporcionado por los miembros del equipo, incluye:

- **Cautín de 60 watts**
- **Taladro con broca de 1/32**
- **Compuertas lógicas de la serie 74**
  - 74LS08
  - 74LS32
  - 74LS04
- **Transistores:** 2N2222A
- **Resistencias varias**
- **Luces LED color rojo**
- **Dip Switch**
- **Borneras de 2 y 3 terminales**
- **Estaño**
- **Esponja para limpiar estaño**
- **Arduino UNO**
- **Cable para protoboard**
- **Protoboard**
- **Placas de fibra de vidrio**
- **Duroport**
- **Carritos de juguete**
- **Sensor de ultrasonico**
- **Fotorresistencias LDR**
- **Ttermocogible**
- **Motor de 1-6 voltios**
- **Teclado 3x3**
- **Cables Dupont**
- **FLIB-FLOP**
- **Arduino Uno**
- **Arduino Mega**
- **Decoders**
- **Display 7 segmentos**

## PRESUPUESTO  


| Fecha       | Presupuesto                        | Q       |
|------------|------------------------------------|--------|
| <span class="th">11/03/2025</span> | PUNTA DE CAUTIN                  | Q50.00  |
|            | 2 BROCAS                           | Q18.00  |
|            | TRASTE PARA GUARDAR COSAS         | Q30.00  |
|            | <span class="subtotal">subtotal</span>                        | <span class="subtotal">Q98.00</span>  |
| <span class="fa">13/03/2025</span> | SENSOR ULTRASONICO               | Q27.00  |
|            | SENSOR DE OBSTACULOS INFRARROJOS   | Q18.00  |
|            | MOTOR DE 1-6 VOLTIOS               | Q15.00  |
|            | <span class="subtotal">subtotal</span>                        | <span class="subtotal">Q60.00</span>  |
| <span class="feha">14/03/2025</span> | 9 FOTORESISTENCIA LDR            | Q33.70  |
|            | 2 BROCAS                           | Q19.00  |
|            | ACIDO, FOTORESISTENCIA Y OTROS    | Q21.00  |
|            | 5 METROS DE ESTAÑO                | Q12.50  |
|            | <span class="subtotal">subtotal</span>                        | <span class="subtotal">Q86.20</span>  |
| <span class="feha">17/03/2025</span> | 3M DE ALAMBRE ROJO PARA PROTOBOARD | Q9.00   |
|            | 1 FOTORESISTENCIAS                 | Q3.75   |
|            | 1M TERMOCOLGIBLE                   | Q3.50   |
|            | 10 RESISTENCIAS 330                | Q5.00   |
|            | 1M TERMOCOLGIBLE                   | Q2.05   |
|            | 5M DE ALAMBRE NEGRO                | Q18.00  |
|            | <span class="subtotal">subtotal</span>                        | <span class="subtotal">Q38.75</span>  |
| <span class="fcha">20/03/2025</span> | 1 Teclado                        | Q15.00  |
|            | 4 metros de cable                  | Q8.00   |
|            | 6 CABLES DUPONT 10CM               | Q3.00   |
|            | <span class="subtotal">subtotal</span>                        | <span class="subtotal">Q26.00</span>  |
| <span class="echa">22/03/2025</span> | 2 ACETONA                        | Q12.00  |
|            | 2 ENCENDEDORES                     | Q4.00   |
|            | 2 FLIP-FLOP                        | Q20.00  |
|            | 3 DECODERS                         | Q45.00  |
|            | <span class="subtotal">subtotal</span>                        | <span class="subtotal">Q81.00</span>  |
| <span class="feha">24/03/2025</span> | SENSOR ULTRASONICO               | Q24.00  |
|            | 2 METROS DE CABLE                  | Q4.00   |
|            | RESISTENCIAS VARIOS                | Q5.00   |
|            | 2 FLIP-FLOP-K                      | Q20.00  |
|            | <span class="subtotal">subtotal</span>                        | <span class="subtotal">Q53.00</span>  |
| <span class="fcha">25/03/2025</span> | 10 M DE ALAMBRE ROJO             | Q12.00  |
|            | 1 FLIP FLOP                        | Q12.00  |
|            | 4 TORNILLOS                        | Q6.00   |
|            | 4 TUERCAS                          | Q2.00   |
|            | 20 CABLES DUPONT                   | Q15.00  |
|            | 5 CABLES DUPONT                    | Q3.70   |
|            | <span class="subtotal">subtotal</span>                        | <span class="subtotal">Q58.70</span>  |
| <span class="feha">26/03/2025</span> | 46 CABLES DUPONT                 | Q52.50  |
|            | BOMBILLA (CAMBIA DE COLOR)         | Q32.50  |
|            | <span class="subtotal">subtotal</span>                        | <span class="subtotal">Q84.50</span>  |
| <span class="feha">27/03/2025</span> | MATERIAL PARA DECORAR            | Q26.25  |
|            | 3 BARRITAS DE SILICON              | Q3.00   |
|            | CHICHARRONES Y TORTILLAS           | Q10.00  |
|            | <span class="subtotal">subtotal</span>                        | <span class="subtotal">Q39.25</span>  |
|            | <span class="total">TOTAL ABSOLUTO</span>                 | <span class="total">Q625.40</span>  |


---

## APORTE INDIVIDUAL DE CADA INTEGRANTE  

# Aportaciones del Proyecto

## Enner Mendizabal - 202302220  
Como coordinador del grupo, proporcionó los materiales necesarios para la maqueta y estableció una base sólida para su construcción. Además, contribuyó activamente en la implementación y distribución de los estacionamientos en los tres niveles de la maqueta, asegurando una estructura funcional y organizada. También brindó apoyo logístico en la planificación general del proyecto, ademas de lograr hacer un contador funcional.

- ## Esteban Sánchez Túchez  
Diseñó y programó el contador digital en Proteus, asegurando su correcto funcionamiento tanto en simulación como en su versión física. Además, desarrolló el código en Arduino para los contadores y propuso ideas innovadoras para mejorar otras secciones del proyecto. También desempeñó un papel clave en guiar a los demas en la implementacion de los demas contadores, garantizando su correcto funcionamiento mediante pruebas y ajustes, ademas ayudo en parte de la decoracion de la misma.

- ## Juan José Sandoval Ruiz  
Se encargó de la creación del puente H, tanto en su versión física como en su impresión, asegurando su correcto diseño y operación. Asimismo, diseñó y construyó el teclado en Proteus y en su versión física, optimizando su funcionalidad y conexión con otros componentes. También desarrolló el código en Arduino para el correcto funcionamiento del teclado y el puente H, asegurando una integración eficiente en el sistema general del proyecto, aporto en la posicion de las luces para cada nivel de estacionmiento.

- ## David Estuardo Barrios Ramírez  
Participó activamente en la soldadura del puente H, asegurando conexiones eléctricas firmes y funcionales. Además, colaboró en la creación de los sensores de los tres niveles de la maqueta, garantizando su correcta instalación y calibración. También brindó apoyo en la construcción estructural de la maqueta y contribuyó en el desarrollo del contador, optimizando su precisión y respuesta dentro del sistema.

- ## Brandon Antonio Marroquín Pérez  
Administró el presupuesto del grupo, asegurando una correcta distribución y asignación de los recursos necesarios para el desarrollo del proyecto. Fue responsable de la elaboración del informe del grupo, documentando de manera detallada cada etapa del proceso. Además, colaboró activamente en la decoración de la maqueta para mejorar su presentación. También asumió la responsabilidad de todo el proceso relacionado con las placas, desde el planchado y la inmersión en ácido hasta el pulido y acabado final, garantizando precisión, calidad y estética en cada detalle del proyecto.



## CONCLUSIONES  
El diseño y simulación del sistema de control de parqueo en Proteus utilizando circuitos combinacionales y secuenciales ha sido eficaz, demostrando la capacidad del sistema para gestionar de manera adecuada los espacios disponibles. La integración de sensores y flip-flops ha permitido implementar un sistema funcional que sigue las reglas de ocupación y liberación de espacios con precisión.

Se ha implementado un mecanismo de seguridad que garantiza la protección contra accesos no autorizados. El sistema de validación de tickets, junto con la alarma de robo en caso de intentos de salida no permitidos, asegura una operación segura del parqueo, evitando manipulaciones no deseadas y protegiendo el sistema contra robos.

La construcción del sistema físico ha respetado las restricciones de hardware, utilizando el número mínimo de dispositivos necesarios sin comprometer la funcionalidad. El sistema se ha ensamblado de manera que opera correctamente bajo condiciones reales, manteniendo un buen desempeño en la gestión de parqueo y en el control de seguridad. 


## ANEXOS  


## APORTE DE TODOS LOS INTEGRANTES DEL GRUPO  

![alt text](/img%20y%20otros/a.png)

![alt text](/img%20y%20otros/b.png)

![alt text](/img%20y%20otros/c.png)

![alt text](/img%20y%20otros/d.png)

![alt text](/img%20y%20otros/e.png)


## DIAGRAMA DEL CIRCUITO IMPRESO  

 - **PUENTEH**

![alt text](/img%20y%20otros/impresion_PuenteH.png )


## FOTOGRAFÍA DE LOS CIRCUITOS FÍSICOS  

- **PUENTE-H**

![alt text](/img%20y%20otros/h.png)

![alt text](/img%20y%20otros/porton.png)


## Videos del funcionamiento de manera separada
<!-- Bootstrap CSS -->
<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">

<div class="container text-center mt-5">
    <h5>Video 1: Puente H con teclado</h5>
    <a href="https://drive.google.com/file/d/1beyIAKXEkxay54qloO74zUteSLEUPP7C/view?usp=sharing" 
       target="_blank" 
       class="btn btn-primary btn-lg shadow-lg">
        🎥 Ver Video
    </a>
    <h5>Video 2: Circuito de estacionamiento</h5>
    <a href="https://drive.google.com/file/d/17yzEijuIVJaPfqoEWJlil1kkXTxCtNVM/view?usp=sharing" 
       target="_blank" 
       class="btn btn-primary btn-lg shadow-lg">
        🎥 Ver Video
    </a>
    <h5>Video 3: funcionamiento del contador</h5>
    <a href="https://drive.google.com/file/d/1iBH4ItbxMRriucN9-L3cGpLwQFgZrWLf/view?usp=sharing" 
       target="_blank" 
       class="btn btn-primary btn-lg shadow-lg">
        🎥 Ver Video
    </a>
    <h5>Video 4: Funcionamiento puente H (inicios)</h5>
    <a href="https://drive.google.com/file/d/1_NcNHPXqe8CUbmW9W54yAJnv0poMBiHt/view?usp=sharing" 
       target="_blank" 
       class="btn btn-primary btn-lg shadow-lg">
        🎥 Ver Video
    </a>
    <h5>Video 5: Servo motor funcional</h5>
    <a href="https://drive.google.com/file/d/1bIblLQhWFZWylOnM9_nF1qKr8OAT_6ox/view?usp=sharing" 
       target="_blank" 
       class="btn btn-primary btn-lg shadow-lg">
        🎥 Ver Video
    </a>
    <h5>Video 6:Unido funcional</h5>
    <a href="https://drive.google.com/file/d/1_mlIQ39Zu3NAc-mnzczPx472EULAjhww/view?usp=sharing" 
       target="_blank" 
       class="btn btn-primary btn-lg shadow-lg">
        🎥 Ver Video
    </a>
</div>
</div>