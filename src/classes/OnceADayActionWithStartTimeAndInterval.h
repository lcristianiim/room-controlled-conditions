#ifndef ActionWithStartAndInterval_H
#define ActionWithStartAndInterval_H

#include <Arduino.h>
#include "RTClib.h"
#include <classes/StartTimeWithInterval.h>


class OnceADayActionWithStartTimeAndInterval
{

private:
    bool isNowAfterStart(DateTime dateTime, int h, int m, int s)
    {
        DateTime specifiedTime(dateTime.year(), dateTime.month(), dateTime.day(), h, m, s);

        return dateTime > specifiedTime;
    }

    bool isInRunningInterval(DateTime dt, int h, int m, int s, int interval, TimeUnit timeUnit)
    {
        switch (timeUnit)
        {
        case TimeUnit::h:
            return handleHour(dt, h, m, s, interval);
            break;

        case TimeUnit::m:
            return handleMinutes(dt, h, m, s, interval);
            break;

        case TimeUnit::s:
            return handleSeconds(dt, h, m, s, interval);
            break;

        default:
            break;
            Serial.println("Handling as default");
            return false;
        }

        Serial.println("Skipping switch and returning false");
        return false;
    }

    bool handleSeconds(DateTime dt, int h, int m, int s, int runningMinutes)
    {
        DateTime startTimeWithSecond(dt.year(), dt.month(), dt.day(), h, m, s);
        DateTime endTimeWithSecond = startTimeWithSecond + TimeSpan(0, 0, 0, runningMinutes);

        return (dt >= startTimeWithSecond && dt <= endTimeWithSecond);
    }

    bool handleMinutes(DateTime dt, int h, int m, int s, int runningMinutes)
    {
        DateTime startTimeWithMinute(dt.year(), dt.month(), dt.day(), h, m, s);
        DateTime endTimeWithMinute = startTimeWithMinute + TimeSpan(0, 0, runningMinutes, 0);

        return (dt >= startTimeWithMinute && dt <= endTimeWithMinute);
    }

    bool handleHour(DateTime dt, int h, int m, int s, int runningMinutes)
    {
        DateTime startTimeWithHour(dt.year(), dt.month(), dt.day(), h, m, s);
        DateTime endTimeWithHour = startTimeWithHour + TimeSpan(0, runningMinutes, 0, 0);

        return (dt >= startTimeWithHour && dt <= endTimeWithHour);
    }

    friend void givenNowAfterStartWithOneSecond_ShouldReturnTrue();
    friend void givenNowAfterStartWithOneMinute_ShouldReturnTrue();
    friend void givenNowAfterStartWithOneHour_ShouldReturnTrue();
    friend void givenNowBeforeStart_ShouldReturnFalse();
    friend void givenNowSameTimeAsStart_ShouldReturnFalse();
    friend void givenNowInsideRunningInterval_ShouldReturnTrue();
    friend void givenNowOutsideTheRunningInterval_ShouldReturnFalse();
    friend void givenNowBeforeStartWithSeconds_ShouldReturnFalse();
    friend void givenNowBeforeStartWithMinutes_ShouldReturnFalse();
    friend void givenNowBeforeStartWithHours_ShouldReturnFalse();


public:
    OnceADayActionWithStartTimeAndInterval()
    {
    }

    int evaluateForAction(DateTime now, StartTimeWithInterval startTimeWithInterval, bool isOn)
    {
        bool isAfter = isNowAfterStart(now, startTimeWithInterval.getHour(), startTimeWithInterval.getMinute(), startTimeWithInterval.getSecond());
        if (isAfter == true)
        {
            bool isInRunningInterv = isInRunningInterval(now, startTimeWithInterval.getHour(), startTimeWithInterval.getMinute(), startTimeWithInterval.getSecond(), startTimeWithInterval.getInterval(), startTimeWithInterval.getTimeUnit());

            if (isInRunningInterv == true && isOn == false)
            {
                return 1;
            }

            if (isInRunningInterv == false && isOn == true)
            {
                return 0;
            }
        }

        return 3;
    };
};

#endif