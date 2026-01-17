#ifndef REMINDERAPP_MAIN_REMINDER_H
#define REMINDERAPP_MAIN_REMINDER_H
#include <iostream>
#include <string>
#include <utility>
#include "Date.h"
#include "Time.h"

class Reminder {
    std::string _reminder;
    Date *_date;
    Time *_time;

public:
    Reminder(std::string reminder, Date *date, Time *time)
        : _reminder(std::move(reminder)),
          _date(date),
          _time(time) {
    }

    Reminder(const Reminder& other) {
        _reminder = other._reminder;
        _date = new Date(*other._date);
        _time = new Time(*other._time);
    }

    Reminder& operator=(const Reminder& other) {
        if (this != &other) {
            delete _date;
            delete _time;

            _reminder = other._reminder;
            _date = new Date(*other._date);
            _time = new Time(*other._time);
        }
        return *this;
    }

    ~Reminder() {
        delete _date;
        delete _time;
    }

    [[nodiscard]] std::string getReminder() const {
        return _reminder;
    }

    [[nodiscard]] Date getDate() const {
        return *_date;
    }

    [[nodiscard]] Time getTime() const {
        return *_time;
    }
};

#endif //REMINDERAPP_MAIN_REMINDER_H