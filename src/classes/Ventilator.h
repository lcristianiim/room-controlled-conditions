#ifndef VENTILATOR_H
#define VENTILATOR_H

#include <Arduino.h>
#include <classes/ActionWithStartAndInterval.h>

ActionWithStartAndInterval actionService;

class VENTILATOR {
private:
    int pin;
    int startHour = 21;
    int startMinute = 3;
    int startSecond = 0;
    int minutesToRun = 1;

public:
    // Constructor to initialize the LED pin
    VENTILATOR(int p) {
        pin = p;
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
        int action = actionService.evaluateForAction(now, startHour, startMinute, startSecond, minutesToRun, isRunning());
        if (action == 1) {
            on();
        }

        if (action == 0) {
            off();
        }
    }
};

#endif