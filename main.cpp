#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
#include "util.h"
using namespace libconfig;
using namespace std;

int main(int argc, char **argv) {
    cout << "\e[1;32mLoading config from \e[0;31m.app/config\e[0m" << endl;
    Config cfg;
    cfg.readFile(".app/config");
    const Setting &cfgRoot = cfg.getRoot();
    string name = cfgRoot["name"].c_str();
    cout << "\e[1;32mProject name is \e[0;31m" << name << "\e[0m" << endl;
    
    string cmd = argv[1];
    if(cmd == "list") {
        printCmd("list", "List scripts");
        cout << "\e[1;32mAvailable scripts:\e[0m" << endl;
        const Setting &scripts = cfgRoot["scripts"];
        int len = scripts.getLength();
        for(int i = 0; i < len; i++) {
            cout << "\e[1;32m - \e[0;31m" << scripts[i]["name"].c_str() << "\e[0m" << endl;
        };
    } else if (cmd == "install") {
        printCmd("install", "Run all scripts and then install project");
        cout << "\e[1;32mInstall \e[0;31m" << name << "\e[1;32m? \e[0;33m[y/N]\e[0m ";
        char choice = (char)cin.get();
        cout << endl;
        if(choice != 'y') {
            cout << "\e[1;33mExiting\e[0m" << endl;
            return 1;
        }

    }

    return 0;
}