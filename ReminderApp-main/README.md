# Проект "Приложение для напоминаний"

### Статус разработки: *В процессе*

### Участники
Перевозников Леонид, Чернятин Дмитрий

### Функция проекта
Позволить пользователю добавлять напоминания в определенное время, просматривать их, удалять их, и напоминать о них в установленное время.

### Использованные инструменты
Данный проект является простым консольным приложением на языке программирования C++ с использованием Cmake, библиотеки chrono, и принципов ООП.

## Диаграмма классов
``` mermaid
classDiagram
    class ErrorType {
        <<enumeration>>
        +YearError
        +MonthError
        +DayError
        +HourError
        +MinutesError
    }
    
    class DAYS {
        <<enumeration>>
        +BEGIN_DAY : 1
        +END_DAY_28 : 28
        +END_DAY_30 : 30
        +END_DAY_31 : 31
    }
    
    class Times {
        <<enumeration>>
        +END_HOUR : 23
        +END_MINUTES : 59
    }
    
    class Date {
        -unsigned int _day
        -unsigned int _month
        -unsigned int _year
        +Date(day=1, month=1, year=1)
        +getDay() unsigned int
        +getMonth() unsigned int
        +getYear() unsigned int
        #checkMonth(month) unsigned int
        #checkDay(day, end) unsigned int
        #checkYear(year) unsigned int
    }
    
    class Time {
        -unsigned int _hour
        -unsigned int _minutes
        +Time(hour=0, minutes=0)
        +getHour() unsigned int
        +getMinutes() unsigned int
        #checkHour(hour) unsigned int
        #checkMinutes(minutes) unsigned int
    }
    
    class Reminder {
        -std::string _reminder
        -Date* _date
        -Time* _time
        +Reminder(reminder, date, time)
        +~Reminder()
        +getReminder() std::string
        +getDate() Date
        +getTime() Time
    }
    
    Date ..|> ErrorType 
    Time ..|> ErrorType 
    Reminder *-- Date 
    Reminder *-- Time
```
