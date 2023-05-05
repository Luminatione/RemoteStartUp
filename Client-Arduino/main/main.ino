#include <WiFiNINA.h>
#include <WebSocketClient.h>

#include "credential.h"
#include "server-config.h"
#include "errors.h"
#include "config.h"

WiFiClient client;
WebSocketClient webSocketClient;

int timeElapsed = 0;

void restart()
{
    Serial.println("Awaitng restart...");
    delay(ON_ERROR_DELAY);
    digitalWrite(RESET_PIN, LOW); 
}

void onError(String message)
{
  Serial.println(message);
  showError();
  restart();
}

void connectWiFi()
{
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
  pinMode(CONTROL_PIN, OUTPUT);
  configReset();
  enableErrors();
  connectWiFi();
  connectWS();
}

void onNotify()
{
    digitalWrite(CONTROL_PIN, HIGH);
    delay(CONTROL_PIN_HIGH_TIME);
    digitalWrite(CONTROL_PIN, LOW);
}

void onUnknowData(String data)
{
  Serial.print(UNKNOW_DATA_MESSAGE);
  Serial.println(data);
  
}

void proccessData(String data)
{
  if(data == BOARD_NOTIFY_MESSAGE)
  {
    return onNotify();
  }
  if(data == BOARD_RESTART_MESSAGE)
  {
    return restart();
  }
  onUnknowData(data);
}

void loop() {
  if(millis() > RESET_TIME)
  {
    restart();
  }

  String data;
  webSocketClient.getData(data);
  proccessData(data);
}