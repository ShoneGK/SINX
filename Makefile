kernel_source_files := $(shell find init/ -name *.c)
kernel_object_files := $(patsubst init/%.c, __temp__/kernel/%.o, $(kernel_source_files))

x86_64_c_source_files := $(shell find include/ -name *.c)
x86_64_c_object_files := $(patsubst include/%.c, __temp__/x86_64/%.o, $(x86_64_c_source_files))

x86_64_asm_source_files := $(shell find arch/x86_64/boot/ -name *.asm)
x86_64_asm_object_files := $(patsubst arch/x86_64/boot/%.asm, __temp__/x86_64/%.o, $(x86_64_asm_source_files))

x86_64_object_files := $(x86_64_c_object_files) $(x86_64_asm_object_files)

$(echo Compiling Source)

$(kernel_object_files): __temp__/kernel/%.o : init/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I include/ -I . -ffreestanding $(patsubst __temp__/kernel/%.o, init/%.c, $@) -o $@

$(x86_64_c_object_files): __temp__/x86_64/%.o : include/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I include/ -I . -ffreestanding $(patsubst __temp__/x86_64/%.o, include/%.c, $@) -o $@

$(x86_64_asm_object_files): __temp__/x86_64/%.o : arch/x86_64/boot/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst __temp__/x86_64/%.o, arch/x86_64/boot/%.asm, $@) -o $@

.PHONY: build
build: $(kernel_object_files) $(x86_64_object_files)
#	mkdir __temp__
#	mkdir __temp__/kernel
#	mkdir __temp__/x86_64
#	mkdir __temp__/x86_64/boot
	mkdir __temp__/build
	mkdir __temp__/build/x86_64
	touch __temp__/build/x86_64/kernel.bin
	x86_64-elf-ld -n -o __temp__/build/x86_64/kernel.bin -T bootloader/x86_64/linker.ld $(kernel_object_files) $(x86_64_object_files) && \
	cp __temp__/build/x86_64/kernel.bin bootloader/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o kernel.iso bootloader/x86_64/iso

run:
	make build