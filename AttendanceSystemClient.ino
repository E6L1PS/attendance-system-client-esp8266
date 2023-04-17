#include<MFRC522.h>
#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

#define RST_PIN D1
#define SS_PIN D2

//pc setup
const char* ssid = "TP-Link_8CE0";
const char* pass = "33508030";

String postRequest = "http://192.168.0.106:8080/api/v1/attendance/";

//phone setup
const char* ssid_phone = "Xiaomi 11T Pro";
const char* pass_phone = "asdfghjk";

String postRequestPhone = "http://192.168.87.69:8080/api/v1/attendance/";

const char* gateName = "First";

MFRC522 mfrc522(SS_PIN, RST_PIN);

void connectWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Waiting for connection.");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  connectWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Reconnecting...");
    connectWiFi();
  }

  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String uid_;
    uid_ += String(mfrc522.uid.uidByte[1]) + String(mfrc522.uid.uidByte[2]) + String(mfrc522.uid.uidByte[3]) + String(mfrc522.uid.uidByte[4]);
    Serial.print("Card UID: "); 
    Serial.println(uid_.toInt());

    HTTPClient http;
    WiFiClient client;

    http.begin(client, postRequest + uid_ + "/" + gateName);
    int httpCode = http.POST("");

    if (httpCode > 0) {
      Serial.printf("HTTP request success, code %d\n", httpCode);
    } else {
      Serial.printf("HTTP request failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
    delay(5000);
  }
}