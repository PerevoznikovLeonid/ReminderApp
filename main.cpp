#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <thread>
#include <fstream>
#include "headers/Date.h"
#include "headers/Time.h"
#include "headers/Reminder.h"

using namespace std;
const string TXT_FILE = "reminders.txt";

// Сохраняет список в текстовый файл
void saveToTxt(const vector<Reminder>& list_reminder) {
    ofstream file(TXT_FILE);
    try {
        if (!file.is_open()) {
            throw errors::FileError("Error opening file");
        }
    }
    catch (const errors::FileError& error) {
        cerr << error.what() << endl;
    }

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
}

// Загружает список из текстового файла
void loadFromTxt(vector<Reminder>& list_reminder) {
    ifstream file(TXT_FILE);
    if (!file.is_open()) {
        return;
    }

    list_reminder.clear();
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        // Найти reminder
        size_t rem_start = line.find("reminder:\"");
        if (rem_start == string::npos) continue;
        rem_start += 10;

        size_t rem_end = line.find('\"', rem_start);
        if (rem_end == string::npos) continue;

        string reminder_text = line.substr(rem_start, rem_end - rem_start);

        // Найти day
        size_t day_start = line.find("day:", rem_end);
        if (day_start == string::npos) continue;
        day_start += 4;

        size_t day_end = line.find(' ', day_start);
        if (day_end == string::npos) day_end = line.find("month:", day_start);
        string day_str = line.substr(day_start, day_end - day_start);

        // Найти month
        size_t month_start = line.find("month:", day_end);
        if (month_start == string::npos) continue;
        month_start += 6;

        size_t month_end = line.find(' ', month_start);
        if (month_end == string::npos) month_end = line.find("year:", month_start);
        string month_str = line.substr(month_start, month_end - month_start);

        // Найти year
        size_t year_start = line.find("year:", month_end);
        if (year_start == string::npos) continue;
        year_start += 5;

        size_t year_end = line.find(' ', year_start);
        if (year_end == string::npos) year_end = line.find("hour:", year_start);
        string year_str = line.substr(year_start, year_end - year_start);

        // Найти hour
        size_t hour_start = line.find("hour:", year_end);
        if (hour_start == string::npos) continue;
        hour_start += 5;

        size_t hour_end = line.find(' ', hour_start);
        if (hour_end == string::npos) hour_end = line.find("minutes:", hour_start);
        string hour_str = line.substr(hour_start, hour_end - hour_start);

        // Найти minutes
        size_t min_start = line.find("minutes:", hour_end);
        if (min_start == string::npos) continue;
        min_start += 8;

        string min_str = line.substr(min_start);

        int day = stoi(day_str);
        int month = stoi(month_str);
        int year = stoi(year_str);
        int hour = stoi(hour_str);
        int minutes = stoi(min_str);

        Reminder new_rem(reminder_text, new Date(day, month, year), new Time(hour, minutes));
        list_reminder.push_back(new_rem);
    }
    file.close();
}

// Добавляет напоминание в список
Reminder addReminder(vector<Reminder>& list_reminder) {
    string reminder;
    cout << "Set a reminder:" << endl;
    getline(cin, reminder);
    bool repeat;
    do {
        repeat = false;

        string temp_input;

        cout << "Enter the year:" << endl;
        getline(cin, temp_input);
        const int year = stoi(temp_input);

        cout << "Enter the month:" << endl;
        getline(cin, temp_input);
        const int month = stoi(temp_input);

        cout << "Enter the day:" << endl;
        getline(cin, temp_input);
        const int day = stoi(temp_input);

        cout << "Enter the hour:" << endl;
        getline(cin, temp_input);
        const int hour = stoi(temp_input);

        cout << "Enter the minutes:" << endl;
        getline(cin, temp_input);
        const int minutes = stoi(temp_input);

        try {
            // Проверка на то, прошла ли дата
            const auto now = std::chrono::system_clock::now();
            const auto time = std::chrono::system_clock::to_time_t(now);
            const auto time_local = *localtime(&time);

            constexpr int TM_YEAR_BEGIN = 1900;
            constexpr int TM_MONTH_BEGIN = 1;
            if (time_local.tm_mday > day || time_local.tm_mon > month + TM_MONTH_BEGIN || time_local.tm_year + TM_YEAR_BEGIN > year) {
                throw errors::PassedDateTimeError("Date has already passed.");
            }
            if (time_local.tm_hour > hour || time_local.tm_min > minutes) {
                throw errors::PassedDateTimeError("Time has already passed.");
            }

            Reminder result(reminder, new Date(day, month, year), new Time(hour, minutes));
            list_reminder.push_back(result);
            cout << "Reminder added." << endl;
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
        catch (errors::MonthError& error) {
            cerr << error.what() << endl;
            repeat = true;
        }
        catch (errors::DayError& error) {
            cerr << error.what() << endl;
            repeat = true;
        }
        catch (errors::PassedDateTimeError& error) {
            cerr << error.what() << endl;
            repeat = true;
        }
    } while (repeat);
}

// Выводит список напоминаний в консоль
void printList(const vector<Reminder> &bookmarks) {
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

// Удаляет напоминание
void deleteReminder(vector<Reminder> &bookmarks) {
    string delete_index;
    cout << "Enter the id of the reminder you want to delete:";
    getline(cin, delete_index);
    const int request_int = stoi(delete_index);

    try {
        if (request_int >= bookmarks.size() || request_int < 0) {
            throw errors::IndexError("You entered a non-existent id.");
        }
    }
    catch (errors::IndexError& error) {
        cerr << error.what() << endl;
    }
    bookmarks.erase(bookmarks.begin() + request_int);
    saveToTxt(bookmarks);
    cout << "Reminder deleted successfully." << endl;
}

// Проверяет напоминание на соответствие текущему времени, выводит и удаляет из списка, если соответствует
void checkReminders(vector<Reminder>& reminder_list) {
    const auto now = chrono::system_clock::now();
    const auto time = chrono::system_clock::to_time_t(now);
    const auto time_local = *localtime(&time);

    const auto current_date = new Date(time_local.tm_mday, time_local.tm_mon + 1, time_local.tm_year + 1900);
    const auto current_time = new Time(time_local.tm_hour, time_local.tm_min);

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

    for (const int & it : std::ranges::reverse_view(to_delete)) {
        reminder_list.erase(reminder_list.begin() + it);
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
            addReminder(list_reminder);
        } else if (request == "view") {
            printList(list_reminder);
        } else if (request == "del") {
            deleteReminder(list_reminder);
        }
    }
    saveToTxt(list_reminder);
    cout << "Goodbye!" << endl;
    return 0;
}