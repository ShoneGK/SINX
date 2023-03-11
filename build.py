# custom python build system
# to easily compile the source code efficiently
# ----------------------------------------------------------------

import os
import shutil

class BuildSystem():

    def __init__(self, args=None):

        # remove __temp__ if compilation fails
        if os.path.isdir("__temp__"):
            shutil.rmtree("__temp__")
        
        # search for all source files - h
        hfiles, hBuildFiles = self.sourceFiles(".h")
        # search for all source files - c
        cfiles, cBuildFiles = self.sourceFiles(".c")
        # search for all source files - asm
        asmfiles, asmBuildFiles = self.sourceFiles(".asm")
        # search for all source files - ld
        linkerfiles, x = self.sourceFiles(".ld")
        x = None

        # begin compilation




    def sourceFiles(self, extension):
        fileList = []
        buildFileList = []
        lastFile = ""

        for root, dirs, files in os.walk("."):
            for file in files:
                if file.endswith(".ld"):
                    fileList.append(os.path.join(root, file))

        for x in range(len(fileList)):
            tmp = fileList[x].split("/")
            for x in range(len(tmp)):
                lastFile = tmp[x]
            lastFile = lastFile.replace(extension, ".o")
            buildFileList.append(lastFile)
            lastFile = ""

        return fileList, buildFileList
        
    def runGCCX86(self, file, buildFile):
        ofile = buildFile
        ofile = "__temp__" + ofile
        os.system("x86_64-elf-gcc -c -I include/ -I . -ffreestanding", file, "-o", ofile)


x = BuildSystem()