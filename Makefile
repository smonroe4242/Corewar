#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smonroe <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/26 22:02:30 by smonroe           #+#    #+#              #
#    Updated: 2018/08/26 23:34:22 by smonroe          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = asm

SRC = asm.c op.c

INC = -I libft -I . -L libft -lft

FLG = -Wall -Werror -Wextra

FSAN = -fsanitize=address

all: $(NAME)

$(NAME):
	gcc $(FLG) -o $(NAME) $(SRC) $(INC)

clean:
	rm -rf *~ \#*\# a.out*

fclean: clean
	rm -rf $(NAME)

re: fclean all

lldb:
	gcc $(FLG) -o $(NAME) $(SRC) $(INC) -g

fsan:
	gcc $(FLG) -o $(NAME) $(SRC) $(INC) -g $(FSAN)