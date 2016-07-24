##
##
##
##

CC		=	gcc
ASM		=	nasm
LD		=	ld

NAME		=	kernel.bin

SRCS		=	kernel.c screen.c utils.c

OBJS		=	$(SRCS:.c=.o)

CFLAGS		+=	-W -Wall -Wextra
CFLAGS		+=	-ffreestanding
CFLAGS		+=	-m32

LDFLAGS		+=	--oformat binary -Ttext 1000
LDFLAGS		+=	-m elf_i386

RM		=	rm -rf

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(LD) $(LDFLAGS) $(OBJS) -o $(NAME)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
