#!/bin/sh
depnotfound() {
    printf "\e[1;31mnot found\e[0m\n"
    echo
    printf "\e[31m$1 was not found. Please make sure it is installed and configured correctly.\e[0m\n"
}
check() {
    printf "\e[1;32m$1 \e[1;33m...\e[0m "
    ($2 > /dev/null 2>&1 && printf "\e[1;32mfound\e[0m\n") || (depnotfound $1 && exit 1)
}
printf "\e[1;32mInstalling app...\e[0m\n"
echo
printf "\e[1;32mChecking dependencies...\e[0m\n"
check "Meson" "meson --version" || exit 1
check "Ninja" "ninja --version" || exit 1
check "libconfig++" "pkg-config --libs libconfig++" || exit 1
echo
printf "\e[1;32mBuilding...\e[0m\n"
rm -rf build
meson build || exit 1
ninja -C build || exit 1
echo
printf "\e[1;32mInstalling...\e[0m\n"
install -Dt ~/.local/bin/ -m 755 ./build/app
echo
printf "\e[1;32mSuccess! \e[0;32mapp is now installed in ~/.local/bin. Test it with \`app\`.\e[0m\n"
