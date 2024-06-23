#include <iostream>
#include <vector>
#include <string>
/* Date class with private variables for year month and day
   I used YMD format because it's better for sorting */
class Date {
private:
    int year, month, day;
public:
    Date(int y, int m, int d) : year(y), month(m), day(d) {}

    // Using getters for YMD
    int getYear() const {
        return year;
    }
    int getMonth() const {
        return month;
    }
    int getDay() const {
        return day;
    }
    void print() const {
        std::cout << month << "/" << day << "/" << year;
    }
};

// Appointment class
class Appointment {
private:
    std::string description;
    Date date;
public:
    Appointment(const std::string& desc, int y, int m, int d)
        : description(desc), date(y, m, d) {}

    virtual ~Appointment() = default;
    virtual bool occurs_on(int year, int month, int day) const = 0;

    std::string getDescription() const {
        return description;
    }
    Date getDate() const {
        return date;
    }
    void print() const {
        std::cout << description << " on ";
        date.print();
        std::cout << std::endl;
    }
};

// Day class for singular date appointments
class Day : public Appointment {
public:
    Day(const std::string& desc, int y, int m, int d)
        : Appointment(desc, y, m, d) {}

    bool occurs_on(int year, int month, int day) const override {
        Date date = getDate();
        return (date.getYear() == year && date.getMonth() == month && date.getDay() == day);
    }
};

// Monthly class for reoccuring appointments
class Monthly : public Appointment {
public:
    Monthly(const std::string& desc, int y, int m, int d)
        : Appointment(desc, y, m, d) {}

    bool occurs_on(int year, int month, int day) const override {
        Date date = getDate();
        return (date.getMonth() == month && date.getDay() == day);
    }
};

int main() {
    // Program intro
    std::cout << "Appointment Tracker\n" << "\n";

    std::vector<Appointment*> appointments;

    // Test appointments
    appointments.push_back(new Day("Dad's Birthday", 2024, 12, 24));
    appointments.push_back(new Day("CSC 252 C++ Zoom Lecture", 2024, 6, 24));
    appointments.push_back(new Day("Last day of class", 2024, 6, 29));
    appointments.push_back(new Monthly("All staff meeting - In office", 2024, 6, 26));
    appointments.push_back(new Monthly("Mortgate Payment Due", 2024, 1, 5));

    // Prompts user for input
    int year, month, day;
    std::cout << "Check your calendar for appointments (year month day): ";
    std::cin >> year >> month >> day;

    std::cout << "Appointments on ";
    Date queryDate(year, month, day);
    queryDate.print();
    std::cout << ":" << std::endl;

    for (const auto& appt : appointments) {
        if (appt->occurs_on(year, month, day)) {
            appt->print();
        }
    }

    // Clean up
    for (auto appt : appointments) {
        delete appt;
    }

    return 0;
}