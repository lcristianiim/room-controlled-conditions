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
        pinMode(pin, OUTPUT);
    }

    // Method to turn the LED on
    void on() {
        Serial.println(String(pin));

        digitalWrite(pin, LOW);
        timeOn = rtcManager.getCurrentTime();
    }

    // Method to turn the LED off
    void off() {
        Serial.println(String(pin));

        digitalWrite(pin, HIGH);
        timeOff = rtcManager.getCurrentTime();
    }

    bool isRunning() {
        // this is reversed because the relay is off when pin is 1
        int buttonState = digitalRead(pin);

        if (buttonState == 0) {
          Serial.println(String(buttonState));
          return true;
        } else {
          Serial.println(String(buttonState));
          return false;
        }
    }

    void evaluate(DateTime now) {
        int action = acService.evaluateForAction(now, timeOn, timeOff, startAndStopDurations, isRunning());

        if (action == 1) {
            Serial.println("Turned on");
            on();
        }

        if (action == 0) {
            Serial.println("Turned off");
            off();
        }
    }
};

#endif