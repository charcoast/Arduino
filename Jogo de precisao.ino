/*
   Jogo de precisão - Código envolvendo maior parte dos exemplos.
  Utilizado como base: AnalogReadSerial
  O exemplo utilizava-se de um sinal PWM regulado por um potenciômetro para variar a luminosidade
  de um LED.

  Nesta versão do código, o potênciometro regula a luminosidade do LED vermelho, e também a frequência
  tocada no buzzer. Porém, dentro de uma determinada faixa de valores na leitura do potenciômetro(MinFaixa~MaxFaixa),
  o LED vermelho é desligado, o LED verde é ligado, e o buzzer desligado, indicando que a resistência do
  potenciômetro se enquadra na faixa configurada.

  Neste código, há uma faixa de valores para a leitura do potenciometro definida por MinFaixa e MaxFaixa.
  Quando o usuário deixa o potenciometro na posição que corresponde à faixa de valores definida, um LED
  verde é ligado. Em contrapartida, se o potenciometro não estiver nesta faixa, um buzzer começará a
  tocar e um LED vermelho acenderá, tendo a frequência tocada no buzzer e a luminosidade do LED vermelho
  variando conforme for ficando mais próximo ou distante da faia de valores definida.
*/
#define MinFaixa  501 //Define o valor mínimo da faixa de valores
#define MaxFaixa  521 //Define o valor máximo da faixa de valores

int sensorValue = 0; //Valor lido diretamente do potenciometro
int outputValue = 0; //Valor após o mapeamento para enquadrar 0~1023 para 0~255

#define analogInPin A0   //Define analogInPin como sendo o pino analógico A0
#define LEDvermelho 9   //Define LEDvermelho como sendo o pino 9
#define LEDverde 2     //Define LEDverde como sendo o pino 2
#define Buzzer 7  //Define Buzzer como sendo o pino 7

void setup() {
  pinMode(LEDverde, OUTPUT); // Define o pino 2 como OUTPUT
  pinMode(LEDvermelho, OUTPUT); // Define o pino 2 como OUTPUT
  pinMode(Buzzer, OUTPUT);
  Serial.begin(9600);       // Inicia o monitor serial - Padrão do código base
}

void loop() {

  sensorValue = analogRead(analogInPin); // Lê o pino digital A0 e grava em "sensorValue"

  if (MinFaixa < sensorValue && MaxFaixa > sensorValue) {
    noTone(Buzzer); //Desliga o buzzer
    digitalWrite(LEDverde, HIGH); //Seta o pino digital 2 como HIGH
    analogWrite(LEDvermelho, 0); //Seta o sinal PWM do pino 9 como 0
  } else {
    if (sensorValue < MinFaixa) {
      outputValue = map(sensorValue, MinFaixa, 1023, 255, 0);//Mapeia o valor do potenciometro para 255~0
      tone(Buzzer, outputValue); //Toca a frequência baseada no valor da resistencia do potenciômetro
      digitalWrite(LEDverde, LOW);//Seta o pino digital 2 como LOW
      if (outputValue > 255) {
        analogWrite(LEDvermelho, 255); //Seta o sinal PWM do pino 9 baseado no valor da resistencia do potenciômetro
      } else {
        analogWrite(LEDvermelho, outputValue); //Seta o sinal PWM do pino 9 baseado no valor da resistencia do potenciômetro
      }
    }
    if (sensorValue > MaxFaixa ) {
      outputValue = 0;
      outputValue = map(sensorValue, MaxFaixa, 1023, 0, 255);//Mapeia o valor do potenciometro para 0~255
      tone(Buzzer, outputValue); //Toca a frequência baseada no valor da resistencia do potenciômetro
      digitalWrite(LEDverde, LOW);//Seta o pino digital 2 como LOW
      analogWrite(LEDvermelho, outputValue); //Seta o sinal PWM do pino 9 baseado no valor da resistencia do potenciômetro
    }
  }

  Serial.print("sensor = "); //Printa o texto no monitor serial
  Serial.printl(sensorValue);//Printa o texto no monitor serial
  Serial.print("output = ");//Printa o texto no monitor serial
  Serial.println(outputValue);//Printa o texto no monitor serial

  delay(50); // Da uma pausa de 50ms no código a cada loop
}
