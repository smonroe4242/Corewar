/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 21:44:39 by jochang           #+#    #+#             */
/*   Updated: 2018/09/23 21:44:41 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

static t_flag init_flags(void)
{
	t_flag	flags;

	flags.p = 0;
	flags.n = 0;
	flags.d = 0;
	flags.w = 0;
	flags.fd = 0;
	return (flags);
}

static t_flag	set_flags(char c, t_flag flags)
{
	flags.p = (c == 'p' ? 1 : flags.p);
	flags.n = (c == 'n' ? 1 : flags.n);
	flags.d = (c == 'd' ? 1 : flags.d);
	flags.w = (c == 'w' && !flags.w ? ft_atoi(g_optarg) : flags.w);
	return (flags);
}

t_flag	ft_setopt(int ac, char **av)
{
	t_flag	flags;
	int8_t	opt;

	flags = init_flags();
	g_optind = 1;
	while ((opt = ft_getopt(ac, av, "pndw:")) != -1)
	{
		err_invflag(opt);
		flags = set_flags(opt, flags);
	}
	//flags.fd = (flags.p) ? open(OUT, O_CREAT | O_TRUNC | O_WRONLY) : 1;
	//if (flags.fd == -1)
	//	exit(1);
	flags.d = (flags.d) ? 1000000/flags.d : 0;
	return (flags);
}
