# Find all .c files in the project
C_FILES := $(shell find . -name '*.c')
C_OBJFILES := $(patsubst %.c, __temp__/kernel/%.o, $(C_FILES))

# Find all .asm files in the project
ASM_FILES := $(shell find . -name '*.asm')
ASM_OBJ_FILES := $(patsubst %.asm, __temp__/x86_64/%.o, $(ASM_FILES))


CC=x86_64-elf-gcc
LD=x86_64-elf-ld
CFLAGS=-c -I include/ -I . -I include/sinx/ -ffreestanding
ASMFLAGS=-f elf64


# create list of .o files
OBJ := $(C_OBJFILES) $(ASM_OBJ_FILES)

$(echo Compiling Source)

# compile .c files to .o
$(C_OBJFILES): __temp__/kernel/%.o : %.c
	mkdir -p $(dir $@) && \
	$(CC) $(CFLAGS) $(patsubst __temp__/kernel/%.o, %.c, $@) -o $@

# compile .asm file to .o
$(ASM_OBJ_FILES): __temp__/x86_64/%.o : %.asm
	mkdir -p $(dir $@) && \
	nasm  $(ASMFLAGS) $(patsubst __temp__/x86_64/%.o, %.asm, $@) -o $@

.PHONY: build
build: $(OBJ)
	mkdir __temp__/build
	mkdir __temp__/build/x86_64
	touch __temp__/build/x86_64/kernel.bin
	x86_64-elf-ld -n -o __temp__/build/x86_64/kernel.bin -T bootloader/x86_64/linker.ld $(OBJ) && \
	cp __temp__/build/x86_64/kernel.bin bootloader/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o kernel.iso bootloader/x86_64/iso && \
	rm -r __temp__\