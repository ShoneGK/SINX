# Find all .c files in the project
kernel_source_files := $(shell find . -name '*.c')
kernel_object_files := $(patsubst %.c, __temp__/kernel/%.o, $(kernel_source_files))

# Find all .asm files in the project
x86_64_asm_source_files := $(shell find . -name '*.asm')
x86_64_asm_object_files := $(patsubst %.asm, __temp__/x86_64/%.o, $(x86_64_asm_source_files))

# create list of .o files
x86_64_object_files := $(kernel_object_files) $(x86_64_asm_object_files)

$(echo Compiling Source)

# compile .c files to .o
$(kernel_object_files): __temp__/kernel/%.o : %.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I include/ -I . -ffreestanding $(patsubst __temp__/kernel/%.o, %.c, $@) -o $@

# compile .asm file to .o
$(x86_64_asm_object_files): __temp__/x86_64/%.o : %.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst __temp__/x86_64/%.o, %.asm, $@) -o $@

.PHONY: build
build: $(x86_64_object_files)
	mkdir __temp__/build
	mkdir __temp__/build/x86_64
	touch __temp__/build/x86_64/kernel.bin
	x86_64-elf-ld -n -o __temp__/build/x86_64/kernel.bin -T bootloader/x86_64/linker.ld $(x86_64_object_files) && \
	cp __temp__/build/x86_64/kernel.bin bootloader/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o kernel.iso bootloader/x86_64/iso && \
	rm -r __temp__\