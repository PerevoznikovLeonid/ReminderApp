#ifndef REMINDERAPP_MAIN_TIME_H
#define REMINDERAPP_MAIN_TIME_H

#include "ErrorTypes.h"

enum Times {
    END_HOUR = 23, END_MINUTES = 59
};

class Time {
private:
    unsigned int _hour;
    unsigned int _minutes;

    static unsigned int checkHour(const unsigned int hour) {
        if (hour > Times::END_HOUR) {
            throw errors::HourError("Invalid hour.");
        }
        return hour;
    }

    static unsigned int checkMinutes(const unsigned int minutes) {
        if (minutes > Times::END_MINUTES) {
            throw errors::MinutesError("Invalid minutes.");
        }
        return minutes;
    }

public:
    explicit Time(const int hour = 0, const int minutes = 0) {
        _hour = checkHour(hour);
        _minutes = checkMinutes(minutes);
    }

    [[nodiscard]] unsigned int getHour() const {
        return _hour;
    }

    [[nodiscard]] unsigned int getMinutes() const {
        return _minutes;
    }

    bool operator==(const Time& other) const {
        return _hour == other._hour && _minutes == other._minutes;
    }
};




#endif //REMINDERAPP_MAIN_TIME_H