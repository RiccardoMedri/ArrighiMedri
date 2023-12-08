#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid     = "testWifiSSID";
const char* password = "testWifiSSID";

const char index_html[] PROGMEM = R"rawliteral(
    <!DOCTYPE HTML><html><head>
    <title>ESP Input Form</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    </head><body>
    <form action="/addCard">
        Nome: <input type="text" name="nome">
        Cognome: <input type="text" name="cognome">
        Ruolo: <input type="text" name="ruolo">
        <input type="submit" value="Submit">
    </form><br>
    </body></html>)rawliteral";

ESP8266WebServer server(80);
WiFiClient wifiClient;
String urlDB = "http://X.X.X.X/addCard";

void setup() {
  Serial.begin(115200);
  delay(10);
  setupRouting();
}

void loop() {
  server.handleClient();
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

void setupRouting() {
    server.on("/addCard", handleCredential);
    server.on("/", handleHome);
    server.begin();
}

void handleHome(){
    server.send(200, "text/html", index_html);
}

void handleCredential() {
  String nome = server.arg("nome");
  String cognome = server.arg("cognome");
  String ruolo = server.arg("ruolo");

  if(nome != "" && cognome != "" && ruolo != ""){
    server.send(200, "text.html", addToDB(urlDB, nome, cognome, ruolo))
  }else{
    server.send(200, "text/html", "Form non compilato");
  }
}

String addToDB(String url, String nome, String cognome, String ruolo){
  HTTPClient http;
  String urlCompleto = url + "/" + nome + "-" + cognome + "-" + ruolo;
  http.begin(wifiClient, url.c_str());
  
  int httResponseCode = http.GET()

  http.end();
}