/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 20:58:00 by jochang           #+#    #+#             */
/*   Updated: 2019/01/01 20:40:42 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

int		main(int ac, char **av)
{
	t_head	file[MAX_PLAYERS];
	t_flag	flags;
	int		i;

	err_nofile("cw", ac);
	flags = ft_setopt(ac, av);
	if (g_optind >= ac)
		err_nofile("cw", 1);
	ft_bzero(&file, sizeof(t_head) * MAX_PLAYERS);
	i = 0;
	while (g_optind < ac && i < MAX_PLAYERS)
		file[i++] = parse_file(av[g_optind++]);
	init_vm(file, flags);
	return (0);
}
