
#ifndef HEATER_H
#define HEATER_H

#include <Arduino.h>
#include "RTCManager/GlobalRTCManager.h" 
#include <classes/GeneralActionHandler.h>



class Heater {
private:
    int pin;
    float targetTemp;
    GeneralActionHandler generalActionHandler;

public:
    Heater(int p, float targetTemp) : generalActionHandler() {
        // pinMode(pin, OUTPUT);
    }

    void on() {
        digitalWrite(pin, LOW);
    }

    void off() {
        digitalWrite(pin, HIGH);
    }

    bool isOn() {
        int buttonState = digitalRead(pin);

        // Check if the button is pressed (HIGH)
        if (buttonState == 0) {
          return true;
        } else {
          return false;
        }
    }

    void evaluate(float temperature, bool isDay) {
        int result = generalActionHandler.evaluateHeater(temperature, isDay, targetTemp, isOn());
        if (result == 1) {
            on();
        }

        if (result == 0) {
            off();
        }
    }
};

#endif