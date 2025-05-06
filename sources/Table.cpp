#include "Tables.hpp"
 

bool Table::isFree() const 
{
    return currentClient_.empty();
}

const std::string& Table::getClient() const 
{
    return currentClient_;
}

int Table::getRevenue() const 
{
    return revenue_;
}

int Table::getUsageMinutes() const 
{
    return usageMinutes_;
}

void Table::occupy(const std::string& client, const Time& time) 
{
    currentClient_ = client;
    startTime_ = time;
}

int Table::release(const Time& time, int price) 
{
    int mins = time - startTime_;
    int hours = (mins + 59) / 60;
    revenue_ += hours * price;
    usageMinutes_ += mins;
    currentClient_.clear();
    return mins;
}
