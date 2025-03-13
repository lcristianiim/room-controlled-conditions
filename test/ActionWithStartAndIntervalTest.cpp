#include <Arduino.h>
#include <unity.h>
#include "RTClib.h"
#include <../src/classes/ActionWithStartAndInterval.h>

ActionWithStartAndInterval service;

void setUp(void) {
    // set stuff up here
}

void isNowAfterStart_GivenNowAfterStart_ShouldReturnTrue() {
    DateTime now(2025, 10, 5, 14, 30, 0);
    bool result = service.isNowAfterStart(now, 14, 29, 59);

    TEST_ASSERT_TRUE(result);
}
void isNowAfterStart_GivenNowBeforeStart_ShouldReturnFalse() {
    DateTime now(2025, 10, 5, 14, 30, 0);
    bool result = service.isNowAfterStart(now, 14, 30, 1);

    TEST_ASSERT_FALSE(result);
}

void isNowAfterStart_GivenNowSameTimeAsStart_ShouldReturnFalse() {
    DateTime now(2025, 10, 5, 14, 30, 0);
    bool result = service.isNowAfterStart(now, 14, 30, 0);

    TEST_ASSERT_FALSE(result);
}

void isInRunningInterval_GivenNowInsideRunningInterval_ShouldReturnTrue() {
    DateTime now(2025, 10, 5, 14, 30, 59);
    bool result = service.isInRunningInterval(now, 14, 30, 0, 1);

    TEST_ASSERT_TRUE(result);
}

void isInRunningInterval_GivenNowOutsideTheRunningInterval_ShouldReturnFalse() {
    DateTime now(2025, 10, 5, 14, 31, 1);
    bool result = service.isInRunningInterval(now, 14, 30, 0, 1);

    TEST_ASSERT_FALSE(result);
}

void evaluateForAction_GivenProperIntervalAndDeviceOff_ShouldReturn1ToTurnItOn() {
    DateTime now(2025, 10, 5, 14, 30, 25);
    int result = service.evaluateForAction(now, 14, 30, 0, 1, false);

    TEST_ASSERT_EQUAL(1, result);
}

void givenNowOutsideIntervalAndDeviceOn_ShouldReturn0ToTurnItOff() {
    DateTime now(2025, 10, 5, 14, 31, 1);
    int result = service.evaluateForAction(now, 14, 30, 0, 1, true);

    TEST_ASSERT_EQUAL(0, result);
}

void setup()
{
    delay(2000); // service delay
    UNITY_BEGIN();

    RUN_TEST(isNowAfterStart_GivenNowAfterStart_ShouldReturnTrue);
    RUN_TEST(isNowAfterStart_GivenNowBeforeStart_ShouldReturnFalse);
    RUN_TEST(isNowAfterStart_GivenNowSameTimeAsStart_ShouldReturnFalse);
    RUN_TEST(isInRunningInterval_GivenNowInsideRunningInterval_ShouldReturnTrue);
    RUN_TEST(isInRunningInterval_GivenNowOutsideTheRunningInterval_ShouldReturnFalse);
    RUN_TEST(evaluateForAction_GivenProperIntervalAndDeviceOff_ShouldReturn1ToTurnItOn);
    RUN_TEST(givenNowOutsideIntervalAndDeviceOn_ShouldReturn0ToTurnItOff);

    UNITY_END(); // stop unit testing
}

void loop()
{
}