#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smonroe <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/26 22:02:30 by smonroe           #+#    #+#              #
#    Updated: 2018/09/10 00:38:50 by smonroe          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ASM = asm

NAME = corewar

SRCDIR = srcs

SRCA = srcs/asm.c srcs/op.c srcs/funcy.c

SRCB = srcs/corewar.c srcs/vm.c srcs/pc.c srcs/display.c srcs/cycle.c

INC = -I libft -I . -L libft -lft

FLG = -Wall -Werror -Wextra

FSAN = -fsanitize=address

all: $(NAME)

$(NAME):
	gcc $(FLG) -o $(ASM) $(SRCA) $(INC)
	gcc $(FLG) -o $(NAME) $(SRCB) $(INC)

clean:
	/bin/rm -rf *~ \#*\# a.out* $(OBJDIR)/*.o

fclean: clean
	/bin/rm -rf $(ASM) $(NAME)

re: fclean all

lldb:
	gcc $(FLG) -o $(ASM) $(SRCA) $(INC) -g
	gcc $(FLG) -o $(NAME) $(SRCB) $(INC) -g

fsan:
	gcc $(FLG) -c $(SRCS) -g $(FSAN) -g $(FSAN)
	mv *.o $(OBJDIR)
	gcc $(FLG) -o $(ASM) $(SRCA) $(INC) -g $(FSAN)
	gcc $(FLG) -o $(NAME) $(SRCB) $(INC) -g $(FSAN)
