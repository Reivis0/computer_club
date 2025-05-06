#pragma once
#include "Time.hpp"
#include "Events.hpp"
#include "Clients.hpp"
#include "Tables.hpp"
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cctype>


class Club 
{
public:
    Club() : numTables(0), pricePerHour(0), openTime(), closeTime(), currentLine(0) {};
    void loadConfiguration(std::istream& inputFile);
    void processEvents(std::istream& inputFile);
    void closeDay();
    void printReport(std::ostream& out) const;

private:
    int numTables;
    int pricePerHour;
    Time openTime, closeTime;
    std::vector<Table> tables;
    std::map<std::string, Client> clients;
    std::queue<std::string> waitQueue;
    std::vector<std::string> logEvents;
    int currentLine;

    void handleEvent(const Event& e);
    void addLog(const std::string& s);
    void genError(const Event& e, const std::string& err);
};
