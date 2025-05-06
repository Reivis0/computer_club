#include "Time.hpp"

Time::Time(const std::string& time) 
{
    static const std::regex re(R"(^([0-1]\d|2[0-3]):([0-5]\d)$)");
    std::smatch m;
    if (!std::regex_match(time, m, re))
        throw std::invalid_argument("Invalid time format");
    hours_ = std::stoi(m[1].str());
    minutes_ = std::stoi(m[2].str());
}

std::string Time::toString() const 
{
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours_
        << ":" << std::setw(2) << std::setfill('0') << minutes_;
    return oss.str();
}

int Time::toMinutes() const 
{
    return hours_ * 60 + minutes_;
}

std::string Time::fromMinutes(int total) 
{
    std::string res = std::to_string(total / 60).size() == 1 ? "0" + std::to_string(total / 60) : std::to_string(total / 60);
    res += ":";
    res += (std::to_string(total % 60).size() == 1 ? "0" + std::to_string(total % 60) : std::to_string(total % 60));
    return res;
              
}

int Time::operator-(const Time& other) const 
{
    return toMinutes() - other.toMinutes();
}

bool Time::operator<(const Time& other) const 
{
    return toMinutes() < other.toMinutes();
}

bool Time::operator<=(const Time& other) const 
{
    return toMinutes() <= other.toMinutes();
}

bool Time::operator==(const Time& other) const 
{
    return hours_ == other.hours_ && minutes_ == other.minutes_;
}
