from os import getAppFilename, commandLineParams
import decls
from commands/install import installCmd
from commands/help import helpCmd
echo "\e[1;32mStarting...\e[0m"
echo "\e[1;32mConfig directory is \e[0;31m", configDir, "\e[0m"
let args = commandLineParams()
case args[0]
of "help": args.helpCmd(getAppFilename())
of "install": args.installCmd()