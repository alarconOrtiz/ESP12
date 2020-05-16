#include "ESPAsyncWebServer.h"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void InitServer()
{
   server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

   server.onNotFound([](AsyncWebServerRequest *request) {
      request->send(400, "text/plain", "Not found");
   });

   server.begin();
}

void ProcessRequest(AsyncWebSocketClient *client, String request)
{
   Serial.println(request);
   StaticJsonDocument<200> doc;
   DeserializationError error = deserializeJson(doc, request);
   if (error)
   {
      return;
   }

   String command = doc["command"];
   if (command == "Set")
   {
      setData(client, request);
   }
   if (command == "Get")
   {
      getData(client, request);
   }
}

void setData(AsyncWebSocketClient *client, String request)
{
   StaticJsonDocument<200> doc;
   DeserializationError error = deserializeJson(doc, request);
   if (error)
   {
      return;
   }

   int id = doc["id"];
   bool ledStatus = doc["status"];
   Serial.println(id);
   Serial.println(ledStatus);
}

void getData(AsyncWebSocketClient *client, String request)
{
   String response;
   StaticJsonDocument<300> jsonDoc;
   jsonDoc["id"] = random(0, 10);
   jsonDoc["status"] = random(0, 2);
   serializeJson(jsonDoc, response);

   client->text(response);
}