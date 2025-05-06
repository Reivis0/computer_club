#include "Club.hpp"


void Club::loadConfiguration(std::istream& in) 
{
    std::string line;

    if (!std::getline(in, line)) throw std::invalid_argument("ERROR: format error at line 1");
    currentLine = 1;
    try 
    {
        for(const char el:line)
        if(!isdigit(el)) throw EXIT_SUCCESS;
        
        numTables = std::stoi(line);
        if (numTables <= 0) throw EXIT_SUCCESS;
    } 
    catch (...) 
    {
        throw std::invalid_argument("Format error at line 1");
    }

    tables.assign(numTables, Table());

    if (!std::getline(in, line)) throw std::invalid_argument("ERROR: format error at line 2");
    currentLine = 2;
    {
        std::istringstream ss(line);
        std::string o, c;
        if (!(ss >> o >> c)) throw EXIT_SUCCESS;
        openTime  = Time(o);
        closeTime = Time(c);
        if (!(openTime < closeTime)) throw EXIT_SUCCESS;
    }

    if (!std::getline(in, line)) throw std::invalid_argument("ERROR: format error at line 3");
    currentLine = 3;
    try 
    {
        pricePerHour = std::stoi(line);
        if (pricePerHour <= 0) throw EXIT_SUCCESS;
    } 
    catch (...) 
    {
        throw std::invalid_argument("ERROR: format error at line 3");
    }
}

void Club::processEvents(std::istream& in) 
{
    std::string line;
    while (std::getline(in, line)) 
    {
        ++currentLine;
        if (line.empty()) continue;
        Event e(line, currentLine);
        addLog(e.toString());
        handleEvent(e);
    }
}

void Club::closeDay() 
{
    for (auto& [name, client] : clients) 
    {
        logEvents.push_back(closeTime.toString() + " 11 " + name);
        if (client.isSitting()) 
        {
            int tnum = client.getTable() - 1;
            tables[tnum].release(closeTime, pricePerHour);
        }
    }
}

void Club::printReport(std::ostream& out) const 
{
    auto sorted = logEvents;
    out << openTime.toString() << "\n";
    for (auto& s : sorted) out << s << "\n";
    out << closeTime.toString() << "\n";
    for (int i = 0; i < numTables; ++i) 
    {
        int mins = tables[i].getUsageMinutes();
        out << (i+1) << " " << tables[i].getRevenue()
            << " " << Time::fromMinutes(mins) << "\n";
    }
}

void Club::handleEvent(const Event& e) 
{
    const auto& p = e.params;
    switch (e.id) {
        case 1: 
        {
            auto& name = p[0];
            if (clients.count(name)) return genError(e, "YouShallNotPass");
            if (e.time < openTime)    return genError(e, "NotOpenYet");
            clients.emplace(name, Client(name));
            break;
        }
        case 2: 
        {
            auto& name = p[0];
            int tnum = std::stoi(p[1]);
            if (!clients.count(name)) return genError(e, "ClientUnknown");
            if (tnum < 1 || tnum > numTables) return genError(e, "PlaceIsBusy");
            auto& tbl = tables[tnum-1];
            auto& cl  = clients.at(name);
            if (!tbl.isFree() && tbl.getClient() != name)
                return genError(e, "PlaceIsBusy");
            if (cl.isSitting() && cl.getTable() == tnum) return; 

            if (cl.isSitting()) 
            {
                int old = cl.getTable() - 1;
                tables[old].release(e.time, pricePerHour);
            }
            tbl.occupy(name, e.time);
            cl.sit(tnum, e.time);
            break;
        }
        case 3: 
        {
            auto& name = p[0];
            bool freeExists = false;
            for (auto& t : tables) if (t.isFree()) freeExists = true;
            if (freeExists) return genError(e, "ICanWaitNoLonger!");
            if (waitQueue.size() >= numTables) {
                clients.erase(name);
                return addLog(e.time.toString() + " 11 " + name);
            }
            waitQueue.push(name);
            break;
        }
        case 4: 
        { 
            auto& name = p[0];
            if (!clients.count(name)) return genError(e, "ClientUnknown");
            auto& cl = clients.at(name);
            if (cl.isSitting()) 
            {
                int idx = cl.getTable() - 1;
                tables[idx].release(e.time, pricePerHour);
                if (!waitQueue.empty()) {
                    auto next = waitQueue.front(); waitQueue.pop();
                    tables[idx].occupy(next, e.time);
                    clients.at(next).sit(idx+1, e.time);
                    addLog(e.time.toString() + " 12 " + next + " " + std::to_string(idx+1));
                }
            }
            clients.erase(name);
            break;
        }
    }
}

void Club::addLog(const std::string& s) {
    logEvents.push_back(s);
}

void Club::genError(const Event& e, const std::string& err) {
    logEvents.push_back(e.time.toString() + " 13 " + err);
}
