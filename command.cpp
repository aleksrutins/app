#include <string>
#include <libconfig.h++>
#include "util.h"

namespace command {
    int run(std::string env, std::string cmd) {
        using namespace std;
        string fullCmd = "(" + env + "; " + cmd + ")";
        cout << "\e[1;33m% \e[0m\e[4;31m" << cmd << "\e[0m" << endl;
        return system(fullCmd.c_str());
    }
}