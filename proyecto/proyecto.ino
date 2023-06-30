#include <DHT.h>
#include <DHT_U.h>

#include <ESP32Servo.h>
#include <WiFi.h>
#include <NewPing.h>

#define DHTPIN 0
#define DNLEDPIN 2
#define THLEDPIN 4
#define FOTORESPIN 6
#define VENTILADORPIN 8
#define BOMBAPIN 10
#define MOTORPIN 12
#define TRIGGER_PIN 12 
#define ECHO_PIN 11  
#define MAX_DISTANCE 200

//internet?
#define WIFI_SSID "**"
#define WIFI_PASSWORD "**"

#define DHTTYPE    DHT11

DHT dht(DHTPIN, DHTTYPE);
NewPing distancia(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo servoMotor;
//llamar las funciones del dht11 con dht.

//VARIABLE DE LA HORA
int hora = 13;

void setup() {
  Serial.begin(9600);
  WIFInit();
  pinMode(DNLEDPIN, OUTPUT);
  pinMode(THLEDPIN, OUTPUT);
  pinMode(BOMBAPIN, OUTPUT);
  pinMode(VENTILADORPIN, OUTPUT);
  servoMotor.attach(MOTORPIN,500,2500);
  servoMotor.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  verificarTemp();
  verificarNoche();
  verificarNivelAgua();
  verificarComida();  
  delay(30000);
}


//FUNCIONES
void verificarTemp(){
  float temp = dht.readTemperature();
  if(temp >= 25){
    digitalWrite(VENTILADORPIN, HIGH);
    digitalWrite(THLEDPIN, LOW);
  }else if(temp <= 20){
    digitalWrite(VENTILADORPIN, LOW);
    digitalWrite(THLEDPIN, HIGH);
  }else{
    digitalWrite(VENTILADORPIN, LOW);
    digitalWrite(THLEDPIN, LOW);
  }
}

void verificarNoche(){
  int res = digitalRead(FOTORESPIN);
  if(res == HIGH){
    digitalWrite(DNLEDPIN, LOW);
  }else{
    digitalWrite(DNLEDPIN, HIGH);
  }
}

void verificarNivelAgua(){
  float dis = distancia.ping_cm();
  Serial.println(dis);

  if(dis <= 4){
    while(dis <= 4){
      digitalWrite(BOMBAPIN, HIGH);
    }
    digitalWrite(BOMBAPIN, LOW);
  }else{
    digitalWrite(BOMBAPIN, LOW);
  }
}

void verificarComida(){
  if(hora >= 13 && hora <14){
    servoMotor.write(10); //MOVER EL MOTOR 10 GRADOS
    delay(1000); //1SEG PARA CERRAR LA COMPUERTA DE COMIDA
    servoMotor.write(0);
  }
}

void WIFInit()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando a WiFi.... ");
  while(WiFi.status() != WL_CONNECTED)
  {
  Serial.print(".");
  delay(300);
  }
  Serial.println();
  Serial.print("Conectado con IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}
