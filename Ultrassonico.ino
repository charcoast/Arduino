/*  Sinalizador de porta
 * 
 * Este código tem como objetivo indicar se a porta está aberta ou fechada,
 * emitindo um som e ligando um LED vermelho ou verde dependendo da situação.
 *
 */

#include <Ultrasonic.h>

#define LEDVerde 5
#define LEDVermelho 6
#define buzzer 7

#define Echo 10
#define Trigger 11
Ultrasonic ultrasonic(Trigger, Echo);

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(LEDVerde, OUTPUT);
  pinMode(LEDVermelho, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  float distancia = ultrasonic.distanceRead();

  if (distancia == 2.0) {
    digitalWrite(LEDVerde, HIGH);
    digitalWrite(LEDVermelho, LOW);
    Serial.print("Distancia: ");
    Serial.println(distancia);
    Serial.println("Porta fechada");
    tone(buzzer, 850);
    delay(200);
    noTone(buzzer);
    delay(100);
    tone(buzzer, 850);
    delay(200);
    noTone(buzzer);
  }
    if(distancia > 2.0) {
    digitalWrite(LEDVerde, LOW);
    digitalWrite(LEDVermelho, HIGH);
    Serial.print("Distancia: ");
    Serial.println(distancia);
    Serial.println("Porta aberta");
    tone(buzzer, 300);
    delay(200);
    noTone(buzzer);
    delay(100);
    tone(buzzer, 300);
    delay(200);
    noTone(buzzer);
  }

}
