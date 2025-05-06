#include "Clients.hpp"


const std::string& Client::getName() const 
{
     return name_; 
}

bool Client::isSitting() const 
{
     return tableNum_ != 0;
}

int Client::getTable() const 
{
     return tableNum_; 
}

const Time& Client::getStartTime() const 
{
     return startTime_; 
}

void Client::sit(int table, const Time& time) 
{
    tableNum_ = table;
    startTime_ = time;
}

int Client::leave(const Time& time) 
{
    int minutes = time - startTime_;
    tableNum_ = 0;
    return minutes;
}

void Client::reset() 
{
    tableNum_ = 0;
}
