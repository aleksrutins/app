#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
#include "util.h"
using namespace std;
using namespace libconfig;

namespace RunCmd {
    int run(int argc, char **argv, string name, const Setting &cfgRoot, string env) {
        for (int i = 0; i < cfgRoot["scripts"].getLength(); i++) {
            if(cfgRoot["scripts"][i]["name"].c_str() == string(argv[2])) break;
            if(i == (cfgRoot["scripts"].getLength() - 1)) {
                cout << "\e[1;31mNo script named \e[0m\e[0;31m" << argv[2] << "\e[0m" << endl;
                return 1;
            }
        }
        for (int i = 0; i < cfgRoot["scripts"].getLength(); i++) {
            const Setting &script = cfgRoot["scripts"][i];
            cout << "\e[1;32mRunning \e[0;31m" << script["name"].c_str() << "\e[0m" << endl;
            for (int j = 0; j < script["commands"].getLength(); j++) {
                if(int res = command::run(env, script["commands"][j].c_str())) {
                    cout << "\e[1;31mError " << res << "\e[0m" << endl;
                    help::printDepsError(cfgRoot);
                    return res;
                };
            }
            if(string(script["name"].c_str()) == string(argv[2])) return 0;
        }
        return 0;
    }
}