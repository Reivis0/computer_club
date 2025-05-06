#include "Events.hpp"


Event::Event(const std::string& line, int lineNo) 
{
    const std::regex general(R"(^(\d{2}:\d{2})\s+([1-4])\s+(.*)$)");
    std::smatch m;
    if (!std::regex_match(line, m, general))
        throw std::invalid_argument("ERROR: incorrect format: " + std::to_string(lineNo));

    time = Time(m[1].str());
    id = std::stoi(m[2].str());

    std::istringstream iss(m[3].str());
    std::string tok;
    while (iss >> tok) params.push_back(tok);

    static const std::regex reName(R"(^[a-z0-9_-]+$)");
    static const std::regex reNum(R"(^\d+$)");

    switch (id) {
        case 1:
        case 3:
        case 4:
            if (params.size() != 1 || !std::regex_match(params[0], reName))
                throw std::invalid_argument("ERROR: incorrect format: " + std::to_string(lineNo));
            break;
        case 2:
            if (params.size() != 2 ||
                !std::regex_match(params[0], reName) ||
                !std::regex_match(params[1], reNum))
                throw std::invalid_argument("ERROR: incorrect format: " + std::to_string(lineNo));
            break;
        default:
            throw std::invalid_argument("ERROR: incorrect format: " + std::to_string(lineNo));
    }
}

std::string Event::toString() const 
{
    std::ostringstream oss;
    oss << time.toString() << " " << id;
    for (auto& p : params) oss << " " << p;
    return oss.str();
}
