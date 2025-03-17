#ifndef REPEATABLE_START_AND_STOP_ACTION_H
#define REPEATABLE_START_AND_STOP_ACTION_H

#include <Arduino.h>
#include "RTClib.h"
#include "StartTimeWithInterval.h"
#include "StartAndStopDurations.h"


class RepeatableStartAndStopAction
{

private:
    bool isNowWithinStartInterval(DateTime now, DateTime timeOn, StartAndStopDurations startAndStopDurations) {
        DateTime endOfTimeOn = getEndOfTimeOn(timeOn, startAndStopDurations);

        if (now < endOfTimeOn) {
            return true;
        }

        return false;
    }

    bool isNowWithinEndInterval(DateTime now, DateTime timeOff, StartAndStopDurations startAndStopDurations) {
        DateTime endOfTimeOff = getEndOfTimeOff(timeOff, startAndStopDurations);

        if (now < endOfTimeOff) {
            return true;
        }

        return false;
    }


    DateTime getEndOfTimeOn(DateTime timeOn, StartAndStopDurations startAndStopDurations) {
        switch (startAndStopDurations.getStartTimeUnit())
        {
        case h:
            return addHours(timeOn, startAndStopDurations.getStart());
            break;

        case m:
            return addMinutes(timeOn, startAndStopDurations.getStart());
            break;

        case s:
            return addSeconds(timeOn, startAndStopDurations.getStart());
            break;
        
        default:
            return timeOn;
            break;
        }

        return timeOn;
    };

    DateTime getEndOfTimeOff(DateTime timeOff, StartAndStopDurations startAndStopDurations) {
        switch (startAndStopDurations.getEndTimeUnit())
        {
        case h:
            return addHours(timeOff, startAndStopDurations.getEnd());
            break;

        case m:
            return addMinutes(timeOff, startAndStopDurations.getEnd());
            break;

        case s:
            return addSeconds(timeOff, startAndStopDurations.getEnd());
            break;
        
        default:
            return timeOff;
            break;
        }

        return timeOff;
    };

    int getElapsedTimeInHours(DateTime start, DateTime end)
    {
        return (end.unixtime() - start.unixtime()) / 3600; // 3600 seconds in an hour
    }

    int getElapsedTimeInMinutes(DateTime start, DateTime end)
    {
        return (end.unixtime() - start.unixtime()) / 60; // 60 seconds in a minute
    }

    unsigned long getElapsedTimeInSeconds(DateTime start, DateTime end)
    {
        return end.unixtime() - start.unixtime(); // Difference in seconds
    }

    DateTime addSeconds(DateTime now, unsigned long seconds) {
        return DateTime(now.unixtime() + seconds);
    }

    DateTime addMinutes(DateTime now, unsigned long minutes) {
        return DateTime(now.unixtime() + (minutes * 60));
    }

    DateTime addHours(DateTime now, unsigned long hours) {
        return DateTime(now.unixtime() + (hours * 3600));
    }

public:
    RepeatableStartAndStopAction()
    {
    }

    int evaluateForAction(DateTime now, DateTime timeOn, DateTime timeOff, StartAndStopDurations startAndStopDurations, bool isOn)
    {

        // if (!isOn && isNowWithinStartInterval(now, timeOn, startAndStopDurations)) {
        //     return 1;
        // }

        if (isOn && !isNowWithinStartInterval(now, timeOn, startAndStopDurations)) {
            return 0;
        }

        if (!isOn && !isNowWithinEndInterval(now, timeOff, startAndStopDurations)) {
            return 1;
        }

        return 3;
        // returns 1 for start
        // returns 0 for stop
        // returns 3 for no action
    };
};

#endif