#include <Arduino.h>
#include <unity.h>
#include "RTClib.h"
#include "OnceADayActionWithStartTimeAndInterval.h"
#include "StartTimeWithInterval.h"
#include "classes/GeneralActionHandler.h"

GeneralActionHandler service;

void setUp(void) {
}

// lights tests
void givenDayTimeAndTemperatureLessThanSetup_ShouldReturnOne() {
    int result = service.evaluateLights(true, 29);

    TEST_ASSERT_EQUAL(1, result);
}

void givenDayTimeAndTemperatureMoreThanSetup_ShouldReturnTwo() {
    int result = service.evaluateLights(true, 31);

    TEST_ASSERT_EQUAL(2, result);
}

void givenDayTimeAndTemperatureEqualThanSetup_ShouldReturnTwo() {
    int result = service.evaluateLights(true, 30);

    TEST_ASSERT_EQUAL(2, result);
}

// heater tests
void givenDayTimeAndTempBellowTargetAndHeaterOn_ShouldStopHeater() {
    int result = service.evaluateHeater(29.2, true, 30, true);
    TEST_ASSERT_EQUAL(0, result);
}

void givenDayTimeAndTempAboveTargetAndHeaterOn_ShouldStopHeater() {
    int result = service.evaluateHeater(30.1, true, 30, true);
    TEST_ASSERT_EQUAL(0, result);
}

void givenDayTimeAndWhateverTemperatureAndHeaterOff_ShouldDoNothing() {
    int resultA = service.evaluateHeater(29.2, true, 30, false);
    int resultB = service.evaluateHeater(31, true, 30, false);

    TEST_ASSERT_EQUAL(3, resultA);
    TEST_ASSERT_EQUAL(3, resultB);
}


void givenNotDayTimeAndTempBellowTargetAndHeaterOn_ShouldDoNothing() {
    int result = service.evaluateHeater(29.2, false, 30, true);
    TEST_ASSERT_EQUAL(3, result);
}

void givenNotDayTimeAndTempBellowTargetAndHeaterOff_ShouldDoNothing() {
    int result = service.evaluateHeater(29.2, false, 30, false);
    TEST_ASSERT_EQUAL(1, result);
}

void givenNotTimeAndTempAboveTargetAndHeaterOn_ShouldStopHeater() {
    int result = service.evaluateHeater(30.1, false, 30, true);
    TEST_ASSERT_EQUAL(0, result);
}

void setup()
{
    UNITY_BEGIN();

    RUN_TEST(givenDayTimeAndTemperatureLessThanSetup_ShouldReturnOne);
    RUN_TEST(givenDayTimeAndTemperatureMoreThanSetup_ShouldReturnTwo);
    RUN_TEST(givenDayTimeAndTemperatureEqualThanSetup_ShouldReturnTwo);
    RUN_TEST(givenDayTimeAndTempBellowTargetAndHeaterOn_ShouldStopHeater);
    RUN_TEST(givenDayTimeAndTempAboveTargetAndHeaterOn_ShouldStopHeater);
    RUN_TEST(givenNotDayTimeAndTempBellowTargetAndHeaterOn_ShouldDoNothing);
    RUN_TEST(givenNotTimeAndTempAboveTargetAndHeaterOn_ShouldStopHeater);
    RUN_TEST(givenNotDayTimeAndTempBellowTargetAndHeaterOff_ShouldDoNothing);
    RUN_TEST(givenDayTimeAndWhateverTemperatureAndHeaterOff_ShouldDoNothing);


    UNITY_END(); // stop unit testing
}

void loop()
{
}