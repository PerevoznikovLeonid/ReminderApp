#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <fstream>
#include "headers/Date.h"
#include "headers/Time.h"
#include "headers/Reminder.h"

using namespace std;
const string TXT_FILE = "reminders.txt";

// Function to save list to text file
void saveToTxt(const vector<Reminder>& list_reminder) {
    ofstream file(TXT_FILE);
    if (!file.is_open()) {
        cout << "Error creating file " << TXT_FILE << endl;
        return;
    }

    cout << "Saving " << list_reminder.size() << " reminders to " << TXT_FILE << endl;

    for (int i = 0; i < list_reminder.size(); i++) {
        file << "id:" << i << " reminder:\""
             << list_reminder[i].getReminder() << "\" day:"
             << list_reminder[i].getDate().getDay() << " month:"
             << list_reminder[i].getDate().getMonth() << " year:"
             << list_reminder[i].getDate().getYear() << " hour:"
             << list_reminder[i].getTime().getHour() << " minutes:"
             << list_reminder[i].getTime().getMinutes() << endl;
    }
    file.close();
    cout << "List saved to " << TXT_FILE << endl;
}

// Function to load list from text file
void loadFromTxt(vector<Reminder>& list_reminder) {
    ifstream file(TXT_FILE);
    if (!file.is_open()) {
        cout << "File " << TXT_FILE << " not found, starting with empty list." << endl;
        return;
    }

    list_reminder.clear();
    string line;
    int loaded_count = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;

        cout << "Parsing line: " << line << endl;  // Debug info

        // Найти reminder (между reminder:"..." )
        size_t rem_start = line.find("reminder:\"");
        if (rem_start == string::npos) continue;
        rem_start += 10;  // пропустить "reminder:"

        size_t rem_end = line.find("\"", rem_start);
        if (rem_end == string::npos) continue;

        string reminder_text = line.substr(rem_start, rem_end - rem_start);

        // Найти day
        size_t day_start = line.find("day:", rem_end);
        if (day_start == string::npos) continue;
        day_start += 4;

        size_t day_end = line.find(" ", day_start);
        if (day_end == string::npos) day_end = line.find("month:", day_start);
        string day_str = line.substr(day_start, day_end - day_start);

        // Найти month
        size_t month_start = line.find("month:", day_end);
        if (month_start == string::npos) continue;
        month_start += 6;

        size_t month_end = line.find(" ", month_start);
        if (month_end == string::npos) month_end = line.find("year:", month_start);
        string month_str = line.substr(month_start, month_end - month_start);

        // Найти year
        size_t year_start = line.find("year:", month_end);
        if (year_start == string::npos) continue;
        year_start += 5;

        size_t year_end = line.find(" ", year_start);
        if (year_end == string::npos) year_end = line.find("hour:", year_start);
        string year_str = line.substr(year_start, year_end - year_start);

        // Найти hour
        size_t hour_start = line.find("hour:", year_end);
        if (hour_start == string::npos) continue;
        hour_start += 5;

        size_t hour_end = line.find(" ", hour_start);
        if (hour_end == string::npos) hour_end = line.find("minutes:", hour_start);
        string hour_str = line.substr(hour_start, hour_end - hour_start);

        // Найти minutes
        size_t min_start = line.find("minutes:", hour_end);
        if (min_start == string::npos) continue;
        min_start += 8;

        string min_str = line.substr(min_start);

        try {
            int day = stoi(day_str);
            int month = stoi(month_str);
            int year = stoi(year_str);
            int hour = stoi(hour_str);
            int minutes = stoi(min_str);

            Reminder new_rem(reminder_text, new Date(day, month, year), new Time(hour, minutes));
            list_reminder.push_back(new_rem);
            loaded_count++;
        } catch (errors::FileError& error) {
            cerr << error.what() << endl;
        }
    }
    file.close();
    cout << "List loaded from " << TXT_FILE << " (" << loaded_count << " reminders)" << endl;
}

Reminder addReminderbookmark(vector<Reminder>& list_reminder) {
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
            Reminder result(reminder, new Date(day, month, year), new Time(hour, minutes));
            cout << "Reminder added." << endl;
            list_reminder.push_back(result);
            saveToTxt(list_reminder);
            return result;
        }
        catch (errors::HourError& error) {
            cerr << error.what() << endl;
            repeat = true;
        }
        catch (errors::MinutesError& error) {
            cerr << error.what() << endl;
            repeat = true;
        }
        catch (errors::YearError& error) {
            cerr << error.what() << endl;
            repeat = true;
        }
        catch (errors::MonthError& error) {
            cerr << error.what() << endl;
            repeat = true;
        }
        catch (errors::DayError& error) {
            cerr << error.what() << endl;
            repeat = true;
        }
    } while (repeat);
}

void print_list(const vector<Reminder> &bookmarks) {
    if (bookmarks.empty()) {
        cout << "No reminders." << endl;
        return;
    }
    for (int i = 0; i < bookmarks.size(); i++) {
        string day = to_string(bookmarks[i].getDate().getDay());
        if (stoi(day) < 10) day = "0" + day;
        string month = to_string(bookmarks[i].getDate().getMonth());
        if (stoi(month) < 10) month = "0" + month;
        string year = to_string(bookmarks[i].getDate().getYear());
        if (stoi(year) < 10) year = "0" + year;
        string hour = to_string(bookmarks[i].getTime().getHour());
        if (stoi(hour) < 10) hour = "0" + hour;
        string minutes = to_string(bookmarks[i].getTime().getMinutes());
        if (stoi(minutes) < 10) minutes = "0" + minutes;

        cout << i << ": ( Reminder: " << bookmarks[i].getReminder()
             << ", Date: " << day << "." << month << "." << year
             << ", Time: " << hour << ":" << minutes << " )" << endl;
    }
}

void delete_reminder(vector<Reminder> &bookmarks) {
    string delete_index;
    cout << "Enter the id of the reminder you want to delete: ";
    getline(cin, delete_index);
    int request_int;
    try {
        request_int = stoi(delete_index);
    } catch (errors::IndexError& error) {
        cout << "Invalid number." << endl;
        return;
    }
    if (request_int >= bookmarks.size() || request_int < 0) {
        cout << "You entered a non-existent id." << endl;
        return;
    }
    bookmarks.erase(bookmarks.begin() + request_int);
    saveToTxt(bookmarks);
    cout << "Reminder deleted successfully." << endl;
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
        reminder_list.erase(reminder_list.begin() + *it);
    }
    if (!to_delete.empty()) {
        saveToTxt(reminder_list);
    }

    delete current_date;
    delete current_time;
}

int main() {
    string request;
    vector<Reminder> list_reminder;

    cout << "Loading reminders..." << endl;
    loadFromTxt(list_reminder);

    thread reminderThread([&list_reminder]() {
        while (true) {
            checkReminders(list_reminder);
            this_thread::sleep_for(chrono::seconds(10));
        }
    });
    reminderThread.detach();

    while (request != "exit") {
        cout << "\nWhat do you want to do?\n"
                "exit - exit the program | add - add a reminder | view - display a list of reminders | del - delete reminder"
             << endl;
        getline(cin, request);
        if (request == "add") {
            addReminderbookmark(list_reminder);
        } else if (request == "view") {
            print_list(list_reminder);
        } else if (request == "del") {
            delete_reminder(list_reminder);
        }
    }
    saveToTxt(list_reminder);
    cout << "Goodbye!" << endl;
    return 0;
}