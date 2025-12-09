#ifndef REMINDERAPP_MAIN_DATE_H
#define REMINDERAPP_MAIN_DATE_H

#include <iostream>

using namespace std;
enum ErrorType {
    YearError, MonthError, DayError, HourError, MinutesError
};
enum DAYS {
    BEGIN_DAY = 1, END_DAY_28 = 28, END_DAY_30 = 30, END_DAY_31 = 31
};

class Date {
private:
    unsigned int _day;
    unsigned int _month;
    unsigned int _year;

    unsigned int checkMonth(const unsigned int month)
    {
        const int MAX_MONTH = 12;
        const int MIN_MONTH = 1;
        if (month > MAX_MONTH || month < MIN_MONTH) {
            throw ErrorType::MonthError;
        }
    }

    unsigned int checkDay(const unsigned int day, const unsigned int end) {
        if (day > end || day < DAYS::BEGIN_DAY) {
            throw ErrorType::DayError;
        }
        return day;
    }

    //TODO: Добавить проверку на больше текущего года
    unsigned int checkYear(const unsigned int year) {
        // if () {
        //     throw ErrorType::YearError;
        // }
        return year;
    }

public:
    Date(const unsigned int day = 1, const unsigned int month = 1, const unsigned int year = 1) {
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
                throw ErrorType::DayError;
        }
    }

    unsigned int getDay() const {
        return _day;
    }

    unsigned int getMonth() {
        return _month;
    }

    unsigned int getYear() {
        return _year;
    }
};

#endif //REMINDERAPP_MAIN_DATE_H