/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/08/30 00:44:23 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_op    op_tab[17] =
{
/*
**	text		#args		arg types									op code		#cycles			real name		see note;
*/
	{"live", 	1,	{T_DIR}, 												1, 		10, 	"alive", 				0, 0},*
	{"ld", 		2,	{T_DIR | T_IND, T_REG}, 								2, 		5, 		"load", 				1, 0},
	{"st", 		2,	{T_REG, T_IND | T_REG}, 								3, 		5, 		"store", 				1, 0},
	{"add", 	3,	{T_REG, T_REG, T_REG}, 									4, 		10, 	"addition", 			1, 0},
	{"sub", 	3,	{T_REG, T_REG, T_REG}, 									5, 		10, 	"subtraction",			1, 0},
	{"and", 	3,	{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 	6, 		6, 		"and  r1 & r2 -> r3",	1, 0},
	{"or", 		3,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	7, 		6, 		"or   r1 | r2 -> r3",	1, 0},
	{"xor", 	3,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	8, 		6, 		"xor  r1 ^ r2 -> r3",	1, 0},
	{"zjmp", 	1,	{T_DIR}, 												9, 		20, 	"jump if zero", 		0, 1},*
	{"ldi", 	3,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 			10, 	25,	 	"load index", 			1, 1},
	{"sti", 	3,	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 			11, 	25,	 	"store index", 			1, 1},
	{"fork", 	1,	{T_DIR}, 												12, 	800, 	"fork", 				0, 1},*
	{"lld", 	2,	{T_DIR | T_IND, T_REG}, 								13, 	10, 	"long load", 			1, 0},
	{"lldi", 	3,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 			14, 	50,	 	"long load index", 		1, 1},
	{"lfork", 	1,	{T_DIR}, 												15, 	1000,	"long fork", 			0, 1},*
	{"aff", 	1,	{T_REG}, 												16, 	2, 		"ascii to stdout",		1, 0},
	{0, 		0,	{0}, 													0, 		0, 		0,						0, 0}
};
/*
** 'r'		 '%'	  'num' | ':'
** reg = 01; dir = 10; ind = 11;
** EDIT: FIRST NUM == 1 ? ACB : NO ACB;
**{1, 1} is only for index commands, always 3 args;
**{1, 0} are simple codes, load store math and aff, 2 or 3 args;
**{0, 1} is forks and jump, only takes 1 direct arg;
**{0, 0} is live only, 1 direct arg but 4 bytes after op code;
**
**if first num == 0, whole command will be 3 bytes. 1 byte opcode, no ACB byte, 2 byte direct.
**if second num == 1, last arg will be 1 byte REG, except sti where IND or REG is interpreted as 2 byte IND.
*/

uint8_t	acb_byte(int i, char **args, int lc)
{
	int	a;
	uint8_t byte;

	byte = 0;
	a = 0;
	while (args[a])
	{
		if (args[a][0] == 'r')
			if (op_tab[i].types[a] & T_REG)
				byte |= (REG_CODE << (6 - a++));
		if (args[a][0] == '%')
			if (op_tab[i].types[a] & T_DIR)
				byte |= (DIR_CODE << (6 - a++));
		if (ft_strchr("0123456789", args[a][0]))
			if (op_tab[i].types[a] & T_IND)
				byte |= (IND_CODE << (6 - a++));
		if (a > op_tab[i].argc)
			comp_error(1, arg[a], lc);
	}
	return (byte);
}

t_byte	arg_bytes(int i, char **args)
{
	t_byte	prm;
	int		a;


	return (prm);
}

t_byte	get_bytes(char **coms, char **args, int lc)
{
	t_byte		byte;
	t_byte		*prm;
	int			i;
	int			n;

	n = 0;
	if (ft_strrchr(coms[n], LABEL_CHAR))
		n++;
	i = -1;
	while (op_tab[++i].name)
		if (!(ft_strcmp(op_tab[i].name, coms[n])))
			break ;
	if (!op_tab[i].name)
		comp_error(0, coms[n], lc);
	byte.count = 0;
	byte.code = (uint8_t *)malloc(2);
	byte.code[byte.count++] = (uint8_t)(op_tab[i].code & 0xff);
	if (op_tab[i].acb)
		byte.code[byte.count++] = acb_byte(i, args, lc);
	prm = arg_bytes(i, args);
	byte.code = (uint8_t)realloc(byte.code, prm.count + byte.count);
	ft_memcpy(&byte.code[byte.count], &prm.code[0], prm.count);
	byte.count += prm.count;
	free(prm.code);
	return (byte);
}

t_byte	asm_parse(char *s, int lc)
{
	char			**coms;
	char			**args;
	int				i;
	char			*comment;

	args = NULL;
	if ((comment = ft_strrchr(line, COMMENT_CHAR)))
		comment = 0;
	line = ft_strtrim(line);
	if (!line[0])
		return ((t_byte)NULL);
	coms = ft_strsplit(s, '\t');
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
	return (get_bytes(coms, args, lc));
}

void	bytecode(int fdc, int fds)
{
	char	*line;
	t_byte	b;
	t_byte	f;
	static int	lc;

	f.code = (uint8_t *)malloc(0);
	f.count = 0;
	while((get_next_line(fds, &line)))
	{
		lc++;
		ft_printf("line: %s\n", line);
		if (line[0])
			if ((b = asm_parse(line, lc)) != (t_byte)NULL)
			{
				b = asm_parse(line, lc);
				f.code = (uint8_t *)realloc(f.code, f.count + b.count);
				ft_memcpy(&f.code[f.count], &b.code[0], b.count);
				f.count += bytes.count;
				free(b.code);
			}
		free(line);
	}
	ft_printf("EOF\n");
	write(fdc, &f.code, f.count);
	free(f.code);
}
