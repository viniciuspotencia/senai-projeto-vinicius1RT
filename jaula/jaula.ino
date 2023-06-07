//Programa: Sensor ultrassônico Arduino acender LED
//Autor: Luan Alves - www.guiarobotica.com
#include "Ultrasonic.h"
Ultrasonic ultrasonic(3, 2);  // Trigger na porta 3 e Echo na porta 2

//Declarando os LED como constantes em seus respectivos pinos
const int ledVerde = 4;
const int ledAmarelo = 5;
const int ledVermelho = 6;
const int echoPin = 2;     //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 3;     //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
const int pinoBuzzer = 7;  //PINO DIGITAL EM QUE O BUZZER ESTÁ CONECTADO

Ultrasonic ultrasonic2(trigPin, echoPin);  //INICIALIZANDO OS PINOS
int distancia;                             //CRIA UMA VARIÁVEL CHAMADA "distancia" DO TIPO INTEIRO

long microsec = 0;  // variaveis de controle
float distanciaCM = 0;

void setup() {
  Serial.begin(9600);         //Inicializando o serial monitor
  pinMode(ledVerde, OUTPUT);  //declarando os LEDs como saida
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(echoPin, INPUT);      //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT);     //DEFINE O PINO COMO SAÍDA (ENVIA)
  pinMode(pinoBuzzer, OUTPUT);  //DECLARA O PINO COMO SENDO SAÍDA
}

void loop() {
  hcsr04();  // FAZ A CHAMADA DO MÉTODO "hcsr04()"
  //Lendo o valor do sensor
  microsec = ultrasonic.timing();

  //Convertendo a distância em CM
  distanciaCM = ultrasonic.convert(microsec, Ultrasonic::CM);

  ledDistancia();
  Serial.print(distanciaCM);  // mostrar a distancia na porta serial
  Serial.println(" cm");      // colocar unidade de medida
  delay(500);                 // espera de 500 milissegundos
}

void ledDistancia() {

  //Desliga todos os LEDs
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);

  // criando as condicoes se a distancia for entre 30 cm e 20 cm
  if (distanciaCM >= 20) {
    digitalWrite(ledVerde, HIGH);  //liga o LED verde
  }
  // se a distancia for 10 cm e 20 cm
  if (distanciaCM <= 20 and distanciaCM >= 10) {
    digitalWrite(ledAmarelo, HIGH);  //liga LED amarelo
  }

  if (distanciaCM < 10) {             // se a distancia for menor que 10 cm
    digitalWrite(ledVermelho, HIGH);  // liga LED vermelho
    tone(pinoBuzzer,1500);//ACIONA O BUZZER
  }else{//SENÃO, FAZ
    noTone(pinoBuzzer);//BUZZER PERMANECE DESLIGADO
  }
}

void hcsr04() {
  digitalWrite(trigPin, LOW);   //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
  delayMicroseconds(2);         // DELAY DE 2 MICROSSEGUNDOS
  digitalWrite(trigPin, HIGH);  //SETA O PINO 6 COM PULSO ALTO "HIGH"
  delayMicroseconds(10);        // DELAY DE 10 MICROSSEGUNDOS
  digitalWrite(trigPin, LOW);   //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
  // FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
  //RESPOSTA DO ECHO EM CENTÍMETROS E ARMAZENA
  //NA VARIÁVEL "distancia"
  //istancia = (ultrasonic.Ranging(distanciaCM)); // VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
  delay(500);  //INTERVALO DE 500 MILISSEGUNDOS
}