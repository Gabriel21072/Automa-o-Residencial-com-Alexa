#include <ESP8266WiFi.h>   
#include "SinricPro.h"
#include "SinricProSwitch.h"
 
#define WIFI_SSID         ""    // Nome do Wifi
#define WIFI_PASS         ""    // Senha do Wifi
#define APP_KEY           ""      // O seu App Key é algo como "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        ""   // O seu App Secret é algo como "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
 
#define Abajour_ID       ""    // Código Tomada 1
#define Lampada_ID       ""    // Código Tomada 2
#define Regua_ID         ""    // Código Tomada 3
#define Ventilador_ID    ""    // Código Tomada 4
 
 
#define Abajour_Pin 0  // O pino fisico onde está ligado
#define Lampada_Pin 1  // O pino fisico onde está ligado
#define Regua_Pin 2  // O pino fisico onde está ligado
#define Ventilador_Pin 3  // O pino fisico onde está ligado
 
#define BAUD_RATE         9600                // Se precisar, pode trocar o baud rate
 
 
void setupWiFi();
void setupSinricPro();
bool AbajourState(const String &deviceId, bool &state);
bool LampadaState(const String &deviceId, bool &state);
bool ReguaState(const String &deviceId, bool &state);
bool VentiladorState(const String &deviceId, bool &state);
 
 
// main setup function
void setup() {
  setupWiFi();
  setupSinricPro(); 
  pinMode(Abajour_Pin, OUTPUT);
  pinMode(Lampada_Pin, OUTPUT);
  pinMode(Regua_Pin, OUTPUT);
  pinMode(Ventilador_Pin, OUTPUT);
  
  digitalWrite(Abajour_Pin, HIGH);
  digitalWrite(Lampada_Pin, HIGH);
  digitalWrite(Regua_Pin, HIGH);
  digitalWrite(Ventilador_Pin, HIGH);
}
 
void loop() {
  SinricPro.handle();
}
 
 
bool AbajourState(const String &deviceId, bool &state) {
  digitalWrite(Abajour_Pin, !state);
  return true; // request handled properly
}
 
bool LampadaState(const String &deviceId, bool &state) {
  digitalWrite(Lampada_Pin, !state);
  return true; // request handled properly
}
 
bool ReguaState(const String &deviceId, bool &state) {
  digitalWrite(Regua_Pin, !state);
  return true; // request handled properly
}
 
bool VentiladorState(const String &deviceId, bool &state) {
  digitalWrite(Ventilador_Pin, !state);
  return true; // request handled properly
}
 
// setup das conexões Wifi
void setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }
}
 
// setup das funções para o SinricPro
void setupSinricPro() {
  // add devices and callbacks to SinricPro
  SinricProSwitch &mySwitch1 = SinricPro[Abajour_ID];
  mySwitch1.onPowerState(AbajourState);
 
  SinricProSwitch &mySwitch2 = SinricPro[Lampada_ID];
  mySwitch2.onPowerState(LampadaState);
 
  SinricProSwitch &mySwitch3 = SinricPro[Regua_ID];
  mySwitch3.onPowerState(ReguaState);
 
  SinricProSwitch &mySwitch4 = SinricPro[Ventilador_ID];
  mySwitch4.onPowerState(VentiladorState);
 
  // setup SinricPro
  SinricPro.onConnected([](){  }); 
  SinricPro.onDisconnected([](){  });
  SinricPro.begin(APP_KEY, APP_SECRET);
}
