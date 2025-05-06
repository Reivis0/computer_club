#ifndef CLIENTS_HPP
#define CLIENTS_HPP

#include "Time.hpp"

class Client 
{
public:
    Client(const std::string& name): name_(name), tableNum_(0), startTime_() {};

    const std::string& getName() const;
    bool isSitting() const;
    int getTable() const;
    const Time& getStartTime() const;

    void sit(int table, const Time& time);
    int leave(const Time& time);
    void reset();

private:
    std::string name_;
    int tableNum_;   
    Time startTime_;
};
#endif