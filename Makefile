#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smonroe <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/26 22:02:30 by smonroe           #+#    #+#              #
#    Updated: 2018/09/06 08:49:47 by smonroe          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ASM = asm

NAME = corewar

SRCDIR = srcs

SRCA = asm.c op.c funcy.c

SRCB = corewar.c vm.c pc.c display.c cycle.c

SRCS = $(addprefix $(SRCDIR)/,$(SRCA)) $(addprefix $(SRCDIR)/,$(SRCB))

OBJDIR = objs

AOBJ = $(SRCA:.c=.o)

OBJA = $(addprefix $(OBJDIR)/,$(AOBJ))

COBJ = $(SRCB:.c=.o)

OBJC = $(addprefix $(OBJDIR)/,$(COBJ))

INC = -I libft -I . -L libft -lft

FLG = -Wall -Werror -Wextra

FSAN = -fsanitize=address

all: $(NAME)

$(NAME):
	gcc $(FLG) -c $(SRCS)
	mv *.o objs/
	gcc $(FLG) -o $(ASM) $(OBJA) $(INC)
	gcc $(FLG) -o $(NAME) $(OBJC) $(INC)

clean:
	/bin/rm -rf *~ \#*\# a.out* $(OBJDIR)/*.o

fclean: clean
	/bin/rm -rf $(ASM) $(NAME)

re: fclean all

lldb:
	gcc $(FLG) -c $(SRCS) -g
	mv *.o objs/
	gcc $(FLG) -o $(ASM) $(OBJA) $(INC) -g
	gcc $(FLG) -o $(NAME) $(OBJC) $(INC) -g

fsan:
	gcc $(FLG) -c $(SRCS) -g $(FSAN) -g $(FSAN)
	mv *.o objs/
	gcc $(FLG) -o $(ASM) $(OBJA) $(INC) -g $(FSAN)
	gcc $(FLG) -o $(NAME) $(OBJC) $(INC) -g $(FSAN)
