#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define pinDHT 14
#define typeDHT DHT22

#define wifi "Wokwi-GUEST"
#define pass ""
#define route "http://127.0.0.1:5000/sensor-data"

DHT dht(pinDHT, typeDHT);

void setup_wifi() {
  WiFi.begin(wifi, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  dht.begin();
  setup_wifi();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000); // this speeds up the simulation

  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(route);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"Temperature\": " + String(temp, 2) + ", \"Humidity\": " + String(humidity, 2) + "}";
    int httpResponseCode = http.POST(payload);

    if(httpResponseCode > 0) {
      Serial.println(httpResponseCode);
      Serial.println(http.getString());
    }
    else {
      Serial.print("Error sending data: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
  else {
    Serial.println("Error Connecting to WiFi");
  }
}
