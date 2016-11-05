#include "WiFi.h"
#include <ESP8266WiFi.h>

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
}

void loop() {
  // @todo
}
