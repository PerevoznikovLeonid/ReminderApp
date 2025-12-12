#include <iostream>
#include <vector>
#include <string>
#include "headers/Date.h"
#include "headers/Time.h"
#include "headers/Reminder.h"
#include <locale>

using namespace std;

// ЗАПИСЫВАЕТ НАПОМИНАНИЕ
Reminder addReminderbookmark() {
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
        } catch (ErrorType error) {
            switch (error) {
                case ErrorType::HourError:
                    cerr << "Неверный час" << endl;
                    break;
                case ErrorType::MinutesError:
                    cerr << "Неверная минута" << endl;
                    break;
                case ErrorType::MonthError:
                    cerr << "Неверный месяц" << endl;
                    break;
                case ErrorType::DayError:
                    cerr << "Неверный день" << endl;
                    break;
                case ErrorType::YearError:
                    cerr << "Неверный год" << endl;
                    break;
                default:
                    cerr << "Неизвестная ошибка";
            }
            repeat = true;
        }
    } while (repeat);
}

// ВЫВОДИТ СПИСОК НАПОМИНАНИЙ
void print_list(const vector<Reminder> &bookmarks) {
    for (int i = 0; i < bookmarks.size(); i++) {
        cout << i << ": ( Напоминание: " << bookmarks[i].getReminder() <<
                "; Время: " << bookmarks[i].getTime().getHour() << ":" << bookmarks[i].getTime().getMinutes() <<
                " Дата: " << bookmarks[i].getDate().getDay() << "." << bookmarks[i].getDate().getMonth() << "." <<
                bookmarks[i].getDate().getYear() << " )" << endl;
    }
}

// УДАЛЯЕТ ЯЧЕЙКИ
void delete_reminder(vector<Reminder> &bookmarks) {
    string delete_index;
    string request;
    cout << "Введите номер напоминания: ";
    getline(cin, delete_index);
    int request_int = stoi(delete_index);
    if (request_int >= bookmarks.size() or request_int < 0) {
        cout << "Вы ввели индекс больше или меньше размера массива" << endl;

        return;
    }
    bookmarks.erase(bookmarks.begin() + stoi(delete_index));
    cout << "Удаление выполнено" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    // system("chcp 1251");
    string request;
    vector<Reminder> list_reminder;
    while (request != "exit") {
        cout <<
                "Хотите добавить напоминание?\n"
                "exit-выход|add-добавить напоминание|view-посмотреть список напоминаний|del-удалить напоминание"
                << endl;
        getline(cin, request);
        if (request == "add") {
            Reminder reminder = addReminderbookmark();
            list_reminder.push_back(reminder);
        } else if (request == "view") {
            print_list(list_reminder);
        } else if (request == "del") {
            delete_reminder(list_reminder);
        }
    }
}
