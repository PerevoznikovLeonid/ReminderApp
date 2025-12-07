#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

enum ErrorType {
    YearError, MonthError, DayError, HourError, MinutesError
};
enum DAYS {
    BEGIN_DAY = 1, END_DAY_28 = 28, END_DAY_30 = 30, END_DAY_31 = 31
};
enum Times
{
    END_HOUR = 23, END_MINUTES = 59
};

class Time
{
private:
    unsigned int _hour;
    unsigned int _minutes;

    unsigned int checkHour(const unsigned int hour)
    {
        if (hour > Times::END_HOUR) {
            throw ErrorType::HourError;
        }
        return hour;
    }
    unsigned int checkMinutes(const unsigned int minutes)
    {
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

// КЛАСС КОТОРЫЙ ХРАНИТ ДАТУ И ТО ЧТО НАДО СДЕЛАТЬ В ЭТУ ДАТУ
class Reminder
{
private:
    string _reminder;
    Date* _date;
    Time* _time;
public:
    Reminder(const string& reminder, Date *date, Time *time)
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

// ЗАПИСЫВАЕТ НАПОМИНАНИЕ
Reminder addReminderbookmark()
{
    string reminder;
    cout << "Введите напоминание: ";
    getline(cin, reminder);
    bool repeat;

    do {
        repeat = false;


        string temp_input;
        cout << "Введите час: ";
        getline(cin, temp_input);
        const int hour = stoi(temp_input);

        cout << "Введите минуты: ";
        getline(cin, temp_input);
        const int minutes = stoi(temp_input);

        cout << "Введите год: ";
        getline(cin, temp_input);
        const int year = stoi(temp_input);

        cout << "Введите месяц: ";
        getline(cin, temp_input);
        const int month = stoi(temp_input);

        cout << "Введите день: ";
        getline(cin, temp_input);
        const int day = stoi(temp_input);

        try {
            const auto reminderTime = new Time(hour, minutes);
            const auto reminderDate = new Date(day, month, year);
            Reminder result(reminder, reminderDate, reminderTime);
            cout << "Дата запомнена." << endl;
            return result;
        }
        catch (ErrorType error) {
            switch (error) {
                case ErrorType::HourError:
                    cerr << "Неверный час" << endl;
                    break;
                case ErrorType::MinutesError:
                    cerr << "Неверный менута" << endl;
                    break;
                case ErrorType::MonthError:
                    cerr << "Неверный месяц" << endl;
                    break;
                case ErrorType::DayError:
                    cerr << "Неверный день" << endl;
                    break;
                default: ;
            }
            repeat = true;
        }
    } while (repeat);
}
// ВЫВОДИТ СПИСОК НАПОМИНАНИЙ
void print_list(const vector<Reminder>& bookmarks)
{
    for (int i = 0; i < bookmarks.size(); i++)
    {
        cout << i << ": ( Напоминание: " << bookmarks[i].getReminder() <<
        "; Время: "<< bookmarks[i].getTime().getHour()<<":"<< bookmarks[i].getTime().getMinutes()<<
        " Дата: " << bookmarks[i].getDate().getDay() << "." << bookmarks[i].getDate().getMonth() << "." << bookmarks[i].getDate().getYear() << " )" << endl;
    }
}
// УДАЛЯЕТ ЯЧЕЙКИ
void delete_reminder(vector<Reminder>& bookmarks)
{
    string delete_index;
    string request;
    cout << "Введите номер напоминания: ";
    getline(cin, delete_index);
    int request_int = stoi(delete_index);
    if (request_int >= bookmarks.size() or request_int < 0)
    {
        cout << "Вы ввели индекс больше или меньше размера массива" << endl;

        return;
    }
    bookmarks.erase(bookmarks.begin() + stoi(delete_index));
    cout << "Удаление выполнено" << endl;
}

int main()
{
    system("chcp 1251");
    string request;
    vector<Reminder> list_reminder;
    do
    {
        cout << "Хотите добавить напоминание? |0-выход|1-добавить напоминание|2-посмотреть список напоминаний|3-удалить напоминание" << endl;
        getline(cin, request);
        if (request == "1")
        {
            Reminder reminder = addReminderbookmark();
            list_reminder.push_back(reminder);
        }
        else if (request == "2")
        {
            print_list(list_reminder);
        }
        else if (request == "3")
        {
            delete_reminder(list_reminder);
        }
    } while (request != "0");
}