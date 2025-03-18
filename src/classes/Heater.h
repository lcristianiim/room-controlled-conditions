
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
        pinMode(pin, OUTPUT);
    }

    void on() {
        digitalWrite(pin, HIGH);
    }

    void off() {
        digitalWrite(pin, LOW);
    }

    bool isOn() {
        int buttonState = digitalRead(pin);

        // Check if the button is pressed (HIGH)
        if (buttonState == HIGH) {
          return true;
        } else {
          return false;
        }
    }

    void evaluate(float temperature, bool isDay, bool isOn()) {
        generalActionHandler.evaluateHeater(temperature, isDay, targetTemp, isOn());
    }
};

#endif