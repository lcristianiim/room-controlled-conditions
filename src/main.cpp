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
RTC_DS1307 rtc;


char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int redLightPin = 13;
int yellowLightPin = 12;
int ventilatorPin = 8;
int heaterPin = 7;

int ventilatorRunFor = 1;
TimeUnit ventilatorRunForTimeUnit = TimeUnit::m;
int ventilatorStopFor = 10;
TimeUnit ventilatorStopForTimeUnit = TimeUnit::m;

// Define what a day is. 'Day' is when light is required. 'Night' is when dark is required.
int maxTemperature = 30; // in celsius
int dayStartHour = 6;
int dayStartMinute = 0;
int dayStartSecond = 0;
int dayInterval = 16;
TimeUnit dayIntervalTimeUnit = TimeUnit::h;

Light redLight(redLightPin, dayStartHour, dayStartMinute, dayStartSecond, dayInterval, dayIntervalTimeUnit);
Light yellowLight(yellowLightPin, dayStartHour, dayStartMinute, dayStartSecond, dayInterval, dayIntervalTimeUnit);
Ventilator ventilator(ventilatorPin, ventilatorRunFor, ventilatorRunForTimeUnit, ventilatorStopFor, ventilatorStopForTimeUnit);
Heater heater(heaterPin, maxTemperature);

GeneralActionHandler actionHandler;

void setup()
{
  Serial.begin(9600);
  rtcManager.begin();
  sensors.begin();
  delay(2000);

  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // rtc.adjust(DateTime(2025, 1, 21, 12, 47, 0));

  pinMode(ventilatorPin, OUTPUT);
  pinMode(redLightPin, OUTPUT);
  pinMode(yellowLightPin, OUTPUT);
  pinMode(heaterPin, OUTPUT);

  ventilator.off();
  redLight.off();
  yellowLight.off();
  heater.off();
}

void printDate(DateTime now)
{
  char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
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
  printDate(now);
  
  
  float temp = getTemperature();
  bool isDay = actionHandler.isDay(now, dayStartHour, dayStartMinute, dayStartSecond, dayInterval, dayIntervalTimeUnit);

  // Serial.println("======");
  // Serial.println("isDay");
  // Serial.println(isDay ? "on" : "off");
  // Serial.println("======");
  Serial.println("Temperature");
  Serial.println(String(temp));
  // Serial.println("======");
  // Serial.println("Red light");
  // Serial.println(redLight.isRunning() ? "on" : "off");
  // Serial.println("======");
  // Serial.println("White light");
  // Serial.println(yellowLight.isRunning() ? "on" : "off");
  // Serial.println("======");
  // Serial.println("Heater");
  // Serial.println(heater.isOn() ? "on" : "off");
  // Serial.println("======");
  // Serial.println("Ventilator");
  // Serial.println(ventilator.isRunning() ? "on" : "off");
  // Serial.println("======");

  ventilator.evaluate(now);
  Serial.println(isDay ? "is day" : "is night");

  if (isDay) {

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
    if (redLight.isRunning()) {
      redLight.off();
    }

    if (yellowLight.isRunning()) {
      redLight.off();
    }

    heater.evaluate(temp, isDay);
  }
}


void loop() {
  generalFunction();
  delay(1000);
}