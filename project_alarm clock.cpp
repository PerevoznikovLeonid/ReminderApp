#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

enum ErrorType {
    YearError, MonthError, DayError
};
enum DAYS {
    BEGIN_DAY = 1, END_DAY_28 = 28, END_DAY_30 = 30, END_DAY_31 = 31
};

class Date {
private:
    unsigned int _day;
    unsigned int _month;
    unsigned int _year;

    void CheckMonth(int month)
    {
        const int MAX_MONTH = 12;
        const int MIN_MONTH = 1;
        if (month > MAX_MONTH || month < MIN_MONTH) {
            throw ErrorType::MonthError;
        }
    }

    void CheckDay(int day, int end) {
        if (day > end || day < DAYS::BEGIN_DAY) {
            throw ErrorType::DayError;
        }
    }

public:
    void Init(int day, int month, int year) {
        CheckMonth(month);

        switch (month) {
        case 1:
            CheckDay(day, DAYS::END_DAY_31);
            break;
        case 2:
            CheckDay(day, DAYS::END_DAY_28);
            break;
        case 3:
            CheckDay(day, DAYS::END_DAY_31);
            break;
        case 4:
            CheckDay(day, DAYS::END_DAY_30);
            break;
        case 5:
            CheckDay(day, DAYS::END_DAY_31);
            break;
        case 6:
            CheckDay(day, DAYS::END_DAY_30);
            break;
        case 7:
            CheckDay(day, DAYS::END_DAY_31);
            break;
        case 8:
            CheckDay(day, DAYS::END_DAY_31);
            break;
        case 9:
            CheckDay(day, DAYS::END_DAY_30);
            break;
        case 10:
            CheckDay(day, DAYS::END_DAY_31);
            break;
        case 11:
            CheckDay(day, DAYS::END_DAY_30);
            break;
        case 12:
            CheckDay(day, DAYS::END_DAY_31);
            break;
        }

        _day = day;
        _month = month;
        _year = year;

    }

    int GetDay() {
        return _day;
    }

    int GetMonth() {
        return _month;
    }
    int GetYear() {
        return _year;
    }
};

// СТРУКТУРА КОТОРАЯ ХРАНИТ ДАТУ И ТО ЧТО НАДО СДЕЛАТЬ В ЭТУ ДАТУ
struct Reminder
{
    string reminder;
    Date date;
};
// ЗАПИСЫВАЕТ НАПОМИНАНИЕ
Reminder add_reminderbookmark()
{
    Reminder result;
    cout << "Введите напоминание: ";
    getline(cin, result.reminder);
    bool repeat;

    do {
        repeat = false;

        string temp_input;
        cout << "Введите год: ";
        getline(cin, temp_input);
        int year = stoi(temp_input);

        cout << "Введите месяц: ";
        getline(cin, temp_input);
        int month = stoi(temp_input);

        cout << "Введите день: ";
        getline(cin, temp_input);
        int day = stoi(temp_input);

        try {
            result.date.Init(day, month, year);
            cout << "Дата запомнена." << endl;
        }
        catch (ErrorType error) {
            switch (error) {
            case ErrorType::MonthError:
                cerr << "Неверный месяц" << endl;
                break;
            case ErrorType::DayError:
                cerr << "Неверный день" << endl;
                break;
            }
            repeat = true;
        }
    } while (repeat);

    return result;
}
// ВЫВОДИТ СПИСОК НАПОМИНАНИЙ
void print_list(vector<Reminder>& bookmarks)
{
    for (int i = 0; i < bookmarks.size(); i++)
    {
        cout << i << ": ( Напоминание: " << bookmarks[i].reminder << "; Дата: " << bookmarks[i].date.GetDay() << "." << bookmarks[i].date.GetMonth() << "." << bookmarks[i].date.GetYear() << " )" << endl;
    }
}
// УДАЛЯЕТ ЯЧЕЙКИ
void delete_reminder(vector<Reminder>& bookmarks)
{
    string delete_index;
    string request;
    int request_int;
    cout << "Введите номер напоминания: ";
    getline(cin, delete_index);
    request_int = stoi(delete_index);
    if (request_int >= bookmarks.size() or request_int < 0)
    {
        cout << "Вы ввели индекс больше или меньше размера массива" << endl;

        return;
    }
    bookmarks.erase(bookmarks.begin() + stoi(delete_index));
    cout << "Удаление выполнино" << endl;

    return;
}

int main()
{
    system("chcp 1251");

    Reminder reminder;
    string request;
    vector<Reminder> list_reminder;
    do
    {
        cout << "Хотите добавить напоминание? |0-выход|1-добавить напоминание|2-посмотреть список напоминаний|3-удалить напоминание" << endl;
        getline(cin, request);
        if (request == "1")
        {
            reminder = add_reminderbookmark();
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