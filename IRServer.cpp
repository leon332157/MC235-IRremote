#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

#include "webpage.hpp"
#include "password.hpp"

#define NUM_CMD 20


MDNSResponder mdns;
ESP8266WiFiMulti WifiMulti;
#define TIMEOUT 5000


ESP8266WebServer server(80);
#undef HOSTNAME
#define HOSTNAME "esp8266"

const uint16_t IRLed = 16;  // D0 PIN //ESP GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(IRLed);       // Set the GPIO to be used to sending the message.

#define RED 14
#define GREEN 12
#define BLUE 13

inline void blinkLED(uint8_t pin, uint16_t time_ms) {
  digitalWrite(pin, 1);
  //esp_try_delay(time_ms, NULL);
  delay(time_ms);
  digitalWrite(pin, 0);
  delay(time_ms);
}

static char send_buf[4096] = { 0 };
void handleRoot() {
  digitalWrite(BLUE,1);
  snprintf(send_buf,sizeof send_buf, INDEX, WiFi.localIP().toString().c_str(),"");
  server.send(200, "text/html", send_buf);
  digitalWrite(BLUE,0);
}

void handleIr() {
  digitalWrite(BLUE,1);
  if (!server.hasArg("code")) {
    server.send(401, "text/plain", "missing ?code=");
  }
  uint8_t code = server.arg(0).toInt();
  uint16_t msg = 0;
  if (code <= 63) {
    msg = irsend.encodeRC5X(20, code, true);
  } else {
    msg = irsend.encodeRC5X(16, code, true);
  }
  irsend.sendRC5(msg);
  char temp[16];
  snprintf(temp,sizeof temp, "Sent: %x", msg);
  //sprintf(send_buf, PAGE, WiFi.localIP().toString().c_str(),temp);
  server.send(200, "text/html", send_buf);
  digitalWrite(BLUE, 0);
}

void handleRC5X() {
  digitalWrite(BLUE,1);
  bool release = false;
  if (!server.hasArg("dev")) {
    server.send(401, "text/plain", "missing ?dev=");
    return;
  }
  if (!server.hasArg("code")) {
    server.send(401, "text/plain", "missing ?code=");
    return;
  }
  if (server.hasArg("release")) {
    release = true;
  }

  uint16_t dev = server.arg(0).toInt();
  uint64_t code = server.arg(1).toInt();

  uint16_t msg = irsend.encodeRC5X(dev, code, release);
  irsend.sendRC5(msg);
  char temp[16] = { 0 };
  snprintf(temp,sizeof temp, "Sent: %x", msg);
  server.send(200, "text/plain", temp);
  digitalWrite(BLUE,0);
}

void handleRC5() {
  digitalWrite(BLUE,1);
  bool release = false;
  if (!server.hasArg("dev")) {
    server.send(401, "text/plain", "missing ?dev=");
    return;
  }
  if (!server.hasArg("code")) {
    server.send(401, "text/plain", "missing ?code=");
    return;
  }
  if (server.hasArg("release")) {
    release = true;
  }


  uint16_t dev = server.arg(0).toInt();
  uint64_t code = server.arg(1).toInt();

  uint16_t msg = irsend.encodeRC5(dev, code, release);
  irsend.sendRC5(msg);
  char temp[16] = { 0 };
  snprintf(temp,16, "Sent: %x", msg);
  server.send(200, "text/plain", temp);
  digitalWrite(BLUE,0);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
}

void setup(void) {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  irsend.begin();
  Serial.begin(9600, SERIAL_8N1, SERIAL_TX_ONLY);
  while (!Serial) {}
  WiFi.mode(WIFI_STA);
  for (int i = 0; i < NUM_CONN; i++) {
    WifiMulti.addAP(SSID_Arr[i], PASSWORD_Arr[i]);
  }
  
  char buf[16];
  for (uint8_t i = 20; i <= 20; i++) {
    break;
    for (uint8_t j = 0; j <= 127; j++) {
      if (j == 36 || j == 12 || j == 53||j == 45) continue;
      //uint16_t msg = irsend.encodeRC5(i, j, true);
      uint16_t msg = irsend.encodeRC5X(i, j, true);
      sprintf(buf, "i: %d j:%d msg: %x", i, j, msg);
      Serial.println(buf);
      irsend.sendRC5(msg);
      delay(1000);
      //}
    }
  }

  while (1) {
    break;
    char buf[64];
    //uint16_t msg = irsend.encodeRC5(17, 70, true);
    uint16_t msg = irsend.encodeRC5X(20, 26, true);
    //uint16_t msg = 0xd4F;
    //uint16_t msg = 0xc2d;
    sprintf(buf, "msg: %x", msg);
    Serial.println(buf);
    irsend.sendRC5(msg);
    delay(3000);
  }
  if (mdns.begin(HOSTNAME)) {
    Serial.println("MDNS responder started");
    // Announce http tcp service on port 80
    mdns.addService("http", "tcp", 80);
  }
  
  server.on("/", HTTP_GET, handleRoot);
  server.on("/ir",HTTP_GET, handleIr);
  server.on("/rc5x",HTTP_GET, handleRC5X);
  server.on("/rc5",HTTP_GET, handleRC5);
  //server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  mdns.update();
  server.handleClient();
  if (WifiMulti.run(5000) != WL_CONNECTED) {
    blinkLED(RED, 500);
  }
  //if (WiFi.status() == WL_CONNECTED) blinkLED(GREEN, 80);
}
