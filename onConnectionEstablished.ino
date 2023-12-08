// Ця функція викликається, коли все підключено (Wifi і MQTT)
// ПОПЕРЕДЖЕННЯ: ВИ ПОТРІБНО РЕАЛІЗУВАТИ ЦЕ, ЯКЩО ВИКОРИСТОВУЄТЕ EspMQTTClient
void onConnectionEstablished()
{
  //Підпишіться на topic і відобразіть отримане повідомлення на Serial
  client.subscribe("cmnd/stepper", [](const String & payload) 
      {
          Serial.println(payload);
          str = payload;
          step = str.toInt ();
          krokvpered();
      });

// Publish a message to topic
  client.publish("stat/stepper", "Кроковий двигун включився");           // Ви можете активувати прапорець збереження, встановивши для третього параметра значення true
  
  }