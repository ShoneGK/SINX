# MYOS
A basic multiboot2 compliant operating system for learning purposes
NOTE - THIS IS A HOBBY PROJECT SO DON'T EXPECT MUCH

## CHANGELOG

completely cleaned up source and distributed source to multiple files

## BUILDING
 make sure you have docker and qemu installed and running
 1. download and extract the source
 2. cd into source directory
 3. create a docker image using the provided Dockerfile (you only have to do this once!)
`docker build buildenv -t myos-buildenv`
 4. enter the docker environment
  - Linux or MacOS: `docker run --rm -it -v "$(pwd)":/root/env myos-buildenv`
  - Windows (CMD): `docker run --rm -it -v "%cd%":/root/env myos-buildenv`
 5. run makefile inside docker env
 `make build`
 6. exit docker environment
 `exit`
 7. run the iso!
 `sudo qemu-system-x86_64 kernel.iso`
 
## TODO
- [x] do a very basic code organize
- [x] make a keyboard driver
- [x] add keyboard support
- [x] add a more advanced keybord input system
- [ ] convert project to camelCase
- [ ] organize #include statements to remove repeats
- [ ] fix enter and backspace bugs
- [ ] add basic command framework
- [x] clean up / remove print.c
- [ ] make a more advanced userland shell
- [x] make a red screen of death / kernel panic state
- [x] add the ability to BACKSPACE :D
- [x] do a complete filetree redisign
- [x] GET 64 BIT/LONG MODE SUPPORT :D
- [x] make a basic input system
- [ ] add POSIX compliance
- --------------------------------------------
