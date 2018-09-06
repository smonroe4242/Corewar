/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 00:22:39 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/06 09:42:03 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_env(uint8_t **mem, uint8_t **ref, t_head champ[MAX_PLAYERS], t_pc *pc)
{
	int		cycle;
	int		die;
	int		step;

	cycle = 0;
	die = CYCLE_TO_DIE;
	(void)mem;
	(void)ref;
//	pc->alive = 1;
//	pc->next->alive = 1;
//	pc->next->next->alive = 1;
	pc->next->next->next->alive = 1;
	while (die > 0)
	{
		step = 0;
		while (step++ < die)
		{
//			ft_dump_mem(*mem, *ref);
			ft_printf("%d:%d\n", step, cycle);
			cycle++;
		}
		pc_scan_rem(pc);
		if (!pc->alive)
			pc = pc_rem_head(pc);
		prove(pc);
		die -= CYCLE_DELTA;
	}
	die = 0;
	while (champ[die].pnum != champ[0].pnum)
		die++;
	ft_printf("Player %d (%s) won\n", champ[die].pnum, champ[die].name);
	pc_free(pc);
}

void	init_proc(uint8_t **mem, uint8_t **ref, t_head champ[MAX_PLAYERS], int n)
{
	t_pc	*pc;
	int		i;

	pc = pc_new(champ[0].pnum, 0);
	i = 0;
	while (++i < n)
		pc_app(pc, pc_new(champ[i].pnum, MEM_SIZE / n * i));
	ft_dump_mem(*mem, *ref);
	init_env(mem, ref, champ, pc);
}

void	init_vm(t_head champ[MAX_PLAYERS], int n)
{
	uint8_t		*mem;
	uint8_t		*ref;
	int			i;

	mem = ft_memalloc(MEM_SIZE);
	ref	= ft_memalloc(MEM_SIZE);
	i = -1;
	while (++i < n)
	{
		ft_memcpy(&mem[MEM_SIZE / n * i], champ[i].code, champ[i].size);
		ft_memset(&ref[MEM_SIZE / n * i], -champ[i].pnum, champ[i].size);
	}
	init_proc(&mem, &ref, champ, n);
	ft_memset(mem, 0, MEM_SIZE);
	free(mem);
	ft_memset(ref, 0, MEM_SIZE);
	free(ref);
}
