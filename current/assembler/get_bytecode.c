/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bytecode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 23:50:27 by jochang           #+#    #+#             */
/*   Updated: 2018/09/09 23:50:30 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

//disgusting lol
static uint8_t	acb_byte(int i, char **args, int lc)
{
	int	a;
	uint8_t byte;

	byte = 0;
	a = 0;
	while (a < g_op_tab[i].argc)
	{
		if (ft_strchr("-0123456789:", args[a][0]))
		{
			if (g_op_tab[i].types[a] & T_IND)
				byte |= (IND_CODE << (6 - (a++ << 1)));
			else
				err_invarg(args[a], lc);
		}
		else if (args[a][0] == 'r')
		{			
			if (g_op_tab[i].types[a] & T_REG)
				byte |= (REG_CODE << (6 - (a++ << 1)));
			else
				err_invarg(args[a], lc);
		}
		else if (args[a][0] == '%')
		{
			if (g_op_tab[i].types[a] & T_DIR)
				byte |= (DIR_CODE << (6 - (a++ << 1)));
			else
				err_invarg(args[a], lc);
		}
		else
			err_invarg(args[a], lc);
	}
	if (args[a])
		err_invarg(args[a], lc);
	return (byte);
}

static t_byte	arg_bytes(int i, char **args, int lc, uint8_t acb)
{
	t_byte		prm;
	int			a;
	int			n;

	n = 0;
	prm = t_byte_init();
	if (g_op_tab[i].acb == 0)
		return (arg_no_acb(i, args[0], lc, prm));
	a = -1;
	while (args[++a])
	{
		if (a > g_op_tab[i].argc)
			err_invarg(args[a], lc);
		if (ft_strchr(args[a], ':'))
			prm = arg_label(prm, args[a], n, lc);
		else if ((acb >> (6 - (a << 1)) & 0x3) == REG_CODE)
			prm = arg_reg(prm, args[a], lc);
		else if ((acb >> (6 - (a << 1)) & 0x3) == DIR_CODE && g_op_tab[i].flag2 == 1)
			prm = arg_ind(prm, &args[a][1], lc);
		else if ((acb >> (6 - (a << 1)) & 0x3) == DIR_CODE && g_op_tab[i].flag2 == 0)
			prm = arg_dir(prm, args[a], lc);
		else if ((acb >> (6 - (a << 1)) & 0x3) == IND_CODE)
			prm = arg_ind(prm, args[a], lc);
	}
	return (prm);
}

static void		free_line(char **coms, char **args)
{
	int i;

	if (coms)
	{
		i = -1;
		while (coms[++i])
			free(coms[i]);
		free(coms);
	}
	if (args)
	{
		i = -1;
		while (args[++i])
			free(args[i]);
		free(args);
	}
}

static t_byte	get_bytes(char **coms, char **args, int lc)
{
	t_byte		byte;
	t_byte		prm;
	int			i;
	int			n;

	n = 0;
	byte = t_byte_init();
	if (ft_strrchr(coms[n], LABEL_CHAR))
	{
		byte.label = ft_strndup(coms[n], ft_strlen(coms[n]) - 1);
		n++;
	}
	i = -1;
	while (g_op_tab[++i].name)
		if (!(ft_strcmp(g_op_tab[i].name, coms[n])))
			break ;
	if (!g_op_tab[i].name)
		err_invop(coms[n], lc);
	byte.code = (uint8_t *)realloc(byte.code, 2);
	byte.code[byte.count++] = (uint8_t)(g_op_tab[i].code & 0xff);
	if (g_op_tab[i].acb)
		byte.code[byte.count++] = acb_byte(i, args, lc);
	prm = arg_bytes(i, args, lc, byte.code[byte.count - 1]);
	byte = t_byte_append(byte, prm); 
	byte = label_append(byte, prm);
	t_byte_free(&prm);
	free_line(coms, args);
	return (byte);
}

static t_byte	asm_parse(char *line, int lc)
{
	t_byte			null;
	char			**coms;
	char			**args;
	int				i;
	char			*cmt;

	args = NULL;
	null = t_byte_init();
	if (!line[0])
		return (null);
	//ft_putendl(line);
	cmt = ft_strchr(line, COMMENT_CHAR);
	if (cmt)
		*cmt = 0;
	cmt = ft_strtrim(line);
//	free(cmt);
	if (!cmt[0])
		return (null);
	//ft_putendl(cmt);
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

t_byte			get_bytecode(int fds)
{
	char		*line;
	t_label		*l;
 	t_byte		b;
	t_byte		f;
	static int	lc;

	f = t_byte_init();
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
				l = label_add(b, f, l);
			t_byte_free(&b);
		}
		free(line);
	}
	f.code = label_fill(f, l);
	return (f);
}