# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jochang <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/19 01:31:43 by jochang           #+#    #+#              #
#    Updated: 2018/09/24 02:11:37 by jochang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CHK = chk/ft_isalnum.c \
	  chk/ft_isalpha.c \
	  chk/ft_isascii.c \
	  chk/ft_isdigit.c \
	  chk/ft_isprint.c \
	  chk/ft_isspace.c \
	  chk/ft_placevalue.c \
	  chk/ft_wordcount.c \
	  chk/ft_wordlen.c \

CNV = cnv/ft_atoi.c \
	  cnv/ft_itoa.c \

BIT = bit/ft_swapendian.c \
	  bit/ft_swapnendian.c \
	  bit/ft_swapendian64.c \
	  bit/ft_swapnendian64.c \

GET = get/ft_getopt.c \
	  get/ft_getstdin.c \
	  get/ft_getnstdin.c \
	  get/get_next_line.c \

LST = lst/ft_lstadd.c \
	  lst/ft_lstdel.c \
	  lst/ft_lstdelone.c \
	  lst/ft_lstiter.c \
	  lst/ft_lstmap.c \
	  lst/ft_lstnew.c \

MEM = mem/ft_bzero.c \
	  mem/ft_memalloc.c \
	  mem/ft_memccpy.c \
	  mem/ft_memchr.c \
	  mem/ft_memcmp.c \
	  mem/ft_memcpy.c \
	  mem/ft_memdel.c \
	  mem/ft_memmove.c \
	  mem/ft_memset.c \
	  mem/ft_realloc.c \

PUT = put/ft_putchar.c \
	  put/ft_putchar_fd.c \
	  put/ft_putwchar.c \
	  put/ft_putendl.c \
	  put/ft_putendl_fd.c \
	  put/ft_putnbr.c \
	  put/ft_putnbr_fd.c \
	  put/ft_putstr.c \
	  put/ft_putstr_fd.c \
	  put/ft_printmemory.c \

STR = str/ft_strcat.c \
	  str/ft_strccpy.c \
	  str/ft_strcpy.c \
	  str/ft_strchr.c \
	  str/ft_strclr.c \
	  str/ft_strcmp.c \
	  str/ft_strdel.c \
	  str/ft_strdup.c \
	  str/ft_strequ.c \
	  str/ft_striter.c \
	  str/ft_striteri.c \
	  str/ft_strjoin.c \
	  str/ft_strlcat.c \
	  str/ft_strlen.c \
	  str/ft_strlower.c \
	  str/ft_strmap.c \
	  str/ft_strmapi.c \
	  str/ft_strncat.c \
	  str/ft_strncmp.c \
	  str/ft_strncpy.c \
	  str/ft_strndup.c \
	  str/ft_strnequ.c \
	  str/ft_strnew.c \
	  str/ft_strnstr.c \
	  str/ft_strrchr.c \
	  str/ft_strrev.c \
	  str/ft_strsplit.c \
	  str/ft_strsplitwsp.c \
	  str/ft_strstr.c \
	  str/ft_strsub.c \
	  str/ft_strtrim.c \
	  str/ft_strupper.c \
	  str/ft_tolower.c \
	  str/ft_toupper.c \

SRC = $(CHK) $(CNV) $(BIT) $(GET) $(LST) $(MEM) $(PUT) $(STR)

OBJ = *.o

INC = inc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@echo "\033[32mmaking libft...\033[0m"
	@gcc $(CFLAGS) -c $(SRC) -I $(INC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@echo "\033[33mcleaning libft repository...\033[0m"
	@/bin/rm -f $(OBJ)

fclean: clean
	@echo "\033[33mremoving libft library file...\033[0m"
	@/bin/rm -f $(NAME)

re: fclean all
