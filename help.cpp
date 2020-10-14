#include <string>
#include <libconfig.h++>
#include "util.h"
using namespace std;
namespace help {
    void printCmd(std::string name, std::string desc, bool header) {
        if(header) {
            std::cout << "\n\e[1;33m -- \e[1;32m" << name << "\e[1;31m - " << desc << "\e[1;33m --\e[0m\n" << std::endl;
        } else {
            std::cout << "\e[1;33m - \e[1;32m" << name << "\e[1;31m - " << desc << "\e[0m" << std::endl;
        }
    }
    void printHelp() {
        cout << "\n\e[1;32mAvailable commands:\e[0m" << endl;
        printCmd("install", "Install the current project", false);
        printCmd("list", "List scripts", false);
        printCmd("run <script>", "Run <script>.", false);
    }
}