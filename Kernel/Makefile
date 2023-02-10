kernel.o : kernel.c
	gcc -m32 -ffreestanding -c kernel.c -o kernel.o

kernel_entry.o : kernel_entry.asm
	nasm -felf kernel_entry.asm -o kernel_entry.o

link:
	ld -m elf_i386 -o kernel.bin -Ttext 0x1000 kernel_entry.o kernel.o
	ld -m elf_i386 -o Kernel.bin -Ttext 0x1000 kernel.bin --oformat binary
	rm kernel.bin

clean:
	-rm *.o *.bin

all:
	make clean
	make kernel.o
	make kernel_entry.o
	make link