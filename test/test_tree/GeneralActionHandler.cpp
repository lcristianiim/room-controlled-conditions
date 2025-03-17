#include <Arduino.h>
#include <unity.h>
#include "RTClib.h"
#include "OnceADayActionWithStartTimeAndInterval.h"
#include "StartTimeWithInterval.h"
#include "classes/GeneralActionHandler.h"

GeneralActionHandler service(30);

void setUp(void) {
}

void givenDayTimeAndTemperatureLessThanSetup_ShouldReturnOne() {
    int result = service.evaluate(true, 29);

    TEST_ASSERT_EQUAL(1, result);
}

void givenDayTimeAndTemperatureMoreThanSetup_ShouldReturnTwo() {
    int result = service.evaluate(true, 31);

    TEST_ASSERT_EQUAL(2, result);
}

void givenDayTimeAndTemperatureEqualThanSetup_ShouldReturnTwo() {
    int result = service.evaluate(true, 30);

    TEST_ASSERT_EQUAL(2, result);
}

void setup()
{
    UNITY_BEGIN();

    RUN_TEST(givenDayTimeAndTemperatureLessThanSetup_ShouldReturnOne);
    RUN_TEST(givenDayTimeAndTemperatureMoreThanSetup_ShouldReturnTwo);
    RUN_TEST(givenDayTimeAndTemperatureEqualThanSetup_ShouldReturnTwo);

    UNITY_END(); // stop unit testing
}

void loop()
{
}