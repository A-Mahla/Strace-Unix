# **************************************************************************** #
#                                                                              #
#                                                     :::       :::     :::    #
#    Makefile                                        :+:       :+: :+: :+:     #
#                                                  +:++:+     +:+  +  +:+      #
#    By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+       #
#                                              +#+    +#+   +#+     +#+        #
#    Created: 2023/10/17 02:01:51 by amahla  #+#      #+#  #+#     #+#         #
#    Updated: 2023/11/26 00:16:53 by amahla ###       ########     ########    #
#                                                                              #
# **************************************************************************** #


NAME	:= 	ft_strace
IMAGE	:= 	ubuntu
CC		:=	gcc
CFLAGS	:=	-Wall -Werror -Wextra
DFLAGS	:=	-MMD -MP
INC		:=	-I inc
OUTDIR 	:=	obj
SRCDIR	:=	src
SRC		:=	$(addprefix $(SRCDIR)/,	strace.c		\
									process.c		\
									print_syscall.c	\
									print_type.c	\
									path.c			\
									signals.c		\
									split.c			\
									)
OBJ		:=	$(SRC:.c=.o)
DEP 	:=	$(SRC:.c=.d)
RM		:=	rm -rf


all		: $(NAME)

$(OUTDIR)/%.o	: %.c 
	$(CC) $(DFLAGS) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME)	: $(OUTDIR)	$(addprefix $(OUTDIR)/, $(OBJ))
	$(CC) $(CFLAGS) -o $@ $(addprefix $(OUTDIR)/, $(OBJ)) $(INC)

$(OUTDIR)	:
	@mkdir -p $(addprefix $@/, $(SRCDIR))

.PHONY	: all debug clean fclean re

run		: all
	docker build . -t $(IMAGE)
	docker run -it --entrypoint=/bin/bash $(IMAGE)

debug	: CFLAGS=-g3 -Wall -Werror -Wextra
debug	: all

clean	:
	$(RM) $(OUTDIR)

fclean	: clean
	$(RM) $(NAME)
	docker system prune -af

re		: fclean
	make all

-include	$(addprefix $(OUTDIR)/, $(DEP)))
