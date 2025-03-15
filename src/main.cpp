#include <Arduino.h>
#include "RTClib.h"
#include <classes/Ventilator.h>
#include <classes/Light.h>
#include "RTCManager/RTCManager.h"

RTCManager rtcManager;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
Light light(13, 22, 40, 30, 10, TimeUnit::s);

void setup()
{
  Serial.begin(9600);
  rtcManager.begin();
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
  DateTime now = rtcManager.getCurrentTime();
  printCurrentTime(now);

  light.evaluate(now);
}

void loop() {
  generalFunction();
  delay(1000);
}