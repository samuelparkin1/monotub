void test_mode()  
{ 
  //controlling co2 levels
  
  co2_current = analogRead(co2_potiometer); // read from potetiometer
  if (co2_current < co2_lower_range)// if co2 is MORE than minimum co2 turm fan ON
      {
        if (fan_state == HIGH) {
        fan_state = LOW;
        }
      digitalWrite(fan_relay,fan_state);
      }
      
  if (co2_current > co2_upper_range)// if co2 is LESS than maximum humidity turm fan OFF
      {
        if (fan_state == LOW){
        fan_state = HIGH;
        }
      digitalWrite(fan_relay,fan_state);
      }

  //controlling humidity levels
  
  humidity_current = analogRead(humidity_potiometer); // read from potetiometer
  if (humidity_current> humidity_lower_range)// if humidity is MORE than minimum humidity turm fan ON
      {
        if (humidifier_state == HIGH) {
        humidifier_state = LOW;
        }
      digitalWrite(humidifier_relay,humidifier_state);
      }
    
  if (humidity_current< humidity_upper_range)// if humidity is LESS than maximum humidity turm fan OFF
      {
        if (humidifier_state == LOW) {
        humidifier_state = HIGH;
        }
      digitalWrite(humidifier_relay,humidifier_state);
      }

  //controlling temp levels
  
  temp_current = analogRead(temp_potiometer); // read from potetiometer
  if (temp_current > temp_lower_range)// if temp is MORE than minimum temp turm fan ON
      {
        if (temp_state == HIGH) {
        temp_state = LOW;
        }
      digitalWrite(temp_relay,temp_state);
      }
    
  if (temp_current < temp_upper_range)// if temp is LESS than maximum temp turm fan OFF
      {
        if (temp_state == LOW) {
        temp_state = HIGH;
        }
      digitalWrite(temp_relay,temp_state);
      }
    
  Serial.print (fan_state);
  Serial.print (" ");
  Serial.print (co2_current);
  Serial.print (" current co2 ppm.");
  Serial.print (" ");
  Serial.print (co2_setpoint);
  Serial.print (" co2 setpoint.");
  Serial.print (" ");
  Serial.print (co2_lower_range);
  Serial.print (" co2 lower range.");
  Serial.print (" ");
  Serial.print (co2_upper_range);
  Serial.println (" co2 upper range.");

  Serial.print (humidifier_state);
  Serial.print (" ");
  Serial.print (humidity_current);
  Serial.print (" current humidity ppm.");
  Serial.print (" ");
  Serial.print (humidity_setpoint);
  Serial.print (" humidity setpoint.");
  Serial.print (" ");
  Serial.print (humidity_lower_range);
  Serial.print (" humidity lower range.");
  Serial.print (" ");
  Serial.print (humidity_upper_range);
  Serial.println (" co2 upper range.");

  Serial.print (temp_state);
  Serial.print (" ");
  Serial.print (temp_current);
  Serial.print (" current temp ppm.");
  Serial.print (" ");
  Serial.print (temp_setpoint);
  Serial.print (" temp setpoint.");
  Serial.print (" ");
  Serial.print (temp_lower_range);
  Serial.print (" temp lower range.");
  Serial.print (" ");
  Serial.print (temp_upper_range);
  Serial.println (" co2 upper range.");
  
  Serial.println();  

delay(500);
}
