
//D1(GPIO5) ESP8266 підключаєм до SCL lsd1602
//D2 (GPIO4)ESP8266 підключаємо до SDA lsd1602
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <LiquidCrystal_I2C.h>

const char *WIFI_SSID = "BV";
const char *WIFI_PASSWORD = "0504692700";

const char* MQTT_HOST = "192.168.0.73";
const int   MQTT_PORT = 1883;
const char* MQTT_CLIENT_ID = "ESP8266 NodeMCU";
const char* MQTT_USER = "bvv";
const char* MQTT_PASSWORD = "vaso1965";

const char* TOPIC1 = "ptzm_voltage";
const char* TOPIC2 = "ptzm_current";
const char* TOPIC3 = "ptzm_power";
const char* TOPIC4 = "ptzm_energy";

float value;
float ptzmVoltag;
float ptzmCurrent;
float ptzmPower;
float ptzmEnergy;
String strTopic;

LiquidCrystal_I2C lcd(0x27, 16, 2);  //для NodeMCU звичайно використовується ця адреса, в противному вападку сканером I2C шукаємо адресу в 1-Wire шині
WiFiClient client;
PubSubClient mqttClient(client);

//void callback(char* topic, byte* payload, unsigned int length)
void callback(const char* topic, byte* payload, unsigned int length)
   
       {
             payload[length] = '\0';   //чистим від мусора довжина строчки
             float value = String((char*) payload).toInt();
             Serial.println(topic);
             Serial.println(value);
//           Serial.println(strPayload);  
  
  
  
             String strTopic = String(topic); //получаем название топика
                 if (strTopic == "ptzm_voltage")
                     {
                        ptzmVoltag=value;
                     }
                if (strTopic == "ptzm_current")
                     {
                        ptzmCurrent=value;
                     }
                if (strTopic == "ptzm_power")
                     {
                        ptzmPower=value;
                     }

                if (strTopic == "ptzm_energy")
                    {
                       ptzmEnergy=value;
                    }

                lcd.setCursor(0, 0);            //1 позиція першого рядка
                lcd.print(ptzmVoltag,0);
                lcd.print("v");

                lcd.setCursor(9, 0);            //8 позиція першого рядка
                lcd.print(ptzmCurrent,0);
                lcd.print("a");

                lcd.setCursor(0, 1);            //8 позиція першого рядка
                lcd.print(ptzmPower,0);
                lcd.print("wt");

                lcd.setCursor(9, 1);            //8 позиція першого рядка
                lcd.print(ptzmEnergy,0);
                lcd.print("kwt");

                delay (1000);                 
      
        }

void setup()
       {
           Serial.begin(57600);

           WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
           while (WiFi.status() != WL_CONNECTED) 
                 {
                    delay(500);
                    Serial.print(".");
                 }

           Serial.println("Connected to Wi-Fi");

           mqttClient.setServer(MQTT_HOST, MQTT_PORT);
           mqttClient.setCallback(callback);

           while (!client.connected()) 
                 {
                     if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD )) 
                      {
                         Serial.println("Connected to MQTT broker");
                      } else 
                      
                              {
                                 delay(500);
                                 Serial.print(".");
                              }
                 }

           mqttClient.subscribe(TOPIC1);
           mqttClient.subscribe(TOPIC2);
           mqttClient.subscribe(TOPIC3);
           mqttClient.subscribe(TOPIC4);

           lcd.begin();                 // устанавливаем количество столбцов и строк экрана
           lcd.backlight();             // устанавливаем подсветку

    }

void loop()
    {
         mqttClient.loop();  //запускаємо цикл отримання топиків
    }



    
