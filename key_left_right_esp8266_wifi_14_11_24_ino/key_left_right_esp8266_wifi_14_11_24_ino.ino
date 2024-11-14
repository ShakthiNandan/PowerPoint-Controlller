#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "qwertyuiop";      
const char* password = "asdfghjkl"; 
const int buttonUp = 14;  // GPIO pin connected to the "left" button
const int buttonDown = 12; // GPIO pin connected to the "right" button

ESP8266WebServer server(80); // Create a web server instance on port 80

bool rightpress = false;
bool leftpress = false;
void setup() {
  Serial.begin(115200);  // Start serial communication for debugging

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to WiFi with IP: ");
  Serial.println(WiFi.localIP());

  // Configure button pins as input with internal pull-up resistors
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);

  // Define routes for volume control
  server.on("/getAction", HTTP_GET, []() {
    if (leftpress) {
      server.send(200, "text/plain", "left");
      leftpress = false;  // Reset action
    } else if (rightpress) {
      server.send(200, "text/plain", "right");
      rightpress = false;  // Reset action
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
    rightpress = true;
    delay(500); // debounce delay
  }
  if (digitalRead(buttonDown) == LOW) {
    leftpress = true;
    delay(500); // debounce delay
  }

  server.handleClient();
}
