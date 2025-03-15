#include <Arduino.h>
#include <unity.h>
#include "RTClib.h"
#include "OnceADayActionWithStartTimeAndInterval.h"
#include "StartTimeWithInterval.h"

OnceADayActionWithStartTimeAndInterval service;

void setUp(void) {
    // set stuff up here
}

void givenNowAfterStartWithOneSecond_ShouldReturnTrue() {
    DateTime now(2025, 10, 5, 14, 30, 1);

    bool result = service.isNowAfterStart(now, 14, 30, 0);

    TEST_ASSERT_TRUE(result);
}

void givenNowAfterStartWithOneMinute_ShouldReturnTrue() {
    DateTime now(2025, 10, 5, 14, 31, 0);

    bool result = service.isNowAfterStart(now, 14, 30, 0);

    TEST_ASSERT_TRUE(result);
}

void givenNowAfterStartWithOneHour_ShouldReturnTrue() {
    DateTime now(2025, 10, 5, 15, 30, 0);

    bool result = service.isNowAfterStart(now, 14, 30, 0);

    TEST_ASSERT_TRUE(result);
}

void givenNowBeforeStartWithSeconds_ShouldReturnFalse() {
    DateTime now(2025, 10, 5, 14, 29, 59);
    bool result = service.isNowAfterStart(now, 14, 30, 0);

    TEST_ASSERT_FALSE(result);
}

void givenNowBeforeStartWithMinutes_ShouldReturnFalse() {
    DateTime now(2025, 10, 5, 14, 29, 00);
    bool result = service.isNowAfterStart(now, 14, 30, 0);

    TEST_ASSERT_FALSE(result);
}

void givenNowBeforeStartWithHours_ShouldReturnFalse() {
    DateTime now(2025, 10, 5, 13, 30, 0);
    bool result = service.isNowAfterStart(now, 14, 30, 0);

    TEST_ASSERT_FALSE(result);
}

void givenNowSameTimeAsStart_ShouldReturnFalse() {
    DateTime now(2025, 10, 5, 14, 30, 0);
    bool result = service.isNowAfterStart(now, 14, 30, 0);

    TEST_ASSERT_FALSE(result);
}

void givenNowInsideRunningInterval_ShouldReturnTrue() {
    DateTime now(2025, 10, 5, 14, 30, 59);
    bool result = service.isInRunningInterval(now, 14, 30, 0, 1, TimeUnit::m);

    TEST_ASSERT_TRUE(result);
}

void givenNowOutsideTheRunningInterval_ShouldReturnFalse() {
    DateTime now(2025, 10, 5, 14, 31, 1);
    bool result = service.isInRunningInterval(now, 14, 30, 0, 1, TimeUnit::m);

    TEST_ASSERT_FALSE(result);
}

void givenProperIntervalAndDeviceOff_ShouldReturn1ToTurnItOn() {
    DateTime now(2025, 10, 5, 14, 30, 25);
    Serial.println("Got here");
    StartTimeWithInterval startTimeWithInterval(14, 30, 0, 1, TimeUnit::m);
    int result = service.evaluateForAction(now, startTimeWithInterval, false);

    TEST_ASSERT_EQUAL(1, result);
}

void givenNowOutsideIntervalAndDeviceOn_ShouldReturn0ToTurnItOff() {
    DateTime now(2025, 10, 5, 14, 31, 1);
    StartTimeWithInterval startTimeWithInterval(14, 30, 0, 1, TimeUnit::m);

    int result = service.evaluateForAction(now, startTimeWithInterval, true);

    TEST_ASSERT_EQUAL(0, result);
}

void givenNowOutsideIntervalAndDeviceOn_ShouldReturn0ToTurnItOfff() {
    DateTime now(2025, 3, 12, 22, 56, 1);
    StartTimeWithInterval startTimeWithInterval(22, 55, 0, 1, TimeUnit::m);

    int result = service.evaluateForAction(now, startTimeWithInterval, true);

    TEST_ASSERT_EQUAL(0, result);
}

void setup()
{
    delay(1000); // service delay
    UNITY_BEGIN();

    RUN_TEST(givenNowAfterStartWithOneSecond_ShouldReturnTrue);
    RUN_TEST(givenNowAfterStartWithOneMinute_ShouldReturnTrue);
    RUN_TEST(givenNowAfterStartWithOneHour_ShouldReturnTrue);
    RUN_TEST(givenNowBeforeStartWithSeconds_ShouldReturnFalse);
    RUN_TEST(givenNowBeforeStartWithMinutes_ShouldReturnFalse);
    RUN_TEST(givenNowBeforeStartWithHours_ShouldReturnFalse);
    RUN_TEST(givenNowSameTimeAsStart_ShouldReturnFalse);
    RUN_TEST(givenNowInsideRunningInterval_ShouldReturnTrue);
    RUN_TEST(givenNowOutsideTheRunningInterval_ShouldReturnFalse);
    RUN_TEST(givenProperIntervalAndDeviceOff_ShouldReturn1ToTurnItOn);
    RUN_TEST(givenNowOutsideIntervalAndDeviceOn_ShouldReturn0ToTurnItOff);
    RUN_TEST(givenNowOutsideIntervalAndDeviceOn_ShouldReturn0ToTurnItOfff);

    UNITY_END(); // stop unit testing
}

void loop()
{
}