#include <WiFiNINA.h>
#include <WebSocketClient.h>

#include "credential.h"
#include "server-config.h"
#include "errors.h"
#include "config.h"

WiFiClient client;
WebSocketClient webSocketClient;

void errorReset()
{
    Serial.println("Awaitng restart...");
    delay(ON_ERROR_DELAY);
    digitalWrite(RESET_PIN, LOW); 
}

void onError(String message)
{
  Serial.println(message);
  showError();
  errorReset();
}

void connectWiFi() {
  Serial.begin(9600);
  while (!Serial);
  if (WiFi.begin(SSID, PASSWORD) == WL_CONNECTED) {
    Serial.print("Connected to ");
    Serial.println(SSID);
    WiFi.setTimeout(WIFI_CONNECTION_TIMEOUT);
  } else {
    Serial.print("Failed to connected to ");
    Serial.println(SSID);
    showError();
  }
}

void connectWS()
{
  webSocketClient.path = "/";
  webSocketClient.host = SERVER_IP;
  webSocketClient.protocol = WEB_SOCKET_PROTOCOL;

  if (client.connect(SERVER_IP, SERVER_PORT)) 
  {
    Serial.println(SERVER_CONNECTION_SUCCEED);
    if (webSocketClient.handshake(client)) 
    {
      Serial.println(HANDSHAKE_SUCCEED);
      webSocketClient.sendData(BOARD_REGISTER_MESSAGE);
    } 
    else 
    {
      onError(HANDSHAKE_FAILED);
    }
  }
  else 
  {
    onError(SERVER_CONNECTION_FAILED);
  }
}

void configReset()
{
  pinMode(RESET_PIN, OUTPUT); 
  digitalWrite(RESET_PIN, HIGH);
}

void setup() {
  configReset();
  enableErrors();
  connectWiFi();
  connectWS();
}

void loop() {
  String data;
   webSocketClient.getData(data);

  if (data.length() > 0) 
  {
    Serial.print("Received data: ");
    Serial.println(data);
  }
}