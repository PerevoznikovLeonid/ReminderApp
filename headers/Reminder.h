#ifndef REMINDERAPP_MAIN_REMINDER_H
#define REMINDERAPP_MAIN_REMINDER_H
#include <iostream>
#include <string>
#include "Date.h"
#include "Time.h"

class Reminder {
private:
    string _reminder;
    Date *_date;
    Time *_time;

public:
    Reminder(const string &reminder, Date *date, Time *time)
        : _reminder(reminder),
          _date(date),
          _time(time) {
    }

    ~Reminder() {
        delete _date;
        delete _time;
    }

    string getReminder() const {
        return _reminder;
    }

    Date getDate() const {
        return *_date;
    }

    Time getTime() const {
        return *_time;
    }
};

#endif //REMINDERAPP_MAIN_REMINDER_H
