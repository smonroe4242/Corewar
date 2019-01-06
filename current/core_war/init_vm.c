/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:06:50 by jochang           #+#    #+#             */
/*   Updated: 2019/01/05 18:11:40 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

static t_cyc	init_t_cyc(t_mem **mem, int num_champs)
{
	t_cyc	info;

	info.cycle = 0;
	info.last = 0;
	info.num_champs = num_champs;
	ft_bzero(info.last_live, sizeof(info.last_live));
	ft_bzero(info.pcount, sizeof(info.pcount));
	info.mem = mem;
	return (info);
}

static void	init_proc(t_mem *mem, t_head champ[MAX_PLAYERS], t_flag flag)
{
	t_cyc	info;
	t_pc	*pc;
	int		i;
	int		winner;
	int		n;

	n = 0;
	while (n < MAX_PLAYERS && champ[n].pnum)
		n++;
	pc = pc_new(champ[0].pnum, 0, mem[0].byte);
	i = 0;
	while (++i < n)
		pc_app(&pc,
		pc_new(champ[i].pnum, MEM_SIZE / n * i, mem[MEM_SIZE / n * i].byte));
	info = init_t_cyc(&mem, n);
	g_head = pc;
	if (!(winner = init_env(info, champ, flag)))
		ft_printf("There has been a tie!\n", champ[0].pnum, champ[0].name);
	else
	{
		i = 0;
		while (champ[i].pnum != winner && i < MAX_PLAYERS)
			i++;
		ft_printf("Player %d (%s) won\n", champ[i].pnum, champ[i].name);
	}
}

void	init_vm(t_head champ[MAX_PLAYERS], t_flag flag)
{
	t_mem		*mem;
	int			i;
	int			n;

	mem = ft_memalloc(sizeof(*mem) * (MEM_SIZE + 4));
	n = 0;
	while (n < MAX_PLAYERS && champ[n].pnum)
	{
		ft_printf("Fighter #%d: %s (\"%s\"), at %d bytes long!\n",
		n + 1, champ[n].name, champ[n].comment, champ[n].size);
		n++;
	}
	i = -1;
	while (++i < n)
		cw_memw(&mem[MEM_SIZE / n * i], champ[i].code, champ[i].size, -champ[i].pnum);
	init_proc(mem, champ, flag);
}
