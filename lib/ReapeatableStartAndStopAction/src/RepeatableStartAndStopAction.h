#ifndef REPEATABLE_START_AND_STOP_ACTION_H
#define REPEATABLE_START_AND_STOP_ACTION_H

#include <Arduino.h>
#include "RTClib.h"
#include "StartTimeWithInterval.h"
#include "StartAndStopDurations.h"


class RepeatableStartAndStopAction
{

private:


public:
    RepeatableStartAndStopAction()
    {
    }

    int evaluateForAction(DateTime now, DateTime timeOn, DateTime timeOff, StartAndStopDurations startAndStopDurations, bool isOn)
    {
        // returns 1 for start
        // returns 0 for stop
        // returns 3 for no action
    };
};

#endif