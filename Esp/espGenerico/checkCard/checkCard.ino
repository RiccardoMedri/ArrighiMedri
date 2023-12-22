#include <ESP8266HTTPClient.h>
#include <WifiClient.h>

// #define RED_LED 9
// #define GREEN_LED 8

const char* ssid = "";
const char* password = "";

String urlDB = "http://0.0.0.0/tessera/";
WiFiClient wifiClient;
byte mac[6];
String macAddress = "";

void setup() {
  Serial.begin(9600);
  // pinMode(RED_LED, OUTPUT);
  // pinMode(GREEN_LED, OUTPUT);
  connessione();
  for(int i = 0; i < 5; ++i) {
    macAddress += mac[i];
    macAddress += ":";
  }
  macAddress += mac[5];
}

void loop() {
    if(/*lettura della tessare*/) {
        String idTessera = ""; // = metodo per prendere il valore scansionato
        if(checkID(idTessera, urlDB)) {
            // digitalWrite(GREEN_LED, HIHG);
            // delay(2000);
            // digitalWrite(GREEN_LED, LOW);
            // simulazione led con stampa a seriale
            Serial.println("GREEN LED IS BLINKING!");
        }
        else {
            // digitalWrite(RED_LED, HIHG);
            // delay(2000);
            // digitalWrite(GREEN_LED, LOW);
            // simulazione led con stampa a seriale
            Serial.println("RED LED IS BLINKING");
        }
    }
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

bool checkID(String idTessera, String url) {
    HTTPClient http;
    String urlCompleto = url + idTessera + "-" + macAddress;
    http.begin(wifiClient, urlCompleto.c_str());

    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
        http.end();
        return true;
    }

    http.end();
    return false;
} 