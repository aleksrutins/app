from install import nil
proc helpCmd*(args: seq[string], appFilename: string): void =
    echo "\e[33m----------\e[0m"
    echo "Usage: \e[1;32m", appFilename, " \e[0m<\e[0;31mcommand\e[0m> [\e[0;33margs\e[0m]"
    echo "Commands:"
    echo install.help()