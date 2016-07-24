##
##
##
##

ASM		=	nasm

NAME		=	bootloader.o

ASM_SRCS	=	bootloader.S

ASM_OBJS	=	$(ASM_SRCS:.S=.o)

ASMFLAGS	+=	-f bin

RM		=	rm -rf

all		:	$(NAME)

clean		:
			$(RM) $(ASM_OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

%.o		:	%.S
			$(ASM) $(ASMFLAGS) -o $@ $<

.PHONY		:	all clean fclean re
