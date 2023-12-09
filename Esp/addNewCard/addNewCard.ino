#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <ESP8266HTTPClient.h>
#include <WifiClient.h>

const char* ssid     = "";
const char* password = "";

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
String urlDB = "http://0.0.0.0/tessera/nuovaTessera";

void setup() {
  delay(6000);
  Serial.begin(115200);
  delay(10);
  connessione();
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
    server.on("/limitAccess", handleAccess);
    server.begin();
}

void handleAccess() {
  
}

void handleHome(){
    server.send(200, "text/html", index_html);
}

void handleCredential() {
  String nome = server.arg("nome");
  String cognome = server.arg("cognome");
  String ruolo = server.arg("ruolo");

  if(nome != "" && cognome != "" && ruolo != ""){
    server.send(200, "text.html", addToDB(urlDB, nome, cognome, ruolo));
  }else{
    server.send(200, "text/html", "Form non compilato");
  }
}

String addToDB(String url, String nome, String cognome, String ruolo){

  // scansione del nfc e recupero idtessera

  HTTPClient http;
  String urlCompleto = url + "/" + "000" + "-" + nome + "-" + cognome + "-" + ruolo;
  http.begin(wifiClient, urlCompleto.c_str());
  
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String response = "";
    switch (httpResponseCode){
      case 200:
        response = http.getString();
      break;
      case 404:
        response = "risorsa non disponibile";
      break;
      default:
        response = "codice di errore: " + String(httpResponseCode);
      break;
    }
  http.end();
  Serial.println(response);
  return response;
  }
  
  http.end();
  
  return "Response code < 0";
}