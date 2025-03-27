#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>
#include "OnceADayActionWithStartTimeAndInterval.h"
#include "StartTimeWithInterval.h"

class Light {
private:
    int pin;
    StartTimeWithInterval startTimeWithInterval;
    OnceADayActionWithStartTimeAndInterval actionService;

public:
    // Constructor to initialize the LED pin
    Light(int p, int hour, int minute, int second, int interval, TimeUnit unit) : pin(p), startTimeWithInterval(hour, minute, second, interval, unit), actionService() {
    }

    // Method to turn the LED on
    void on() {
        digitalWrite(pin, LOW);
    }

    // Method to turn the LED off
    void off() {
        digitalWrite(pin, HIGH);
    }

    bool isRunning() {
        int pinState = digitalRead(pin);

        // Check if the button is pressed (HIGH)
        if (pinState == 0) {
          return true;
        } else {
          return false;
        }
    }

    void evaluate(DateTime now) {
        int action = actionService.evaluateForAction(now, startTimeWithInterval, isRunning());
        if (action == 1) {
            on();
        }

        if (action == 0) {
            off();
        }
    }
};

#endif