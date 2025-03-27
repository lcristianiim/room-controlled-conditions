#ifndef VENTILATOR_H
#define VENTILATOR_H

#include <Arduino.h>
#include "RepeatableStartAndStopAction.h"
#include "StartAndStopDurations.h"
#include "RTCManager/GlobalRTCManager.h" 

class Ventilator {
private:
    int pin;
    StartAndStopDurations startAndStopDurations;
    RepeatableStartAndStopAction acService;
    DateTime timeOn;
    DateTime timeOff;

public:
    Ventilator(int p, int start, TimeUnit startUnit, int stop, TimeUnit stopUnit) : pin(p), startAndStopDurations(start, startUnit, stop, stopUnit), acService() {
    }

    // Method to turn the LED on
    void on() {
        digitalWrite(pin, LOW);
        timeOn = rtcManager.getCurrentTime();
    }

    // Method to turn the LED off
    void off() {
        digitalWrite(pin, HIGH);
        timeOff = rtcManager.getCurrentTime();
    }

    bool isRunning() {
        // this is reversed because the relay is off when pin is 1
        int buttonState = digitalRead(pin);

        if (buttonState == 0) {
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