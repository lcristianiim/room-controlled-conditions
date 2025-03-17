#include <Arduino.h>
#include <unity.h>
#include "RTClib.h"
#include "TimeUnit.h"
#include "StartAndStopDurations.h"
#include "RepeatableStartAndStopAction.h"


RepeatableStartAndStopAction action;

void setUp(void) {

}

void givenTimeOnInIntervalAndIsOnFalse_ShouldReturnOne()
{
    StartAndStopDurations durations(1, TimeUnit::m, 1, TimeUnit::m);
    DateTime now(2025, 10, 5, 14, 30, 1);
    DateTime timeOn(2025, 10, 5, 14, 30, 0);
    DateTime timeOff(2025, 10, 5, 14, 29, 0);
    bool isOn = false;

    int result = action.evaluateForAction(now, timeOn, timeOff, durations, isOn);


    TEST_ASSERT_EQUAL(1, result);
}

void givenTimeOnInIntervalAndIsOnFalseWithDifferentTimeUnits_ShouldReturnOne()
{
    StartAndStopDurations durations(1, TimeUnit::h, 1, TimeUnit::m);
    DateTime now(2025, 10, 5, 14, 30, 1);
    DateTime timeOn(2025, 10, 5, 14, 50, 0);
    DateTime timeOff(2025, 10, 5, 14, 29, 0);
    bool isOn = false;

    int result = action.evaluateForAction(now, timeOn, timeOff, durations, isOn);


    TEST_ASSERT_EQUAL(1, result);
}

void givenTimeOffInIntervalAndIsOnTrue_ShouldReturnZero()
{
    StartAndStopDurations durations(1, TimeUnit::m, 1, TimeUnit::m);
    DateTime now(2025, 10, 5, 14, 30, 1);
    DateTime timeOff(2025, 10, 5, 14, 30, 0);
    DateTime timeOn(2025, 10, 5, 14, 29, 0);
    bool isOn = true;

    int result = action.evaluateForAction(now, timeOn, timeOff, durations, isOn);


    TEST_ASSERT_EQUAL(0, result);
}

void givenTimeOffInIntervalAndIsOnTrueA_ShouldReturnZero()
{
    StartAndStopDurations durations(1, TimeUnit::m, 1, TimeUnit::h);
    DateTime now(2025, 10, 5, 14, 50, 1);
    DateTime timeOn(2025, 10, 5, 14, 29, 0);
    DateTime timeOff(2025, 10, 5, 14, 30, 0);
    bool isOn = true;

    int result = action.evaluateForAction(now, timeOn, timeOff, durations, isOn);


    TEST_ASSERT_EQUAL(0, result);
}

void a() {
    StartAndStopDurations durations(1, TimeUnit::s, 1, TimeUnit::s);
    DateTime now(2025, 3, 15, 18, 41, 50);
    DateTime timeOn(2025, 3, 15, 18, 41, 44);
    DateTime timeOff(2025, 3, 15, 18, 41, 40);
    bool isOn = true;

    int result = action.evaluateForAction(now, timeOn, timeOff, durations, isOn);

    TEST_ASSERT_EQUAL(0, result);
}

void setup()
{
    // delay(1000);
    UNITY_BEGIN();

    RUN_TEST(givenTimeOnInIntervalAndIsOnFalse_ShouldReturnOne);
    RUN_TEST(givenTimeOffInIntervalAndIsOnTrue_ShouldReturnZero);
    RUN_TEST(givenTimeOnInIntervalAndIsOnFalseWithDifferentTimeUnits_ShouldReturnOne);
    RUN_TEST(givenTimeOffInIntervalAndIsOnTrueA_ShouldReturnZero);
    RUN_TEST(a);

    UNITY_END(); // stop unit testing
}

void loop()
{
}