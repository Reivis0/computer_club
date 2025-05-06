#ifndef TABLES_HPP
#define TABLES_HPP

#include "Time.hpp"
#include <cmath>

class Table 
{
public:
    Table() : currentClient_(""), startTime_(), revenue_(0), usageMinutes_(0) {};

    bool isFree() const;
    const std::string& getClient() const;
    int getRevenue() const;
    int getUsageMinutes() const;

    void occupy(const std::string& client, const Time& time);
    int release(const Time& time, int price);

private:
    std::string currentClient_;
    Time startTime_;
    int revenue_;
    int usageMinutes_;
};
#endif