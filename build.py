# custom python build system
# to easily compile the source code efficiently
# ----------------------------------------------------------------

import os
import shutil

# TODO: make link() be more extensible


class BuildSystem:
    def __init__(self, args=None):
        # remove __temp__ if compilation fails
        if os.path.isdir("__temp__"):
            shutil.rmtree("__temp__")

        # setup basic temp folder tree
        os.system("mkdir __temp__/")  # root
        os.system("mkdir __temp__/build/x86_64/ -p")  # for kernel .bin file
        os.system("mkdir __temp__/kernel/ -p")  # for source files *.o
        os.system("mkdir __temp__/x86_64/ -p")  # for asm files

        os.system(
            "touch __temp__/build/x86_64/kernel.bin"
        )  # creating an empty bin file

        self.hfiles = []
        self.hBuildFiles = []
        self.cfiles = []
        self.cBuildFiles = []
        self.asmfiles = []
        self.asmBuildFiles = []
        self.linkerfiles = []

    def sourceFiles(self, extension):
        fileList = []
        buildFileList = []
        lastFile = ""

        for root, dirs, files in os.walk("."):
            for file in files:
                if file.endswith(extension):
                    fileList.append(os.path.join(root, file))

        for x in range(len(fileList)):
            tmp = fileList[x].split("/")
            for x in range(len(tmp)):
                lastFile = tmp[x]
            lastFile = lastFile.replace(extension, ".o")
            buildFileList.append(lastFile)
            lastFile = ""

        return fileList, buildFileList

    def scrapeSrcFiles(self):
        # files - h

        self.hfiles, self.hBuildFiles = self.sourceFiles(".h")

        # files - c
        self.cfiles, self.cBuildFiles = self.sourceFiles(".c")

        # files - asm
        self.asmfiles, self.asmBuildFiles = self.sourceFiles(".asm")

        # files - ld
        self.linkerfiles, x = self.sourceFiles(".ld")

    def compileSource(self):
        for x in range(len(self.hfiles)):
            self.runGCCX86(self.hfiles[x], self.hBuildFiles[x])

        for x in range(len(self.cfiles)):
            self.runGCCX86(self.cfiles[x], self.cBuildFiles[x])

        for x in range(len(self.asmfiles)):
            self.runNASMX86(self.asmfiles[x], self.asmBuildFiles[x])

    def runGCCX86(self, file, buildFile):
        ofile = buildFile
        ofile = "__temp__/kernel/" + ofile
        command = (
            "x86_64-elf-gcc -c -I include/ -I . -ffreestanding " + file + " -o " + ofile
        )
        os.system(command)

    def runNASMX86(self, file, buildFile):
        ofile = buildFile
        ofile = "__temp__/x86_64/" + ofile
        command = "nasm -f elf64 " + file + " -o " + ofile
        os.system(command)

    def link(self):
        command = "x86_64-elf-ld -n -o __temp__/build/x86_64/kernel.bin -T bootloader/x86_64/linker.ld __temp__/kernel/main.o __temp__/x86_64/header.o __temp__/x86_64/main.o __temp__/x86_64/main64.o"
        os.system(command)

    def isoGen(self):
        os.system(
            "cp __temp__/build/x86_64/kernel.bin bootloader/x86_64/iso/boot/kernel.bin"
        )
        os.system(
            "grub-mkrescue /usr/lib/grub/i386-pc -o kernel.iso bootloader/x86_64/iso"
        )


if __name__ == "__main__":
    x = BuildSystem()
    print("\033[32m" + "Loaded Build System " + "/U+2705")
    print('\033[39m')
    x.scrapeSrcFiles()
    print("\033[32m" + "Scraped Source Files ")
    print('\033[39m')
    x.compileSource()
    print("\033[32m" + "Compiled Source Files ")
    print('\033[39m')
    x.link()
    print("\033[32m" + "Linked Source Files ")
    print('\033[39m')
    x.isoGen()
    print("\033[32m" + "Generated ISO ")
    print('\033[39m')

    if os.path.isdir("__temp__"):
        shutil.rmtree("__temp__")
    print("\033[32m" + "Removed __temp__ file ")
    print('\033[39m')
