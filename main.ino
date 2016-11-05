#include "WiFi.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

StaticJsonBuffer<200> jsonBuffer;
ESP8266WebServer server(80);

void sendSuccessfulResponse() {
  JsonObject& response = jsonBuffer.createObject();
  response["success"] = true;

  char buffer[256];
  response.printTo(buffer, sizeof(buffer));

  server.send(200, "application/json", buffer);
}

void sendFailedResponse(char* message = "", int code = 500) {
  JsonObject& response = jsonBuffer.createObject();
  response["success"] = false;
  if(sizeof(message)) {
    response["error"] = message;
  }

  char buffer[256];
  response.printTo(buffer, sizeof(buffer));

  server.send(code, "application/json", buffer);
}

void handleRoot() {
  sendSuccessfulResponse();
}

void handle404() {
  sendFailedResponse("Page not found.", 404);
}

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("WiFi connected: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.onNotFound(handle404);
  server.begin();
}

void loop() {
  server.handleClient();
}
