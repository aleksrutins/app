#include <string>
#include <libconfig.h++>
#include "util.h"

namespace command {
    void run(std::string env, std::string cmd) {
        using namespace std;
        string fullCmd = env + " " + cmd;
        cout << "\e[1;33m% \e[2;31m" << cmd << "\e[0m" << endl;
        system(fullCmd.c_str());
    }
}