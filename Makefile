default:
	nasm -fbin src/x86/boot/bootloader.S -o bin/bootloader.bin
	nasm -felf32 src/x86/kernel/kernel.S -o objres/kasm.o
	nasm -felf32 src/x86/kernel/interrupts/impl/ISR.S -o obj/israsm.o
	gcc -c -m32 src/x86/kernel/kmain.c -ffreestanding -fno-pie -fstack-protector -mgeneral-regs-only -o obj/kmain.o
	gcc -c -m32 src/x86/kernel/interrupts/impl/exceptions.c -ffreestanding -fno-pie -fstack-protector -mgeneral-regs-only -o obj/exceptions.o
	gcc -c -m32 src/x86/kernel/interrupts/impl/IDT.c -ffreestanding -fno-pie -fstack-protector -mgeneral-regs-only -o obj/idt.o
	gcc -c -m32 src/x86/kernel/interrupts/impl/ISR.c -ffreestanding -fno-pie -fstack-protector -mgeneral-regs-only -o obj/isr.o
	gcc -c -m32 src/x86/kernel/util/impl/strings.c -ffreestanding -fno-pie -fstack-protector -o obj/strings.o
	gcc -c -m32 src/x86/kernel/drivers/impl/VGA.c -ffreestanding -fno-pie -fstack-protector -o obj/vga.o
	gcc -c -m32 src/x86/kernel/drivers/impl/IO.c -ffreestanding -fno-pie -fstack-protector -o obj/io.o
	gcc -c -m32 src/x86/kernel/drivers/impl/PIT.c -ffreestanding -fno-pie -fstack-protector -o obj/pit.o
	ld -melf_i386 -Tlink.ld objres/*.o obj/*.o --oformat binary -o bin/kernel.bin
	cat bin/bootloader.bin bin/kernel.bin > bin/NekoOS.bin
	sudo dd if=/dev/zero of=NekoOS.img bs=1024 count=1440
	@ # Put the OS stuff in the image.
	sudo dd if=bin/NekoOS.bin of=NekoOS.img

all:
	make; make burnusb; make runusb

burnusb:
	sudo dd if=NekoOS.img of=/dev/sdb

runusb:
	sudo qemu-system-x86_64 -hda /dev/sdb -monitor stdio -d int -no-reboot -D logfile.txt -M smm=off 

run:
	sudo qemu-system-x86_64 -fda NekoOS.img -monitor stdio
