#include <Arduino.h>
#include "RTClib.h"
#include <classes/Ventilator.h>
#include <classes/Light.h>
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

void generalFunction() {
  Serial.println("@@@ ===== start");
  DateTime now = rtcManager.getCurrentTime();
  printCurrentTime(now);


  // TODO
  // actionHandler.evaluateLights();


  // light.evaluate(now);
  // ventilator.evaluate(now);

  sensors.requestTemperatures();

  float temp = sensors.getTempCByIndex(0);
  Serial.println();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("°C");

  Serial.println();
  Serial.println("@@@ ===== end");
  Serial.println("""");
}


void loop() {
  // generalFunction();

  delay(1000);
}