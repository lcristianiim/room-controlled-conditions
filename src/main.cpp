#include <Arduino.h>
#include "RTClib.h"
#include <classes/Ventilator.h>
#include <classes/Light.h>
#include <classes/Heater.h>
#include <classes/GeneralActionHandler.h>
#include "RTCManager/GlobalRTCManager.h" 

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int redLightPin = 13;
int yellowLightPin = 12;
int ventilatorPin = 8;
int heaterPin = 7;

int ventilatorRunFor = 1;
TimeUnit ventilatorRunForTimeUnit = TimeUnit::m;
int ventilatorStopFor = 1;
TimeUnit ventilatorStopForTimeUnit = TimeUnit::m;

// Define what a day is. 'Day' is when light is required. 'Night' is when dark is required.
int maxTemperature = 31; // in celsius
int dayStartHour = 22;
int dayStartMinute = 40;
int dayStartSecond = 30;
int dayInterval = 18;
TimeUnit dayIntervalTimeUnit = TimeUnit::h;

Light redLight(redLightPin, dayStartHour, dayStartMinute, dayStartSecond, dayInterval, dayIntervalTimeUnit);
Light yellowLight(yellowLightPin, dayStartHour, dayStartMinute, dayStartSecond, dayInterval, dayIntervalTimeUnit);
Ventilator ventilator(ventilatorPin, ventilatorRunFor, ventilatorRunForTimeUnit, ventilatorStopFor, ventilatorStopForTimeUnit);
Heater heater(heaterPin, 30);

GeneralActionHandler actionHandler;

void setup()
{
  Serial.begin(9600);
  rtcManager.begin();
  sensors.begin();
}

void printCurrentTime(DateTime now)
{
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}

float getTemperature() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

void generalFunction() {
  DateTime now = rtcManager.getCurrentTime();
  // printCurrentTime(now);
  
  
  float temp = getTemperature();
  bool isDay = actionHandler.isDay(now, dayStartHour, dayStartMinute, dayStartSecond, dayInterval, dayIntervalTimeUnit);

  if (isDay) {

    // if heater is on, then turn it off, because it's day time
    if (heater.isOn()) {
      heater.off();
    }

    if (temp < 30) {
      redLight.evaluate(now);
      if (yellowLight.isRunning()) {
        yellowLight.off();
      }
    } else {
      yellowLight.evaluate(now);
      if (redLight.isRunning()) {
        redLight.off();
      }
    }
  } else {
    // if red light is on, then turn if off because it's night time
    if (redLight.isRunning()) {
      redLight.off();
    }

    if (temp < 30) {
      heater.evaluate(temp, isDay);
      if (redLight.isRunning()) {
        redLight.off();
      }
    }
  }
}


void loop() {
  generalFunction();

  delay(1000);
}