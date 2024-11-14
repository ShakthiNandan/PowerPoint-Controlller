#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ESP8266_Hotspot";
const char* password = "12345678";

ESP8266WebServer server(80);

const int buttonUp = 12;   // Pin connected to volume up button
const int buttonDown = 14; // Pin connected to volume down button

bool increaseVolume = false;
bool decreaseVolume = false;

void setup() {
  Serial.begin(115200);

  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);

  // Set up ESP8266 as an access point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Define routes for volume control
  server.on("/getVolumeAction", HTTP_GET, []() {
    if (increaseVolume) {
      server.send(200, "text/plain", "increase");
      increaseVolume = false;  // Reset action
    } else if (decreaseVolume) {
      server.send(200, "text/plain", "decrease");
      decreaseVolume = false;  // Reset action
    } else {
      server.send(200, "text/plain", "none");
    }
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Check button states
  if (digitalRead(buttonUp) == LOW) {
    increaseVolume = true;
    delay(500); // debounce delay
  }
  if (digitalRead(buttonDown) == LOW) {
    decreaseVolume = true;
    delay(500); // debounce delay
  }

  server.handleClient();
}
