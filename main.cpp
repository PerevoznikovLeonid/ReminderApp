#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include "headers/Date.h"
#include "headers/Time.h"
#include "headers/Reminder.h"

using namespace std;

// adding a reminder
Reminder addReminderbookmark() {
    string reminder;
    cout << "Set a reminder:" << endl;
    getline(cin, reminder);
    bool repeat;
    do {
        repeat = false;

        string temp_input;
        cout << "Enter the hour:" << endl;
        getline(cin, temp_input);
        const int hour = stoi(temp_input);

        cout << "Enter the minutes:" << endl;
        getline(cin, temp_input);
        const int minutes = stoi(temp_input);

        cout << "Enter the year:" << endl;
        getline(cin, temp_input);
        const int year = stoi(temp_input);

        cout << "Enter the month:" << endl;
        getline(cin, temp_input);
        const int month = stoi(temp_input);

        cout << "Enter the day:" << endl;
        getline(cin, temp_input);
        const int day = stoi(temp_input);

        try {
            Reminder result(reminder,
                new Date(day, month, year),
                new Time(hour, minutes));
            cout << "Reminder added." << endl;
            return result;
        }
        catch (errors::HourError error) {
            cerr << error.what() << endl;
            repeat = true;
        }
        catch (errors::MinutesError error) {
            cerr << error.what() << endl;
            repeat = true;
        }
        catch (errors::YearError error) {
            cerr << error.what() << endl;
            repeat = true;
        }
        catch (errors::MonthError error) {
            cerr << error.what() << endl;
            repeat = true;
        }
        catch (errors::DayError error) {
            cerr << error.what() << endl;
            repeat = true;
        }
    } while (repeat);
}

// prints the entire list
void print_list(const vector<Reminder> &bookmarks) {
    for (int i = 0; i < bookmarks.size(); i++) {
        string day = to_string(bookmarks[i].getDate().getDay());
        if (stoi(day) < 10) {
            const string temp = "0" + day;
            day = temp;
        }
        string month = to_string(bookmarks[i].getDate().getMonth());
        if (stoi(month) < 10) {
            const string temp = "0" + month;
            month = temp;
        }
        string year = to_string(bookmarks[i].getDate().getYear());
        if (stoi(year) < 10) {
            const string temp = "0" + year;
            year = temp;
        }
        string hour = to_string(bookmarks[i].getTime().getHour());
        if (stoi(hour) < 10) {
            const string temp = "0" + hour;
            hour = temp;
        }
        string minutes = to_string(bookmarks[i].getTime().getMinutes());
        if (stoi(minutes) < 10) {
            const string temp = "0" + minutes;
            minutes = temp;
        }

        cout << i << ": ( Reminder: " << bookmarks[i].getReminder() <<
                ", Date: " << day << "." << month << "." << year <<
                ", Time: " << hour << ":" << minutes << " )" << endl;
    }
}

// deleting reminders
void delete_reminder(vector<Reminder> &bookmarks) {
    string delete_index;
    string request;
    cout << "Enter the id of the reminder you want to delete: ";
    getline(cin, delete_index);
    int request_int = stoi(delete_index);
    if (request_int >= bookmarks.size() or request_int < 0) {
        cout << "You entered a non-existent id." << endl;
        return;
    }
    bookmarks.erase(bookmarks.begin() + stoi(delete_index));
    cout << "Reminder deleted succesfully." << endl;
}

void checkReminders(vector<Reminder>& reminder_list) {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    auto time_local = *localtime(&time);

    auto current_date = new Date(time_local.tm_mday, time_local.tm_mon + 1, time_local.tm_year + 1900);
    auto current_time = new Time(time_local.tm_hour, time_local.tm_min);

    vector<int> to_delete;
    for (int i = 0; i < reminder_list.size(); i++) {
        if (reminder_list[i].getDate() == *current_date &&
            reminder_list[i].getTime() == *current_time) {
            cout << "!!! Reminder " << i << ":" << endl;
            cout << "=================" << endl;
            cout << reminder_list[i].getReminder() << endl;
            cout << "=================" << endl;
            to_delete.push_back(i);
            }
    }

    for (auto it = to_delete.rbegin(); it != to_delete.rend(); ++it) {
        reminder_list.erase(reminder_list.begin() + to_delete[*it]);
    }

    delete current_date;
    delete current_time;
}

int main() {
    string request;
    vector<Reminder> list_reminder;

    thread reminderThread([&list_reminder]() {
            while (true) {
                checkReminders(list_reminder);
                this_thread::sleep_for(chrono::seconds(10));
            }
        });

    reminderThread.detach();

    while (request != "exit") {

        cout <<
                "What do you want to do?\n"
                "exit - exit the program | add - add a reminder | view - display a list of reminders | del - delete reminder"
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