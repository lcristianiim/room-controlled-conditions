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

GeneralActionHandler actionHandler;
Ventilator ventilator(ventilatorPin, ventilatorRunFor, ventilatorRunForTimeUnit, ventilatorStopFor, ventilatorStopForTimeUnit);

void redLightOn()
{
  digitalWrite(redLightPin, LOW);
}

void redLightOff()
{
  digitalWrite(redLightPin, HIGH);
}

void yellowLightOn()
{
  digitalWrite(yellowLightPin, LOW);
}

void yellowLightOff()
{
  digitalWrite(yellowLightPin, HIGH);
}

void heaterOn()
{
  digitalWrite(heaterPin, LOW);
}

void heaterOff()
{
  digitalWrite(heaterPin, HIGH);
}

bool isElementRunning(int pin)
{
  int pinState = digitalRead(pin);

  // Check if the button is pressed (HIGH)
  if (pinState == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void setup()

{

#ifndef ESP8266
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB
#endif

  Serial.begin(9600);
  rtcManager.begin();
  sensors.begin();
  delay(1000);


#ifndef ESP8266
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB
#endif

  if (!rtc.begin())
  {
    Serial.println("Could't find RTC");
    Serial.flush();
    while (1)
      delay(10);
  }

  // for some reason this works only from the arduino ide. Check the example
  // from RTClib -> DS1307
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // rtc.adjust(DateTime(2025, 4, 5, 23, 37, 0));

  pinMode(ventilatorPin, OUTPUT);
  pinMode(redLightPin, OUTPUT);
  pinMode(yellowLightPin, OUTPUT);
  pinMode(heaterPin, OUTPUT);

  // ventilator.off();
  // redLightOff();
  // yellowLightOff();
  // heaterOff();
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

float getTemperature()
{
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

void generalFunction()
{
  DateTime now = rtcManager.getCurrentTime();
  printDate(now);

  float temp = getTemperature();
  bool isDay = actionHandler.isDay(now, dayStartHour, dayStartMinute, dayStartSecond, dayInterval, dayIntervalTimeUnit);

  Serial.println("Temperature");
  Serial.println(String(temp));

  ventilator.evaluate(now);
  Serial.println(isDay ? "is day" : "is night");

  if (isDay)
  {
    heaterOff();

    if (temp < 30)
    {
      redLightOn();
      yellowLightOff();
    }
    else
    {
      yellowLightOn();
      redLightOff();
    }
  }
  else
  {
    redLightOff();
    redLightOff();
    heaterOn();
  }
}

void loop()
{
  generalFunction();
  // rtc.adjust(DateTime(2025, 4, 6, 9, 33, 0));

  delay(1000);
}