#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "Time.hpp"
#include <string>
#include <vector>

struct Event 
{
    Time time;
    int id;
    std::vector<std::string> params;

    Event(const std::string& line, int lineNo);
    std::string toString() const;
};

#endif