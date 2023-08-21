#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

#define ON_Board_LED 2

#define LED_D8 15

const char* ssid = "";
const char* password = "";

const char *host = "";

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  pinMode(ON_Board_LED, OUTPUT);
  digitalWrite(ON_Board_LED, HIGH);

  pinMode(LED_D8, OUTPUT);
  digitalWrite(LED_D8, LOW);


  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");

    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);

  }

  digitalWrite(ON_Board_LED, HIGH);

  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

}

void loop() {

  HTTPClient http;


  String GetAddress, LinkGet, getData;
  int id = 0;
  GetAddress = "NodeMCU_Get_Database/GetData.php";
  LinkGet = host + GetAddress;
  getData = "ID=" + String(id);
  Serial.println("----------------Connect to Server-----------------");
  Serial.println("Get LED Status from Server or Database");
  Serial.print("Request Link : ");
  Serial.println(LinkGet);
  http.begin(LinkGet);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCodeGet = http.POST(getData);
  String payloadGet = http.getString();
  Serial.print("Response Code : ");
  Serial.println(httpCodeGet);
  Serial.print("Returned data from Server : ");
  Serial.println(payloadGet);

  if (payloadGet == "1") {
    digitalWrite(LED_D8, HIGH);
  }
  if (payloadGet == "0") {
    digitalWrite(LED_D8, LOW);
  }


  Serial.println("----------------Closing Connection----------------");
  http.end();
  Serial.println();
  Serial.println("Please wait 5 seconds for the next connection.");
  Serial.println();
  delay(5000);
}
