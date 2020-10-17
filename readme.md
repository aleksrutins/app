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
Clone this repository and run `install.sh`. This will notify you if any dependencies are not found.
## Updating
Run:
```sh
$ app install munchkinhalfling/app
```
## Usage
### With a GitHub project
Run:
```sh
$ app install <org>/<repo>
```
### With a non-GitHub project
Clone the project, `cd` into its directory, and run `app install`.
## Add to your project
Copy and paste the contents of `.app/config` in this repo over to `.app/config` in your project, and customize it to your needs. An `init` command that does this for you is on the way.