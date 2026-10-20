clean:
	rm -rf *.o
kernel:
	gcc -g -m32 -fno-stack-protector -ffreestanding -fno-builtin -c boot/kernel/Main.c -o Main.o
	gcc -g -m32 -fno-stack-protector -ffreestanding -fno-builtin -c boot/kernel/gdt.c -o gdt.o
	gcc -g -m32 -fno-stack-protector -ffreestanding -fno-builtin -c boot/kernel/vga.c -o vga.o
	gcc -g -m32 -fno-stack-protector -ffreestanding -fno-builtin -c boot/kernel/idt.c -o idt.o
	gcc -g -m32 -fno-stack-protector -ffreestanding -fno-builtin -c boot/kernel/util.c -o util.o
assembly:
	nasm -f elf32 boot/boot.s -o boot.o
	nasm -f elf32 boot/kernel/gdt.s -o gdtasm.o
	nasm -f elf32 boot/kernel/idt.s -o idtasm.o
linker:
	ld -m elf_i386 -T boot/linker.ld -o kernel Main.o gdt.o vga.o gdtasm.o boot.o util.o idt.o idtasm.o
ISO:
	grub-mkrescue -o OS.iso ISO/