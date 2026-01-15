#ifndef REMINDERAPP_ERRORTYPES_H
#define REMINDERAPP_ERRORTYPES_H

#include <stdexcept>
#include <string>

namespace errors {
    class ProgramError : public std::runtime_error {
    public:
        explicit ProgramError(const std::string& message)
          : std::runtime_error(message) {
        }

        ~ProgramError() noexcept override = default;
    };



    class DateError : public ProgramError {
    public:
        explicit DateError(const std::string& message)
          : ProgramError(message) {
        }

        ~DateError() noexcept override = default;
    };

    class YearError : public DateError {
    public:
        explicit YearError(const std::string& message)
          : DateError(message) {
        }

        ~YearError() noexcept override = default;
    };

    class MonthError : public DateError {
    public:
        explicit MonthError(const std::string& message)
          : DateError(message) {
        }

        ~MonthError() noexcept override = default;
    };

    class DayError : public DateError {
    public:
        explicit DayError(const std::string& message)
          : DateError(message) {
        }

        ~DayError() noexcept override = default;
    };



    class TimeError : public ProgramError {
    public:
        explicit TimeError(const std::string& message)
          : ProgramError(message) {
        }

        ~TimeError() noexcept override = default;
    };

    class HourError : public TimeError {
    public:
        explicit HourError(const std::string& message)
          : TimeError(message) {
        }

        ~HourError() noexcept override = default;
    };

    class MinutesError : public TimeError {
    public:
        explicit MinutesError(const std::string& message)
          : TimeError(message) {
        }

        ~MinutesError() noexcept override = default;
    };
}

// enum ErrorType {
//     YearError, MonthError, DayError, HourError, MinutesError
// };

#endif //REMINDERAPP_ERRORTYPES_H