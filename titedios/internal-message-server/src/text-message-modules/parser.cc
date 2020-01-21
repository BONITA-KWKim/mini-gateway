#include "parser.h"

std::vector<std::pair<std::string, std::string>> parser (std::string message)
{
    std::cout << COUT_PREFIX << message << std::endl;

    std::vector<std::pair<std::string, std::string>> results =  
    {
        { "Test 1", "Test 1" }, {"Test 2", "Test 2"}
    };

    return results;
}