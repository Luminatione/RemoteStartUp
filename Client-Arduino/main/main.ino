#include <WiFiNINA.h>
#include <WebSocketClient.h>

#include "credential.h"
#include "server-config.h"

#define DEBUGGING

WiFiClient client;
WebSocketClient webSocketClient;

void connectWiFi() {
  Serial.begin(9600);
  while (!Serial);
  if (WiFi.begin(SSID, PASSWORD) == WL_CONNECTED) {
    Serial.print("Connected to ");
    Serial.println(SSID);
    WiFi.setTimeout(3600 * 24 * 1000);
  } else {
    Serial.print("Failed to connected to ");
    Serial.println(SSID);
  }
}

void connectWS()
{
  webSocketClient.path = "/";
  webSocketClient.host = SERVER_IP;
  webSocketClient.protocol = WEB_SOCKET_PROTOCOL;

  if (client.connect(SERVER_IP, SERVER_PORT)) {
    Serial.println("Connected to server");
    if (webSocketClient.handshake(client)) {
      Serial.println("Handshake successful");
      Serial.println(client.connected());
      webSocketClient.sendData("register");
    } else {
      Serial.println("Handshake failed");
      
    }
  } else {
    Serial.println("Failed to connect to server");
    while(1) {
      // Hang on failure
    }
  }
}

void setup() {
  connectWiFi();
  connectWS();
}

void loop() {
  String data;
   webSocketClient.getData(data);

  if (data.length() > 0) {
    Serial.print("Received data: ");
    Serial.println(data);
  }
}