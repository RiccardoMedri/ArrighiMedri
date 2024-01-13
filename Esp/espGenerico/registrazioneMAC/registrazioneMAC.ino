//questo script ha lo scopo di registrare il MAC address di un nuovo nodo nel database
//così che sia riconosciuto dai controller del webserver
//questo script viene eseguito solo una volta in fase di registrazione 
#include <ESP8266HTTPClient.h>
#include "setupConnection.h"

const char* ssid     = "iPhone di Riccardo (2)";
const char* password = "RiccardoMed";

String url = "http://172.20.10.4:3000/macAddress/nuovoMacAddress/";
WiFiClient wifiClient;
String macAddress = WiFi.macAddress();

void setup() {
  Serial.begin(9600);
  setupConnection(ssid, password);

  sendMacAddress();
}

void loop() {

}

void sendMacAddress() {
  HTTPClient http;
  String urlFull = url + macAddress; 
  http.begin(wifiClient, urlFull.c_str());

  http.addHeader("Content-Type", "text/plain");
  int httpResponseCode = http.GET();

  Serial.print("Codice di risposta ");
  Serial.println(httpResponseCode);

  http.end();
}