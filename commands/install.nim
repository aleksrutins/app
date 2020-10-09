proc installCmd*(args: seq[string]): void =
    echo ""
proc help*(): string =
    echo "\e[1;32minstall \e[0m<\e[0;31mpackage\e[0m>\tInstall \e[0;31mpackage\e[0m."