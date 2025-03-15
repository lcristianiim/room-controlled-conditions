#ifndef VENTILATOR_H
#define VENTILATOR_H

#include <Arduino.h>
#include "RepeatableStartAndStopAction.h"
#include "StartAndStopDurations.h"
#include "RTClib.h"

RTC_DS1307 rtc;

class Ventilator {
private:
    int pin;
    StartAndStopDurations startAndStopDurations;
    RepeatableStartAndStopAction acService;
    DateTime timeOn;
    DateTime timeOff;

public:
    Ventilator(int p, int start, TimeUnit startUnit, int stop, TimeUnit stopUnit) : pin(p), startAndStopDurations(start, startUnit, stop, stopUnit), acService() {
        pinMode(pin, OUTPUT); // Set the pin as an output
    }

    // Method to turn the LED on
    void on() {
        digitalWrite(pin, HIGH);
        timeOn = rtc.now();
    }

    // Method to turn the LED off
    void off() {
        digitalWrite(pin, LOW);
        timeOff = rtc.now();
    }

    bool isRunning() {
        int buttonState = digitalRead(pin);

        // Check if the button is pressed (HIGH)
        if (buttonState == HIGH) {
          return true;
        } else {
          return false;
        }
    }

    void evaluate(DateTime now) {
        int action = acService.evaluateForAction(now, timeOn, timeOff, startAndStopDurations, isRunning());
        if (action == 1) {
            on();
        }

        if (action == 0) {
            off();
        }
    }
};

#endif