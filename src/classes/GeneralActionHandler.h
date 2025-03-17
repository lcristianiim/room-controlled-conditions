#ifndef GENERAL_ACTION_HANDLER_H
#define GENERAL_ACTION_HANDLER_H

class GeneralActionHandler
{
private:
    int maxTemperature;
public:
    GeneralActionHandler(int maxTemperature)
    {
        this->maxTemperature = maxTemperature;
    }

    // the 'day' term reffers to when the chickens need light
    // the 'night' term reffers to when the chickens need dark
    int evaluate(bool isDay, float temperature)
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
};

#endif