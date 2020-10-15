#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
#include "util.h"
#include "InstallCmd.hpp"
#include "RunCmd.hpp"
using namespace libconfig;
using namespace std;
int main(int argc, char **argv) {
    try {
        cout << "\e[1;32mLoading config from \e[0;31m.app/config\e[0m" << endl;
        Config cfg;
        cfg.readFile(".app/config");
        const Setting &cfgRoot = cfg.getRoot();
        string name = cfgRoot["name"].c_str();
        cout << "\e[1;32mProject name is \e[0;31m" << name << "\e[0m" << endl;
        string prefix = "~/.local/share/app-pm/install/" + name;
        system(("mkdir -p " + prefix).c_str());
        string env = "prefix=" + prefix;

        string cmd = argv[1];
        if(cmd == "list") {
            help::printCmd("list", "List scripts");
            cout << "\e[1;32mAvailable scripts:\e[0m" << endl;
            const Setting &scripts = cfgRoot["scripts"];
            int len = scripts.getLength();
            for(int i = 0; i < len; i++) {
                cout << "\e[1;32m - \e[0;31m" << scripts[i]["name"].c_str() << "\e[0m" << endl;
            };
        } else if (cmd == "install") {
            return InstallCmd::run(argc, argv, name, cfgRoot, env, prefix);
        } else if (cmd == "run") {
            return RunCmd::run(argc, argv, name, cfgRoot, env);
        } else {
            help::printHelp();
        }
    } catch(std::logic_error) {
        help::printHelp();
    }
    return 0;
}