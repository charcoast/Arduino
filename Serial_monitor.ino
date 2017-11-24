void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

String texto;
bool comando_valido = true;

void loop() {
  while(Serial.available()){
    String letra = Serial.readString();
    texto.concat(letra);
    comando_valido = false;
  }
  if(texto == "ligar"){
    Serial.println("Comando: ligar");
    Serial.println("LED ligado");
    digitalWrite(13, HIGH);
    comando_valido = true;
    texto = "";
  }else if(texto == "desligar"){
    Serial.println("Comando: desligar");
    Serial.println("LED desligado");
    digitalWrite(13, LOW);
    comando_valido = true;
    texto = "";
  }else if(comando_valido == false){
    Serial.print("Comando: ");
    Serial.println(texto);
    Serial.println("Comando invalido.");
    texto = "";
  }

}
