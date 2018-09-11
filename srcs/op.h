/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2018/09/06 05:39:50 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets. -> all values are in bytes
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
** This assumes an int is 4 bytes. Is it the same on current machine?
*/

#ifndef OP_H
# define OP_H
# include "../libft/libft.h"
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
# define COMMENT_LENGTH			(2048 + 8)
# define COREWAR_EXEC_MAGIC		0xea83f3
# define HEADER_SIZE			PROG_NAME_LENGTH + COMMENT_LENGTH + 8
# define END16(x) ((x << 8) | (x >> 8))
# define END3(x) ((x & 0xff0000) >> 8) | ((x & 0xff00) << 8)
# define END32(x) ((x << 24) | (x >> 24) | END3(x))
# define MEM(x) (x % MEM_SIZE)
# define IDX(x) (x % IDX_MOD)

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
	int							acb;
	int							flag2;
}								t_op;
/*
** This struct for declaring op tab in op.c
*/

typedef struct					s_label
{
	char						*name;
	uint16_t					loc;
	uint16_t					addr;
}								t_label;

typedef struct					s_byte
{
	char						*label;
	uint8_t						*code;
	uint16_t						count;
	t_label						*l;
}								t_byte;

void							asm_error(int n);
void							comp_error(int n, char *s, int l);
void							free_line(char **coms, char **args);
t_header						get_header(int fd);

void							t_byte_free(t_byte *x);
uint8_t							acb_byte(int i, char **args, int lc);
t_byte							arg_bytes(int i, char **args, int lc, uint8_t acb);
t_byte							get_bytes(char **coms, char **args, int lc);
t_byte							asm_parse(char *s, int lc);
t_byte							bytecode(int fds);

t_byte							init_t_byte(void);
t_byte							t_byte_append(t_byte org, t_byte app);
t_byte							label_append(t_byte org, t_byte app);
t_label							*add_lab(t_byte b, t_byte f, t_label *l);
uint8_t							*labelify(t_byte f, t_label *l);

#endif
