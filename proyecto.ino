#include <Servo.h>
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

//llamar las funciones del dht11 con dht.

void setup() {
  // put your setup code here, to run once:
  WIFInit();
}

void loop() {
  // put your main code here, to run repeatedly:

}


//FUNCIONES
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
