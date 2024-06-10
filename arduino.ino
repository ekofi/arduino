#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

//Internet baglantısı
const char* ssid = "kullaniciadi"; 
const char* password = "sifre";

AsyncWebServer server(80);

void setup() {
  Serial.begin(9600);

  // Wi-Fi'ye bağlayalim
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi'ye bağlanıyor...");
  }
  Serial.println("WiFi'ye bağlandı");

  StaticJsonDocument<200> jsonDoc;
  jsonDoc["sensor"] = "DHT11";
  jsonDoc["value"] = 25.5;
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // HTTP POST isteği gönderme
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://localhost:3000/");  // Node.js sunucunuzun IP adresi ve portu
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(jsonString);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("POST isteği başarısız oldu, Hata kodu: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }

void loop() {}