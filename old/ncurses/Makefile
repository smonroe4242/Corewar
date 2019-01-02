#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smonroe <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/06 20:04:13 by smonroe           #+#    #+#              #
#    Updated: 2018/09/06 20:11:02 by smonroe          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = go

SRC = main.c

INC = -I ../libft -lncurses -L ../libft -lft

FLG = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	gcc $(FLG) -o $(NAME) $(SRC) $(INC)

clean:
	/bin/rm -rf *~ a.out*

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all