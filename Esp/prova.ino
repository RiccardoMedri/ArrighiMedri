#ifdef ESP32
    #include <WiFi.h>
    #include <WebServer.h>
#else
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
#endif

/*
  TESTED ON ESP32/ESP8266
*/


String indexHtml = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}.button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}.button2 {background-color: #555555;}</style></head><body><h1>ESP32 Web Server</h1>";

const char* ssid     = "routerAA";
const char* password = "123456789";

/*
  salvo già due stringhe che userò per gestire lo stato del pulsante, andando a variarlo fra "led on" e "led off"
*/
String ledOn = "<p>GPIO 26 - state ON</p><p><a href=\"/ledManagement?ledPin=26&status=0\"><button class=\"button button2\">OFF</button></a></p>";
String ledOff = "<p>GPIO 26 - state OFF</p><p><a href=\"/ledManagement?ledPin=26&status=1\"><button class=\"button\">ON</button></a></p>";

#ifdef ESP32
  WebServer server(80);
#else
  ESP8266WebServer server(80);
#endif

void setup() {
    Serial.begin(115200);
    pinMode(26, OUTPUT);

    delay(3000);

    Serial.print("Loading: ");
    for(int i = 0; i < 10; ++i) {
      Serial.print('#');
      delay(500);
    }

    Serial.println("Loading done!");

    delay(3000);

    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    for(int i = 0; i < 6; ++i) {
      Serial.print("AP IP address: ");
      Serial.println(IP);
      delay(1000);
    }
    setupRouting();
}

void loop(){
    server.handleClient();
}

void setupRouting() {
    server.on("/", handleLed);
    server.on("/ledManagement", handleLedState);
    server.begin();
}

void handleLed(){  
  server.send(200, "text/html", (indexHtml + ledOff));
}

void handleLedState() {
  if(server.arg("status") == "1") {
    analogWrite(26, HIGH);
    Serial.println("Led ON");
    server.send(200, "text/html", (indexHtml + ledOn));
  }
  else {
    analogWrite(26, LOW);
    Serial.println("Led OFF");
    server.send(200, "text/html", (indexHtml + ledOff));
  }
}
