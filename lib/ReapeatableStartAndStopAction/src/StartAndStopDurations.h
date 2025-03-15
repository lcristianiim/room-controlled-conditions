#ifndef START_AND_STAP_DURATIONS_H
#define START_AND_STAP_DURATIONS_H

#include <TimeUnit.h>

class StartAndStopDurations {
    private:
        int start;
        TimeUnit startUnit;
        int end;
        TimeUnit endUnit;

    public:
        StartAndStopDurations(int start, TimeUnit startUnit, int end, TimeUnit endUnit) {
            this->start = start;
            this->startUnit = startUnit;
            this->end = end;
            this->endUnit = endUnit;
        }
};

#endif