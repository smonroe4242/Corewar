/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/09/04 23:32:10 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_op    op_tab[17] =
{
/*
**	text		#args		arg types									op code		#cycles			real name		see note;
*/
	{"live", 	1,	{T_DIR}, 												1, 		10, 	"alive", 				0, 0},//5
	{"ld", 		2,	{T_DIR | T_IND, T_REG}, 								2, 		5, 		"load", 				1, 0},//5
	{"st", 		2,	{T_REG, T_IND | T_REG}, 								3, 		5, 		"store", 				1, 0},//5
	{"add", 	3,	{T_REG, T_REG, T_REG}, 									4, 		10, 	"addition", 			1, 0},//5
	{"sub", 	3,	{T_REG, T_REG, T_REG}, 									5, 		10, 	"subtraction",			1, 0},//5
	{"and", 	3,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	6, 		6, 		"and  r1 & r2 -> r3",	1, 0},//5
	{"or", 		3,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	7, 		6, 		"or   r1 | r2 -> r3",	1, 0},//5
	{"xor", 	3,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 	8, 		6, 		"xor  r1 ^ r2 -> r3",	1, 0},//5
	{"zjmp", 	1,	{T_DIR}, 												9, 		20, 	"jump if zero", 		0, 1},//3
	{"ldi", 	3,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 			10, 	25,	 	"load index", 			1, 1},//5
	{"sti", 	3,	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 			11, 	25,	 	"store index", 			1, 1},//5
	{"fork", 	1,	{T_DIR}, 												12, 	800, 	"fork", 				0, 1},//3
	{"lld", 	2,	{T_DIR | T_IND, T_REG}, 								13, 	10, 	"long load", 			1, 0},//
	{"lldi", 	3,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 			14, 	50,	 	"long load index", 		1, 1},//
	{"lfork", 	1,	{T_DIR}, 												15, 	1000,	"long fork", 			0, 1},//3
	{"aff", 	1,	{T_REG}, 												16, 	2, 		"ascii to stdout",		1, 0},//3
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

void		ft_print_mem(uint8_t *mem, int n)
{
	char	*chars;
	int		i;

	if (mem == NULL)
		return ;
	chars = "0123456789abcdef";
	i = -1;
	while (++i < n)
	{
		if(!(i % 16))
		{
			ft_putchar('\n');
			ft_printf("%.7x ", i + HEADER_SIZE);
		}
		ft_putchar(chars[mem[i] >> 4]);
		ft_putchar(chars[mem[i] & 0x0f]);
		ft_putchar(' ');

	}
	ft_putchar('\n');
}

void		t_byte_free(t_byte *x)
{
	int		i;

	i = -1;
	if (x->l)
	{
		while (x->l[++i].name)
			free(x->l[i].name);
		free(x->l);
	}
	if (x->code)
		free(x->code);
	if (x->label)
		free(x->label);
}

uint8_t	acb_byte(int i, char **args, int lc)
{
	int	a;
	uint8_t byte;

	byte = 0;
	a = 0;
	while (a < op_tab[i].argc)
	{
		if (ft_strchr("-0123456789:", args[a][0]))
		{
			if (op_tab[i].types[a] & T_IND)
				byte |= (IND_CODE << (6 - (a++ << 1)));
			else
				comp_error(1, args[a], lc);
		}
		else if (args[a][0] == 'r')
		{			
			if (op_tab[i].types[a] & T_REG)
				byte |= (REG_CODE << (6 - (a++ << 1)));
			else
				comp_error(1, args[a], lc);
		}
		else if (args[a][0] == '%')
		{
			if (op_tab[i].types[a] & T_DIR)
				byte |= (DIR_CODE << (6 - (a++ << 1)));
			else
				comp_error(1, args[a], lc);
		}
		else
			comp_error(1, args[a], lc);
	}
	if (args[a])
		comp_error(1, args[a], lc);
	return (byte);
}

t_byte	arg_label(t_byte prm, char *arg, int n, int lc)
{
	uint16_t	x;
	char		*lab;

	x = 0;
	if (!(lab = ft_strchr(arg, LABEL_CHAR)))
		comp_error(1, arg, lc);
	prm.code = (uint8_t *)realloc(prm.code, (prm.count + IND_SIZE));
	ft_memcpy(&prm.code[prm.count], &x, IND_SIZE);
	prm.l[n].name = ft_strdup(&lab[1]);
	prm.l[n++].loc = prm.count;
	prm.count += IND_SIZE;
	ft_printf("arg_label");
	ft_print_mem(prm.code, prm.count);
	return (prm);
}

t_byte	arg_reg(t_byte prm, char *arg, int lc)
{
	uint8_t	x;
	char	*r;

	if (!(r = ft_strchr(arg, 'r')))
		comp_error(1, arg, lc);
	prm.code = (uint8_t *)realloc(prm.code, (prm.count + T_REG));
	x = (int8_t)ft_atoi(&r[1]);
	ft_memcpy(&prm.code[prm.count], &x, T_REG);
	prm.count += T_REG;
	ft_printf("arg_reg");
	ft_print_mem(prm.code, prm.count);
	return (prm);
}

t_byte	arg_dir(t_byte prm, char *arg, int lc)
{
	uint32_t	x;
	char		*d;

	if (!(d = ft_strchr(arg, DIRECT_CHAR)))
		comp_error(1, arg, lc);
	prm.code = (uint8_t *)realloc(prm.code, (prm.count + DIR_SIZE));
	x = (int32_t)ft_atoi(&d[1]);
	x = END32(x);
	ft_memcpy(&prm.code[prm.count], &x, DIR_SIZE);
	prm.count += DIR_SIZE;
	ft_printf("arg_dir");
	ft_print_mem(prm.code, prm.count);
	return (prm);
}

t_byte arg_ind(t_byte prm, char *arg, int lc)
{
	uint16_t	x;
	char		*c;

	(void)lc;
	if (!(c = ft_strchr(arg, DIRECT_CHAR)))
		c = arg;
	else
		c += 1;
	prm.code = (uint8_t *)realloc(prm.code, (prm.count + IND_SIZE));
	x = (int16_t)ft_atoi(c);
	x = END16(x);
	ft_memcpy(&prm.code[prm.count], &x, IND_SIZE);
	prm.count += IND_SIZE;
	ft_printf("arg_ind");
	ft_print_mem(prm.code, prm.count);
	return (prm);
}

t_byte arg_no_acb(int i, char *arg, int lc, t_byte prm)
{
	(void)i;
	if (ft_strchr(arg, ':'))
		prm	= arg_label(prm, arg, 0, lc);
	else if (op_tab[i].code == 1)
		prm = arg_dir(prm, arg, lc);
	else
		prm = arg_ind(prm, arg, lc);
	return (prm);
}

t_byte	arg_bytes(int i, char **args, int lc, uint8_t acb)
{
	t_byte		prm;
	int			a;
	int			n;

	n = 0;
	prm = init_t_byte();
	if (op_tab[i].acb == 0)
		return (arg_no_acb(i, args[0], lc, prm));
	a = -1;
	while (args[++a])
	{
		if (a > op_tab[i].argc)
			comp_error(1, args[a], lc);
		if (ft_strchr(args[a], ':'))
			prm = arg_label(prm, args[a], n, lc);
		else if ((acb >> (6 - (a << 1)) & 0x3) == REG_CODE)
			prm = arg_reg(prm, args[a], lc);
		else if ((acb >> (6 - (a << 1)) & 0x3) == DIR_CODE && op_tab[i].flag2 == 1)
			prm = arg_ind(prm, &args[a][1], lc);
		else if ((acb >> (6 - (a << 1)) & 0x3) == DIR_CODE && op_tab[i].flag2 == 0)
			prm = arg_dir(prm, args[a], lc);
		else if ((acb >> (6 - (a << 1)) & 0x3) == IND_CODE)
			prm = arg_ind(prm, args[a], lc);
	}
	return (prm);
}

t_byte	get_bytes(char **coms, char **args, int lc)
{
	t_byte		byte;
	t_byte		prm;
	int			i;
	int			n;

	n = 0;
	byte = init_t_byte();
	if (ft_strrchr(coms[n], LABEL_CHAR))
	{
		byte.label = ft_strndup(coms[n], ft_strlen(coms[n]) - 1);
		n++;
	}
	i = -1;
	while (op_tab[++i].name)
		if (!(ft_strcmp(op_tab[i].name, coms[n])))
			break ;
	if (!op_tab[i].name)
		comp_error(0, coms[n], lc);
	byte.code = (uint8_t *)realloc(byte.code, 2);
	byte.code[byte.count++] = (uint8_t)(op_tab[i].code & 0xff);
	if (op_tab[i].acb)
		byte.code[byte.count++] = acb_byte(i, args, lc);
	prm = arg_bytes(i, args, lc, byte.code[byte.count - 1]);
	byte = t_byte_append(byte, prm);
	byte = label_append(byte, prm);
	t_byte_free(&prm);
	free_line(coms, args);
	return (byte);
}

t_byte	asm_parse(char *line, int lc)
{
	t_byte			null;
	char			**coms;
	char			**args;
	int				i;
	char			*cmt;

	args = NULL;
	null = init_t_byte();
	if (!line[0])
		return (null);
	ft_putendl(line);
	cmt = ft_strchr(line, COMMENT_CHAR);
	if (cmt)
		*cmt = 0;
	cmt = ft_strtrim(line);
//	free(cmt);
	if (!cmt[0])
		return (null);
	ft_putendl(cmt);
//	coms = ft_strsplit(cmt, '\t');
	coms = ft_strsplitwsp(cmt);
//	if (cmt)
//		free(cmt);
	i = 0;
	while (coms[i])
		i++;
	if (--i)
		args = ft_strsplit(coms[i], ',');
	t_byte_free(&null);
	null = get_bytes(coms, args, lc);
	free(cmt);
	return (null);
}

t_byte	bytecode(int fds)
{
	char	*line;
	t_label *l;
	t_byte	b;
	t_byte	f;
	static int	lc;

	f = init_t_byte();
	l = NULL;
	while((get_next_line(fds, &line)))
	{
		lc++;
		if (line[0])
		{
			b = asm_parse(line, lc);
			if (b.code)
				f = t_byte_append(f, b);
			if (b.code && b.l[0].name)
				f = label_append(f, b);
			if (b.label)
				l = add_lab(b, f, l);
			t_byte_free(&b);
		}
		free(line);
	}
	f.code = labelify(f, l);
	return (f);
}
