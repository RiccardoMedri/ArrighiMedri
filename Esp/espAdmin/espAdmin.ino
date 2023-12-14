#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WifiClient.h>

const char* ssid     = "Vodafone-A81417726";
const char* password = "vwwcb2b99xd8983";

const char index_html[] PROGMEM = R"rawliteral(
    <!DOCTYPE HTML><html><head>
    <title>ESP Input Form</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    </head><body>
        <ul style = "list-style-type: none;">
            <li>
                <p>Inserire i dati per una nuova tessera</p>
                <form action="/addCard">
                    Nome: <input type="text" name="nome">
                    Cognome: <input type="text" name="cognome">
                    Ruolo: <input type="text" name="ruolo">
                    <input type="submit" value="Submit">
                </form>
            </li>
            <li style = "padding-top: 3%;">
                <p>Limitare il numero di accessi</p>
                <form action="/limitAccess">
                    <select name = "number" id = "number">
                    </select>
                    <input type="submit" value="Submit">
                </form>
            </li>
            <li style = "padding-top: 3%;">
                <p>Cancellare una tessera</p>
                <form action="/deleteCard">
                    <input type="submit" value="Submit">
                </form>
            </li>
        </ul>
    <br>
    </body>
    <script>
        let res = "";
        for(let i = 0; i < 101; ++i) {
            res += "<option>" + i + "</option>";
        }
        document.getElementById("number").innerHTML = res;
    </script>
</html>)rawliteral";

ESP8266WebServer server(80);
WiFiClient wifiClient;
String urlAddCard = "http://192.168.1.9:3000/tessera/nuovaTessera/";
String urlAccess = "http://192.168.1.9:3000/tessera/limitaAccessi/";
String urlDeleteCard ="http://192.168.1.9:3000/tessera/deleteCard/";
byte mac[6];
String macAddress = "";

void setup() {
  delay(6000);
  Serial.begin(115200);
  delay(10);
  connessione();
  setupRouting();
  WiFi.macAddress(mac);

  for(int i = 0; i < 5; ++i) {
      macAddress += mac[i];
      macAddress += ":";
  }
  macAddress += mac[5];
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
    server.on("/", handleHome);
    server.on("/addCard", handleAddCard);
    server.on("/limitAccess", handleAccess);
    server.on("/deleteCard", handleDeleteCard);
    server.begin();
}

void handleHome(){
    server.send(200, "text/html", index_html);
}

void handleAccess() {
  String limit = server.arg("number");

  // scansione del tag nfc

  String uidCard = "000"; // il valore verrà preso dalla scansione dell'NFC
  String fullUrl = urlAccess + /*UID CARD*/ uidCard + limit + macAddress;

  String sendResult = httpRequest(fullUrl);

  server.send(200, "text/html", sendResult);
}

void handleAddCard() {
  String nome = server.arg("nome");
  String cognome = server.arg("cognome");
  String ruolo = server.arg("ruolo");

  // scansione del tag nfc

  String uidCard = "000";

  String fullUrl = urlAddCard + "-" + uidCard + "-" + nome + "-" + cognome + "-" + ruolo + "-" + macAddress;
  String sendResult = httpRequest(fullUrl);

  if(nome != "" && cognome != "" && ruolo != ""){
    server.send(200, "text.html", sendResult);
  }else{
    server.send(200, "text/html", "Form non compilato");
  }
}

void handleDeleteCard() {
  // scansione del tag nfc

  String uidCard = "000";
  String fullUrl = urlDeleteCard + uidCard + "-" + macAddress;
  String sendResult = httpRequest(fullUrl);

  server.send(200, "text/html", sendResult);
}

String httpRequest(String fullUrl) {
  HTTPClient http;

  http.begin(wifiClient, fullUrl.c_str());

  int httpResponseCode = http.GET();

  if(httpResponseCode > 0) {
    String response = "";
    switch (httpResponseCode) {
      case 200:
        response = http.getString();
        break;
      case 404:
        response = "risorsa non disponibile";
      default:
        response = "codice di errore: " + String(httpResponseCode);
        break;
      
      http.end();
      return response;
    }
  }

  http.end();
  return "Response code < 0";
}