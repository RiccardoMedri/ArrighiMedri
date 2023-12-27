#include <ESP8266HTTPClient.h>
#include <setupConnection.h>
// 84:cc:a8:ae:a0:12

const char* ssid     = "AndroidAPc5c2";
const char* password = "routerpw";

String url = "http://192.168.68.238:3000/macAddress/nuovoMacAddress/";
WiFiClient wifiClient;
String macAddress = WiFi.macAddress();

void setup() {
  Serial.begin(9600);
  //setupConnection();
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