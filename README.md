# SINX
 A basic 64bit multiboot2 compliant operating system for learning purpouses

## BUILDING
 make sure you have docker and qemu installed and running
 1. download and extract the source
 2. cd into source directory
 3. create a docker image using the provided Dockerfile (you only have to do this once!)
`docker build buildenv -t sinx-buildenv`
 4. enter the docker environment
  - Linux or MacOS: `docker run --rm -it -v "$(pwd)":/root/env sinx-buildenv`
  - Windows (CMD): `docker run --rm -it -v "%cd%":/root/env sinx-buildenv`
 5. run makefile inside docker env
 `make build`
 6. exit docker environment
 `exit`
 7. run the iso!
 `sudo qemu-system-x86_64 kernel.iso`
 
## TODO
- [x] do a very basic code organize
- [x] make a keyboard driver
- [x] add a more advanced keybord input system
- [x] clean up / remove print.c
- [x] make a red screen of death / kernel panic state
- [x] add the ability to BACKSPACE
- [x] do a complete filetree redisign
- [x] GET 64 BIT/LONG MODE SUPPORT
- [x] make a basic input system
- [x] rewrite VGA driver for stability/font control
- [x] make a more advanced userland shell
- [x] add basic command framework
- [x] fix enter and backspace bugs
- [x] add a blinking cursor
- [x] read from RTC
- [x] rewrite all c code into file.c and file.h respectively
- [x] create/modify a better build system
- [ ] add inturupts
- [ ] test on real hardware
- [ ] organize functions into appropriate files
- [ ] add full ASCII compatability
- [ ] convert project to camelCase
- [ ] organize #include statements to remove repeats
- [ ] add POSIX compliance
- [ ] add filesystem support
- --------------------------------------------
