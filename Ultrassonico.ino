/*  Sinalizador de porta
 * 
 * Este código tem como objetivo indicar se a porta está aberta ou fechada,
 * emitindo um som e ligando um LED vermelho ou verde dependendo da situação.
 *
 */

#include <Ultrasonic.h> //Inclusão da biblioteca

#define LEDVerde 5    //Define o pino LEDVerde
#define LEDVermelho 6 //Define o pino LEDVermelho
#define buzzer 7      //Define o pino buzzer

#define Echo 10       //Define o pino Echo
#define Trigger 11    //Define o pino Trigger
Ultrasonic ultrasonic(Trigger, Echo); //Inicia o sensor ultrassonico usando os valores de Trigger(11) e Echo (10)
void setup() {
  pinMode(buzzer, OUTPUT);  //Define buzzer como sendo um pino OUTPUT
  pinMode(LEDVerde, OUTPUT);  //Define LEDVerde como sendo um pino OUTPUT
  pinMode(LEDVermelho, OUTPUT); //Define LEDVermelho como sendo um pino OUTPUT

  Serial.begin(9600);

}

void loop() {
  float distancia = ultrasonic.distanceRead();  //Armazena a leitura da distância na variável flutuante distancia

  if (distancia == 2.0) { //Condicional com distancia
    digitalWrite(LEDVerde, HIGH); //Definindo nível lógico alto ao LEDVerde
    digitalWrite(LEDVermelho, LOW); //Definindo nível lógico baixo ao LERVermelho
    Serial.print("Distancia: ");  //Escreve no monitor serial
    Serial.println(distancia);    //Escreve no monitor serial
    Serial.println("Porta fechada");  //Escreve no monitor serial
    tone(buzzer, 850);  //Toca no buzzer com frequência 850
    delay(200); //Delay de 200ms
    noTone(buzzer);
    delay(100);
    tone(buzzer, 850);
    delay(200);
    noTone(buzzer); //Para de tocar no buzzer
  } else if(distancia > 2.0) {
    digitalWrite(LEDVerde, LOW);  //Definindo nível lógico baixo ao LEDVerde
    digitalWrite(LEDVermelho, HIGH);  //Definindo nível lógico alto ao LEDVermelho
    Serial.print("Distancia: ");  //Escreve no monitor serial
    Serial.println(distancia);    //Escreve no monitor serial
    Serial.println("Porta aberta"); //Escreve no monitor serial
    tone(buzzer, 300);  //Toca no buzzer com frequência 300
    delay(200); //Delay de 200ms
    noTone(buzzer);
    delay(100);
    tone(buzzer, 300);
    delay(200);
    noTone(buzzer); //Para de tocar no buzzer
  }

}
