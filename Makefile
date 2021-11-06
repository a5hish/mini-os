OBJECT=loader.asm
OUTPUT=bin
OS_ISO=$(OUTPUT)/iso

CC=gcc
CFLAGS=-m32 -c

AS=nasm
ASFLAGS=-f elf32


all: loader.o kernel_main.o klinker.ld
	ld -m elf_i386 -T klinker.ld -o kernel kernel_main.o loader.o
	mkdir -p $(OUTPUT)/
	cp *.o kernel $(OUTPUT)/

run: gen_iso
	qemu-system-i386 -boot d -cdrom my_os.iso

gen_iso: kernel
	mkdir -p $(OS_ISO)/boot/grub
	cp grub.cfg $(OS_ISO)/boot/grub/
	grub-file --is-x86-multiboot $(OUTPUT)/kernel
	cp kernel $(OS_ISO)/boot/
	grub-mkrescue -o my_os.iso $(OS_ISO)

loader.o: loader.asm
	$(AS) $(ASFLAGS) loader.asm -o loader.o

kernel_main.o: kernel_main.c
	$(CC) $(CFLAGS) kernel_main.c -o kernel_main.o

clean:
	rm -rf $(OUTPUT)
	rm *.o *.iso kernel
