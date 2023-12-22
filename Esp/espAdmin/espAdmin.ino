#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WifiClient.h>

// #define GREEN_LED 8
// #define RED_LED 9

const char* ssid     = "AndroidAPc5c2";
const char* password = "routerpw";

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
            <li style = "padding-top: 3%;">
              <p>Visualizzare le timbrature di una tessera</p>
              <form action="/getData">
                  Nome: <input type="text" name="nome">
                  Cognome: <input type="text" name="cognome">
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
String urlAddCard = "http://192.168.68.238:3000/tessera/nuovaTessera/";
String urlAccess = "http://192.168.68.238:3000/tessera/limitaAccessi/";
String urlDeleteCard = "http://192.168.68.238:3000/tessera/deleteCard/";
String urlAddMacAddress = "http://192.168.68.238:3000/macAddress/nuovoMacAddress/";
String urlGetData = "http://192.168.68.238:3000/timbrature/";
byte mac[6];
String macAddress = "";

void setup() {
  Serial.begin(115200);
  // pinMode(GREEN_LED, OUTPUT);
  // pinMode(RED_LED, OUTPUT);
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
    server.on("/macAddress", handleMacAddress);
    server.on("/getData", handleData);
    server.begin();
}

void handleHome(){
    server.send(200, "text/html", index_html);
}

void handleAccess() {
  String limit = server.arg("number");

  // Serial.digitalWrite(GREEN_LED, HIGH);
  // scansione del tag nfc
  // Serial.digitalWrite(GREEN_LED, LOW);

  String uidCard = "500"; // il valore verrà preso dalla scansione dell'NFC
  String fullUrl = urlAccess + /*UID CARD*/ uidCard + "-" + limit + "-" + macAddress;

  String sendResult = httpRequest(fullUrl);

  server.send(200, "text/html", sendResult);
}

void handleAddCard() {
  String nome = server.arg("nome");
  String cognome = server.arg("cognome");
  String ruolo = server.arg("ruolo");

  // scansione del tag nfc

  String uidCard = "500";

  String fullUrl = urlAddCard + uidCard + "-" + nome + "-" + cognome + "-" + ruolo + "-" + macAddress;
  String sendResult = httpRequest(fullUrl);

  server.send(200, "text.html", sendResult);
}

void handleDeleteCard() {
  // scansione del tag nfc

  String uidCard = "500";
  String fullUrl = urlDeleteCard + uidCard + "-" + macAddress;
  String sendResult = httpRequest(fullUrl);

  server.send(200, "text/html", sendResult);
}

void handleMacAddress() {
  if (server.hasArg("plain")== false){
 
    server.send(200, "text/plain", "Body non ricevuto");
    return;
  }
  
  String macAddressNodo = server.arg("plain");
  String fullUrl = urlAddMacAddress + macAddress + "-" + macAddressNodo;
  String sendResult = httpRequest(fullUrl);
  
  server.send(200, "text/html", sendResult);
}

void handleData() {
  String nome = server.arg("nome");
  String cognome = server.arg("cognome");
  String fullUrl = urlGetData + nome + "-" + cognome;

  String result = httpRequest(fullUrl);
  String script = "<script> let arr = " + result + "; let result = ''; for(let i = 0; i < arr.length; ++i) { result += '<tr>' + '<td>' + arr[i]['data'] + '</td>' + '<td>' + arr[i]['orario'] + '</td>' + '</tr>'} document.getElementById('data').innerHTML += result; </script>";
  String index = "<p>Visualizzare le timbrature di una tessera</p> <form action='/getData'> Nome: <input type='text' name='nome'> Cognome: <input type='text' name='cognome'> <input type='submit' value='Submit'></form> <table style = 'padding-top: 3%;' id = 'data'><dr><th>Data</th><th>Orario</th></dr></table>" + script;

  server.send(200, "text/html", index);
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
        break;
      default:
        response = "codice di errore: " + String(httpResponseCode);
        break;
    }

    http.end();
    return response;
  }

  http.end();
  return "Response code < 0";
}