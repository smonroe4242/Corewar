#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smonroe <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/26 22:02:30 by smonroe           #+#    #+#              #
#    Updated: 2018/09/05 17:23:52 by smonroe          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ASM = asm

NAME = corewar

SRCA = asm.c op.c funcy.c

SRCC = corewar.c

INC = -I libft -I . -L libft -lft

FLG = -Wall -Werror -Wextra

FSAN = -fsanitize=address

all: $(NAME)

$(NAME):
	gcc $(FLG) -o $(ASM) $(SRCA) $(INC)
	gcc $(FLG) -o $(NAME) $(SRCC) $(INC)

clean:
	rm -rf *~ \#*\# a.out*

fclean: clean
	rm -rf $(ASM) $(NAME)

re: fclean all

lldb:
	gcc $(FLG) -o $(ASM) $(SRCA) $(INC) -g
	gcc $(FLG) -o $(NAME) $(SRCC) $(INC) -g

fsan:
	gcc $(FLG) -o $(ASM) $(SRCA) $(INC) -g $(FSAN)
	gcc $(FLG) -o $(NAME) $(SRCC) $(INC) -g $(FSAN)
