#include <string>
#include <libconfig.h++>
namespace RunCmd {
    int run(int argc, char **argv, std::string name, const libconfig::Setting &cfgRoot, std::string env);
}