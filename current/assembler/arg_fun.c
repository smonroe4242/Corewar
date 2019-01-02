/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_fun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 21:41:42 by jochang           #+#    #+#             */
/*   Updated: 2018/09/12 21:41:53 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

t_byte	arg_no_acb(int i, char *arg, int lc, t_byte prm)
{
	(void)i;
	if (ft_strchr(arg, ':'))
		prm = arg_label(prm, arg, 0, lc);
	else if (g_op_tab[i].code == 1)
		prm = arg_dir(prm, arg, lc);
	else
		prm = arg_ind(prm, arg, lc);
	return (prm);
}

t_byte	arg_label(t_byte prm, char *arg, int n, int lc)
{
	uint16_t	x;
	char		*lab;

	x = 0;
	if (!(lab = ft_strchr(arg, LABEL_CHAR)))
		err_invarg(arg, lc);
	prm.code = (uint8_t *)realloc(prm.code, (prm.count + IND_SIZE));
	ft_memcpy(&prm.code[prm.count], &x, IND_SIZE);
	prm.l[n].name = ft_strdup(&lab[1]);
	prm.l[n++].loc = prm.count;
	prm.count += IND_SIZE;
	//ft_printf("arg_label");
	//ft_printmemory(prm.code, prm.count, 0, 0);
	return (prm);
}

t_byte	arg_reg(t_byte prm, char *arg, int lc)
{
	uint8_t	x;
	char	*r;

	if (!(r = ft_strchr(arg, 'r')))
		err_invarg(arg, lc);
	prm.code = (uint8_t *)realloc(prm.code, (prm.count + T_REG));
	x = (int8_t)ft_atoi(&r[1]);
	ft_memcpy(&prm.code[prm.count], &x, T_REG);
	prm.count += T_REG;
	//ft_printf("arg_reg");
	//ft_printmemory(prm.code, prm.count, 0, 0);
	return (prm);
}

t_byte	arg_dir(t_byte prm, char *arg, int lc)
{
	uint32_t	x;
	char		*d;

	if (!(d = ft_strchr(arg, DIRECT_CHAR)))
		err_invarg(arg, lc);
	prm.code = (uint8_t *)realloc(prm.code, (prm.count + DIR_SIZE));
	x = (int32_t)ft_atoi(&d[1]);
	x = END32(x);
	ft_memcpy(&prm.code[prm.count], &x, DIR_SIZE);
	prm.count += DIR_SIZE;
	//ft_printf("arg_dir");
	//ft_printmemory(prm.code, prm.count, 0, 0);
	return (prm);
}

t_byte	arg_ind(t_byte prm, char *arg, int lc)
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
	//ft_printf("arg_ind");
	//ft_printmemory(prm.code, prm.count, 0, 0);
	return (prm);
}
