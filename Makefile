##
##
##
##

DD		=	dd conv=notrunc > /dev/null 2> /dev/null
MAKE		=	make
QEMU		=	qemu-system-i386

NAME		=	yOS.img

BOOTLOADER	=	bootloader/bootloader.o
KERNEL		=	kernel/kernel.bin

RM		=	rm -rf

all		:	$(NAME)

$(NAME)		:	$(BOOTLOADER) $(KERNEL) disk
			$(DD) if=$(BOOTLOADER) of=$(NAME)
			$(DD) if=$(KERNEL) of=$(NAME) obs=1 seek=512
$(BOOTLOADER)	:
			$(MAKE) -C bootloader

$(KERNEL)	:
			$(MAKE) -C kernel

disk		:
			dd if=/dev/zero of=$(NAME) bs=1M count=10 > /dev/null 2> /dev/null

clean		:
			$(MAKE) -C bootloader clean
			$(MAKE) -C kernel clean

fclean		:	clean
			$(MAKE) -C bootloader fclean
			$(MAKE) -C kernel fclean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re

run		:
			$(QEMU) $(NAME)
r		:	all run
