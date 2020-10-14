#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
#include "util.h"
using namespace std;
using namespace libconfig;
namespace InstallCmd {
    int run(int argc, char **argv, string name, const Setting &cfgRoot, string env) {
        help::printCmd("install", "Run all scripts and then install project");
        cout << "\e[1;32mInstall \e[0;31m" << name << "\e[1;32m? \e[0;33m[y/N]\e[0m ";
        char choice = (char)cin.get();
        cout << endl;
        if(choice != 'y') {
            cout << "\e[1;33mExiting\e[0m" << endl;
            return 1;
        }
        const Setting &scripts = cfgRoot["scripts"];
        const Setting &installCmds = cfgRoot["install"];
        int nScripts = scripts.getLength();
        int nInstallCmds = installCmds.getLength();
        for(int i = 0; i < nScripts; i++) {
            const Setting &script = scripts[i];
            cout << "\e[1;32mRunning \e[0;31m" << script["name"].c_str() << "\e[0m" << endl;
            for(int j = 0; j < script["commands"].getLength(); j++) {
                command::run(env, script["commands"][j].c_str());
            }
        }
        cout << "\e[1;32mInstalling\e[0m" << endl;
        for(int i = 0; i < nInstallCmds; i++) {
            command::run(env, installCmds[i].c_str());
        }
        return 0;
    }
}