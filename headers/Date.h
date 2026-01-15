#ifndef REMINDERAPP_MAIN_DATE_H
#define REMINDERAPP_MAIN_DATE_H

#include <chrono>
#include "ErrorTypes.h"

enum DAYS {
    BEGIN_DAY = 1, END_DAY_28 = 28, END_DAY_30 = 30, END_DAY_31 = 31
};

class Date {
    unsigned int _day;
    unsigned int _month;
    unsigned int _year;

    static unsigned int checkMonth(const unsigned int month)
    {
        constexpr int MAX_MONTH = 12;
        constexpr int MIN_MONTH = 1;
        if (month > MAX_MONTH || month < MIN_MONTH) {
            throw errors::MonthError("Invalid month.");
        }
        return month;
    }

    static unsigned int checkDay(const unsigned int day, const unsigned int end) {
        if (day > end || day < DAYS::BEGIN_DAY) {
            throw errors::DayError("Invalid day.");
        }
        return day;
    }

    static unsigned int checkYear(const unsigned int year) {
        const auto now = std::chrono::system_clock::now();
        const auto time = std::chrono::system_clock::to_time_t(now);
        const auto time_local = localtime(&time);
        constexpr int TM_YEAR_BEGIN = 1900;
        if (time_local->tm_year + TM_YEAR_BEGIN > year) {
            throw errors::YearError("Invalid Year");
        }
        return year;
    }

public:
    explicit Date(const unsigned int day = 1, const unsigned int month = 1, const unsigned int year = 1) {
        _month = checkMonth(month);
        _year = checkYear(year);
        switch (month) {
            case 1:
                _day = checkDay(day, DAYS::END_DAY_31);
                break;
            case 2:
                _day = checkDay(day, DAYS::END_DAY_28);
                break;
            case 3:
                _day = checkDay(day, DAYS::END_DAY_31);
                break;
            case 4:
                _day = checkDay(day, DAYS::END_DAY_30);
                break;
            case 5:
                _day = checkDay(day, DAYS::END_DAY_31);
                break;
            case 6:
                _day = checkDay(day, DAYS::END_DAY_30);
                break;
            case 7:
                _day = checkDay(day, DAYS::END_DAY_31);
                break;
            case 8:
                _day = checkDay(day, DAYS::END_DAY_31);
                break;
            case 9:
                _day = checkDay(day, DAYS::END_DAY_30);
                break;
            case 10:
                _day = checkDay(day, DAYS::END_DAY_31);
                break;
            case 11:
                _day = checkDay(day, DAYS::END_DAY_30);
                break;
            case 12:
                _day = checkDay(day, DAYS::END_DAY_31);
                break;
            default:
                throw errors::DayError("Invalid Day.");
        }
    }

    [[nodiscard]] unsigned int getDay() const {
        return _day;
    }

    [[nodiscard]] unsigned int getMonth() const {
        return _month;
    }

    [[nodiscard]] unsigned int getYear() const {
        return _year;
    }

    bool operator==(const Date& other) const {
        return _day == other._day && _month == other._month && _year == other._year;
    }
};

#endif //REMINDERAPP_MAIN_DATE_H