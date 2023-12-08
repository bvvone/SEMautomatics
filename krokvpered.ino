void krokvpered()
{
    stepper.reverse(dir);
    stepper.setTarget(step);                   // ціль step кроків
    Serial.print("Поточна позиція ");
    Serial.println(stepper.getCurrent());      // получить поточну позицію

  if (stepper.ready())            //якщо мотор доїхав до встановленої позиції і зупинився однократно поверне true
    {
        current_position = stepper.getTarget();
        client.publish("stat/stepper", String(current_position));
        Serial.println(stepper.pos);
    }    


}