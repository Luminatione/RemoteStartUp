#include <WiFiNINA.h>
#include "credential.h"

void connect()
{
  Serial.begin(9600);
  while (!Serial);

  // attempt to connect to WiFi network
  if (WiFi.begin(SSID, PASSWORD) == WL_CONNECTED) {
    Serial.println("Connected to WiFi network");
  } else {
    Serial.println("Failed to connect to WiFi network");
  }
}

void setup() {
  connect();
}

void loop() {
  // your code here
}