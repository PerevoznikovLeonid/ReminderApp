cmake_minimum_required(VERSION 4.0)
project(ReminderApp)

set(CMAKE_CXX_STANDARD 20)

add_executable(ReminderApp main.cpp
        headers/Date.h
        headers/Reminder.h
        headers/Time.h
        headers/ErrorTypes.h)