#include <Wire.h>
#include <Arduino.h>
#include "SparkFun_SCD30_Arduino_Library.h" //
#include "DFRobot_LCD.h"
SCD30 airSensor; // include SCD30 sensor

// controller modes
int controller_in_auto_mode = LOW;
int controller_in_sensor_mode = LOW;
int controller_in_test_mode = LOW;
int current_controller_mode = LOW; 

// Variables
int fan_state = LOW; // fan state.
int humidifier_state = LOW; // humidifier state.
int temp_state = LOW; // temp controller state.

//LCD display
DFRobot_LCD lcd(16, 2); //16 characters and 2 lines of show
String LCD_fan_mode = "Off";
String LCD_humidifier_mode = "Off";
String LCD_temp_mode = "Off";

// test mode
int test_mode_state = LOW;

// Time Variables
unsigned long sensor_previousMillis = 0; //time since last reading.
unsigned long fan_previousMillis = 0; //Fan ON/OFF interval timer.
unsigned long humidifier_previousMillis = 0; //humidifier ON/OFF interval timer.
unsigned long temp_previousMillis = 0; //temp ON/OFF interval timer.

//sensor variables
const int sensor_fail_Time = 10000; //after 10 seconds sensor is deamed in fail state

// Auto mode Variables
const long fan_on_interval = 5000; //Co2 fan to turn on for 5 secs.
const long fan_off_interval = 100000; //Co2 fan to turn on for 10 mins.
const long humidifier_on_interval = 10000; //humidifier to turn on for 10 secs.
const long humidifier_off_interval = 300000; //humidifier to turn on for 30 mins.
const long temp_on_interval = 10000; //Temperture controller to turn on for 10 secs.
const long temp_off_interval = 60000; //Temperture controller to turn off for 60 secs.

//Digital Input variables
const int testing_mode_input =5; // bridge input to start testing mode with potentiometer

// Analog Input Variables
int co2_potiometer = A0; // Analog input pin 0 for Co2 potentiometer
int humidity_potiometer = A1; // Analog input pin 1 for humidity potentiometer
int temp_potiometer = A2; // Analog input pin 2 for temperature potentiometer

//Digital Output variables
const int fan_relay = 10; // digital output for co2 fan relay
const int humidifier_relay = 11; // digital output for humidifier relay
const int temp_relay = 12; // digital output for Temperture controller relay
const int testing_mode_output = 3; //testing pin to supply 5DC for testing pin input.
const int ledPin = LED_BUILTIN;

//Co2 Variables
int co2_setpoint = 800; // set point for Co2 to be 800 ppm
float co2_deviation_percentage = .02; //a setpoint divation of 2%
int co2_upper_range = (co2_setpoint + (co2_setpoint*co2_deviation_percentage)); // calculated co2 upper range
int co2_lower_range = (co2_setpoint - (co2_setpoint*co2_deviation_percentage)); // calculated co2 lower range
int co2_current = 0; //co2 current reading

//Humidity Variables
int humidity_setpoint = 80; // set point for humidity to be 80%
float humidity_deviation_percentage = .02; //a humidity setpoint divation of 2%
int humidity_upper_range = (humidity_setpoint + (humidity_setpoint*humidity_deviation_percentage)); // calculated humidity upper range
int humidity_lower_range = (humidity_setpoint - (humidity_setpoint*humidity_deviation_percentage)); // calculated humidity upper range
int humidity_current = 0; //humidity current reading

//Temperature Variables
int temp_setpoint = 25; // set point for Temperture controller to be 25 degress
float temp_deviation_percentage = .10; //a Temperture controller setpoint divation of 10%
int temp_upper_range = (temp_setpoint + (temp_setpoint*temp_deviation_percentage)); // calculated Temperture controller upper range
int temp_lower_range = (temp_setpoint - (temp_setpoint*temp_deviation_percentage)); // calculated Temperture controller upper range
int temp_current = 0; //Temperture controller current reading


void setup()
{
  lcd.init(); // start up LCD Display
  lcd.print("STARTING MONOTUB CONTROLLER");
  Serial.begin(115200); // start up serial monitor in 115200 buadrate
  Serial.println("STARTING MONOTUB CONTROLLER"); // print startup line.
  Wire.begin(); // begin wire communication

  // set the digital pin inputs.
  pinMode(testing_mode_input, INPUT); // secifiy testing input

  // set the digital pin as output:
  pinMode(ledPin, OUTPUT); // secify Arduino borads LED as output
  pinMode(fan_relay, OUTPUT); // secify digital output for co2 fan relay
  digitalWrite(fan_relay, LOW);
  pinMode(humidifier_relay, OUTPUT); // secify digital output for humidifier fan relay
  digitalWrite(humidifier_relay, LOW);
  pinMode(temp_relay, OUTPUT); // secify digital output for tempeurture controler relay
  digitalWrite(temp_relay, LOW);
  pinMode(testing_mode_output, OUTPUT); // secify digital output to power testing input

  // set testing digital output high:
  digitalWrite(testing_mode_output, HIGH); // turn on testing output.

  //test if sensor is working correctly
  if (airSensor.begin() == false) // verifies if communication with SCD30 sensor isn't respoding.
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FAULT----SCD30 sensor not detected.");
    lcd.command(0x18);
    Serial.println("FAULT----SCD30 sensor not detected. Please check wiring. "); // serial montior to display fault
    //delay(10000) // redudent code
    ;
  }
  delay(5000);
}

void loop()
{
  unsigned long sensor_currentMillis = millis();
  test_mode_state = digitalRead(testing_mode_input);
  if (test_mode_state == HIGH)
    sensor_mode();

    

  else {
    if (airSensor.dataAvailable())
    { sensor_previousMillis = sensor_currentMillis;
      sensor_mode();
    }
    else {
      //Serial.println (sensor_currentMillis - sensor_previousMillis);
      if (sensor_currentMillis - sensor_previousMillis >= sensor_fail_Time)
      {
        auto_mode ();
      }
    }

    delay(00);
  }
}
