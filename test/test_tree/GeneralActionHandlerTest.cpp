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

void givenNowInDayInterval_ShouldReturnTrue() {

    bool result1 = service.isDay(DateTime(2025, 10, 5, 7, 0, 0), 6, 0, 0, 1, TimeUnit::h);
    bool result2 = service.isDay(DateTime(2025, 10, 5, 6, 1, 0), 6, 0, 0, 1, TimeUnit::m);
    bool result3 = service.isDay(DateTime(2025, 10, 5, 6, 0, 1), 6, 0, 0, 1, TimeUnit::s);
    bool result4 = service.isDay(DateTime(2025, 10, 5, 6, 59, 59), 6, 0, 0, 1, TimeUnit::h);
    bool result5 = service.isDay(DateTime(2025, 10, 5, 6, 0, 59), 6, 0, 0, 1, TimeUnit::m);
    bool result6 = service.isDay(DateTime(2025, 10, 5, 6, 0, 0), 6, 0, 0, 1, TimeUnit::h);
    bool result7 = service.isDay(DateTime(2025, 10, 5, 6, 0, 0), 6, 0, 0, 1, TimeUnit::m);
    bool result8 = service.isDay(DateTime(2025, 10, 5, 6, 0, 0), 6, 0, 0, 1, TimeUnit::s);

    TEST_ASSERT_TRUE(result1);
    TEST_ASSERT_TRUE(result2);
    TEST_ASSERT_TRUE(result3);
    TEST_ASSERT_TRUE(result4);
    TEST_ASSERT_TRUE(result5);
    TEST_ASSERT_TRUE(result6);
    TEST_ASSERT_TRUE(result7);
    TEST_ASSERT_TRUE(result8);

}

void givenNowNotInDayInterval_ShouldReturnFalse() {

    bool result1 = service.isDay(DateTime(2025, 10, 5, 5, 1, 0), 6, 0, 0, 1, TimeUnit::h);
    bool result2 = service.isDay(DateTime(2025, 10, 5, 5, 1, 0), 6, 0, 0, 1, TimeUnit::m);
    bool result3 = service.isDay(DateTime(2025, 10, 5, 5, 1, 0), 6, 0, 0, 1, TimeUnit::s);

    bool result5 = service.isDay(DateTime(2025, 10, 5, 7, 0, 1), 6, 0, 0, 1, TimeUnit::h);
    bool result6 = service.isDay(DateTime(2025, 10, 5, 6, 1, 1), 6, 0, 0, 1, TimeUnit::m);
    bool result7 = service.isDay(DateTime(2025, 10, 5, 5, 59, 59), 6, 0, 0, 1, TimeUnit::s);

    bool result8 = service.isDay(DateTime(2025, 10, 5, 6, 2, 1), 6, 0, 0, 1, TimeUnit::m);
    bool result9 = service.isDay(DateTime(2025, 10, 5, 6, 0, 2), 6, 0, 0, 1, TimeUnit::s);

    TEST_ASSERT_FALSE(result1);
    TEST_ASSERT_FALSE(result2);
    TEST_ASSERT_FALSE(result3);
    TEST_ASSERT_FALSE(result5);
    TEST_ASSERT_FALSE(result6);
    TEST_ASSERT_FALSE(result7);
    TEST_ASSERT_FALSE(result8);
    TEST_ASSERT_FALSE(result9);

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
    RUN_TEST(givenNowInDayInterval_ShouldReturnTrue);
    RUN_TEST(givenNowNotInDayInterval_ShouldReturnFalse);


    UNITY_END(); // stop unit testing
}

void loop()
{
}