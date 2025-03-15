#ifndef RTCMANAGER_H
#define RTCMANAGER_H

#include <Wire.h>
#include <RTClib.h>

class RTCManager {
public:
    RTCManager(); // Constructor
    void begin(); // Method to initialize the RTC
    DateTime getCurrentTime(); // Method to get the current time

private:
    RTC_DS1307 rtc; // RTC object
};

#endif // RTCMANAGER_H