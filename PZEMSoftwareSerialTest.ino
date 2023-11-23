#include <Arduino.h>
#include <PZEM004Tv30.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

const char* ssid     ="BV";
const char* password = "0504692700";

PZEM004Tv30 pzem(D1, D2); // (RX,TX)connect to TX,RX of PZEM1
PZEM004Tv30 pzem2(D5, D6);  // (RX,TX) connect to TX,RX of PZEM2
PZEM004Tv30 pzem3(D7, D8);  // (RX,TX) connect to TX,RX of PZEM3

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);             //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);             //This line hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid, password);      //Connect to your WiFi router
  Serial.println("");
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
    delay(250);
  }
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.println("Connected to Network/SSID");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

}

void loop() {
  // wait for WiFi connection
  //main energy meter
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf(); 
  Serial.print(voltage);
  Serial.print(current);
  Serial.print(power);
  Serial.print(energy);
  Serial.print(frequency);
  Serial.print(pf);
  //energymeter 2
  float voltage2 = pzem2.voltage();
  float current2 = pzem2.current();
  float power2 = pzem2.power();
  float energy2 = pzem2.energy();
  float frequency2 = pzem2.frequency();
  float pf2 = pzem2.pf();
  Serial.println();
  Serial.print(voltage2);
  Serial.print(current2);
  Serial.print(power2);
  Serial.print(energy2);
  Serial.print(frequency2);
  Serial.print(pf2);
  // energy meter 3
  float voltage3 = pzem3.voltage();
  float current3 = pzem3.current();
  float power3 = pzem3.power();
  float energy3 = pzem3.energy();
  float frequency3 = pzem3.frequency();
  float pf3 = pzem3.pf();
  Serial.println();
  Serial.print(voltage3);
  Serial.print(current3);
  Serial.print(power3);
  Serial.print(energy3);
  Serial.print(frequency3);
  Serial.print(pf3);
  delay(4000);
}
