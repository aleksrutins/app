#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <filesystem>
#include <libconfig.h++>
#include <unistd.h>
#include "util.h"
using namespace std;
namespace fs = std::filesystem;
using namespace libconfig;
namespace InstallCmd {
    int run(int argc, char **argv, string name, const Setting &cfgRoot, string env, string prefix, bool = true);
    int depend(const Setting &cfgRoot, string env, string prefix) {
        
        char initWD[FILENAME_MAX];
        getcwd(initWD, FILENAME_MAX); // Get workdir of overarching project
        cout << "\e[1;32mInstalling build dependencies\e[0m" << endl;
        const Setting &buildDepends = cfgRoot["dev_depends"];
        for(int i = 0; i < buildDepends.getLength(); i++) {
            const Setting &dep = buildDepends[i];
            cout << "\e[1;32mPulling \e[0;31m" << dep.c_str() << "\e[1;32m from GitHub...\e[0m" << endl;
            cout << "\e[1;32mPreparing directories...\e[0m" << endl;
            auto srcPath = fs::path(string(getenv("HOME")) + "/.local/share/app-pm/source/").concat(dep.c_str());
            string rmCmd = string("rm -rf ") + srcPath.c_str();
            string mkdirCmd = string("mkdir -p ") + srcPath.c_str();
            command::run("true", rmCmd);
            command::run("true", mkdirCmd);
            cout << "\e[1;32mCloning...\e[0m" << endl;
            string gitCmd = string("git clone ") + "https://github.com/" + dep.c_str() + ".git" + " " + srcPath.c_str();
            command::run("true", gitCmd);
            cout << "\e[1;32mSwitching directories...\e[0m" << endl;
            chdir(srcPath.c_str());
            char *fakeArgv[] = {"app", "install", const_cast<char *>(dep.c_str())};
            Config cfg;
            try {
                cfg.readFile(".app/config");
            } catch(FileIOException) {
                return 1;
            }
            const Setting &newCfgRoot = cfg.getRoot();
            string pkgName = newCfgRoot["name"].c_str();
            cout << "\e[1;32mInstalling \e[0;31m" << pkgName << "\e[0m";
            run(3, fakeArgv, pkgName, newCfgRoot, env, prefix, true);
        }
        cout << "\e[1;32mInstalling runtime dependencies\e[0m" << endl;
        const Setting &depends = cfgRoot["depends"];
        for(int i = 0; i < depends.getLength(); i++) {
            const Setting &dep = depends[i];
            cout << "\e[1;32mPulling \e[0;31m" << dep.c_str() << "\e[1;32m from GitHub...\e[0m" << endl;
            cout << "\e[1;32mPreparing directories...\e[0m" << endl;
            auto srcPath = fs::path(string(getenv("HOME")) + "/.local/share/app-pm/source/").concat(dep.c_str());
            string rmCmd = string("rm -rf ") + srcPath.c_str();
            string mkdirCmd = string("mkdir -p ") + srcPath.c_str();
            command::run("true", rmCmd);
            command::run("true", mkdirCmd);
            cout << "\e[1;32mCloning...\e[0m" << endl;
            string gitCmd = string("git clone ") + "https://github.com/" + dep.c_str() + ".git" + " " + srcPath.c_str();
            command::run("true", gitCmd);
            cout << "\e[1;32mSwitching directories...\e[0m" << endl;
            chdir(srcPath.c_str());
            char *fakeArgv[] = {"app", "install", const_cast<char *>(dep.c_str())};
            Config cfg;
            try {
                cfg.readFile(".app/config");
            } catch(FileIOException) {
                return 1;
            }
            const Setting &newCfgRoot = cfg.getRoot();
            string pkgName = newCfgRoot["name"].c_str();
            cout << "\e[1;32mInstalling \e[0;31m" << pkgName << "\e[0m";
            run(3, fakeArgv, pkgName, newCfgRoot, env, prefix, true);
        }
        chdir(initWD);
        return 0;
    }
    int run(int argc, char **argv, string name, const Setting &cfgRoot, string env, string prefix, bool autoinstall) {
        help::printCmd("install", "Run all scripts and then install a project");
        
        if(!autoinstall) {
            cout << "\e[1;32mInstall \e[0;31m" << name << "\e[1;32m? \e[0;33m[y/N]\e[0m ";
            char choice = (char)cin.get();
            cout << endl;
            if(choice != 'y') {
                cout << "\e[1;33mExiting\e[0m" << endl;
                return 1;
            }
        }
        
        if(int res = depend(cfgRoot, env, prefix)) {
            return res;
        }

        const Setting &scripts = cfgRoot["scripts"];
        const Setting &installCmds = cfgRoot["install"];
        int nScripts = scripts.getLength();
        int nInstallCmds = installCmds.getLength();
        for(int i = 0; i < nScripts; i++) {
            const Setting &script = scripts[i];
            cout << "\e[1;32mRunning \e[0;31m" << script["name"].c_str() << "\e[0m" << endl;
            for(int j = 0; j < script["commands"].getLength(); j++) {
                if(int res = command::run(env, script["commands"][j].c_str())) {
                    cout << "\e[1;31mError " << res << "\e[0m" << endl;
                    help::printDepsError(cfgRoot);
                    return res;
                };
            }
        }
        cout << "\e[1;32mInstalling\e[0m" << endl;
        for(int i = 0; i < nInstallCmds; i++) {
            if(int res = command::run(env, installCmds[i].c_str())) {
                cout << "\e[1;31mError " << res << "\e[0m" << endl;
                help::printDepsError(cfgRoot);
                return res;
            };
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
            localDir = "~/.local";
        }
        return 0;
    }
}