#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "config.h"
#include "Server.hpp"

ESP8266WebServer server(80);


void setup(void) {
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(WiFi.status());
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
 

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) 
{
  server.handleClient();
}
