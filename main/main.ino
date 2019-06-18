#include "DHT.h"

#define DHTPIN 2     // pin connected to DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define LOOP_DELAY 3000

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

float h; // Humidity value
float t; // Temperature value
float hic; // Heat index

void setup() {
  Serial.begin(115200);
  Serial.println(F("Starting..."));

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements
  delay(LOOP_DELAY);

  // Read values
  h = dht.readHumidity();
  t = dht.readTemperature();

  // Check if any reads failed
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index
  hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C Heat index: "));
  Serial.print(hic);
  Serial.println(F("°C "));
}
