#ifdef ESP32
    #include <WiFi.h>
    #include <WebServer.h>
#else
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
#endif

const char* ssid     = "";
const char* password = "";

String urlDB = "http://0.0.0.0/tessera/";
WiFiClient wifiClient;
byte mac[6];
String macAddress = "";

void setup() {
  Serial.begin(9600);
  connessione();
  for(int i = 0; i < 5; ++i) {
    macAddress += mac[i];
    macAddress += ":";
  }
  macAddress += mac[5];

  sendMacAddress();
}

void loop() {

}

void connessione() {
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

void sendMacAddress() {
  HTTPClient http;
  String url
}