#ifndef GENERAL_ACTION_HANDLER_H
#define GENERAL_ACTION_HANDLER_H

#include <TimeUnit.h>

class GeneralActionHandler
{
private:
public:
    GeneralActionHandler()
    {
    }

    // the 'day' term reffers to when the chickens need light
    // the 'night' term reffers to when the chickens need dark
    int evaluateLights(bool isDay, float temperature)
    {
        if (isDay && temperature < 30) {
            // evaluate red light
            return 1;
        }

        if (isDay && temperature >= 30) {
            // evaluate white light
            return 2;
        }

        return true;
    };

    int evaluateHeater(float temperature, bool isDay, float targetTemp, bool isOn) {

        if (isDay && isOn) {
            return 0;
        }

        if (isDay && !isOn) {
            return 3;
        }

        if (!isDay && (temperature < targetTemp) && !isOn) {
            return 1;
        }

        if (!isDay && (temperature < targetTemp) && isOn) {
            return 3;
        }

        if (!isDay && (temperature > targetTemp) && !isOn) {
            return 3;
        }

        if (!isDay && (temperature > targetTemp) && isOn) {
            return 0;
        }

        return 0;
    }

    bool isDay(DateTime now, int dayStartHour, int dayStartMinute, int dayStartSecond, int dayInterval, TimeUnit unit)
    {

        DateTime start(now.year(), now.month(), now.day(), dayStartHour, dayStartMinute, dayStartSecond);
        DateTime end = start;

        if (unit == TimeUnit::h) {
            end = (start + TimeSpan(0, dayInterval, 0, 0));
            return (now <= end) && (now >= start);
        }

        if (unit == TimeUnit::m)
        {
            end = (start + TimeSpan(0, 0, dayInterval, 0));
            return (now <= end) && (now >= start);
        }

        if (unit == TimeUnit::s)
        {
            end = (start + TimeSpan(0, 0, 0, dayInterval));
            return (now <= end) && (now >= start);
        }

        return (now <= end) && (now >= start);
    };

    void printDates(DateTime now, DateTime start, DateTime end) {
        Serial.println("Now");
        printCurrentTime(now);

        Serial.println("Start");
        printCurrentTime(start);

        Serial.println("End");
        printCurrentTime(end);
    }

    char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

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
};

#endif