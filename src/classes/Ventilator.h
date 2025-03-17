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
        pinMode(pin, OUTPUT); // Set the pin as an output
    }

    // Method to turn the LED on
    void on() {
        digitalWrite(pin, HIGH);
        timeOn = rtcManager.getCurrentTime();
    }

    // Method to turn the LED off
    void off() {
        digitalWrite(pin, LOW);
        timeOff = rtcManager.getCurrentTime();
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
        if (timeOn.timestamp() == "2000-01-01T00:00:00") {
            Serial.println("FIRST INITIALIZATION");
            timeOff = now;
            on();
        }
        
        Serial.println("Evaluation triggered with:");
        Serial.print("now: "); Serial.print(now.timestamp());
        Serial.println();
        Serial.print("timeOn: "); Serial.print(timeOn.timestamp());
        Serial.println();
        Serial.print("timeOff: "); Serial.print(timeOff.timestamp());
        Serial.println();
        Serial.print("isRunning() "); Serial.print(isRunning());

        int action = acService.evaluateForAction(now, timeOn, timeOff, startAndStopDurations, isRunning());
        Serial.println();
        Serial.print("Action is: ");
        Serial.print(String(action));

        if (action == 1) {
            on();
        }

        if (action == 0) {
            off();
        }
    }
};

#endif