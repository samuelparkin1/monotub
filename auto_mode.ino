void auto_mode () {
  unsigned long auto_currentMillis = millis();
  if (controller_in_auto_mode == LOW)
  {
    lcd.clear();
    controller_in_auto_mode = HIGH;
    controller_in_sensor_mode = LOW;
    controller_in_test_mode = LOW;
  }
  lcd.setCursor(0, 0);
  lcd.write("Fan ");
  lcd.print(LCD_fan_mode);
  lcd.setCursor(0, 1);
  lcd.write("Humidifer ");
  lcd.print(LCD_humidifier_mode);


  Serial.print(auto_currentMillis - fan_previousMillis);
  Serial.print(" ");
  Serial.print(fan_state);
  Serial.print(" ");
  Serial.print(auto_currentMillis - humidifier_previousMillis);
  Serial.print(" ");
  Serial.print(humidifier_state);
  Serial.print(" ");
  Serial.print(auto_currentMillis - temp_previousMillis);
  Serial.print(" ");
  Serial.println(temp_state);
  Serial.println (" ");

  if (fan_state == HIGH)
  {
    if (auto_currentMillis - fan_previousMillis >= fan_on_interval)
    {
      fan_previousMillis = auto_currentMillis;
      if (fan_state == HIGH)
      {
        fan_state = LOW;
        LCD_fan_mode = "OFF";
      }
      digitalWrite(fan_relay, fan_state);
      delay(500);
    }
  }
  if (fan_state == LOW)
  {
    if (auto_currentMillis - fan_previousMillis >= fan_off_interval)
    {
      fan_previousMillis = auto_currentMillis;
      if (fan_state == LOW)
      {
        fan_state = HIGH;
        LCD_fan_mode = "ON ";
      }
      digitalWrite(fan_relay, fan_state);
      delay(500);
    }
  }
  if (humidifier_state == HIGH)
  {
    if (auto_currentMillis - humidifier_previousMillis >= humidifier_on_interval)
    {
      humidifier_previousMillis = auto_currentMillis;
      if (humidifier_state == HIGH)
      {
        humidifier_state = LOW;
        LCD_humidifier_mode = "OFF";
      }
      digitalWrite(humidifier_relay, humidifier_state);
    }
  }
  if (humidifier_state == LOW)
  {
    if (auto_currentMillis - humidifier_previousMillis >= humidifier_off_interval)
    {
      humidifier_previousMillis = auto_currentMillis;
      if (humidifier_state == LOW)
      {
        humidifier_state = HIGH;
        LCD_humidifier_mode = "ON ";
      }
      digitalWrite(humidifier_relay, humidifier_state);
    }
  }
  if (temp_state == HIGH)
  {
    if (auto_currentMillis - temp_previousMillis >= temp_on_interval)
    {
      temp_previousMillis = auto_currentMillis;
      if (temp_state == HIGH)
      {
        temp_state = LOW;
        LCD_temp_mode = "Off";
      }
      digitalWrite(temp_relay, temp_state);
    }
  }
  if (temp_state == LOW)
  {
    if (auto_currentMillis - temp_previousMillis >= temp_off_interval)
    {
      temp_previousMillis = auto_currentMillis;
      if (temp_state == LOW)
      {
        temp_state = HIGH;
        LCD_temp_mode = "On";
      }
      digitalWrite(temp_relay, temp_state);
    }
  }
}
