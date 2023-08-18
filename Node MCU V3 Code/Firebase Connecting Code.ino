#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "iot-led-cube-project-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "tIOUhaDKqrNcky2sTxBVlRFuy21G84NRdIVFrloX"
#define WIFI_SSID "컴과고보다는 부소마고"
#define WIFI_PASSWORD "dongwook"
int fireStatus = 0;

void setup(){
    Serial.begin(115200);
    pinMode(D1, OUTPUT);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.println("Connected.");
    Serial.println(WiFi.localIP());
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.set("LED1", 0);
}

void loop(){
    fireStatus = Firebase.getInt("LED1");
    if (fireStatus == 1){
        Serial.println("Led Turned ON");
        digitalWrite(D1, HIGH);
    }
    else{
        Serial.println("Led Turned OFF");
        digitalWrite(D1, LOW);
    }
}
