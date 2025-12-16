#include <iostream>
#include <vector>
#include <string>
#include "headers/Date.h"
#include "headers/Time.h"
#include "headers/Reminder.h"
#include <locale>

using namespace std;

// adding a reminder
Reminder addReminderbookmark() {
    string reminder;
    cout << "set a reminder: ";
    getline(cin, reminder);
    bool repeat;

    do {
        repeat = false;


        string temp_input;
        cout << "enter the hour: ";
        getline(cin, temp_input);
        const int hour = stoi(temp_input);

        cout << "enter the minutes: ";
        getline(cin, temp_input);
        const int minutes = stoi(temp_input);

        cout << "enter the year: ";
        getline(cin, temp_input);
        const int year = stoi(temp_input);

        cout << "enter the month: ";
        getline(cin, temp_input);
        const int month = stoi(temp_input);

        cout << "enter the day: ";
        getline(cin, temp_input);
        const int day = stoi(temp_input);

        try {
            const auto reminderTime = new Time(hour, minutes);
            const auto reminderDate = new Date(day, month, year);
            Reminder result(reminder, reminderDate, reminderTime);
            cout << "reminder remembered." << endl;
            return result;
        } catch (ErrorType error) {
            switch (error) {
                case ErrorType::HourError:
                    cerr << "wrong hour" << endl;
                    break;
                case ErrorType::MinutesError:
                    cerr << "incorrect minutes" << endl;
                    break;
                case ErrorType::MonthError:
                    cerr << "wrong month" << endl;
                    break;
                case ErrorType::DayError:
                    cerr << "wrong day" << endl;
                    break;
                case ErrorType::YearError:
                    cerr << "wrong year" << endl;
                    break;
                default:
                    cerr << "unknown error";
            }
            repeat = true;
        }
    } while (repeat);
}

// ������� ������ �����������
void print_list(const vector<Reminder> &bookmarks) {
    for (int i = 0; i < bookmarks.size(); i++) {
        cout << i << ": ( Reminder: " << bookmarks[i].getReminder() <<
                "; Time: " << bookmarks[i].getTime().getHour() << ":" << bookmarks[i].getTime().getMinutes() <<
                " Date: " << bookmarks[i].getDate().getDay() << "." << bookmarks[i].getDate().getMonth() << "." <<
                bookmarks[i].getDate().getYear() << " )" << endl;
    }
}

// deleting reminders
void delete_reminder(vector<Reminder> &bookmarks) {
    string delete_index;
    string request;
    cout << "What number do you want to delete under?: ";
    getline(cin, delete_index);
    int request_int = stoi(delete_index);
    if (request_int >= bookmarks.size() or request_int < 0) {
        cout << "you entered a non-existent index" << endl;

        return;
    }
    bookmarks.erase(bookmarks.begin() + stoi(delete_index));
    cout << "the removal is completed" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    // system("chcp 1251");
    string request;
    vector<Reminder> list_reminder;
    while (request != "exit") {
        cout <<
                "what do you want to do?\n"
                "exit-exit the program|add-add a reminder|view-display a list of reminders|del-delete reminder"
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
