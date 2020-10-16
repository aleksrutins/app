#include <string>
#include <libconfig.h++>
#include "util.h"
using namespace std;
using namespace libconfig;
namespace help {
    void printCmd(std::string name, std::string desc, bool header) {
        if(header) {
            std::cout << "\n\e[1;33m -- \e[1;32m" << name << "\e[0;33m - " << desc << "\e[1;33m --\e[0m\n" << std::endl;
        } else {
            std::cout << "\e[1;33m - \e[1;32m" << name << "\e[0;33m - " << desc << "\e[0m" << std::endl;
        }
    }
    void printHelp() {
        cout << "\n\e[1;32mAvailable commands:\e[0m" << endl;
        printCmd("install [repo]", "Install the current project, or if `repo` is specified, installs the specified GitHub repo", false);
        printCmd("list", "List scripts", false);
        printCmd("run <script>", "Run `script`.", false);
        printCmd("Anything else", "Print this message", false);
    }
    void printDepsError(const Setting &cfgRoot) {
        cout << "\n\e[1;32mPlease make sure you have the following dependencies installed:" << endl
             << "Compile-time:\e[0m" << endl;
        auto &compileDeps = cfgRoot["notify_dev_depends"];
        for(int i = 0; i < compileDeps.getLength(); i++) {
            cout << " \e[33m-\e[0m " << compileDeps[i].c_str() << endl;
        }
        cout << "\e[1;32mRun-time:\e[0m" << endl;
        auto &runTimeDeps = cfgRoot["notify_depends"];
        for(int i = 0; i < runTimeDeps.getLength(); i++) {
            cout << " \e[33m-\e[0m " << runTimeDeps[i].c_str() << endl;
        }
    }
}