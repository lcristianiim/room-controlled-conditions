// RTCManager.cpp
#include "RTCManager.h"

RTCManager::RTCManager() {
    // Constructor
}

void RTCManager::begin() {
    #ifndef ESP8266
    while (!Serial)
        ; // wait for serial port to connect. Needed for native USB
    #endif

    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1)
        delay(10);
    }

    // Check if the RTC is running
    if (!rtc.isrunning()) {
        Serial.println("RTC lost power, setting the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set to compile time
    }
}

DateTime RTCManager::getCurrentTime() {
    return rtc.now(); // Return the current time
}