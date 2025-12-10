#ifndef REMINDERAPP_MAIN_TIME_H
#define REMINDERAPP_MAIN_TIME_H

#include <ctime>
using namespace std;


enum Times {
    END_HOUR = 23, END_MINUTES = 59
};

class Time {
private:
    unsigned int _hour;
    unsigned int _minutes;

    unsigned int checkHour(const unsigned int hour) {
        if (hour > Times::END_HOUR) {
            throw ErrorType::HourError;
        }
        return hour;
    }

    unsigned int checkMinutes(const unsigned int minutes) {
        if (minutes > Times::END_MINUTES) {
            throw ErrorType::MinutesError;
        }
        return minutes;
    }

public:
    Time(const int hour = 0, const int minutes = 0) {
        _hour = checkHour(hour);
        _minutes = checkMinutes(minutes);
    }

    unsigned int getHour() const {
        return _hour;
    }

    unsigned int getMinutes() const {
        return _minutes;
    }
};




#endif //REMINDERAPP_MAIN_TIME_H
