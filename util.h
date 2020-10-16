#ifndef UTIL_H
#define UTIL_H
#include <string>
#include <iostream>
#include <libconfig.h++>
namespace help {
    void printCmd(std::string, std::string, bool = true);
    void printHelp();
    void printDepsError(const libconfig::Setting &);
}
namespace command {
    int run(std::string, std::string, bool = true);
}
#endif