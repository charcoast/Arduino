/*
   Jogo de precisão - Código envolvendo maior parte dos exemplos.
  Utilizado como base: AnalogReadSerial
  O exemplo utilizava-se de um sinal PWM regulado por um potenciômetro para variar a luminosidade
  de um LED.

  Nesta versão do código, o potênciometro regula a luminosidade do LED vermelho, e também a frequência
  tocada no buzzer. Porém, dentro de uma determinada faixa de valores na leitura do potenciômetro(MinFaixa~MaxFaixa),
  o LED vermelho é desligado, o LED verde é ligado, e o buzzer desligado, indicando que a resistência do
  potenciômetro se enquadra na faixa configurada.
*/

#define MinFaixa  501
#define MaxFaixa  521

int sensorValue = 0;
int outputValue = 0;

#define analogInPin A0
#define LEDvermelho 9
#define LEDverde 2
#define Buzzer 7

void setup() {
  pinMode(LEDverde, OUTPUT);
  pinMode(LEDvermelho, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  sensorValue = analogRead(analogInPin);

  if (MinFaixa < sensorValue && MaxFaixa > sensorValue) {
    noTone(Buzzer);
    digitalWrite(LEDverde, HIGH);
    analogWrite(LEDvermelho, 0);
  } else {
    if (sensorValue < MinFaixa) {
      outputValue = map(sensorValue, MinFaixa, 1023, 255, 0);
      tone(Buzzer, outputValue);
      digitalWrite(LEDverde, LOW);
      if (outputValue > 255) {
        analogWrite(LEDvermelho, 255);
      } else {
        analogWrite(LEDvermelho, outputValue);
      }
    }
    if (sensorValue > MaxFaixa ) {
      outputValue = 0;
      outputValue = map(sensorValue, MaxFaixa, 1023, 0, 255);
      tone(Buzzer, outputValue);
      digitalWrite(LEDverde, LOW);
      analogWrite(LEDvermelho, outputValue);
    }
  }

  Serial.print("sensor = ");
  Serial.printl(sensorValue);
  Serial.print("output = ");
  Serial.println(outputValue);

  delay(50);
}
