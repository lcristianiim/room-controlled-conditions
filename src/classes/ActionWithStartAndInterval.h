#ifndef ActionWithStartAndInterval_H
#define ActionWithStartAndInterval_H

#include <Arduino.h>
#include "RTClib.h"

class ActionWithStartAndInterval {

public:
    ActionWithStartAndInterval() {
    }

    bool isNowAfterStart(DateTime dateTime, int h, int m, int s)
    {
        DateTime specifiedTime(dateTime.year(), dateTime.month(), dateTime.day(), h, m, s);

        return dateTime > specifiedTime;
    }

    bool isInRunningInterval(DateTime dt, int h, int m, int s, int runningMinutes)
    {
        DateTime startTime(dt.year(), dt.month(), dt.day(), h, m, s);
        DateTime endTime = startTime + TimeSpan(0, 0, runningMinutes, 0);

        return (dt >= startTime && dt <= endTime);
    }

    int evaluateForAction(DateTime now, int startHour, int startMinute, int startSecond, int minutesToRun, bool isOn)
    {
        bool isAfter = isNowAfterStart(now, startHour, startMinute, startSecond);
        if (isAfter == true)
        {
            bool isInRunningInterv = isInRunningInterval(now, startHour, startMinute, startSecond, minutesToRun);

            Serial.println("Is in running inverval: " + String(isInRunningInterv ? "true" : "false"));
            Serial.println("Is on: " + String(isOn ? "true" : "false"));

            if (isInRunningInterv == true && isOn == false)
            {
                Serial.println("Evaluation: " + String(1));
                return 1;
            }

            if (isInRunningInterv == false && isOn == true)
            {
                Serial.println("Evaluation: " + String(0));
                return 0;
            }
        }

        Serial.println("Evaluation: " + String(3));
        return 3;
    };
};

#endif