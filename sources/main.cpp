#include <iostream>
#include <fstream>
#include "Club.hpp"


int main(int argc, char* argv[]) 
{
    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " test_file.txt\n";
        return EXIT_FAILURE;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) 
    {
        std::cerr << "Cannot open file: " << argv[1] << "\n";
        return EXIT_FAILURE;
    }

    try 
    {
        Club club;
        club.loadConfiguration(inputFile);
        club.processEvents(inputFile);
        club.closeDay();
        club.printReport(std::cout);
    } 
    catch (const std::invalid_argument& ex) 
    {
        std::cerr << ex.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}