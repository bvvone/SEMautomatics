#include "EspMQTTClient.h"
#define GS_NO_ACCEL           //прискорення руху ми не використовуємо облегчуємо програму
#define DRIVER_STEP_TIME 10  // меняем задержку на 10 мкс
#include "GyverStepper2.h"

GStepper2 <STEPPER2WIRE> stepper(200, 13, 12, 14);  //кроки на один оберт двигуна (технічний паспорт двигуна), step (GPIO13 (D7)), dir (GPIO12 (D6)), en (GPIO14(D5))

int step = 0;                //кількість кроків 
int current_position = 0;    // поточна позиція
String str;                  //cтрочка для перетворення строкової величини отриманої з MQTT в INT
//int dir = 1;                 //напрямок обертання крокового двигуна
int dir = 0;                 //напрямок обертання крокового двигуна
EspMQTTClient client(
  "BV",
  "0504692700",
  "192.168.0.179",    // MQTT Broker server ip
  "openhabian",       // Можна опустити, якщо не потрыбно
  "vaso1965",         // Можна опустити, якщо не потрыбно
  "ESP_stepper",      // Ім’я клієнта, яке унікально ідентифікує ваш пристрій (TestClient.local)
  1883                // Порт MQTT, за замовчуванням 1883. Цей рядок можна опустити
);

void setup()
{
    Serial.begin(115200);
//  Додаткові функції EspMQTTClient
    client.enableDebuggingMessages();                // Увімкнути повідомлення про налагодження, які надсилаються на послідовний порт
    client.enableHTTPWebUpdater("bvv", "vaso1965" ); // Увімкніть програму веб-оновлення. Користувач і пароль за замовчуванням мають значення MQTTUsername і MQTTPassword.
    onConnectionEstablished();
 

//  stepper.setRunMode(FOLLOW_POS);    //Установка режиму роботи, mode: FOLLOW_POS - рух до позиції setTarget(...) 
    stepper.autoPower(true);           //автоматичне управління живленням, включається при true
    stepper.enable();
//  stepper.setMaxSpeed(100);          //встановити швидкість руху при русі до позиції setTarget() в кроках/сек
    stepper.setSpeed(100);          //встановити швидкість руху при русі до позиції setTarget() в кроках/сек
}

void loop()
   {
      client.loop();
      stepper.tick();   // мотор асинхронно крутиться тут
   } 



