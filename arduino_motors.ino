//motor_A
int motor_a_pin1 = 2 ;
int motor_a_pin2 = 3 ;
 
//motor_B
int motor_b_pin1 = 5 ;
int motor_b_pin2 = 4 ;

//sensor
//Programa: Conectando Sensor Ultrassonico HC-SR04 ao Arduino
//Autor: FILIPEFLOP
 
//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>
 
//Define os pinos para o trigger e echo
#define pino_trigger 6
#define pino_echo 7
 
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
 
int DELAY = 2000;

int andando = 1;
int re = 2;
int esquerda = 3;
int sts = 0;

void setup() {

  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
  
  pinMode(motor_a_pin1, OUTPUT);
  pinMode(motor_a_pin2, OUTPUT);
  pinMode(motor_b_pin1, OUTPUT);
  pinMode(motor_b_pin2, OUTPUT);
}

void loop() {
  if (sts == 0) { //inicio
    sts = andando;
    Serial.println("INICIO");
  } else if (sts == andando) { // andando
    if (achouAlgo()) {
      sts = re;
    }
    praFrente();
    Serial.println("ANDANDO");
  } else if (sts == re) { //re
    if (!achouAlgo()) {
      sts = andando;
    }
    praTras();
    Serial.println("RE");
  }
//  else if (sts == esquerda) {
//    if (achouAlgo()) {
//      sts = re;
//    } else if (caminhoLivre()) {
//      sts = andando;
//    }
//    praEsquerda();
//    
//    Serial.println("ESQUERDA");
//  }
}

boolean caminhoLivre() {
  float cmMsec = getDistanciaDoObstaculo();
  return cmMsec > 100.0;
}

boolean achouAlgo(){
  float cmMsec = getDistanciaDoObstaculo();
  return cmMsec <= 70.0;
}

float getDistanciaDoObstaculo() {
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
    Serial.print("Distancia em cm: ");
  Serial.println(cmMsec);
  return cmMsec;
}

void moverParaFrente(int pin1, int pin2) {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}

void moverParaTras(int pin1, int pin2) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

void desligaMotor(){
  digitalWrite(motor_a_pin1, LOW);
  digitalWrite(motor_a_pin2, LOW);

  digitalWrite(motor_b_pin1, LOW);
  digitalWrite(motor_b_pin2, LOW);
}

void praFrente(){
  moverParaFrente(motor_a_pin1, motor_a_pin2);
  moverParaFrente(motor_b_pin1, motor_b_pin2);
}

void praTras(){
  moverParaTras(motor_a_pin1, motor_a_pin2);
  moverParaTras(motor_b_pin1, motor_b_pin2);
}

void praDireita(){
  moverParaFrente(motor_a_pin1, motor_a_pin2);
  moverParaTras(motor_b_pin1, motor_b_pin2);
}

void praEsquerda(){
  //moverParaTras(motor_a_pin1, motor_a_pin2);
  moverParaFrente(motor_b_pin1, motor_b_pin2);
}
