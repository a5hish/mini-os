OBJ=kernel_main.o loader.o kprint.o

KERNEL_IMAGE=kernel
OUTPUT=bin
OS_ISO=$(OUTPUT)/iso

CC=gcc
INCLUDES=include
CFLAGS=-m32 -I$(INCLUDES) -c
LD_SCRIPT=klinker.ld

AS=nasm
ASFLAGS=-f elf32


all: $(OBJ)
	ld -m elf_i386 -T $(LD_SCRIPT) -o $(KERNEL_IMAGE) $(OBJ)
	mkdir -p $(OUTPUT)/
	cp *.o kernel $(OUTPUT)/

run: gen-iso
	qemu-system-i386 -boot d -cdrom my_os.iso

gen-iso: kernel
	mkdir -p $(OS_ISO)/boot/grub
	cp grub.cfg $(OS_ISO)/boot/grub/
	grub-file --is-x86-multiboot $(OUTPUT)/kernel
	cp kernel $(OS_ISO)/boot/
	grub-mkrescue -o my_os.iso $(OS_ISO)

loader.o: loader.asm
	$(AS) $(ASFLAGS) loader.asm -o loader.o

kernel_main.o: kernel_main.c kprint.o
	$(CC) $(CFLAGS) kernel_main.c -o kernel_main.o

kprint.o: kprint.c
	$(CC) $(CFLAGS) kprint.c -o kprint.o

clean:
	rm -rf $(OUTPUT)
	rm *.o *.iso kernel
