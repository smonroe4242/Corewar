/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2018/08/29 20:45:36 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets. -> all values are in bytes
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
** This assumes an int is 4 bytes. Is it the same on current machine?
*/

#ifndef OP_H
# define OP_H
# include "libft/libft.h"
# include <fcntl.h>

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4 * 1024) //4096 bytes
# define IDX_MOD				(MEM_SIZE / 8) //512 bytes
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6) //682 bytes

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char					t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
# define HEADER_SIZE			PROG_NAME_LENGTH + COMMENT_LENGTH + 8

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;
/*
** This header goes at the top of every warrior file
*/

typedef struct					s_op
{
	char						*name;
	int							argc;
	int							types[4];
	int							code;
	int							cycles;
	char						*desc;
	int							flag1;
	int							flag2;
}								t_op;
/*
** This struct for declaring op tab in op.c
*/

typedef struct					s_line
{
	char						*label;
	int							op;
	int							p[3];
}								t_line;

typedef struct					s_byte
{
	uint8_t						code[14];
	uint8_t						count;
	uint8_t						lcode;
	uint8_t						lbyte;
	t_byte						*next;
}

typedef struct					s_label
{
	char						*name;
	int							num;
	uint32_t					loc;
}								t_label;

void							asm_error(int n);
void							com_error(int n, char *s, int l);
uint32_t						endian_swap(uint32_t);
t_header						get_header(int fd);

t_byte							get_bytes(char **coms, char **args);
t_byte							asm_parse(char *s);
void							bytecode(int fds, int fdc);

#endif
