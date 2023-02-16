#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

const char* ssid = "TP-Link_8CE0";
const char* pass = "33508030";

String postRequest = "http://192.168.0.106:8080/at/add/";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting for connection.");
  }
  Serial.println("Connection established.");







    if(WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    int uid = 5;

    http.begin(client, postRequest + uid);

    Serial.println(http.POST(""));
    http.end();
  } else {
    Serial.println("Error in WiFi connection.");
  }
}

void loop() {
  /*
  if(WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    int uid = 5;

    http.begin(client, postRequest + uid);

    Serial.println(http.POST(""));
    http.end();
  } else {
    Serial.println("Error in WiFi connection.");
  }*/
} 
