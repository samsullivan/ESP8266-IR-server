#include "WiFi.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <IRremoteESP8266.h>

StaticJsonBuffer<200> jsonBuffer;
ESP8266WebServer server(80);
IRsend irsend(4);

void sendSuccessfulResponse() {
  JsonObject& response = jsonBuffer.createObject();
  response["success"] = true;

  char buffer[256];
  response.printTo(buffer, sizeof(buffer));

  server.send(200, "application/json", buffer);
}

void sendFailedResponse(char* message, int code = 500) {
  JsonObject& response = jsonBuffer.createObject();
  response["success"] = false;
  response["error"] = message;

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

void transmitIR(String command) {
  if(command == "power") {
    irsend.sendNEC(0x20DF10EF, 40);
  } else if(command == "input") {
    irsend.sendNEC(0x20DFF40B, 40);
  } else if(command == "play") {
    irsend.sendNEC(0x20DFCC33, 40);
  } else if(command == "pause") {
    irsend.sendNEC(0x20DFEC13, 40);
  } else if(command == "volume up") {
    irsend.sendNEC(0x20DF40BF, 40);
  } else if(command == "volume down") {
    irsend.sendNEC(0x20DFC03F, 40);
  } else if(command == "fast forward") {
    irsend.sendNEC(0x20DFB748, 40);
  } else if(command == "rewind") {
    irsend.sendNEC(0x20DFAC53, 40);
  } else {
    sendFailedResponse("Invalid command for TV.");
    return;
  }
}

void handleTV() {
  String command = server.arg("command");
  transmitIR(command);

  sendSuccessfulResponse();
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
  server.on("/tv", HTTP_POST, handleTV);
  server.onNotFound(handle404);
  server.begin();

  irsend.begin();
}

void loop() {
  server.handleClient();
}
