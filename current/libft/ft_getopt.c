/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 10:02:36 by smonroe           #+#    #+#             */
/*   Updated: 2019/01/02 10:03:09 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_getopt(int ac, char **av, char *flg)
{
	static int	nxt;
	int			i;

	g_optind += (&g_optarg == &av[g_optind] ? 1 : 0);
	g_optarg = NULL;
	if (g_optind >= ac || av[g_optind][0] != '-')
		return (-1);
	i = -1;
	nxt++;
	while (++i < (int)ft_strlen(flg))
	{
		if (av[g_optind][nxt] == flg[i])
		{
			if (flg[i + 1] == ':')
				g_optarg = av[g_optind][nxt + 1] ? &av[g_optind][nxt + 1]
						: &av[g_optind + 1][0];
			if (!(av[g_optind][nxt + 1]))
				(g_optind++) ? (nxt = 0) : 0;
			g_optind += (g_optarg) ? 1 : 0;
			return (flg[i]);
		}
	}
	g_optopt = av[g_optind][nxt];
	return ('?');
}
