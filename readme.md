# app
> A Linux-only (maybe OSX) replacement for hubcap using libconfig
## Dependencies
- Build
  - [Meson](https://mesonbuild.com)
  - Ninja (Included with Meson)
  - A working C++17 compiler (GCC or Clang should work)
- Runtime
  - [libconfig++](https://github.com/hyperrealm/libconfig)
## Installation
Bootstrap it! \
First, build it:
```sh
$ meson build
$ ninja -C build
```
Then, bootstrap:
```sh
$ ./build/app install
```
This will build it again, and then spit out a binary in `~/.local/bin`. Make sure that's in your `$PATH`.
## Usage
Clone a repository that uses app (automatic cloning is on the way), and run `app install`. This will build and install the project.

## Add to your project
Copy and paste the contents of `.app/config` in this repo over to `.app/config` in your project, and customize it to your needs. An `init` command that does this for you is on the way.