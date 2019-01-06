/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:31:51 by jochang           #+#    #+#             */
/*   Updated: 2019/01/05 18:18:21 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"
#include "../inc/gui.h"

static int		live_sum(uint32_t p[MAX_PLAYERS])
{
	uint32_t	total;
	uint32_t		i;

	total = 0;
	i = -1;
	while (++i < MAX_PLAYERS)
		total += p[i];
	return (total);
}

int		init_env(t_cyc info, t_head champ[MAX_PLAYERS], t_flag flag)
{
	int32_t		die;
	int32_t		step;
	uint32_t	total;
	uint32_t	kill;
	t_ncrs		ncrs;

	char c; // remove
	
	die = CYCLE_TO_DIE;
	kill = 0;
	cw_memcp(&info.mem[0][MEM_SIZE], &info.mem[0][0], REG_SIZE);
	//init visualizer here
	ncrs = init_gui(&info, champ, flag);
	scanf("%c", &c);
	while (die > 0)
	{
		//insert pause check here
		step = 0;
		if (!g_head)
			break ;
		while (step++ < die)
		{
			pc_scan_op(&info, g_head);
//			scanf("%c", &c);
//			if (flag.n)
//				display(&info, champ, flag); //display runs update gui
			//ft_printf("\e[35m%d\e[0m\n", info.cycle);
			info.cycle++;
		}
		total = live_sum(info.pcount);
		ft_memset(&info.pcount, 0, sizeof(info.pcount));
		pc_scan_rem(&g_head);
		if (!g_head)
			break ;
		if (total >= NBR_LIVE)
		{
			kill = 0;
			die -= CYCLE_DELTA;
		}
		else
			kill++;
		if (kill == MAX_CHECKS)
		{
			kill = 0;
			die -= CYCLE_DELTA;
		}
		update_memblock(ncrs, &info);
	}
	if (g_head)
		pc_free(g_head);
	if (flag.n)
		endwin();
	return (info.last);
}
