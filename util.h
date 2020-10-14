#include <string>
#include <iostream>
void printCmd(std::string name, std::string desc, bool header = true) {
    if(header) {
        std::cout << "\n\e[1;33m -- \e[1;32m" << name << "\e[1;31m - " << desc << "\e[1;33m --\e[0m\n" << std::endl;
    } else {
        std::cout << "\e[1;33m - \e[1;32m";
    }
}