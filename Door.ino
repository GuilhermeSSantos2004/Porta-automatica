#include <Servo.h>

#include "WiFi.h"             // WiFi Library 
#include <HTTPClient.h>

const int sensorPinD1 = 8; //TRIG
const int echoPinD1 = 7; //ECHO

const int sensorPinD2 = 6; //TRIG
const int echoPinD2 = 5; //ECHO

float distanceD1;
float distanceD2;

int count = -1; 

Servo servo1; //cria um novo objeto servo

int incomingByte = 0; // for incoming serial data


/* Configuração do Wi-Fi ---------------------------------------------------------*/

char wifiSsid[] = "homepage"; // Nome da rede Wi-Fi
char wifiPass[] = "carromoto";     // Senha da rede Wi-Fi

char serverAddress[] = "https://api.tago.io/data";  // endereço TagoIO 
char contentHeader[] = "application/json";
char tokenHeader[]   = "048c70a2-0935-4521-88e1-33668ef60f1c"; // TagoIO Token

HTTPClient client;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPinD1, OUTPUT);
  pinMode(echoPinD1, INPUT);
  
  servo1.attach(9); //conecta o objeto servo1 ao pino 9
  servo1.write(0);
  pinMode(sensorPinD2, OUTPUT);
  pinMode(echoPinD2, INPUT);

  init_wifi(); //função para conectar no host
 
}

void loop() {
 
 
 SensorD1();
 SensorD2();
  
 
  
 if (Serial.available() > 0) {
   
   incomingByte = Serial.read();

   //Serial.print("Eu recebi: ");
   Serial.println(incomingByte, DEC);
   
   forceOpen();
  }


 EnviaDadosTago();

  
  
// delay(1200);
 Serial.print("Quantidade de veses que a porta foi aberta: ");
 Serial.print(count);
 Serial.println();
  
}

/**

   @Inicializa a conexão wifi

*/

void init_wifi(void) {

  Serial.println("Conectando Wifi...");

  Serial.print("SSID: ");

  Serial.println(wifiSsid);

  Serial.print("PASS: ");

  Serial.println(wifiPass);

  WiFi.begin(wifiSsid, wifiPass);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("WiFi Conectado!");

  Serial.print("IP is ");

  Serial.println(WiFi.localIP());

}

void EnviaDadosTago() {
  
  
  char anyData[30];

  char postData[300];

  char anyData1[30];

  char bAny[30];

  int statusCode = 0;



  strcpy(postData, "{\n\t\"variable\": \"Abertura porta\",\n\t\"value\": ");

  dtostrf(count, 6, 2, anyData);

  strncat(postData, anyData, 100);

  strcpy(anyData1, ",\n\t\"unit\": \"ºC\"\n\t}\n");

  strncat (postData, anyData1, 100);

  Serial.println(postData);

  client.begin(serverAddress);

  client.addHeader("Content-Type", contentHeader);

  client.addHeader("Device-Token", tokenHeader);

  statusCode = client.POST(postData);



  // read the status code and body of the response

  Serial.print("Status code: ");

  Serial.println(statusCode);

  Serial.println("End of POST to TagoIO");

  Serial.println();
  }

void forceOpen(){
  
  if (incomingByte == 49){
    Serial.print("PORTA ABERTA");
    Serial.print(incomingByte);
    servo1.write(90);  
    delay(5000);

  }
  else {
    Serial.print("PORTA FECHADA");
    Serial.print(incomingByte);
    servo1.write(90);
    delay(5000);
    

  }
  
}
void OpenDoor(){
  
  if (distanceD1 <= 30.00 || distanceD2 <= 30.00){
    Serial.print("----");
    servo1.write(90);  
    count +=1;
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
