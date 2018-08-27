/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/08/26 23:34:47 by smonroe          ###   ########.fr       */
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
{1, 1} is only for index codes, always 3 args;
{1, 0} are simple codes, load store math and aff, 2 or 3 args;
{0, 1} is forks and jump, only takes 1 direct arg;
{0, 0} is live only, 1 direct arg but 4 bytes after op code;

if first num == 0, whole command will be 3 bytes. 1 byte opcode, no ACB byte, 2 byte direct.
if second num == 1, last arg will be 1 byte REG, except sti where IND or REG is interpreted as 2 byte IND.
*/

void	bytecode(int fdc, int fds)
{
	char	*line;
	char	*com;
	char	**word;
	char	**param;
	int		i;

	(void)fdc;
	get_next_line(fds, &line);
	if ((com = ft_strchr(line, COMMENT_CHAR)))
		com = 0;
	word = ft_strsplit(line, ' ');
	i = 0;
	while (word[i])
		i++;
	param = ft_strsplit(word[--i], ',');
	i = -1;
	while (word[++i])
	{
		ft_printf("W:%d : %s\n", i, word[i]);
		free(word[i]);
	}
	i = -1;
	while (param[++i])
	{
		ft_printf("P:%d : %s\n", i, param[i]);
		free(param[i]);
	}
	free(word);
	free(param);
	free(line);
}