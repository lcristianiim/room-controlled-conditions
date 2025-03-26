#ifndef GENERAL_ACTION_HANDLER_H
#define GENERAL_ACTION_HANDLER_H

class GeneralActionHandler
{
private:
public:
    GeneralActionHandler()
    {
    }

    // the 'day' term reffers to when the chickens need light
    // the 'night' term reffers to when the chickens need dark
    int evaluateLights(bool isDay, float temperature)
    {
        if (isDay && temperature < 30) {
            // evaluate red light
            return 1;
        }

        if (isDay && temperature >= 30) {
            // evaluate white light
            return 2;
        }

        return true;
    };

    int evaluateHeater(float temperature, bool isDay, float targetTemp, bool isOn) {
        if (isDay && isOn) {
            return 0;
        }

        if (isDay && !isOn) {
            return 3;
        }

        if (!isDay && (temperature < targetTemp) && !isOn) {
            return 1;
        }

        if (!isDay && (temperature < targetTemp) && isOn) {
            return 3;
        }

        if (!isDay && (temperature > targetTemp) && !isOn) {
            return 3;
        }

        if (!isDay && (temperature > targetTemp) && isOn) {
            return 0;
        }

        return 0;
    }

    bool isDay(DateTime now, int dayStartHour, int dayStartMinute, int dayStartSecond, int dayInterval, TimeUnit unit)
    {

        DateTime start(now.year(), now.month(), now.day(), dayStartHour, dayStartMinute, dayStartSecond);
        DateTime end;

        if (unit == TimeUnit::h) {
            end = (start + TimeSpan(0, dayInterval, 0, 0));
        }

        if (unit == TimeUnit::m) {
            end = (start + TimeSpan(0, 0, dayInterval, 0));
        }

        if (unit == TimeUnit::s) {
            end = (start + TimeSpan(0, 0, 0, dayInterval));
        }


        return (now <= end) && (now >= start);
    };
};

#endif