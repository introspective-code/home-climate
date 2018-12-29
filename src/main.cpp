#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <ThingSpeak.h>
#include <WiFi.h>

#include "config.h"

#define DHTPIN 16
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");

  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.println("Temperature: ");
  Serial.println(temperature);
  Serial.println("Humidity: ");
  Serial.println(humidity);

  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  delay(30000);
}