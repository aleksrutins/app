#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
#include "util.h"
#include "InstallCmd.hpp"
#include "RunCmd.hpp"
#include <filesystem>
#include <unistd.h>
using namespace libconfig;
using namespace std;
namespace fs = std::filesystem;
int main(int argc, char **argv) {
    try {
        if (argc > 2 && string(argv[1]) == "install") {
            cout << "\e[1;32mPulling \e[0;31m" << argv[2] << "\e[1;32m from GitHub...\e[0m" << endl;
            cout << "\e[1;32mPreparing directories...\e[0m" << endl;
            auto srcPath = fs::path(string(getenv("HOME")) + "/.local/share/app-pm/source/").concat(argv[2]);
            string rmCmd = string("rm -rf ") + srcPath.c_str();
            string mkdirCmd = string("mkdir -p ") + srcPath.c_str();
            command::run("true", rmCmd, false);
            command::run("true", mkdirCmd, false);
            cout << "\e[1;32mCloning...\e[0m" << endl;
            string gitCmd = string("git clone ") + "https://github.com/" + argv[2] + ".git" + " " + srcPath.c_str();
            command::run("true", gitCmd, false);
            cout << "\e[1;32mSwitching directories...\e[0m" << endl;
            chdir(srcPath.c_str());
        }
        if (argc < 2) {
            help::printHelp();
            return 1;
        }
        cout << "\e[1;32mLoading config from \e[0;31m.app/config\e[0m" << endl;
        Config cfg;
        cfg.readFile(".app/config");
        const Setting &cfgRoot = cfg.getRoot();
        string name = cfgRoot["name"].c_str();
        cout << "\e[1;32mProject name is \e[0;31m" << name << "\e[0m" << endl;
        string prefix = string(getenv("HOME")) + "/.local/share/app-pm/install/" + name;
        system(("mkdir -p " + prefix).c_str());
        string env = "prefix=\"" + prefix + "\"";

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
            return 1;
        }
    } catch(std::logic_error) {
        help::printHelp();
        return 1;
    } catch(libconfig::FileIOException) {
        cout << "\e[1;31mCould not load config\e[0m" << endl;
        help::printHelp();
    }
    return 0;
}