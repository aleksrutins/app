project('app', 'cpp')
libconfig = dependency('libconfig++')
executable('app', ['main.cpp', 'InstallCmd.cpp', 'command.cpp', 'help.cpp', 'RunCmd.cpp'], dependencies: [libconfig], install : true)
