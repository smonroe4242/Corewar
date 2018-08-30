/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/08/29 21:04:24 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_op    op_tab[17] =
{//	text		#args		arg types									op code		#cycles			real name		?	?
	{"live", 	1,	{T_DIR}, 												1, 		10, 	"alive", 				0, 0},
//						2
	{"ld", 		2,	{T_DIR | T_IND, T_REG}, 								2, 		5, 		"load", 				1, 0},
//						2	|	4	,	1
	{"st", 		2,	{T_REG, T_IND | T_REG}, 								3, 		5, 		"store", 				1, 0},
//						1	,	4	|	1
	{"add", 	3,	{T_REG, T_REG, T_REG}, 									4, 		10, 	"addition", 			1, 0},
//						1	,	1	,	1
	{"sub", 	3,	{T_REG, T_REG, T_REG}, 									5, 		10, 	"subtraction",			1, 0},
//						1	,	1	,	1
	{"and", 	3,	{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 	6, 		6, 		"and  r1 & r2 -> r3",	1, 0},
//						1	|	2	|	4	,	1	|	4	|	2	,	1
	{"or", 		3,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	7, 		6, 		"or   r1 | r2 -> r3",	1, 0},
//						1	|	4	|	2	,	1	|	4	|	2	,	1
	{"xor", 	3,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	8, 		6, 		"xor  r1 ^ r2 -> r3",	1, 0},
//						1	|	4	|	2	,	1	|	4	|	2	,	1
	{"zjmp", 	1,	{T_DIR}, 												9, 		20, 	"jump if zero", 		0, 1},
//						2
	{"ldi", 	3,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 			10, 	25,	 	"load index", 			1, 1},
//						1	|	2	|	4	,	2	|	1	,	1
	{"sti", 	3,	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 			11, 	25,	 	"store index", 			1, 1},
//						1	,	1	|	2	|	4	,	2	|	1
	{"fork", 	1,	{T_DIR}, 												12, 	800, 	"fork", 				0, 1},
//						2
	{"lld", 	2,	{T_DIR | T_IND, T_REG}, 								13, 	10, 	"long load", 			1, 0},
//						2	|	4	,	1
	{"lldi", 	3,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 			14, 	50,	 	"long load index", 		1, 1},
//						1	|	2	|	4	,	2	|	1	,	1
	{"lfork", 	1,	{T_DIR}, 												15, 	1000,	"long fork", 			0, 1},
//						2
	{"aff", 	1,	{T_REG}, 												16, 	2, 		"ascii to stdout",		1, 0},
//						1
	{0, 		0,	{0}, 													0, 		0, 		0,						0, 0}
};

/*
**{1, 1} is only for index commands, always 3 args;
**{1, 0} are simple codes, load store math and aff, 2 or 3 args;
**{0, 1} is forks and jump, only takes 1 direct arg;
**{0, 0} is live only, 1 direct arg but 4 bytes after op code;
**
**if first num == 0, whole command will be 3 bytes. 1 byte opcode, no ACB byte, 2 byte direct.
**if second num == 1, last arg will be 1 byte REG, except sti where IND or REG is interpreted as 2 byte IND.
*/
uint8_t	asm_label(char *nlab)
{
	static s_label	labels;
}

t_byte	get_bytes(char **coms, char **args)
{
	t_byte		byte;
	int			i;
	int			n;

	n = 0;
	if (ft_strrchr(coms[n], LABEL_CHAR))
		byte.lcode = asm_label(coms[n++]);
	i = 0;
	while (op_tab[i])
		if (!(ft_strcmp(op_tab[i].name, coms[n])))
			break ;
	byte.code	
	return (byte);
}

t_byte	asm_parse(char *s)
{
	char	**coms;
	char	**args;
	int		i;

	word = ft_strsplit(line, '\t');
	i = -1;
	while (coms[++i])
		ft_printf("W:%d : %s\n", i, coms[i]);
	if (--i)
	{
		args = ft_strsplit(coms[--i], ',');
		i = -1;
		while (args[++i])
			ft_printf("\tP:%d : %s\n", i, args[i]);
	}
	return (get_bytes(coms, args));
}

void	bytecode(int fdc, int fds)
{
	char	*line;
	t_byte	bytes;
	char	*comment;

	(void)fdc;
	while((get_next_line(fds, &line)))
	{
		ft_printf("line: %s\n", line);
		if (line[0])
		{
			if ((comment = ft_strrchr(line, COMMENT_CHAR)))
				comment = 0;
			if (line[0])
			{
				bytes = asm_parse(line);
				write(fdc, &bytes.code, bytes.count);
			}
		}
		free(line);
	}
	ft_printf("EOF\n");
}
