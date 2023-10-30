#include <Servo.h>

const int sensorPinD1 = 8; //TRIG
const int echoPinD1 = 7; //ECHO

const int sensorPinD2 = 6; //TRIG
const int echoPinD2 = 5; //ECHO

float distanceD1;
float distanceD2;

Servo servo1; //cria um novo objeto servo

void setup() {
  Serial.begin(9600);
  pinMode(sensorPinD1, OUTPUT);
  pinMode(echoPinD1, INPUT);
  
  servo1.attach(9); //conecta o objeto servo1 ao pino 9
  servo1.write(0);
  pinMode(sensorPinD2, OUTPUT);
  pinMode(echoPinD2, INPUT);
 
}

void loop() {
 
 
 SensorD1();
 SensorD2();
  
}
void OpenDoor(){
  
  if (distanceD1 <= 30.00 || distanceD2 <= 30.00){
    Serial.print("----");
    servo1.write(90);  
  }
  else {
    Serial.print("---");
    delay(2000);
    servo1.write(0);
  }
}


void SensorD1(){
  
 digitalWrite(sensorPinD1, LOW);
 delayMicroseconds(5);        
 digitalWrite(sensorPinD1, HIGH);  
 delayMicroseconds(10);      
 digitalWrite(sensorPinD1, LOW); 
 distanceD1 = pulseIn(echoPinD1, HIGH) / 58.0; // Convertendo para centímetros
 
 Serial.print("Distancia D1 = ");
 Serial.print(distanceD1);         
 Serial.print(" cm");         
 Serial.println(); // Muda para uma nova linha
  
 OpenDoor();
 
}

void SensorD2(){
   
  digitalWrite(sensorPinD2, LOW);
  delayMicroseconds(5);        
  digitalWrite(sensorPinD2, HIGH);  
  delayMicroseconds(10);      
  digitalWrite(sensorPinD2, LOW); 
  distanceD2 = pulseIn(echoPinD2, HIGH) / 58.0; // Convertendo para centímetros
   
  OpenDoor();
 
  Serial.print("Distancia D2 = ");
  Serial.print(distanceD2);         
  Serial.print(" cm");         
  Serial.println(); // Muda para uma nova linha
  
}
