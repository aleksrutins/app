#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <iostream>
namespace help {
    void printCmd(std::string, std::string, bool = true);
    void printHelp();
}
namespace command {
    void run(std::string, std::string);
}
#endif