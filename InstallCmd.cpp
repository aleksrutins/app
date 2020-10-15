#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <filesystem>
#include <libconfig.h++>
#include "util.h"
using namespace std;
namespace fs = std::filesystem;
using namespace libconfig;
namespace InstallCmd {
    int run(int argc, char **argv, string name, const Setting &cfgRoot, string env, string prefix) {
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
        cout << "\e[1;32mCreating symlinks\e[0m" << endl;
        fs::path localDir = "~/.local";
        const Setting &files = cfgRoot["files"];
        for (int i = 0; i < files.getLength(); i++) {
            const Setting &curFile = files[i];
            auto installPath = localDir.concat(curFile["install_path"].c_str());
            auto printSrcPath = fs::path("(install prefix)").concat(curFile["pkg_path"].c_str());
            auto actualSrcPath = fs::path(prefix).concat(curFile["pkg_path"].c_str());
            cout << "\e[1;31m" << printSrcPath.c_str() << "\e[0;33m -> \e[1;31m" << installPath.c_str() << "\e[0m" << endl;
            string mkdir_cmd = "mkdir -p ";
            mkdir_cmd += installPath.parent_path().c_str();
            string cmd = "ln -sf ";
            cmd = cmd + actualSrcPath.c_str() + " " + installPath.c_str();
            system(mkdir_cmd.c_str());
            system(cmd.c_str());
        }
        return 0;
    }
}