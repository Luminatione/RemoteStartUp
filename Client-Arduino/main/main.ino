#include <WiFiNINA.h>
#include "credential.h"
#include <simpleRPC.h>

void connect() {
  Serial.begin(9600);
  while (!Serial)
    ;

  // attempt to connect to WiFi network
  if (WiFi.begin(SSID, PASSWORD) == WL_CONNECTED) {
    Serial.println("Connected to WiFi network");
  } else {
    Serial.println("Failed to connect to WiFi network");
  }
}

void test() {
  Serial.println("Called");
}

void setup() {
  connect();
  Serial.begin(9600);
}

void loop() {
  interface(Serial, test, "test method");
}