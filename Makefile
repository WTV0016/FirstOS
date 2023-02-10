write:
	dd conv=notrunc if=Bootsector/boot_sect.bin of=disk.img bs=512 seek=0 count=1
	dd conv=notrunc if=Kernel/Kernel.bin of=disk.img bs=512 seek=1

qemu:
	qemu-system-i386 -fda disk.img

all:
	make write
	make qemu