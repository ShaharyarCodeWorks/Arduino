#define BLYNK_TEMPLATE_ID "TMPL6WgIoUAI6"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define DHTPIN D4  // DHT11 data pin
#define DHTTYPE DHT11

char auth[] = "aHYpyPr1stHBc7-mvJd17c-8NCL-dvQU";  // Replace with your Blynk authentication token
char ssid[] = "Shaharyar";      // Replace with your WiFi credentials
char pass[] = "FGFGFGFG";

DHT dht(DHTPIN, DHTTYPE);

// Define Virtual Pins
#define VIRTUAL_PIN_TEMPERATURE V0
#define VIRTUAL_PIN_HUMIDITY V1
#define VIRTUAL_PIN_ON_OFF V2

bool deviceStatus = false;

BLYNK_WRITE(VIRTUAL_PIN_ON_OFF) {
  deviceStatus = param.asInt();
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
}

void loop() {
  Blynk.run();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    if (deviceStatus) {
      // If the device is ON, update gauges with actual sensor values
      Blynk.virtualWrite(VIRTUAL_PIN_TEMPERATURE, temperature); // Virtual Pin V0 for temperature
      Blynk.virtualWrite(VIRTUAL_PIN_HUMIDITY, humidity);    // Virtual Pin V1 for humidity
    } else {
      // If the device is OFF, set gauges to zero
      Blynk.virtualWrite(VIRTUAL_PIN_TEMPERATURE, 0); // Set temperature to zero when OFF
      Blynk.virtualWrite(VIRTUAL_PIN_HUMIDITY, 0);    // Set humidity to zero when OFF
    }
    Blynk.virtualWrite(VIRTUAL_PIN_ON_OFF, deviceStatus);

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C\t");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    if (deviceStatus) {
      // Your code for when the device is ON
      // Add your on logic here
    } else {
      // Your code for when the device is OFF
      // Add your off logic here
    }

    delay(2000); // You can adjust the delay as needed
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }
}
