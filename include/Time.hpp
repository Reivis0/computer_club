#ifndef TIME_HPP
#define TIME_HPP

#include <string>
#include <regex>
#include <sstream>
#include <iomanip>
#include <exception>


class Time 
{
public:
    Time() : hours_(0), minutes_(0) {};
    Time(const std::string& time);
    std::string toString() const;
    int toMinutes() const;
    static std::string fromMinutes(int totalMinutes);
    int operator-(const Time& other) const;
    bool operator<(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator==(const Time& other) const;
private:
    int hours_;
    int minutes_;
};


#endif