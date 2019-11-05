#include "arduino_secrets.h"
#include "home_manager.h"

#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define DHTPIN 2     // pin connected to DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define LOOP_DELAY 10000
#define HUMIDITY_NAME "humidity"
#define TEMPERATURE_NAME "temperature"
#define HEAT_INDEX_NAME "heat_index"
#define CELSIUS "°C"

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

bool connected;

float h; // Humidity value
float t; // Temperature value
float hic; // Heat index

char body[200]; // payload

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting...");

    connected = false;

    dht.begin();

    WiFi.hostname("wifi-sensor");
    connectToNetwork();

    connected = true;

    registerThisDevice();
}

void connectToNetwork()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting...");
    }
    Serial.println("Connected!");
}

void registerThisDevice()
{
    Serial.println("Registering device...");
    int result = registerDevice();

    if (result == 1)
    {
        Serial.printf("Device registered");
    }
    else
    {
        Serial.println("WARNING: device not registered");
    }
}

void loop()
{
    if (!connected)
    {
        Serial.println("Device not connected: retry connection...");
        connectToNetwork();
        return;
    }

    if (!isRegistered())
    {
        Serial.println("Device not registered: try registration...");
        registerThisDevice();
    }

    // Wait a few seconds between measurements
    delay(LOOP_DELAY);

    // Read values
    h = dht.readHumidity();
    t = dht.readTemperature();

    // Check if any reads failed
    if (isnan(h) || isnan(t))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Compute heat index
    hic = dht.computeHeatIndex(t, h, false);

    Serial.printf("Humidity: %f\n", h);
    Serial.printf("Temperature: %f °C\n", t);
    Serial.printf("Heat index: %f °C\n", hic);

    int result = sendData(HUMIDITY_NAME, h, "");
    Serial.printf("Result: %d\n", result);
    result = sendData(TEMPERATURE_NAME, t, CELSIUS);
    Serial.printf("Result: %d\n", result);
    result = sendData(HEAT_INDEX_NAME, hic, CELSIUS);
    Serial.printf("Result: %d\n", result);
}
