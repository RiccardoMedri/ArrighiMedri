#include <ESP8266HTTPClient.h>
#include <setupConnection.h>
// 84:cc:a8:ae:a0:12

const char* ssid     = "AndroidAPc5c2";
const char* password = "routerpw";

String urlDB = "http://0.0.0.0/macAddress";
WiFiClient wifiClient;
byte mac[6];
String macAddress = "";

void setup() {
  Serial.begin(9600);
  //setupConnection();
  setupConnection(ssid, password);


  WiFi.macAddress(mac);
  for(int i = 0; i < 5; ++i) {
    macAddress += mac[i];
    macAddress += ":";
  }
  macAddress += mac[5];

  sendMacAddress();
}

void loop() {

}
/*
void setupConnection() {
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
*/

void sendMacAddress() {
  HTTPClient http;
  http.begin(wifiClient, urlDB);

  http.addHeader("Content-Type", "text/plain");
  int httpResponseCode = http.POST(macAddress);

  Serial.print("Codice di risposta");
  Serial.println(httpResponseCode);

  http.end();
}