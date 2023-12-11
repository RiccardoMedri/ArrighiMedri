#include <ESP8266HTTPClient.h>
#include <WifiClient.h>

// #define PIN_LED_RED 9
// #define PIN_LED_GREEN 8

const char* ssid = "";
const char* password = "";
const String macAddress;

String urlDB = "http://0.0.0.0/tessera";

WiFiClient wifiClient;

void setup() {
    Serial.begin(9600);
    // pinMode(PIN_LED_RED, OUTPUT);
    // pinMode(PIN_LED_GREEN, OUTPUT);
    connessione();
    macAddress = WiFi.macAddress();
}

void loop() {
    if(/*lettura della tessare*/) {
        String idTessera = ""; // = metodo per prendere il valore scansionato
        if(checkID(idTessera, urlDB)) {
            // digitalWrite(PIN_LED_GREEN, HIHG);
            // delay(2000);
            // digitalWrite(PIN_LED_GREEN, LOW);
            // simulazione led con stampa a seriale
            Serial.println("GREEN LED IS BLINKING!");
        }
        else {
            // digitalWrite(PIN_LED_RED, HIHG);
            // delay(2000);
            // digitalWrite(PIN_LED_GREEN, LOW);
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
    String urlCompleto = url + "/" + idTessera + "-" + macAddress;
    http.begin(wifiClient, urlCompleto.c_str());

    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
        http.end();
        return true;
    }

    http.end();
    return false;
} 