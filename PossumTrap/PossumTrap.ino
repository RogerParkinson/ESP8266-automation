/*
 * Possum Trap remote sensor
 * Copyright (c) 2016 Roger Parkinson
 * 
 * If GPIO0 is earthed we transmit a message to the host giving our id and the event type.
 * On startup we send a battery level.
 * Every 10 seconds we check the battery level and transmit it if it is low.
 * 
 * Note that to compile you need to edit local_network.h  and add it to this directory: 
 * ~/.arduino15/packages/esp8266/hardware/esp8266/2.0.0/tools/sdk/include
 * 
 * Runs fine on 3xAA batteries delivering 3 to 3.6v. See the eagle PCB for wiring details
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <local_network.h>

char myid[15];
// WiFi information
const char* ssid     = local_network_SSID;
const char* password = local_network_PASSWORD;

// Remote site information
const char* host = local_network__HOST;
const int http_port = local_network__PORT;

ADC_MODE(ADC_VCC); // needed for voltage monitor to work.

WiFiClient client;

volatile int state = HIGH;
volatile int buttonState = 0;
volatile int voltage = 0;
volatile bool voltageReported = LOW;

void isr()
{
  digitalWrite(BUILTIN_LED, LOW);
  delay(500);
  digitalWrite(BUILTIN_LED, HIGH);
  state = !state;
} 
// Attempt to connect to WiFi
void connectWiFi() {
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
 
  // Turn LED on when we are connected
  digitalWrite(BUILTIN_LED, LOW);
}

void sendEvent() {
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, http_port)) {
    return;
  }
  
  // This will send the request to the server
  client.print(String("GET ") + "http://"+host+"/processevent.php?" + "name=" + myid  + "&type=" + 0 + "&param=" + 0 + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
}
void sendBattery() {
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, http_port)) {
    return;
  }
  
  // This will send the battery level request to the server
  client.print(String("GET ") + "http://"+host+"/processevent.php?" + "name=" + myid  + "&type=" + 1 + "&param=" + voltage + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
}
void setup()
{
  Serial.begin(115200);
  pinMode(0, INPUT_PULLUP);
  pinMode(BUILTIN_LED, OUTPUT);
  sprintf(myid,"%ld",ESP.getChipId());
  delay(10);
  attachInterrupt(digitalPinToInterrupt(0), isr, FALLING);
  delay(5000);
  digitalWrite(BUILTIN_LED, HIGH);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  voltage = ESP.getVcc();
  sendBattery();

  WiFi.disconnect();
}

void loop()
{
  if (state != HIGH) {
    connectWiFi();
    sendEvent();
    WiFi.disconnect();
    digitalWrite(BUILTIN_LED, HIGH);
    state = HIGH;
  }
  delay(10000);
  voltage = ESP.getVcc();
  if (voltageReported == LOW) {
    voltage = ESP.getVcc();
    if (voltage < 3000) {
      connectWiFi();
      sendBattery();
      WiFi.disconnect();
      digitalWrite(BUILTIN_LED, HIGH);
      voltageReported = HIGH;
    }
  }

}


