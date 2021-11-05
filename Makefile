OBJECT=loader.asm
OUTPUT=bin

AS=nasm
ASFLAGS=-f elf32

all: loader.o
	mkdir -p $(OUTPUT)/
	cp *.o $(OUTPUT)/

loader.o: loader.asm
	$(AS) $(ASFLAGS) loader.asm -o loader.o

clean:
	rm -rf $(OUTPUT)
	rm *.o
