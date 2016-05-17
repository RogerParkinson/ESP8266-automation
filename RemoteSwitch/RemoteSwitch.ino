/*
 * Remote Switch
 * Copyright (c) 2016 Roger Parkinson
 * 
 * This sends a generic message over WIFI to the server if the n/o switch is closed.
 * It sends a battery status messageon startup.
 * Both messages always have the id of the current chip, the type of boot and the battery level.
 * The type of boot changes depending on whether it was from the startup or the n/o switch
 * closing. We light up the blue LED while transmitting. 
 * 
 * Note that to compile you need to edit local_network.h  and add it to this directory: 
 * ~/.arduino15/packages/esp8266/hardware/esp8266/2.0.0/tools/sdk/include
 * 
 * Runs fine on 2xAA batteries delivering just over 3v.
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <local_network.h>

extern "C" {
#include <user_interface.h>
}

#define SLEEP_TIME 0
//#define SLEEP_TIME 1000000 * 20 // 20 seconds
//#define SLEEP_TIME 1000000 * 86400 // 1 day

char myid[15];
// WiFi information
const char* ssid     = local_network_SSID;
const char* password = local_network_PASSWORD;

// Remote site information
const char* host = local_network__HOST;
const int http_port = local_network__PORT;

ADC_MODE(ADC_VCC); // needed for voltage monitor to work.

WiFiClient client;

volatile int voltage = 0;

// Attempt to connect to WiFi
void connectWiFi() {
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
 
  // Turn LED on when we are connected
  digitalWrite(BUILTIN_LED, LOW);
}

void sendEvent(int t) {
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, http_port)) {
    return;
  }
  
  // This will send the request to the server
  client.print(String("GET ") + "http://"+host+"/processevent.php?" + "name=" + myid  + "&type=" + t + "&battery=" + ESP.getVcc() + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
}
 
void setup()
{
  rst_info *resetInfoPtr;
  resetInfoPtr = ESP.getResetInfoPtr();
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  sprintf(myid,"%ld",ESP.getChipId());
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  sendEvent(resetInfoPtr->reason);

  WiFi.disconnect();
  ESP.deepSleep(SLEEP_TIME, WAKE_RF_DEFAULT);
  delay(100);
}

void loop()
{

}

