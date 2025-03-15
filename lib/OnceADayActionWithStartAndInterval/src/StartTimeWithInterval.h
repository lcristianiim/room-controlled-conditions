#ifndef START_TIME_WITH_INTERVAL_H
#define START_TIME_WITH_INTERVAL_H

#include <../lib/OnceADayActionWithStartAndInterval/src/TimeUnit.h>

class StartTimeWithInterval {
    private:
        int h;
        int m;
        int s;
        int interval;
        TimeUnit timeUnit; 

    public:
        StartTimeWithInterval(int h, int m, int s, int interval, TimeUnit timeUnit) {
            this->h = h;
            this->m = m;
            this->s = s;
            this->interval = interval;
            this->timeUnit = timeUnit;
        }

        int getHour() {
            return h;
        }

        int getMinute() {
            return m;
        }
        int getSecond() {
            return s;
        }
        int getInterval() {
            return interval;
        }
        TimeUnit getTimeUnit() {
            return timeUnit;
        }
};

#endif