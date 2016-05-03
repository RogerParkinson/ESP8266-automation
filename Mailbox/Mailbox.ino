/*

9/4/2016

This is similar to the Possum trap TX. Earth GPIO0 and the ESP8266 will start a connection to the WIFI and send
a GET request to the host, pasing the 'name' as a parameter. The name contains the id of the current
board and the host logs the name and the time. The difference from the possum trap is that we call a different URL.

This runs fine on 3xAA delivering 3.66v, ie with good range. Reaches the furthest possum trap,
but does not reach the gate or the letter box. It does reach the driveway and the extended wifi means
it can now reach the letterbox.
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* myid = "MY_ID";

// WiFi information
const char* ssid     = "MY_SSID";
const char* password = "MY_PASSWORD";

// Remote site information
const char* host = "MY_HOST_IP_ADDRESS";
const int http_port = 80;

ADC_MODE(ADC_VCC); // needed for voltage monitor to work.

WiFiClient client;

volatile int state = HIGH;
volatile int buttonState = 0;
volatile int voltage = 0;
volatile bool voltageReported = LOW;

void isr()
{
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
  client.print(String("GET ") + "http://"+host+"/siren.php?count=1&" + "name=" + myid + " HTTP/1.1\r\n" +
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
  
  // This will send the request to the server
  client.print(String("GET ") + "http://"+host+"/batterylow.php?" + "name=" + myid  + "&battery=" + voltage + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
}
void setup()
{
  Serial.begin(115200);
  pinMode(0, INPUT_PULLUP);
  pinMode(BUILTIN_LED, OUTPUT);
  delay(10);
  attachInterrupt(digitalPinToInterrupt(0), isr, FALLING);
  delay(5000);
  digitalWrite(BUILTIN_LED, HIGH);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

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
  delay(1000);
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


