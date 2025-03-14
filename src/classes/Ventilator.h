#ifndef VENTILATOR_H
#define VENTILATOR_H

#include <Arduino.h>
#include <classes/ActionWithStartAndInterval.h>
#include <classes/StartTimeWithInterval.h>

class VENTILATOR {
private:
    int pin;
    StartTimeWithInterval startTimeWithInterval;
    ActionWithStartAndInterval actionService;

public:
    VENTILATOR(int p) : pin(p), startTimeWithInterval(21, 3, 0, 1, TimeUnit::m), actionService() {
        pinMode(pin, OUTPUT); // Set the pin as an output
    }

    // Method to turn the LED on
    void on() {
        digitalWrite(pin, HIGH);
    }

    // Method to turn the LED off
    void off() {
        digitalWrite(pin, LOW);
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