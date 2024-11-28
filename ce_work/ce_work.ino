#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <utility/wifi_drv.h>
#include "arduino_secrets.h"

const char* ssid          = SECRET_SSID;
const char* password      = SECRET_PASS;
const char* mqtt_username = SECRET_MQTTUSER;
const char* mqtt_password = SECRET_MQTTPASS;
const char* mqtt_server   = "mqtt.cetools.org";
const int mqtt_port       = 1884;

int status = WL_IDLE_STATUS;

WiFiClient wificlient;
PubSubClient client(wificlient);

// MQTT topic for controlling the light
char mqtt_topic_demo[] = "student/CASA0014/light/29/pixel/";

const int vibrationPin = A0; // Pin for the vibration sensor
const int soundPin = A1;     // Pin for the sound sensor
const int vibrationThreshold = 500; // Vibration threshold value

const int total_pixels = 12; // Total number of pixels in the light setup

int currentColor = 0;  // 0: Red, 1: Green, 2: Blue, 3: White
int r = 0, g = 0, b = 0; // Initial RGB values

unsigned long lastVibrationTime = 0; // Record the last time a vibration was detected
unsigned long lastSoundUpdateTime = 0; // Record the last time sound updated pixels
const unsigned long vibrationDebounceInterval = 1000; // Minimum interval between vibration detections (1 second)
const unsigned long soundUpdateInterval = 1000; // Minimum interval for sound updates (1 second)

int activePixels = 0; // Number of active pixels based on sound level

// Function declarations
void sendmqtt(int pixelID, int r, int g, int b);
void startWifi();
void reconnectMQTT();

void setup() {
  Serial.begin(115200);
  delay(1000);

  // WiFi setup
  startWifi();
  client.setServer(mqtt_server, mqtt_port);

  Serial.println("Setup complete");
}

void loop() {
  // Ensure WiFi is connected
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected, reconnecting...");
    startWifi();
  }

  // Ensure MQTT is connected
  if (!client.connected()) {
    Serial.println("MQTT not connected, reconnecting...");
    reconnectMQTT();
  }

  unsigned long currentTime = millis();

  // Vibration Logic (Control Color)
  int vibrationValue = analogRead(vibrationPin);
  if (vibrationValue > vibrationThreshold && (currentTime - lastVibrationTime > vibrationDebounceInterval)) {
    lastVibrationTime = currentTime; // Update the last detection time
    Serial.print("Vibration detected! Sensor Value: ");
    Serial.println(vibrationValue);

    // Change color
    currentColor = (currentColor + 1) % 4; // Cycle through 4 colors
    switch (currentColor) {
      case 0: r = 255; g = 0; b = 0; break; // Red
      case 1: r = 0; g = 255; b = 0; break; // Green
      case 2: r = 0; g = 0; b = 255; break; // Blue
      case 3: r = 255; g = 255; b = 255; break; // White
    }

    // Update all pixels with the new color
    for (int pixelID = 0; pixelID < total_pixels; pixelID++) {
      sendmqtt(pixelID, r, g, b);
    }
  }

  // Sound Logic (Control Pixel Count)
  if (currentTime - lastSoundUpdateTime > soundUpdateInterval) {
    lastSoundUpdateTime = currentTime; // Update last sound time

    int soundValue = analogRead(soundPin);
    Serial.print("Sound Value: ");
    Serial.println(soundValue);

    if (soundValue < 341) { // Low range (0-340)
      activePixels = 4;
    } else if (soundValue < 682) { // Mid range (341-681)
      activePixels = 8;
    } else { // High range (682-1023)
      activePixels = 12;
    }

    // Update pixels based on active pixel count
    for (int pixelID = 0; pixelID < total_pixels; pixelID++) {
      if (pixelID < activePixels) {
        sendmqtt(pixelID, r, g, b); // Active pixels follow vibration-detected color
      } else {
        sendmqtt(pixelID, 0, 0, 0); // Inactive pixels are turned off
      }
    }
  }

  delay(100); // Short delay to prevent excessive loop execution
}

// Send MQTT message to update light color
void sendmqtt(int pixelID, int r, int g, int b) {
  char mqtt_message[100];
  sprintf(mqtt_message, "{\"pixelid\": %d, \"R\": %d, \"G\": %d, \"B\": %d}", pixelID, r, g, b);
  Serial.println(mqtt_topic_demo);
  Serial.println(mqtt_message);

  if (client.publish(mqtt_topic_demo, mqtt_message)) {
    Serial.println("Message published");
  } else {
    Serial.println("Failed to publish message");
  }
}

void startWifi() {
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnectMQTT() {
  while (!client.connected()) {
    String clientId = "kk";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("MQTT connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

