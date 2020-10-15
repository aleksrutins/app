project('app', 'cpp')
add_project_arguments(['--std=c++17'], language: 'cpp')
libconfig = dependency('libconfig++')
executable('app', ['main.cpp', 'InstallCmd.cpp', 'command.cpp', 'help.cpp', 'RunCmd.cpp'], dependencies: [libconfig], install : true)
