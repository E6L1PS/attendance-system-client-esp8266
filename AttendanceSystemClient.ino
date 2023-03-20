#include<MFRC522.h>
#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

#define RST_PIN D1
#define SS_PIN D2

const char* ssid = "TP-Link_8CE0";
const char* pass = "33508030";

String postRequest = "http://192.168.0.106:8080/at/add/";

const char* ssid_phone = "Xiaomi 11T Pro";
const char* pass_phone = "asdfghjk";

String postRequestPhone = "http://192.168.87.69:8080/at/add/";

const char* gateName = "First";

MFRC522 mfrc522(SS_PIN, RST_PIN);


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println(F("Ready"));

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting for connection.");
  }
  Serial.println("Connection established.");

}

void loop() {

if(WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    if(mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      String uid_;
      uid_ += String(mfrc522.uid.uidByte[1]) + String(mfrc522.uid.uidByte[2]) + String(mfrc522.uid.uidByte[3]) + String(mfrc522.uid.uidByte[4]);
      Serial.print(F("Card UID: ")); 
      Serial.println(uid_.toInt());
      http.begin(client, postRequest + uid_ + "/" + gateName);

      Serial.println(http.POST(""));    
      http.end();          
      delay(5000);
   }
  } else {
    Serial.println("Error in WiFi connection.");
  }
} 
